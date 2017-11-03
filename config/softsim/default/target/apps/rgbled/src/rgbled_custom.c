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
            "RGBLED Device open errno: %i on channel %u", errno, (unsigned int)i);
        returnCode = FALSE;
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}


int32 RGBLED_Custom_Send(uint8 Red, uint8 Green, uint8 Blue)
{
    int32 returnCode = 0;
    int ret = 0;
    struct i2c_msg Messages[2];
    struct i2c_rdwr_ioctl_data Packets;
    uint8 RedPWM    = Red;
    uint8 GreenPWM  = Green;
    uint8 BluePWM   = Blue;
    
    if(RedPWM > RGBLED_MAX_BRIGHTNESS)
    {
        RedPWM = 15;
    }
    
    if(GreenPWM > RGBLED_MAX_BRIGHTNESS)
    {
        GreenPWM = 15;
    }
    
    if(BluePWM > RGBLED_MAX_BRIGHTNESS)
    {
        BluePWM = 15;
    }

    const uint8 Data[6] = { RGBLED_I2C_SUB_ADDR_PWM0, BluePWM,
                            RGBLED_I2C_SUB_ADDR_PWM1, GreenPWM,
                            RGBLED_I2C_SUB_ADDR_PWM1, RedPWM };

    Messages[0].addr = RGBLED_I2C_ADDRESS;
    Messages[0].flags = 0;
    Messages[0].buf = &Data;
    Messages[0].len = sizeof(Data);
    
    Packets.msgs  = Messages;
    Packets.nmsgs = 1;
    
    ret = RGBLED_Ioctl(RGBLED_AppCustomData.DeviceFd, I2C_RDWR, &Packets);
    
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(RGBLED_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "RGBLED ioctl returned %i", errno);
        returnCode = -1;
    }

    return returnCode;
}

