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
#include "mpu9250_spi.h"
#include "mpu9250_events.h"
#include "mpu9250_perfids.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/
typedef enum {

/** \brief <tt> 'MPU9250 - ' </tt>
**  \event <tt> 'MPU9250 - ' </tt>
**  
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when a device resource encounters an 
**  error.
**
*/
    MPU9250_DEVICE_ERR_EID = MPU9250_EVT_CNT,

/** \brief <tt> 'MPU9250 - ' </tt>
**  \event <tt> 'MPU9250 - ' </tt>
**  
**  \par Type: Info
**
**  \par Cause:
**
**  This event message is issued when a device successfully complete a
**  self test.
**
*/
    MPU9250_DEVICE_INF_EID,
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    MPU9250_CUSTOM_EVT_CNT
} MPU9250_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
MPU9250_AppCustomData_t MPU9250_AppCustomData;
struct spi_ioc_transfer MPU9250_SPI_Xfer[2];

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/
int32 MPU9250_Ioctl(int fh, int request, void *arg)
{
    int32 returnCode = 0;
    uint32 i = 0;

    for (i=0; i < MPU9250_MAX_RETRY_ATTEMPTS; i++)
    {
        returnCode = ioctl(fh, request, arg);
            
        if (-1 == returnCode && EINTR == errno)
        {
            usleep(MPU9250_MAX_RETRY_SLEEP_USEC);
        }
        else
        {
            break;
        }
    }

    return returnCode;
}


void MPU9250_Custom_InitData(void)
{
    /* Set all struct zero values */
    bzero(&MPU9250_AppCustomData, sizeof(MPU9250_AppCustomData));
}


boolean MPU9250_Custom_Init()
{
    boolean returnBool = TRUE;
    int ret = 0;
    int i = 0;
    int8 mode = MPU9250_SPI_DEVICE_MODE;
    int8 bits = MPU9250_SPI_DEVICE_BITS;
    uint32 speed = MPU9250_SPI_DEVICE_SPEED;

    MPU9250_AppCustomData.DeviceFd = open(MPU9250_SPI_DEVICE_PATH, O_RDWR);
    if (MPU9250_AppCustomData.DeviceFd < 0) 
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Device open errno: %i", errno);
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_WR_MODE, &mode);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Can't set SPI mode.");
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_RD_MODE, &mode);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Can't get SPI mode.");
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Can't set bits per word.");
        returnBool = FALSE;
        goto end_of_function;
    }
    
    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Can't get bits per word.");
        returnBool = FALSE;
        goto end_of_function;
    }
    
    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Can't set max speed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Can't get max speed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Keep CS activated */
    MPU9250_SPI_Xfer[0].cs_change = 0; 
    MPU9250_SPI_Xfer[0].delay_usecs = 0; 
    MPU9250_SPI_Xfer[0].speed_hz = speed; 
    MPU9250_SPI_Xfer[0].bits_per_word = 8;
    ///* Keep CS activated */
    //MPU9250_SPI_Xfer[1].cs_change = 0; 
    //MPU9250_SPI_Xfer[1].delay_usecs = 0;
    //MPU9250_SPI_Xfer[1].speed_hz = speed;
    //MPU9250_SPI_Xfer[1].bits_per_word = 8;
    
    ret = MPU9250_ResetDevice();
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Reset device failed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    MPU9250_AppCustomData.Status = MPU9250_CUSTOM_INITIALIZED;

end_of_function:
    return returnBool;
}


boolean MPU9250_Custom_Uninit(void)
{
    boolean returnBool = TRUE;
    int returnCode = 0;

    returnCode = close(MPU9250_AppCustomData.DeviceFd);
    if (-1 == returnCode) 
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Device close errno: %i", errno);
        returnBool = FALSE;
    }
    else
    {
        MPU9250_AppCustomData.Status = MPU9250_CUSTOM_UNINITIALIZED;
    }
    return returnBool;
}


int32 MPU9250_ResetDevice(void)
{
    int32 ret = 0;
    boolean returnBool = TRUE;
    
    returnBool = MPU9250_WriteReg(MPU9250_BIT_H_RESET, MPU9250_REG_PWR_MGMT_1);
    if (FALSE == returnBool) 
    {            
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU9250 ioctl returned %i", errno);
        ret = -1;
    }
    else
    {
        usleep(100000);
    }
    return ret;
}


boolean MPU9250_WriteReg(uint8 Addr, uint8 Data)
{
    int ret;
    unsigned char   buf[32];
    boolean returnBool = TRUE;

    memset(buf, 0, sizeof(buf));
    buf[0] = Addr;
    buf[1] = Data;

    MPU9250_SPI_Xfer[0].tx_buf = (unsigned long)buf;
    MPU9250_SPI_Xfer[0].rx_buf = (unsigned long)buf;
    MPU9250_SPI_Xfer[0].len = 2;

    ret = ioctl(MPU9250_AppData.FD, SPI_IOC_MESSAGE(1), MPU9250_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU9250 ioctl returned %i", errno);
        returnBool = FALSE;
    }
    return returnBool;
};


boolean MPU9250_ReadReg(uint8 Addr, uint8 *returnVal)
{
    int ret = 0;
    unsigned char   buf[32];
    boolean returnBool = TRUE;
    
    /* Null pointer check */
    if(0 == returnVal)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 ReadReg Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    memset(buf, 0, sizeof(buf));
    buf[0] = Addr | 0x80;
    buf[1] = 0;

    MPU9250_SPI_Xfer[0].tx_buf = (unsigned long)buf;
    MPU9250_SPI_Xfer[0].rx_buf = (unsigned long)buf;
    MPU9250_SPI_Xfer[0].len = 2;

    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_MESSAGE(1), MPU9250_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU9250 ioctl returned %i", errno);
    }

    *returnVal = (uint8) buf[1];

end_of_function:
    return returnBool;
}
