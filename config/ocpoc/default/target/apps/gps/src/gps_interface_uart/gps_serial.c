/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "gps_serial.h"
#include "gps_perfids.h"
#include "../gps_parser_ubx/gps_ubx_msg.h"
#include "../gps_parser_ubx/gps_parser_ubx_common.h"

#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
GPS_AppCustomData_t GPS_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/


void GPS_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&GPS_AppCustomData, sizeof(GPS_AppCustomData));
    GPS_AppCustomData.Baud = GPS_SERIAL_IO_SPEED;
    GPS_Parser_Reset();
}


boolean GPS_Custom_Init()
{
    boolean returnBool = TRUE;

    GPS_AppCustomData.DeviceFd = open(GPS_SERIAL_DEVICE_PATH, O_RDWR | O_NOCTTY);
    if (GPS_AppCustomData.DeviceFd < 0) 
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }
    /* Negatiate and set the baud rate */
    returnBool = GPS_Custom_Negotiate_Baud(GPS_AppCustomData.Baud);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device negotiate baud error");
        returnBool = FALSE;
        goto end_of_function;
    }
    OS_printf("ABOUT TO CONFIGURE MESSAGE RATES\n");
    /* Configure all the message rates */
    returnBool = GPS_Custom_Configure();
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device set configuration error");
        returnBool = FALSE;
        goto end_of_function;
    }
    else
    {
        GPS_AppCustomData.Status = GPS_CUSTOM_INITIALIZED;
    }
    
end_of_function:
    return returnBool;
}


boolean GPS_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnCode = close(GPS_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device close errno: %i", errno);
        returnBool = FALSE;
    }
    else
    {
        GPS_AppCustomData.Status = GPS_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


CFE_TIME_SysTime_t GPS_Custom_Get_Time(void)
{
    struct timespec ts;
    int returnCode = 0;
    CFE_TIME_SysTime_t Timestamp = {0, 0};

    returnCode = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (-1 == returnCode)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS clock_gettime errno: %i", errno);
        goto end_of_function;
    }

    Timestamp.Seconds = (uint32) ts.tv_sec;
    Timestamp.Subseconds = (uint32) ts.tv_nsec; 

end_of_function:
    return Timestamp;
}


boolean GPS_Custom_Negotiate_Baud(const uint32 Baud)
{
    uint8 i = 0;
    uint32 baudRate = 0;
    boolean returnBool = TRUE;
    /* TODO use struct defined in gps_ubx_msg instead */
    GPS_Payload_TX_CFG_PRT_t portConfig[2];
    const uint32 baudRates[] = {9600, 38400, 19200, 57600, 115200, 230400};

    for (i = 0; i < sizeof(baudRates) / sizeof(baudRates[0]); i++)
    {
        baudRate = baudRates[i];
        returnBool = GPS_Custom_Set_Baud(baudRate);
        if (FALSE == returnBool)
        {
            returnBool = FALSE;
            goto end_of_function;
        }
        /* TODO verify this works as expected */
        /* flush input and wait for at least 20 ms silence */
        tcflush(GPS_AppCustomData.DeviceFd, TCIFLUSH);
        usleep(20 * 1000);
        tcflush(GPS_AppCustomData.DeviceFd, TCIFLUSH);

        /* Send a CFG-PRT message to set the UBX protocol for in and out
         * and leave the baudrate as it is, we just want an ACK-ACK for this */
        memset(portConfig, 0, 2 * sizeof(GPS_Payload_TX_CFG_PRT_t));
        portConfig[0].portID        = GPS_TX_CFG_PRT_PORTID;
        portConfig[0].mode          = GPS_TX_CFG_PRT_MODE;
        portConfig[0].baudRate      = baudRate;
        portConfig[0].inProtoMask   = GPS_TX_CFG_PRT_INPROTOMASK_GPS;
        portConfig[0].outProtoMask  = GPS_TX_CFG_PRT_OUTPROTOMASK_GPS;
        portConfig[1].portID        = GPS_TX_CFG_PRT_PORTID_USB;
        portConfig[1].mode          = GPS_TX_CFG_PRT_MODE;
        portConfig[1].baudRate      = baudRate;
        portConfig[1].inProtoMask   = GPS_TX_CFG_PRT_INPROTOMASK_GPS;
        portConfig[1].outProtoMask  = GPS_TX_CFG_PRT_OUTPROTOMASK_GPS;
        
        printf("portConfig[0].portID %hhu \n", portConfig[0].portID);
        printf("portConfig[0].reserved1 %hhu \n", portConfig[0].reserved1);
        printf("portConfig[0].txReady %hu \n", portConfig[0].txReady);
        printf("portConfig[0].mode %u \n", portConfig[0].mode);
        printf("portConfig[0].baudRate %u \n", portConfig[0].baudRate);
        printf("portConfig[0].inProtoMask %hu \n", portConfig[0].inProtoMask);
        printf("portConfig[0].outProtoMask %hu \n", portConfig[0].outProtoMask);
        printf("portConfig[0].flags %hu \n", portConfig[0].flags);
        printf("portConfig[0].reserved2 %hu \n", portConfig[0].reserved2);
        printf("portConfig[1].portID %hhu \n", portConfig[1].portID);
        printf("portConfig[1].reserved1 %hhu \n", portConfig[1].reserved1);
        printf("portConfig[1].txReady %hu \n", portConfig[1].txReady);
        printf("portConfig[1].mode %u \n", portConfig[1].mode);
        printf("portConfig[1].baudRate %u \n", portConfig[1].baudRate);
        printf("portConfig[1].inProtoMask %hu \n", portConfig[1].inProtoMask);
        printf("portConfig[1].outProtoMask %hu \n", portConfig[1].outProtoMask);
        printf("portConfig[1].flags %hu \n", portConfig[1].flags);
        printf("portConfig[1].reserved2 %hu \n", portConfig[1].reserved2);
        
        /* send config message */
        returnBool = GPS_Custom_SendMessage(GPS_MESSAGE_CFG_PRT, 
                (uint8 *)portConfig, 2 * sizeof(GPS_Payload_TX_CFG_PRT_t));

        if(FALSE == returnBool)
        {
            /* SendMessage failed try the next baud rate */
            continue;
        }

        /* If an ACK is received here we've matched baud rates */
        returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_PRT,
                GPS_ACK_TIMEOUT);
        if(FALSE == returnBool)
        {
            /* WaitForAck failed try the next baud rate */
            continue;
        }
        
        /* Send a CFG-PRT message again, this time change the baudrate */
        memset(portConfig, 0, 2 * sizeof(GPS_Payload_TX_CFG_PRT_t));
        portConfig[0].portID        = GPS_TX_CFG_PRT_PORTID;
        portConfig[0].mode          = GPS_TX_CFG_PRT_MODE;
        portConfig[0].baudRate      = Baud;
        portConfig[0].inProtoMask   = GPS_TX_CFG_PRT_INPROTOMASK_GPS;
        portConfig[0].outProtoMask  = GPS_TX_CFG_PRT_OUTPROTOMASK_GPS;
        portConfig[1].portID        = GPS_TX_CFG_PRT_PORTID_USB;
        portConfig[1].mode          = GPS_TX_CFG_PRT_MODE;
        portConfig[1].baudRate      = Baud;
        portConfig[1].inProtoMask   = GPS_TX_CFG_PRT_INPROTOMASK_GPS;
        portConfig[1].outProtoMask  = GPS_TX_CFG_PRT_OUTPROTOMASK_GPS;

        printf("portConfig[0].portID %hhu \n", portConfig[0].portID);
        printf("portConfig[0].reserved1 %hhu \n", portConfig[0].reserved1);
        printf("portConfig[0].txReady %hu \n", portConfig[0].txReady);
        printf("portConfig[0].mode %u \n", portConfig[0].mode);
        printf("portConfig[0].baudRate %u \n", portConfig[0].baudRate);
        printf("portConfig[0].inProtoMask %hu \n", portConfig[0].inProtoMask);
        printf("portConfig[0].outProtoMask %hu \n", portConfig[0].outProtoMask);
        printf("portConfig[0].flags %hu \n", portConfig[0].flags);
        printf("portConfig[0].reserved2 %hu \n", portConfig[0].reserved2);
        printf("portConfig[1].portID %hhu \n", portConfig[1].portID);
        printf("portConfig[1].reserved1 %hhu \n", portConfig[1].reserved1);
        printf("portConfig[1].txReady %hu \n", portConfig[1].txReady);
        printf("portConfig[1].mode %u \n", portConfig[1].mode);
        printf("portConfig[1].baudRate %u \n", portConfig[1].baudRate);
        printf("portConfig[1].inProtoMask %hu \n", portConfig[1].inProtoMask);
        printf("portConfig[1].outProtoMask %hu \n", portConfig[1].outProtoMask);
        printf("portConfig[1].flags %hu \n", portConfig[1].flags);
        printf("portConfig[1].reserved2 %hu \n", portConfig[1].reserved2);

        /* send config message */
        returnBool = GPS_Custom_SendMessage(GPS_MESSAGE_CFG_PRT, 
                (uint8 *)portConfig, 2 * sizeof(GPS_Payload_TX_CFG_PRT_t));
        if(FALSE == returnBool)
        {
            continue;
        }
        
        /* no ACK is expected here, but read the buffer anyway in case 
         * we actually get an ACK */
        returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_PRT,
                GPS_ACK_TIMEOUT);
        
        /* If the originally baud negotiated is not the baud just set... */
        if (Baud != baudRate)
        {
            /* Set the same baudrate we configured so both sides 
             * now match speeds */
            returnBool = GPS_Custom_Set_Baud(Baud);
            if (FALSE == returnBool)
            {
                returnBool = FALSE;
                goto end_of_function;
            }
        }
        /* at this point we have correct baudrate on both ends */
        break;
    }
    
    /* If connection or baudrate detection failed */
    if (i >= sizeof(baudRates) / sizeof(baudRates[0]))
    {
        returnBool = FALSE;
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS connection or baudrate detection failed");
    }

end_of_function:
    return returnBool;

}


boolean GPS_Custom_Set_Baud(const uint32 Baud)
{
    int speed = 0;
    int termios_state = 0;
    boolean returnBool = TRUE;
    struct termios uart_config;

    switch (Baud) 
    {
        case 9600:
            speed = B9600;
            break;

        case 19200:  
            speed = B19200;
            break;

        case 38400:  
            speed = B38400;
            break;

        case 57600:  
            speed = B57600;
            break;

        case 115200: 
            speed = B115200;
            break;

        case 230400: 
            speed = B230400;
            break;

        default:
            CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS set baudrate unknown rate error");
            returnBool = FALSE;
            goto end_of_function;
    }
    
    /* fill the struct for the new configuration */
    tcgetattr(GPS_AppCustomData.DeviceFd, &uart_config);

    /* properly configure the terminal (see also https://en.wikibooks.org/wiki/Serial_Programming/termios ) */

    /* Input flags - Turn off input processing
     * convert break to null byte, no CR to NL translation,
     * no NL to CR translation, don't mark parity errors or breaks
     * no input parity check, don't strip high bit off,
     * no XON/XOFF software flow control
     */
    uart_config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | 
            INPCK | ISTRIP | IXON);
    /* Output flags - Turn off output processing
     * no CR to NL translation, no NL to CR-NL translation,
     * no NL to CR translation, no column 0 CR suppression,
     * no Ctrl-D suppression, no fill characters, no case mapping,
     * no local output processing
     * 
     * config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
     *                   ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
     */
    uart_config.c_oflag = 0;
    
    /*
     * No line processing
     * echo off, echo newline off, canonical mode off,
     * extended input processing off, signal chars off
     */
    uart_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

    /* no parity, one stop bit */
    uart_config.c_cflag &= ~(CSTOPB | PARENB);
    
    
    /* set baud rate */
    termios_state = cfsetispeed(&uart_config, speed);
    if (termios_state < 0) 
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device set input baud rate failed errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }
    termios_state = cfsetospeed(&uart_config, speed);
    if (termios_state < 0) 
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device set output baud rate failed errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }

    /* set the parameters */
    termios_state = tcsetattr(GPS_AppCustomData.DeviceFd, TCSANOW, &uart_config);
    if (termios_state < 0) 
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device set terminal parameters failed errno: %i", errno);
        returnBool = FALSE;
    }

end_of_function:

    return returnBool;
}


int32 GPS_Custom_Receive(uint8 *Buffer, uint32 Length, uint32 Timeout)
{
    int32 returnCode = 0;
    int32 bytesRead = 0;

    /* Null check */
    if(0 == Buffer)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS receive null pointer");
        goto end_of_function;
    }
    /* Wait for GPS data */
    returnCode = GPS_Custom_Select(0, 1000 * Timeout);
    if (returnCode <= 0)
    {
        OS_printf("select timed out in custom received\n\n");
        /* Select timeout or error */
        goto end_of_function;
    }
    /* Select returned > 0, data is ready to be read, wait for more
     * data to be available before calling read */
    usleep(GPS_WAIT_BEFORE_READ * 1000);
    
    /* Read GPS data */
    bytesRead = read(GPS_AppCustomData.DeviceFd, Buffer, Length);
    OS_printf("bytesread = %d\n", bytesRead);
    if (bytesRead <= 0)
    {
        /* Read failed */
        goto end_of_function;
    }

end_of_function:

    return bytesRead;
}


int32 GPS_Custom_Select(const uint32 TimeoutSec, const uint32 TimeoutUSec)
{
    int32 returnCode = 0;
    uint32 maxFd = 0;
    uint32 retryAttempts = 0;
    fd_set fds;
    struct timeval timeValue;
    maxFd = 0;
    returnCode = 0;

    while(retryAttempts != GPS_MAX_RETRY_ATTEMPTS)
    {
        /* Set the timeout */
        timeValue.tv_sec = TimeoutSec;
        timeValue.tv_usec = TimeoutUSec;
    
        /* Initialize the set */
        FD_ZERO(&fds);
    
        FD_SET(GPS_AppCustomData.DeviceFd, &fds);
        
        /* Get the greatest fd value for select() */
        maxFd = GPS_AppCustomData.DeviceFd; 
    
        //CFE_ES_PerfLogEntry(GPS_DEVICE_GET_PERF_ID);
        /* Wait for RC data */
        returnCode = select(maxFd + 1, &fds, 0, 0, &timeValue);
        //CFE_ES_PerfLogExit(GPS_DEVICE_GET_PERF_ID);

        /* select() wasn't successful */
        if (-1 == returnCode)
        {
            /* select was interrupted, try again */
            if (EINTR == errno)
            {
                CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "GPS select was interrupted");
                usleep(GPS_MAX_RETRY_SLEEP_USEC);
                retryAttempts++;
                continue;
            }
            else
            {
                /* select returned an error other than EINTR */
                CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "GPS select() returned errno: %i", errno);
                break;
            }
        }
        /* select timed out */
        if (0 == returnCode)
        {
            CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "GPS select() timed out");
            break;
        } 
        /* select() returned and data is ready to be read */
        if(returnCode > 0)
        {
            break;
        }
    } /* end while loop*/

    return returnCode;
}


boolean GPS_Custom_SetChecksum(const uint8 *buffer, const uint16 length, GPS_Checksum_t *checksum)
{
    uint16 i = 0;
    boolean returnBool = TRUE;
    
    /* Null check */
    if(0 == checksum || 0 == buffer)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS set checksum null pointer");
        returnBool = FALSE;
        goto end_of_function;
    }
    
    for (i = 0; i < length; i++) 
    {
        checksum->ck_a = checksum->ck_a + buffer[i];
        checksum->ck_b = checksum->ck_b + checksum->ck_a;
    }

end_of_function:
    return returnBool;
}


boolean GPS_Custom_SendEmptyMessage(const uint16 msg)
{
    boolean returnBool = TRUE;
    int bytesWritten = 0;
    GPS_Header_t   header = { GPS_HEADER_SYNC1_VALUE, 
                              GPS_HEADER_SYNC2_VALUE, 
                              0, 
                              0 };

    GPS_Checksum_t checksum = { 0, 0 };

    /* Populate header */
    header.msg    = msg;
    header.length = 0;
    
    /* Calculate header checksum, skip two sync bytes */
    returnBool = GPS_Custom_SetChecksum((uint8 *)&header + 2, 
            sizeof(header) - 2, &checksum); 
    if (FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Send message */
    bytesWritten = write(GPS_AppCustomData.DeviceFd, (void *)&header, 
            sizeof(header));
    if (bytesWritten != sizeof(header)) 
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    bytesWritten = write(GPS_AppCustomData.DeviceFd, (void *)&checksum, 
            sizeof(checksum));

    if (bytesWritten != sizeof(checksum)) 
    {
        returnBool = FALSE;
    }

end_of_function:

    return returnBool;
}


boolean GPS_Custom_SendMessage(const uint16 msg, const uint8 *payload, const uint16 length)
{
    boolean returnBool = TRUE;
    int bytesWritten = 0;
    GPS_Header_t   header = { GPS_HEADER_SYNC1_VALUE, 
                              GPS_HEADER_SYNC2_VALUE, 
                              0, 
                              0 };

    GPS_Checksum_t checksum = { 0, 0 };

    /* Null check */
    if(0 == payload)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS send message null pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Populate header */
    header.msg    = msg;
    header.length = length;
    
    /* Calculate header checksum, skip two sync bytes */
    returnBool = GPS_Custom_SetChecksum((uint8 *)&header + 2, 
            sizeof(header) - 2, &checksum); 
    if (FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Calculate (add) payload checksum */
    returnBool = GPS_Custom_SetChecksum(payload, length, &checksum); 
    if (FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Send message */
    bytesWritten = write(GPS_AppCustomData.DeviceFd, (void *)&header, 
            sizeof(header));
    if (bytesWritten != sizeof(header)) 
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    bytesWritten = write(GPS_AppCustomData.DeviceFd, (void *)payload, 
            length);
    if (bytesWritten != length) 
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    bytesWritten = write(GPS_AppCustomData.DeviceFd, (void *)&checksum, 
            sizeof(checksum));

    if (bytesWritten != sizeof(checksum)) 
    {
        returnBool = FALSE;
    }

end_of_function:

    return returnBool;
}


uint64 GPS_Custom_Get_Time_Uint64(void)
{
    uint64 timeStamp = 0;
    CFE_TIME_SysTime_t cfeTimeStamp = {0, 0};
    
    cfeTimeStamp = GPS_Custom_Get_Time();

    if(cfeTimeStamp.Seconds == 0 && cfeTimeStamp.Subseconds == 0)
    {
        goto end_of_function;
    }
    timeStamp = cfeTimeStamp.Seconds * 1000000;
    timeStamp += cfeTimeStamp.Subseconds / 1000;

end_of_function:

    return timeStamp;
}


boolean GPS_Custom_WaitForAck(const uint16 msg, const uint32 timeout)
{
    uint32 i = 0;
    int32 bytesRead = 0;
    uint8 from_gps_data[GPS_READ_BUFFER_SIZE];
    boolean done = FALSE;
    boolean timedOut = FALSE;
    boolean returnBool = FALSE;
    uint64 timeStamp = 0;
    uint64 startTime = 0;

    /* Set the ack state to waiting */
    GPS_AppCustomData.AckState = GPS_ACK_WAITING;
    /* Set the message we're looking for */
    GPS_AppCustomData.AckWaitingMsg = msg;
    /* Set the received ack boolean to false */
    GPS_AppCustomData.AckWaitingRcvd = FALSE;

    /* Get the start time */
    startTime = GPS_Custom_Get_Time_Uint64();
    if(0 == startTime)
    {
        goto end_of_function;
    }

    /* while we haven't timed out keep looking for the message */
    while(FALSE == timedOut)
    {
        /* Get the loop iteration time */
        timeStamp = GPS_Custom_Get_Time_Uint64();
        if(0 == timeStamp)
        {
            goto end_of_function;
        }
        
        /* If we've timed out out set the flag to true */
        if(timeStamp >= startTime + timeout * 1000)
        {
            /* TODO remove after debug*/
            OS_printf("WaitForAck timed out\n");
            /* */
            timedOut = TRUE;
        }

        bytesRead = GPS_Custom_Receive(&from_gps_data[0], sizeof(from_gps_data), GPS_PACKET_TIMEOUT);
        /* REMOVE ME */
        for(i = 0; i < bytesRead; ++i)
        {
            OS_printf(" bytes = %hhx ", from_gps_data[i]);
        }
        OS_printf("\n");
        /* end todo*/
        for(i = 0; (FALSE == timedOut) && (i < bytesRead); ++i)
        {
            GPS_DeviceMessage_t message;
            GPS_ParserStatus_t status;

            if(GPS_ParseChar(from_gps_data[i], &message, &status, &done))
            {
                /* TODO remove after debug*/
                if(TRUE == done)
                {
                    OS_printf("ParseChar completed a message\n");
                }
                /* */
                
                if(GPS_AppCustomData.AckState == GPS_ACK_GOT_ACK &&
                   GPS_AppCustomData.AckWaitingRcvd == TRUE)
                {
                    /* TODO remove after debug*/
                    OS_printf("Got an ACK\n");
                    /* */
                    returnBool = TRUE;
                    goto end_of_function;
                }
                if(GPS_AppCustomData.AckState == GPS_ACK_GOT_NAK &&
                   GPS_AppCustomData.AckWaitingRcvd == TRUE)
                {
                    /* TODO remove after debug*/
                    OS_printf("Got an NAK\n");
                    /* */
                    returnBool = FALSE;
                    goto end_of_function;
                }
            }
        }
    }

end_of_function:

return returnBool;
}


boolean GPS_Custom_Configure(void)
{
    boolean returnBool = TRUE;

    /* TODO move this struct define to gps_ubx_msg */
    GPS_Payload_TX_CFG_Rate_t rateConfig;
    
    GPS_CFG_NAV5_t navConfig;
    GPS_CFG_SBAS_t sbasConfig;
    
    /* Setup rate configuration */
    memset(&rateConfig, 0, sizeof(GPS_Payload_TX_CFG_Rate_t));
    rateConfig.measRate = GPS_TX_CFG_RATE_MEASINTERVAL;
    rateConfig.navRate  = GPS_TX_CFG_RATE_NAVRATE;
    rateConfig.timeRef  = GPS_TX_CFG_RATE_TIMEREF;
    
    /* Setup NAV5 configuration */
    memset(&navConfig, 0, sizeof(GPS_CFG_NAV5_t));
    navConfig.mask      = GPS_TX_CFG_NAV5_MASK;
    navConfig.dynModel  = GPS_TX_CFG_NAV5_DYNMODEL;
    navConfig.fixMode   = GPS_TX_CFG_NAV5_FIXMODE;;

    /* Setup SBAS configuration */
    memset(&sbasConfig, 0, sizeof(GPS_CFG_SBAS_t));
    sbasConfig.mode     = GPS_TX_CFG_SBAS_MODE;
     
    /* Send a CFG-RATE message to define update rate */
    returnBool = GPS_Custom_SendMessage(GPS_MESSAGE_CFG_RATE, 
                (uint8 *)&rateConfig, sizeof(GPS_Payload_TX_CFG_Rate_t));
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_RATE, 
            GPS_ACK_TIMEOUT);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    /* send a NAV5 message to set the options for the internal filter */
    returnBool = GPS_Custom_SendMessage(GPS_MESSAGE_CFG_NAV5, 
                (uint8 *)&navConfig, sizeof(GPS_CFG_NAV5_t));
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_NAV5, 
            GPS_ACK_TIMEOUT);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    /* send a SBAS message to set the SBAS options */
    returnBool = GPS_Custom_SendMessage(GPS_MESSAGE_CFG_SBAS, 
                (uint8 *)&sbasConfig, sizeof(GPS_CFG_SBAS_t));
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_SBAS, 
            GPS_ACK_TIMEOUT);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    returnBool = GPS_Custom_SendMessageRate(GPS_MESSAGE_NAV_PVT, 1);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_MSG, 
            GPS_ACK_TIMEOUT);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    returnBool = GPS_Custom_SendMessageRate(GPS_MESSAGE_NAV_DOP, 1);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_MSG, 
            GPS_ACK_TIMEOUT);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    //returnBool = GPS_Custom_SendMessageRate(GPS_MESSAGE_NAV_SVINFO, 5);
    //if(FALSE == returnBool)
    //{
        //goto end_of_function;
    //}

    //returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_MSG, 
            //GPS_ACK_TIMEOUT);
    //if(FALSE == returnBool)
    //{
        //goto end_of_function;
    //}
    
    //returnBool = GPS_Custom_SendMessageRate(GPS_MESSAGE_MON_HW, 1);
    //if(FALSE == returnBool)
    //{
        //goto end_of_function;
    //}

    //returnBool = GPS_Custom_WaitForAck(GPS_MESSAGE_CFG_MSG, 
            //GPS_ACK_TIMEOUT);
    //if(FALSE == returnBool)
    //{
        //goto end_of_function;
    //}

end_of_function:

    return returnBool;
}


boolean GPS_Custom_SendMessageRate(const uint16 msg, const uint8 rate)
{
    GPS_Payload_TX_CFG_Rate_Msg_t rateMsgConfig;
    memset(&rateMsgConfig, 0, sizeof(rateMsgConfig));
    rateMsgConfig.msg = msg;
    rateMsgConfig.rate = rate;
    
    return GPS_Custom_SendMessage(GPS_MESSAGE_CFG_MSG, 
                (uint8 *)&rateMsgConfig, sizeof(rateMsgConfig));
    
}
