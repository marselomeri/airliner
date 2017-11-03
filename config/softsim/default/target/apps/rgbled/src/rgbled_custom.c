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
#include "rgbled_custom.h"
#include "rgbled_driver.h"

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

/************************************************************************
** Local Defines
*************************************************************************/
/* self test command */
#define RGBLED_SELFTEST_CC  (2)

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef enum {

/** \brief <tt> 'RGBLED - ' </tt>
**  \event <tt> 'RGBLED - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    RGBLED_DEVICE_ERR_EID = RGBLED_EVT_CNT,
    
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    RGBLED_CUSTOM_EVT_CNT
} RGBLED_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
RGBLED_AppCustomData_t RGBLED_AppCustomData;
/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/
int32 RGBLED_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < RGBLED_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(RGBLED_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


boolean RGBLED_Custom_InitData(void)
{
    boolean returnBool = TRUE;

    /* Set all struct zero values */
    bzero(&RGBLED_AppCustomData, sizeof(RGBLED_AppCustomData));

    strncpy(RGBLED_AppCustomData.DevName, RGBLED_DEVICE_PATH, RGBLED_MAX_DEVICE_PATH);

    return returnBool;
}


boolean RGBLED_Custom_Init(void)
{
    boolean returnBool = TRUE;
    
    RGBLED_AppCustomData.DeviceFd = open(RGBLED_DEVICE_PATH, O_RDWR);

    if (RGBLED_AppCustomData.DeviceFd < 0) 
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED Device open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }
    else
    {
        RGBLED_AppCustomData.Status = RGBLED_INITIALIZED;
    }
    
    returnBool = RGBLED_Custom_Enable();
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED Device custom enable failed errno: %i", errno);
        goto end_of_function;
    }
    else
    {
        RGBLED_AppCustomData.Status = RGBLED_ENABLED;
    }

end_of_function:
    return returnBool;
}


boolean RGBLED_Custom_Enable(void)
{
    boolean returnBool = FALSE; 
    uint8 settings = 0;

    /* Enable output */
    settings |= RGBLED_I2C_SET_ENABLE;
    settings |= RGBLED_I2C_SET_NOT_POWERSAVE;

    const uint8 data[2] = { RGBLED_I2C_SUB_ADDR_SETTINGS, settings };

    returnBool = RGBLED_Custom_Send(&data, sizeof(data));
    if(TRUE == returnBool)
    {
        RGBLED_AppCustomData.Settings.Enabled = TRUE;
        RGBLED_AppCustomData.Settings.NotPowerSave = TRUE;
    }

    returnBool = RGBLED_Custom_Validate();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED device settings validation failedin custom enable");
    }
    return returnBool;
}


boolean RGBLED_Custom_Disable(void)
{
    boolean returnBool = FALSE;
    uint8 settings = 0;
    
    const uint8 data[2] = { RGBLED_I2C_SUB_ADDR_SETTINGS, settings };
    
    returnBool = RGBLED_Custom_Send(&data, sizeof(data));
    if(TRUE == returnBool)
    {
        RGBLED_AppCustomData.Settings.Enabled = FALSE;
        RGBLED_AppCustomData.Settings.NotPowerSave = FALSE;
    }

    returnBool = RGBLED_Custom_Validate();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED device settings validation failed in custom disable");
    }
    return returnBool;
}


boolean RGBLED_Custom_Validate(void)
{
    boolean returnBool   = FALSE;
    boolean enabled      = FALSE;
    boolean notPowerSave = FALSE;
    uint8 settings = 0;
    uint8 redPWM   = 0;
    uint8 greenPWM = 0;
    uint8 bluePWM  = 0;

    /* The TCA62724FMG LED driver returns 2-bytes */
    uint8 Result[2] = {0, 0};

    returnBool = RGBLED_Custom_Receive(&Result, sizeof(Result));

    if(FALSE == returnBool)
    {
        /* If receive was unsuccessful return FALSE */
        goto end_of_function;
    }
    
    /* Settings are bits 7 - 4 of returned byte 0 */
    settings    = Result[0] & 0xf0;
    /* Red LED duty cycle is bits 3 - 0 of returned byte 0 */
    redPWM      = Result[0] & 0x0f;
    /* Green LED duty cycle is bits 7 - 4 of returned byte 1 */ 
    greenPWM    = Result[1] & 0xf0;
    /* Blue LED duty cycle is bits 3 - 0 of returned byte 1 */
    bluePWM     = Result[1] & 0x0f;
    
    /* If settings bit 5 is set (1) output is enabled */
    if(32 == settings & (1<<5))
    {
        enabled = TRUE;
    }
    
    /* if settings bit 4 is set (1) powersave mode is not set */
    if(16 == settings & (1<<4))
    {
        powerSave = TRUE;
    }
    
    if( RGBLED_AppCustomData.Settings.Enabled        == enabled &&
        RGBLED_AppCustomData.Settings.NotPowerSave   == notPowerSave &&
        RGBLED_AppCustomData.Settings.RedDutyCycle   == redPWM &&
        RGBLED_AppCustomData.Settings.GreenDutyCycle == greenPWM &&
        RGBLED_AppCustomData.Settings.BlueDutyCycle  == bluePWM )
    {
        returnBool = TRUE;
    }
    else
    {
        returnBool = FALSE;
    }

end_of_function:
    return returnBool;
}


boolean RGBLED_Custom_Send(uint8 *Buffer, size_t Length)
{
    int returnCode = 0;
    boolean returnBool = FALSE;
    struct i2c_msg Messages[1];
    struct i2c_rdwr_ioctl_data Packets;

    Messages[0].addr  = RGBLED_I2C_ADDRESS;
    Messages[0].flags = 0;
    Messages[0].buf   = Buffer;
    Messages[0].len   = Length;

    Packets.msgs  = Messages;
    Packets.nmsgs = 1;

    CFE_ES_PerfLogEntry(RGBLED_SEND_PERF_ID);
    returnCode = RGBLED_Ioctl(RGBLED_AppCustomData.DeviceFd, I2C_RDWR, &Packets);
    CFE_ES_PerfLogExit(RGBLED_SEND_PERF_ID);
    
    if (-1 == returnCode) 
    {            
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "RGBLED ioctl returned %i", errno);
        returnBool = FALSE;
    }
    else
    {
        returnBool = TRUE;
    }

    return returnBool;
}


boolean RGBLED_Custom_Receive(uint8 *Buffer, size_t Length)
{
    int returnCode = 0;
    boolean returnBool = FALSE;
    struct i2c_msg messages[1];
    struct i2c_rdwr_ioctl_data packets;

    messages[0].addr  = RGBLED_I2C_ADDRESS;
    messages[0].flags = I2C_M_READ;
    messages[0].buf   = Buffer;
    messages[0].len   = Length;

    Packets.msgs  = messages;
    Packets.nmsgs = 1;

    CFE_ES_PerfLogEntry(RGBLED_RECEIVE_PERF_ID);
    returnCode = RGBLED_Ioctl(RGBLED_AppCustomData.DeviceFd, I2C_RDWR, &packets);
    CFE_ES_PerfLogExit(RGBLED_RECEIVE_PERF_ID);

    if (-1 == returnCode) 
    {            
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "RGBLED ioctl returned %i", errno);
        returnBool = FALSE;
    }
    else
    {
        returnBool = TRUE;
    }

    return returnBool;
}


boolean RGBLED_Custom_SetColor(uint8 Red, uint8 Green, uint8 Blue)
{
    boolean returnBool = FALSE;
    uint8 redPWM    = Red;
    uint8 greenPWM  = Green;
    uint8 bluePWM   = Blue;
    
    /* If any brightness value is greater than max brightness... */
    if(redPWM > RGBLED_MAX_BRIGHTNESS)
    {
        /* Set the value to max brightness */
        redPWM = RGBLED_MAX_BRIGHTNESS;
    }

    if(greenPWM > RGBLED_MAX_BRIGHTNESS)
    {
        greenPWM = RGBLED_MAX_BRIGHTNESS;
    }
    
    if(bluePWM > RGBLED_MAX_BRIGHTNESS)
    {
        bluePWM = RGBLED_MAX_BRIGHTNESS;
    }

    const uint8 data[6] = { RGBLED_I2C_SUB_ADDR_PWM0, BluePWM,
                            RGBLED_I2C_SUB_ADDR_PWM1, GreenPWM,
                            RGBLED_I2C_SUB_ADDR_PWM1, RedPWM };

    returnBool = RGBLED_Custom_Send(&data, sizeof(data));
    
    /* Set the current value */
    RGBLED_AppCustomData.Settings.RedDutyCycle   = redPWM;
    RGBLED_AppCustomData.Settings.GreenDutyCycle = greenPWM;
    RGBLED_AppCustomData.Settings.BlueDutyCycle  = bluePWM;
    
    returnBool = RGBLED_Custom_Validate();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED device settings validation failed");
    }

    return returnBool;
}


boolean RGBLED_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnBool = RGBLED_Custom_Disable();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED Device disable error");
    }
    else
    {
        RGBLED_AppCustomData.Status == RGBLED_INITIALIZED;
    }

    returnCode = close(RGBLED_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "RGBLED Device close errno: %i", errno);
        returnBool = FALSE;
    }
    else
    {
        RGBLED_AppCustomData.Status = RGBLED_UNINITIALIZED;
    }
    return returnBool;
}


