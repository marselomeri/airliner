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
#include "rgbled_driver.h"
#include "rgbled_platform_cfg.h"
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

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

    return (returnCode);
}


void RGBLED_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&RGBLED_AppCustomData, sizeof(RGBLED_AppCustomData));

    strncpy(RGBLED_AppCustomData.DevName, RGBLED_DEVICE_PATH, RGBLED_MAX_DEVICE_PATH);
    return;
}


boolean RGBLED_Custom_Init(void)
{
    boolean returnBool = TRUE;

end_of_function:
    return (returnBool);
}


boolean RGBLED_Custom_Enable(void)
{
    boolean returnBool = FALSE; 
    uint8 settings     = 0;

    return (returnBool);
}


boolean RGBLED_Custom_Disable(void)
{
    boolean returnBool = FALSE;

    return (returnBool);
}


boolean RGBLED_Custom_GetSettings(void)
{
    boolean returnBool   = TRUE;
    boolean enabled      = FALSE;
    boolean notPowerSave = FALSE;
    uint8 settings       = 0;
    uint8 redPWM         = 0;
    uint8 greenPWM       = 0;
    uint8 bluePWM        = 0;


end_of_function:
    return (returnBool);
}


boolean RGBLED_Custom_Validate(void)
{
    boolean returnBool   = FALSE;
    boolean enabled      = FALSE;
    boolean notPowerSave = FALSE;
    uint8 settings       = 0;
    uint8 redPWM         = 0;
    uint8 greenPWM       = 0;
    uint8 bluePWM        = 0;

end_of_function:
    return (TRUE);
}


boolean RGBLED_Custom_Send(uint8 *Buffer, size_t Length)
{
    int returnCode       = 0;
    boolean returnBool   = FALSE;
    struct i2c_msg Messages[1];
    struct i2c_rdwr_ioctl_data Packets;

    return (returnBool);
}


boolean RGBLED_Custom_Receive(uint8 *Buffer, size_t Length)
{
    int returnCode     = 0;
    boolean returnBool = FALSE;

    return (returnBool);
}


boolean RGBLED_Custom_SetColor(uint8 Red, uint8 Green, uint8 Blue)
{
    boolean returnBool = FALSE;

    return (returnBool);
}


boolean RGBLED_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode     = 0;

    return (returnBool);
}
