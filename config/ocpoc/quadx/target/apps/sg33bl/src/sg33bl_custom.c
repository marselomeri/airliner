/****************************************************************************
*
*   Copyright (c) 2019 Windhover Labs, L.L.C. All rights reserved.
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
#include "sg33bl_events.h"
#include "sg33bl_perfids.h"
#include "sg33bl_platform_cfg.h"
#include "sg33bl_map.h"
#include "sg33bl_custom.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef enum {

/** \brief <tt> 'SG33BL - ' </tt>
**  \event <tt> 'SG33BL - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    SG33BL_DEVICE_ERR_EID = SG33BL_EVT_CNT,

/** \brief <tt> 'SG33BL - ' </tt>
**  \event <tt> 'SG33BL - ' </tt>
**  
**  \par Type: Info
**
**  \par Cause:
**
**  This event message is issued when a device successfully complete a
**  self test.
**
*/
    SG33BL_DEVICE_INF_EID,
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    SG33BL_CUSTOM_EVT_CNT
} SG33BL_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
SG33BL_AppCustomData_t SG33BL_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/
boolean SG33BL_Custom_Set_Baud(const uint32 Baud);
boolean SG33BL_Custom_Max_Events_Not_Reached(int32 ind);
uint8 SG33BL_Compute_Checksum(SG33BL_Packet_t *Packet);
boolean SG33BL_Valid_Checksum(SG33BL_Packet_t *Packet);

/************************************************************************
** Function Definitions
*************************************************************************/

void SG33BL_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&SG33BL_AppCustomData, sizeof(SG33BL_AppCustomData));
    SG33BL_AppCustomData.Baud = SG33BL_SERIAL_IO_SPEED;
}


boolean SG33BL_Custom_Init()
{
    boolean returnBool = TRUE;
    uint16 productNum = 0;
    uint16 productVer = 0;
    uint16 firmwareVer = 0;
    uint16 serialSub = 0;
    uint16 serialMain = 0;
    uint16 speed = 0;
    uint16 value = 0;
    
    SG33BL_AppCustomData.DeviceFd = open(SG33BL_SERIAL_DEVICE_PATH, O_RDWR | O_NOCTTY);
    if (SG33BL_AppCustomData.DeviceFd < 0) 
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Set default baud rate. */
    returnBool = SG33BL_Custom_Set_Baud(SG33BL_BAUD_DEFAULT);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL SG33BL_Custom_Set_Baud failed");
        returnBool = FALSE;
        goto end_of_function;
    }

    tcflush(SG33BL_AppCustomData.DeviceFd, TCIFLUSH);

    /* Get device info at default baud rate. */
    returnBool = SG33BL_Custom_Read(SG33BL_REG_PRODUCT_NO, &productNum);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL get product number failed");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = SG33BL_Custom_Read(SG33BL_REG_PRODUCT_VERSION, &productVer);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL get product version failed");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = SG33BL_Custom_Read(SG33BL_REG_FIRMWARE_VERSION, &firmwareVer);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL get firmware version failed");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = SG33BL_Custom_Read(SG33BL_REG_SERIAL_NO_SUB, &serialSub);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL get sub serial number failed");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = SG33BL_Custom_Read(SG33BL_REG_SERIAL_NO_MAIN, &serialMain);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL get main serial number failed");
        returnBool = FALSE;
        goto end_of_function;
    }

    CFE_EVS_SendEvent(SG33BL_DEVICE_INF_EID, CFE_EVS_INFORMATION,
            "SG33BL product number/version %x/%x firmware %x", 
            productNum, productVer, firmwareVer);
            
    CFE_EVS_SendEvent(SG33BL_DEVICE_INF_EID, CFE_EVS_INFORMATION,
            "SG33BL serial sub/main %x/%x", serialSub, serialMain);

    /* Set the baud rate of the device to the configured rate. */
    //switch (SG33BL_AppCustomData.Baud) 
    //{
        //case 9600:
        //{
            //speed = SG33BL_SET_B9600;
            //break;
        //}
        //case 14400:
        //{
            //speed = SG33BL_SET_B14400;
            //break;
        //}
        //case 19200:
        //{
            //speed = SG33BL_SET_B19200;
            //break;
        //}
        //case 38400:
        //{
            //speed = SG33BL_SET_B38400;
            //break;
        //}
        //case 57600:
        //{
            //speed = SG33BL_SET_B57600;
            //break;
        //}
        //case 115200:
        //{
            //speed = SG33BL_SET_B115200;
            //break;
        //}
        //case 229800:
        //{
            //speed = SG33BL_SET_B229800;
            //break;
        //}
        //default:
        //{
            //CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
                //"SG33BL set baudrate unknown rate error %u", 
                //SG33BL_AppCustomData.Baud);
            //returnBool = FALSE;
            //goto end_of_function;
        //}
    //}

    //returnBool =  SG33BL_Custom_Write(SG33BL_REG_BAUD_RATE, speed);
    //if (FALSE == returnBool)
    //{
        //CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            //"SG33BL set baud rate failed");
        //returnBool = FALSE;
        //goto end_of_function;
    //}

    ///* Power reset. */
    //returnBool =  SG33BL_Custom_Write(SG33BL_REG_POWER_CONFIG, SG33BL_BITS_RESET);
    //if (FALSE == returnBool)
    //{
        //CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            //"SG33BL power reset failed");
        //returnBool = FALSE;
        //goto end_of_function;
    //}

    //usleep(SG33BL_STARTUP_TIME);

    ///* Set baud to the configured rate. */
    //returnBool = SG33BL_Custom_Set_Baud(SG33BL_AppCustomData.Baud);
    //if (FALSE == returnBool)
    //{
        //CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            //"SG33BL SG33BL_Custom_Set_Baud failed");
        //returnBool = FALSE;
        //goto end_of_function;
    //}

    //tcflush(SG33BL_AppCustomData.DeviceFd, TCIFLUSH);

    ///* Check the new configuration. */
    //returnBool =  SG33BL_Custom_Read(SG33BL_REG_BAUD_RATE, &value);
    //if (FALSE == returnBool)
    //{
        //CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            //"SG33BL get baud rate failed");
        //returnBool = FALSE;
        //goto end_of_function;
    //}

    //if (speed & value)
    //{
        //CFE_EVS_SendEvent(SG33BL_DEVICE_INF_EID, CFE_EVS_DEBUG,
            //"SG33BL baud rate set %d", SG33BL_AppCustomData.Baud);
    //}
    //else
    //{
        //CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            //"SG33BL baud rate incorrect %hu", value);
        //returnBool = FALSE;
        //goto end_of_function;
    //}

    SG33BL_AppCustomData.Status = SG33BL_CUSTOM_INITIALIZED;

end_of_function:
    return returnBool;
}


boolean SG33BL_Custom_Deinit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnCode = close(SG33BL_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        returnBool = FALSE;
    }
    else
    {
        SG33BL_AppCustomData.Status = SG33BL_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


boolean SG33BL_Custom_Max_Events_Not_Reached(int32 ind)
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


int32 SG33BL_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == SG33BL_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = SG33BL_DEVICE_ERR_EID;
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


boolean SG33BL_Custom_Write(uint8 Addr, uint16 Value)
{
    SG33BL_Packet_t packet = {0};
    boolean returnBool = TRUE;
    int bytesWritten = 0;

    packet.frame_start.header = SG33BL_HEADER_WRITE;
    packet.frame_start.id = SG33BL_HEADER_ID_NONE;
    packet.frame_start.addr = Addr;
    packet.frame_start.length = 2;
    packet.data = Value;
    
    packet.checksum = SG33BL_Compute_Checksum(&packet);

    /* Send message */
    bytesWritten = write(SG33BL_AppCustomData.DeviceFd, (void *)&packet, 
            sizeof(packet));
    if (bytesWritten != sizeof(packet)) 
    {
        returnBool = FALSE;
    }

end_of_function:
    return returnBool;
}


boolean SG33BL_Custom_Read(uint8 Addr, uint16 *Value)
{
    SG33BL_Packet_t inPacket = {0};
    SG33BL_Normal_Read_t outPacket = {0};
    uint8   *BytePtr  = (uint8 *)&inPacket;
    boolean returnBool = TRUE;
    int bytes, i = 0;
    uint8 startIndex = 0;
    char buffer[32] = {0};

    outPacket.frame_start.header = SG33BL_HEADER_WRITE;
    outPacket.frame_start.id = SG33BL_HEADER_ID_NONE;
    outPacket.frame_start.addr = Addr;
    outPacket.frame_start.length = 0;

    outPacket.checksum = (Addr % 0x100);

    bytes = write(SG33BL_AppCustomData.DeviceFd, (void *)&outPacket, 
            sizeof(outPacket));
    if (bytes != sizeof(outPacket)) 
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    tcflush(SG33BL_AppCustomData.DeviceFd, TCIOFLUSH);

    /* Read one byte at a time. */
    for(i = 0; i < sizeof(buffer); ++i)
    {
        bytes = read(SG33BL_AppCustomData.DeviceFd, (void *)&buffer[i], 1);
        if (bytes <= 0)
        {
            CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "SG33BL read returned %d", bytes);
            returnBool = FALSE;
            goto end_of_function;
        }

        if(buffer[i] == 0x69)
        {
            startIndex = i;
        }

        if(i >= sizeof(inPacket) - 1 + startIndex)
        {
            break;
        }
    }

    if(i < sizeof(inPacket) - 1)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL read returned only %d bytes", bytes);
        returnBool = FALSE;
        goto end_of_function;
    }

    memcpy(&inPacket, &buffer[startIndex], sizeof(inPacket));

    returnBool = SG33BL_Valid_Checksum(&inPacket);
    if(TRUE == returnBool)
    {
        *Value = inPacket.data;
    }
    else
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL read failed checksum validation");
    }

end_of_function:
    return returnBool;
}


uint8 SG33BL_Compute_Checksum(SG33BL_Packet_t *PktPtr)
{
   uint16   PktLen   = sizeof(SG33BL_Packet_t) - 2;
   uint8   *BytePtr  = (uint8 *)PktPtr;
   uint8    CheckSum = 0;

   ++BytePtr;

   while (PktLen--)  CheckSum += *(BytePtr++);

   return CheckSum % 0x100;
}


boolean SG33BL_Valid_Checksum(SG33BL_Packet_t *PktPtr)
{
    if(SG33BL_Compute_Checksum(PktPtr) == PktPtr->checksum)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


boolean SG33BL_Custom_Set_Baud(const uint32 Baud)
{
    int speed = 0;
    int termios_state = 0;
    boolean returnBool = TRUE;
    struct termios uart_config;
    int returnVal = 0;

    switch (Baud) 
    {
        case 9600:
        {
            speed = B9600;
            break;
        }
        case 19200:
        {
            speed = B19200;
            break;
        }
        case 38400:
        {
            speed = B38400;
            break;
        }
        case 57600:
        {
            speed = B57600;
            break;
        }
        case 115200:
        {
            speed = B115200;
            break;
        }
        case 230400:
        {
            speed = B230400;
            break;
        }
        default:
        {
            CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "SG33BL set baudrate unknown rate error");
            returnBool = FALSE;
            goto end_of_function;
        }
    }
    
    /* fill the struct for the new configuration */
    returnVal = tcgetattr(SG33BL_AppCustomData.DeviceFd, &uart_config);
    if(returnVal < 0)
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "SG33BL failed to get terminal settings");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* properly configure the terminal 
     * (see also https://en.wikibooks.org/wiki/Serial_Programming/termios ) 
     */

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

    /* Set baud rate. */
    termios_state = cfsetispeed(&uart_config, speed);
    if (termios_state < 0) 
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL set input baud rate failed errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }
    termios_state = cfsetospeed(&uart_config, speed);
    if (termios_state < 0) 
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL set output baud rate failed errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }
    /* set the parameters */
    termios_state = tcsetattr(SG33BL_AppCustomData.DeviceFd, TCSANOW, &uart_config);
    if (termios_state < 0) 
    {
        CFE_EVS_SendEvent(SG33BL_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "SG33BL set terminal parameters failed errno: %i", errno);
        returnBool = FALSE;
    }

end_of_function:

    return returnBool;
}

