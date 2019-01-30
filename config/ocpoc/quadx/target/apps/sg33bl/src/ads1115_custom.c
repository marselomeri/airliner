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
#include "px4lib.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "ads1115_map.h"
#include "ads1115_custom.h"

/************************************************************************
** Local Defines
*************************************************************************/
/** \brief Retry attemps for interrupted ioctl calls.
**
**  \par Limits:
**       None.
*/
#define ADS1115_MAX_RETRY_ATTEMPTS           (2)

/** \brief Sleep time micro seconds for interrupted calls.
**
**  \par Limits:
**       None.
*/
#define ADS1115_MAX_RETRY_SLEEP_USEC         (10)

#define ADS1115_I2C_DEVICE_PATH              "/dev/i2c-4"
#define ADS1115_I2C_SLAVE_ADDRESS            ADS1115_ADDRESS_GND
#define ADS1115_I2C_M_READ                   (0x0001)

/************************************************************************
** Local Structure Declarations
*************************************************************************/
/**
 * \brief ADS1115 device status.
 */
typedef enum
{
    /*! ADS1115 status uninitialized */
    ADS1115_CUSTOM_UNINITIALIZED  = 0,
    /*! ADS1115 status initialized */
    ADS1115_CUSTOM_INITIALIZED    = 1
} ADS1115_Custom_Status_t;


/**
 * \brief ADS1115 custom data.
 */
typedef struct
{
    /*! Device file descriptor. */
    int                             DeviceFd;
    /*! The current device status. */
    ADS1115_Custom_Status_t         Status;
} ADS1115_AppCustomData_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
ADS1115_AppCustomData_t ADS1115_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/
int32 ADS1115_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < ADS1115_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(ADS1115_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


void ADS1115_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&ADS1115_AppCustomData, sizeof(ADS1115_AppCustomData));
}


boolean ADS1115_Custom_Init(void)
{
    boolean returnBool = TRUE;
    int32 returnCode   = 0;
    uint16 value = 0;

    ADS1115_AppCustomData.DeviceFd = open(ADS1115_I2C_DEVICE_PATH, O_RDWR);
    if (ADS1115_AppCustomData.DeviceFd < 0) 
    {
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = ADS1115_readBlock(ADS1115_REG_CONVERSION, &value, sizeof(value));
    if(FALSE == returnBool)
    {
        OS_printf("ADS1115 custom init failed to reg conversion register.\n");
        returnBool = FALSE;
        goto end_of_function;
    }

    ADS1115_AppCustomData.Status = ADS1115_CUSTOM_INITIALIZED;

end_of_function:
    return returnBool;
}


boolean ADS1115_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnCode = close(ADS1115_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        returnBool = FALSE;
    }
    else
    {
        ADS1115_AppCustomData.Status = ADS1115_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


boolean ADS1115_readBlock(uint8 Reg, void *Buffer, size_t Length)
{
    int returnCode       = 0;
    boolean returnBool   = FALSE;
    uint8 cmd            = Reg;

    struct i2c_rdwr_ioctl_data Packets;
    struct i2c_msg Messages[2];

    /* send */
    Messages[0].addr  = ADS1115_I2C_SLAVE_ADDRESS;
    Messages[0].flags = 0;
    Messages[0].buf   = &cmd;
    Messages[0].len   = 1;

    /* receive */
    Messages[1].addr  = ADS1115_I2C_SLAVE_ADDRESS;
    Messages[1].flags = ADS1115_I2C_M_READ;
    Messages[1].buf   = Buffer;
    Messages[1].len   = Length;

    Packets.msgs  = Messages;
    Packets.nmsgs = 2;

    returnCode = ADS1115_Ioctl(ADS1115_AppCustomData.DeviceFd, I2C_RDWR, &Packets);
    if (-1 == returnCode) 
    {            
        returnBool = FALSE;
        OS_printf("ADS1115_Ioctl returned errno %d\n", errno);
    }
    else
    {
        returnBool = TRUE;
    }

    return (returnBool);
}



boolean ADS1115_writeBlock(uint8 Reg, const void *Buffer, size_t Length)
{
    int returnCode       = 0;
    boolean returnBool   = FALSE;
    char buf[32] = {0};

    if(Length + 1 > sizeof(buf))
    {
        goto end_of_function;
    }
    
    buf[0] = Reg;
    memcpy(&buf[1], Buffer, Length);

    struct i2c_rdwr_ioctl_data Packets;
    struct i2c_msg Messages[1];

    /* send */
    Messages[0].addr  = ADS1115_I2C_SLAVE_ADDRESS;
    Messages[0].flags = 0;
    Messages[0].buf   = &buf[0];
    Messages[0].len   = Length + 1;

    Packets.msgs  = Messages;
    Packets.nmsgs = 1;

    returnCode = ADS1115_Ioctl(ADS1115_AppCustomData.DeviceFd, I2C_RDWR, &Packets);

    if (-1 == returnCode) 
    {            
        returnBool = FALSE;
    }
    else
    {
        returnBool = TRUE;
    }

end_of_function:
    return (returnBool);
}

