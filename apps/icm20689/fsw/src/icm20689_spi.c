/****************************************************************************
*
*   Copyright (c) 2020 Windhover Labs, L.L.C. All rights reserved.
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
#include "icm20689_spi.h"
#include "icm20689_events.h"
#include "icm20689_perfids.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>

/************************************************************************
** Local Defines
*************************************************************************/
/** \brief Retry attemps for interrupted ioctl calls.
**
**  \par Limits:
**       None.
*/
#define ICM20689_MAX_RETRY_ATTEMPTS           (2)

/** \brief Sleep time micro seconds for interrupted calls.
**
**  \par Limits:
**       None.
*/
#define ICM20689_MAX_RETRY_SLEEP_USEC         (10)

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef struct
{
    int DeviceFd;
} ICM20689_AppSpiData_t;

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
struct spi_ioc_transfer ICM20689_SPI_Xfer[2];

ICM20689_AppSpiData_t ICM20689_AppSpiData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Function Implementation
*************************************************************************/
int32 ICM20689_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < ICM20689_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(ICM20689_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


boolean ICM20689_Spi_Init(ICM20689_ConfigTbl_t* ConfigTblPtr)
{
    boolean returnBool = TRUE;
    int ret = 0;
    int i = 0;
    int8 mode = ConfigTblPtr->SpiModeSetting;
    int8 bits = ConfigTblPtr->SpiBitsSetting;
    uint32 speed = ConfigTblPtr->SpiSpeedSetting;

    ICM20689_AppSpiData.DeviceFd = open(ConfigTblPtr->SpiPathSetting, O_RDWR);
    if (ICM20689_AppSpiData.DeviceFd < 0) 
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 Device open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_WR_MODE, &mode);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Can't set SPI mode.");
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_RD_MODE, &mode);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Can't get SPI mode.");
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Can't set bits per word.");
        returnBool = FALSE;
        goto end_of_function;
    }
    
    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Can't get bits per word.");
        returnBool = FALSE;
        goto end_of_function;
    }
    
    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Can't set max speed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Can't get max speed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Keep CS activated */
    ICM20689_SPI_Xfer[0].cs_change = 0; 
    ICM20689_SPI_Xfer[0].delay_usecs = 0; 
    ICM20689_SPI_Xfer[0].speed_hz = speed; 
    ICM20689_SPI_Xfer[0].bits_per_word = bits;

end_of_function:
    return returnBool;
}


void ICM20689_Spi_Cleanup(void)
{
    (void) close(ICM20689_AppSpiData.DeviceFd);
}


boolean ICM20689_Write_Reg(uint8 Addr, uint8 Data)
{
    int ret;
    unsigned char   buf[32];
    boolean returnBool = TRUE;

    memset(buf, 0, sizeof(buf));
    buf[0] = Addr;
    buf[1] = Data;

    ICM20689_SPI_Xfer[0].tx_buf = (unsigned long)buf;
    ICM20689_SPI_Xfer[0].rx_buf = (unsigned long)buf;
    ICM20689_SPI_Xfer[0].len = 2;

    ret = ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_MESSAGE(1), ICM20689_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 ioctl returned %i", errno);
        returnBool = FALSE;
    }
    return returnBool;
}


boolean ICM20689_Read_Reg(uint8 Addr, uint8 *returnVal)
{
    int ret = 0;
    unsigned char buf[32];
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == returnVal)
    {
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 ReadReg Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    memset(buf, 0, sizeof(buf));
    buf[0] = Addr | 0x80;
    buf[1] = 0;

    ICM20689_SPI_Xfer[0].tx_buf = (unsigned long)buf;
    ICM20689_SPI_Xfer[0].rx_buf = (unsigned long)buf;
    ICM20689_SPI_Xfer[0].len = 2;

    ret = ICM20689_Ioctl(ICM20689_AppSpiData.DeviceFd, SPI_IOC_MESSAGE(1), ICM20689_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(ICM20689_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 ioctl returned %i", errno);
    }

    *returnVal = (uint8) buf[1];

end_of_function:
    return returnBool;
}

