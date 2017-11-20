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
#include "rcin_sbus.h"
/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

typedef enum {

/** \brief <tt> 'RCIN - ' </tt>
**  \event <tt> 'RCIN - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    RCIN_DEVICE_ERR_EID = RCIN_EVT_CNT,

/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    RCIN_CUSTOM_EVT_CNT

} RCIN_CustomEventIds_t;

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
RCIN_AppCustomData_t RCIN_AppCustomData;
/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/
int32 RCIN_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < RCIN_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(RCIN_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}

int32 RCIN_Read(int fd, void *buf, size_t count)
{
    in32 returnSize = 0;
    uint32 i = 0;
    
    for (i=0; i < RCIN_MAX_RETRY_ATTEMPTS; i++)
    {
        returnSize = read(fd, buf, count);
        /* Interrupted */
        if (-1 == returnSize && EINTR == errno)
        {
            usleep(RCIN_MAX_RETRY_SLEEP_USEC);
        }
        /* No data available */
        else if (-1 == returnSize && EAGAIN == errno)
        {
            usleep(RCIN_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnSize;
}


void RCIN_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&RCIN_AppCustomData, sizeof(RCIN_AppCustomData));
    strncpy(RCIN_AppCustomData.DevName, RCIN_DEVICE_PATH, RCIN_MAX_DEVICE_PATH);
}


boolean RCIN_Custom_Init(void)
{
    boolean returnBool = TRUE;
    int32 returnCode = 0;
    
    /* Open */
    RCIN_AppCustomData.DeviceFd = open(RCIN_DEVICE_PATH, O_RDWR | O_NONBLOCK | O_CLOEXEC);
    if (RCIN_AppCustomData.DeviceFd < 0) 
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN custom device open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }
    else
    {
        RCIN_AppCustomData.Status = RCIN_CUSTOM_INITIALIZED;
    }
    
    /* Get configuration */
    returnCode = RCIN_Ioctl(RCIN_AppCustomData.DeviceFd, TCGETS2, 
            &RCIN_AppCustomData.TerminalConfig);
    if (0 != returnCode)
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN custom get terminal config failed errno: %i", errno);
        goto end_of_function;
    }
    
    /* Setting serial port, 8E2, non-blocking. 100Kbps */
    /* https://linux.die.net/man/3/termios */
    RCIN_AppCustomData.TerminalConfig.c_iflag &= ~(IGNBRK | BRKINT | 
            PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    RCIN_AppCustomData.TerminalConfig.c_oflag &= ~OPOST;
    RCIN_AppCustomData.TerminalConfig.c_lflag &= ~(ECHO | ECHONL | 
            ICANON | ISIG | IEXTEN);

    RCIN_AppCustomData.TerminalConfig.c_cflag &= ~(CSIZE | CRTSCTS | 
            PARODD | CBAUD);
    RCIN_AppCustomData.TerminalConfig.c_iflag |= (INPCK | IGNPAR);
    /* Use BOTHER to specify speed directly in c_[io]speed member */
    RCIN_AppCustomData.TerminalConfig.c_cflag |= (CS8 | CSTOPB | CLOCAL 
            | PARENB | BOTHER | CREAD);
    RCIN_AppCustomData.TerminalConfig.c_ispeed = RCIN_SERIAL_INPUT_SPEED;
    RCIN_AppCustomData.TerminalConfig.c_ospeed = RCIN_SERIAL_OUTPUT_SPEED;
    RCIN_AppCustomData.TerminalConfig.c_cc[VMIN] = RCIN_SERIAL_VMIN_SETTING;
    RCIN_AppCustomData.TerminalConfig.c_cc[VTIME] = RCIN_SERIAL_VTIME_SETTING;
    
    returnCode = RCIN_Ioctl(RCIN_AppCustomData.DeviceFd, TCSETS2, 
            &RCIN_AppCustomData.TerminalConfig);
    if (0 != returnCode)
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN custom set terminal config failed errno: %i", errno);
        goto end_of_function;
    }
    else
    {
        RGBLED_AppCustomData.Status = RGBLED_CUSTOM_ENABLED;
    }

end_of_function:
    return returnBool;
}


boolean RCIN_Measure(PX4_InputRcMsg_t *Measure)
{
    // error Count currently handled outside measure
    //uint16 errorCount = 0;
    int bytesRead = 0;
    boolean returnBool = TRUE;
    uint8 sbusData[25] = {0};

    /* Null pointer check */
    if (0 == Measure)
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN device read null pointer error");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Timestamp */
    Measure->Timestamp = RCIN_Custom_Get_Time();

    /* Read */
    bytesRead = RCIN_Read(RCIN_AppCustomData.DeviceFd, &sbusData, sizeof(sbusData));

    /* TODO handle partial read */
    /* TODO handle out of sync */

    if (25 != bytesRead) 
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN device read error");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Validate SBUS header and end byte */
    if (0x0f != sbusData[0] && 0x00 != sbusData[24]) 
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN device out of sync error");
        returnBool = FALSE;
        goto end_of_function;
    }

    Measure->Values[0] = (uint16)(((sbusData[1] | sbusData[2] << 8) 
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[1] = (uint16)(((sbusData[2] >> 3 | sbusData[3] << 5)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[2] = (uint16)(((sbusData[3] >> 6 | sbusData[4] << 2
            | sbusData[5] << 10) & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f)
            + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[3] = (uint16)(((sbusData[5] >> 1 | sbusData[6] << 7)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[4] = (uint16)(((sbusData[6] >> 4 | sbusData[7] << 4)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[5] = (uint16)(((sbusData[7] >> 7 | sbusData[8] << 1
            | sbusData[9] << 9) & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f)
            + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[6] = (uint16)(((sbusData[9] >> 2 | sbusData[10] << 6)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[7] = (uint16)(((sbusData[10] >> 5 | sbusData[11] << 3)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET; // & the other 8 + 2 channels if you need them
    Measure->Values[8] = (uint16)(((sbusData[12] | sbusData[13] << 8)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[9] = (uint16)(((sbusData[13] >> 3 | sbusData[14] << 5)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[10] = (uint16)(((sbusData[14] >> 6 | sbusData[15] << 2
            | sbusData[16] << 10) & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f)
            + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[11] = (uint16)(((sbusData[16] >> 1 | sbusData[17] << 7)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[12] = (uint16)(((sbusData[17] >> 4 | sbusData[18] << 4)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[13] = (uint16)(((sbusData[18] >> 7 | sbusData[19] << 1
            | sbusData[20] << 9) & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f)
            + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[14] = (uint16)(((sbusData[20] >> 2 | sbusData[21] << 6)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;
    Measure->Values[15] = (uint16)(((sbusData[21] >> 5 | sbusData[22] << 3)
            & 0x07FF) * RCIN_SBUS_SCALE_FACTOR + .5f) + RCIN_SBUS_SCALE_OFFSET;

    /* Channel count */
    Measure->ChannelCount = RCIN_SBUS_CHANNEL_COUNT;
    Measure->RSSI = 100;
    // For now handle outside measure function call.
    //Measure->RcLostFrameCount = errorCount;
    Measure->RcTotalFrameCount = 1;
    Measure->RcPpmFrameLength = 0;
    Measure->RcFailsafe = (sbusData[23] & (1 << 3)) ? TRUE : FALSE;
    Measure->RcLost = (sbusData[23] & (1 << 2)) ? TRUE : FALSE;
    Measure->InputSource = PX4_RC_INPUT_SOURCE_PX4IO_SBUS;
    
end_of_function:
    return returnBool;
}


CFE_TIME_SysTime_t RCIN_Custom_Get_Time(void)
{
    struct timespec ts;
    int returnCode = 0;
    CFE_TIME_SysTime_t Timestamp = {0, 0};

    returnCode = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (-1 == returnCode)
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN clock_gettime errno: %i", errno);
        goto end_of_function;
    }

end_of_function:
    return Timestamp;
}


boolean RCIN_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnCode = close(RCIN_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        CFE_EVS_SendEvent(RCIN_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RCIN Device close errno: %i", errno);
        returnBool = FALSE;
    }
    else
    {
        RCIN_AppCustomData.Status = RCIN_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}
