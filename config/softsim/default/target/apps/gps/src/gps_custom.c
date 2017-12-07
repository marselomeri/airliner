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
#include "gps_events.h"
#include "gps_perfids.h"

#include <termios.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef enum {

/** \brief <tt> 'GPS - ' </tt>
**  \event <tt> 'GPS - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    GPS_DEVICE_ERR_EID = GPS_EVT_CNT,

/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    GPS_CUSTOM_EVT_CNT
} GPS_CustomEventIds_t;


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
int32 GPS_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < GPS_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(GPS_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


void GPS_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&GPS_AppCustomData, sizeof(GPS_AppCustomData));
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
    else
    {
        GPS_AppCustomData.Status = HMC5883_CUSTOM_INITIALIZED;
    }
    
    
end_of_function:
    return returnBool;
}


boolean HMC5883_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnCode = close(GPS_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        CFE_EVS_SendEvent(HMC5883_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "GPS Device close errno: %i", errno);
        returnBool = FALSE;
    }
    else
    {
        GPS_AppCustomData.Status = GPS_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


boolean GPS_Custom_Max_Events_Not_Reached(int32 ind)
{
    if ((ind < CFE_EVS_MAX_EVENT_FILTERS) && (ind > 0))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


int32 GPS_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == GPS_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = GPS_DEVICE_ERR_EID;
        EventTbl[customEventCount++].Mask    = CFE_EVS_FIRST_16_STOP;
    }
    else
    {
        customEventCount = -1;
        goto end_of_function;
    }
    
end_of_function:

    return customEventCount;
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

end_of_function:
    return Timestamp;
}


boolean GPS_Custom_Negotiate_Baud(uint32 *BaudRateSet)
{
    uint8 i = 0;
    uint32 baudRate = 0;
    boolean returnBool = TRUE;
    GPS_Payload_TX_CFG_PRT_t portConfig[2];
    const uint32 baudRates[] = {38400, 57600, 9600, 19200, 115200};
    
    if(0 == BaudRateSet)
    {
        CFE_EVS_SendEvent(GPS_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "GPS negotiate baud null pointer error");
        returnBool = FALSE;
        goto end_of_function;
    }
    
    for (i = 0; i < sizeof(baudRates); i++)
    {
        baudRate = baudRates[i];
        returnBool = GPS_Custom_Set_Baud(baudRate);
        if (FALSE == returnBool)
        {
            returnBool = FALSE;
            goto end_of_function;
        }
        /* flush input and wait for at least 20 ms silence */
        tcflush(GPS_AppCustomData.DeviceFd, TCIFLUSH);
        usleep(20 * 1000);
        /* Send a CFG-PRT message to set the UBX protocol for in and out
         * and leave the baudrate as it is, we just want an ACK-ACK for this */
        memset(portConfig, 0, 2 * sizeof(GPS_Payload_TX_CFG_PRT_t));
        
        portConfig[0].portID        = UBX_TX_CFG_PRT_PORTID;
        portConfig[0].mode          = UBX_TX_CFG_PRT_MODE;
        portConfig[0].baudRate      = baudRate;
        portConfig[0].inProtoMask   = UBX_TX_CFG_PRT_INPROTOMASK_GPS;
        portConfig[0].outProtoMask  = UBX_TX_CFG_PRT_OUTPROTOMASK_GPS;
        portConfig[1].portID        = UBX_TX_CFG_PRT_PORTID_USB;
        portConfig[1].mode          = UBX_TX_CFG_PRT_MODE;
        portConfig[1].baudRate      = baudRate;
        portConfig[1].inProtoMask   = UBX_TX_CFG_PRT_INPROTOMASK_GPS;
        portConfig[1].outProtoMask  = UBX_TX_CFG_PRT_OUTPROTOMASK_GPS;
    }

end_of_function:
    return returnBool;

}


boolean GPS_Custom_Set_Baud(uint32 Baud)
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



int32 GPS_Custom_Receive(void)
{
    uint8 buf[GPS_READ_BUFFER_SIZE];
    int32 returnCode = 0;
    
    
    return returnCode;
}


int32 GPS_Custom_Read(uint8 *Buffer, size_t Length)
{
    int32 bytesRead = 0;
    bytesRead = read(GPS_AppCustomData.DeviceFd, Buffer, Length);
    return bytesRead;
}


int32 GPS_Custom_Select(uint32 TimeoutSec, uint32 TimeoutUSec)
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
