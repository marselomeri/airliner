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
#include "px4lib.h"
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <byteswap.h>
#include <stdint.h>

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


boolean MPU9250_I2C_Master_Reset(void)
{
    boolean returnBool = FALSE;
    uint8 buf = 0;

    /* Get current bits. */
    returnBool = MPU9250_ReadReg(MPU9250_REG_USER_CTRL, &buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set master reset flag. */
    buf = MPU9250_USER_CTRL_I2C_MST_RST | buf;

    returnBool = MPU9250_WriteReg(MPU9250_REG_USER_CTRL, buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

    /* Clear master reset flag. */
    buf &= ~(MPU9250_USER_CTRL_I2C_MST_RST);

    /* Set master enable flag. */
    buf = MPU9250_USER_CTRL_I2C_MST_EN | buf;

    returnBool = MPU9250_WriteReg(MPU9250_REG_USER_CTRL, buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

    returnBool = MPU9250_WriteReg(MPU9250_REG_I2C_MST_CTRL, MPU9250_I2C_MST_CLOCK_400HZ);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

end_of_function:
    return returnBool;
}


boolean MPU9250_Clear_Interrupt(void)
{
    boolean returnBool = FALSE;
    uint8 buf = 0;

    returnBool = MPU9250_ReadReg(MPU9250_REG_INT_STATUS, &buf);

    return returnBool;
}


boolean MPU9250_Fifo_Reset(void)
{
    boolean returnBool = FALSE;
    uint8 buf = 0;

    /* Get current bits. */
    returnBool = MPU9250_ReadReg(MPU9250_REG_USER_CTRL, &buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    /* Clear fifo enable flag. */
    buf &= ~(MPU9250_USER_CTRL_FIFO_EN);

    /* Set fifo reset flag. */
    buf = MPU9250_USER_CTRL_FIFO_RST | buf;

    returnBool = MPU9250_WriteReg(MPU9250_REG_USER_CTRL, buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

    /* Set fifo enable flag. */
    buf = MPU9250_USER_CTRL_FIFO_EN | buf;

    returnBool = MPU9250_WriteReg(MPU9250_REG_USER_CTRL, buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

end_of_function:
    return returnBool;
}

boolean MPU9250_Custom_MagInit(void)
{
    boolean returnBool = FALSE;
    uint8 buf = 0;

    /* Reset AK8963 */
    returnBool = MPU9250_MagWriteReg(MPU9250_AK8963_CNTL2, MPU9250_MAG_CNTL2_SOFT_RESET);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Check the mag device ID. */
    returnBool = MPU9250_MagReadReg(MPU9250_AK8963_WIA, &buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    if(buf != MPU9250_AK8963_Device_ID)
    {
        returnBool = FALSE;
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 mag device ID not found.");
        goto end_of_function;
    }

    /* Get the mag sensitivity adjustment values from fuse rom. */
    returnBool = MPU9250_Custom_Read_MagAdj();
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Continuous measurement mode 2 in 16bit */
    returnBool = MPU9250_MagWriteReg(MPU9250_AK8963_CNTL1, 
            MPU9250_MAG_CNTL1_MODE_CONT_MEASURE_2 | MPU9250_MAG_CNTL1_16_BITS);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set the I2C slave address of AK8963 and set for read. */
    returnBool = MPU9250_MagWriteReg(MPU9250_REG_I2C_SLV0_ADDR, 
            MPU9250_AK8963_I2C_ADDR | MPU9250_SLAVE_READ);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* I2C slave 0 register address from where to begin data transfer */
    returnBool = MPU9250_MagWriteReg(MPU9250_REG_I2C_SLV0_REG, 
            MPU9250_AK8963_ST1);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    returnBool = MPU9250_MagWriteReg(MPU9250_REG_I2C_SLV0_CTRL, 
            MPU9250_SLAVE_EN | MPU9250_SLAVE_READ_8BYTES);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

    /* Sample every 10 samples. Downsample to 100Hz*/
    returnBool = MPU9250_WriteReg(MPU9250_REG_I2C_SLV4_CTRL, 10);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

    returnBool = MPU9250_WriteReg(MPU9250_REG_I2C_MST_DELAY_CTRL, 
            MPU9250_SLAVE_0_DLY_EN);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    usleep(1000);

end_of_function:
    return returnBool;
}


boolean MPU9250_Custom_Init(void)
{
    boolean returnBool = TRUE;
    int ret, i = 0;
    uint8 buf = 0;
    const int8 mode = MPU9250_SPI_DEVICE_MODE;
    const int8 bits = MPU9250_SPI_DEVICE_BITS;
    const uint32 speed = MPU9250_SPI_DEVICE_SPEED;

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

    ret = MPU9250_ResetDevice();
    if (-1 == ret)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                          "Reset device failed.");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Check who am i device ID. */
    returnBool = MPU9250_Read_WhoAmI(&buf);
    if(FALSE == returnBool || buf != MPU9250_AK8963_Device_ID)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 device validation failed");
        goto end_of_function;
    }

    /* TODO Add Gyroscope Self-Test */
    /* TODO Add Accelerometer Self-Test */

    /* Array of registers and values to initialize. */
    const uint8 MPU_Init_Data[MPU9250_INITREGNUM][2] = {
        /* Wakeup */
        {0x00, MPU9250_REG_PWR_MGMT_1},
        /* Enable Acc & Gyro */
        {0x00, MPU9250_REG_PWR_MGMT_2},
        /* Clear */
        {0x00, MPU9250_REG_USER_CTRL},
        /* Clear */
        {0x00, MPU9250_REG_FIFO_EN},
        /* Reset (DMP, FIFO, I2C, sensor registers) */
        {MPU9250_USER_CTRL_DMP_RST |
         MPU9250_USER_CTRL_FIFO_RST |
         MPU9250_USER_CTRL_I2C_MST_RST |
         MPU9250_USER_CTRL_SIG_COND_RST, MPU9250_REG_USER_CTRL},
         /* FIFO enabled, I2C master enable, I2C slave disabled */
        {MPU9250_USER_CTRL_FIFO_EN |
         MPU9250_USER_CTRL_I2C_MST_EN |
         MPU9250_USER_CTRL_I2C_IF_DIS, MPU9250_REG_USER_CTRL},
         /* Enable temp, gyro, accel and mag in the FIFO */
        {MPU9250_FIFO_EN_TEMP_OUT |
         MPU9250_FIFO_EN_GYRO_XOUT |
         MPU9250_FIFO_EN_GYRO_YOUT |
         MPU9250_FIFO_EN_GYRO_ZOUT |
         MPU9250_FIFO_EN_ACCEL_OUT |
         MPU9250_FIFO_EN_SLV0_OUT, MPU9250_REG_FIFO_EN},
         /* Set DLPF 184Hz sampling, FIFO overwrite */
        {MPU9250_BITS_DLPF_CFG_184HZ |
         MPU9250_CONFIG_FIFO_MODE_OVERWRITE, MPU9250_REG_CONFIG},
         /* +-2000dps */
        {MPU9250_BITS_FS_2000DPS, MPU9250_REG_GYRO_CONFIG},
         /* +-4G */
        {MPU9250_BITS_FS_16G, MPU9250_REG_ACCEL_CONFIG},
        /* Accel config 2, Enable Acc LPF , Bandwidth 184Hz */
        {MPU9250_ACCEL_CONFIG2_BW_41HZ, MPU9250_REG_ACCEL_CONFIG2},
        /* I2C 400KHz */
        {MPU9250_I2C_MST_CLOCK_400HZ, MPU9250_REG_I2C_MST_CTRL}
    };

    for(i = 0; i < MPU9250_INITREGNUM; ++i) 
    {
        returnBool = MPU9250_WriteReg(MPU_Init_Data[i][1], MPU_Init_Data[i][0]);
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
        usleep(1000);
    }

    /* Initialize the mag. */
    returnBool = MPU9250_Custom_MagInit();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 custom maginit failed");
        goto end_of_function;
    }

    /* Reset FIFO. */
    returnBool = MPU9250_Fifo_Reset();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 fifo reset failed");
        goto end_of_function;
    }

    /* Clear interrupt status. */
    returnBool = MPU9250_Clear_Interrupt();
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 clear interrupt failed");
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
    
    returnBool = MPU9250_WriteReg(MPU9250_REG_PWR_MGMT_1, MPU9250_PWR_MGMT_1_H_RESET);
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
    unsigned char   buf[2];
    boolean returnBool = TRUE;

    buf[0] = Addr;
    buf[1] = Data;

    MPU9250_SPI_Xfer[0].tx_buf = (unsigned long)buf;
    MPU9250_SPI_Xfer[0].rx_buf = (unsigned long)buf;
    MPU9250_SPI_Xfer[0].len = 2;

    ret = ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_MESSAGE(1), MPU9250_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU9250 ioctl returned %i", errno);
        returnBool = FALSE;
    }
    return returnBool;
}


boolean MPU9250_ReadBlock(uint8 Addr, void *Buf, size_t Len)
{
    int ret = 0;
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == Buf)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 ReadBlock Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Length check */
    if((Len + 1) > MPU9250_SPI_MAX_BUFFER)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 SPI buffer too small");
        returnBool = FALSE;
        goto end_of_function;
    }

    memset(&MPU9250_AppCustomData.BufSpi[0], 0, sizeof(MPU9250_AppCustomData.BufSpi));
    MPU9250_AppCustomData.BufSpi[0] = Addr | 0x80;

    MPU9250_SPI_Xfer[0].tx_buf = (unsigned long)MPU9250_AppCustomData.BufSpi;
    MPU9250_SPI_Xfer[0].rx_buf = (unsigned long)MPU9250_AppCustomData.BufSpi;
    MPU9250_SPI_Xfer[0].len = Len + 1;

    ret = MPU9250_Ioctl(MPU9250_AppCustomData.DeviceFd, SPI_IOC_MESSAGE(1), MPU9250_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MPU9250 ioctl returned %i", errno);
    }

    memcpy(Buf, &MPU9250_AppCustomData.BufSpi[1], Len);

end_of_function:
    return returnBool;
}


boolean MPU9250_ReadReg(uint8 Addr, uint8 *returnVal)
{
    int ret = 0;
    unsigned char   buf[2];
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == returnVal)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 ReadReg Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

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


boolean MPU9250_MagWriteReg(uint8 Addr, uint8 Data)
{
    boolean returnBool = TRUE;
    boolean verified   = FALSE;
    const uint8 retryAttempts = 5;
    const uint8 numWrites = 3;
    uint8 i, j = 0;
    uint8 buf = 0;

    const uint8 configureWrite[3][2] = {
        /* Set the I2C slave addres of AK8963 and set for write. */
        {MPU9250_AK8963_I2C_ADDR | 
            MPU9250_SLAVE_WRITE, MPU9250_REG_I2C_SLV4_ADDR},
        /* I2C slave 0 register address to write to. */
        {Addr, MPU9250_REG_I2C_SLV4_REG},
        /* I2C slave 0 register data to write. */
        {Data, MPU9250_REG_I2C_SLV4_DO}
    };

    /* Setup the write to the mag. */
    for(i = 0; i < numWrites; ++i)
    {
        returnBool = MPU9250_WriteReg(configureWrite[i][1], configureWrite[i][0]);
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
    }

    /* Verify the write to the MPU9250. */
    for(i = 0; i < numWrites; ++i)
    {
        verified = FALSE;
        for(j = 0; j < retryAttempts; ++j)
        {
            returnBool = MPU9250_ReadReg(configureWrite[j][1], &buf);
            if(FALSE == returnBool)
            {
                goto end_of_function;
            }

            if (buf != configureWrite[j][0])
            {
                continue;
            }
            else
            {
                verified = TRUE;
                break;
            }
        }

        if(FALSE == verified)
        {
            CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "MPU9250 MagWriteReg verification failed");
            returnBool = FALSE;
            goto end_of_function;
        }
    }

    returnBool = MPU9250_ReadReg(MPU9250_REG_I2C_SLV4_CTRL, &buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Enable transfer. */
    buf = MPU9250_SLAVE_EN | buf;
    returnBool = MPU9250_WriteReg(MPU9250_REG_I2C_SLV4_CTRL, buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    verified = FALSE;

    /* Check for completion. */
    for(i = 0; i < 1000; ++i)
    {
        usleep(1000);
        returnBool = MPU9250_ReadReg(MPU9250_REG_I2C_MST_STATUS, &buf);
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
        if(buf & MPU9250_I2C_SLV4_DONE)
        {
            verified = TRUE;
            break;
        }
    }

    if(FALSE == verified)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 write to mag did not complete");
        returnBool = FALSE;
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}


boolean MPU9250_MagReadReg(uint8 Addr, uint8 *returnVal)
{
    boolean returnBool = TRUE;
    boolean verified   = FALSE;
    const uint8 retryAttempts = 5;
    const uint8 numWrites = 2;
    uint8 i, j = 0;
    uint8 buf = 0;

    const uint8 configureWrite[2][2] = {
        /* Set the I2C slave addres of AK8963 and set for read. */
        {MPU9250_AK8963_I2C_ADDR | 
            MPU9250_SLAVE_READ, MPU9250_REG_I2C_SLV4_ADDR},
        /* I2C slave 0 register address to read from. */
        {Addr, MPU9250_REG_I2C_SLV4_REG}
    };

    /* Setup the read from the mag. */
    for(i = 0; i < numWrites; ++i)
    {
        returnBool = MPU9250_WriteReg(configureWrite[i][1], configureWrite[i][0]);
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
    }

    /* Verify the write to the MPU9250. */
    for(i = 0; i < numWrites; ++i)
    {
        verified = FALSE;
        for(j = 0; j < retryAttempts; ++j)
        {
            returnBool = MPU9250_ReadReg(configureWrite[j][1], &buf);
            if(FALSE == returnBool)
            {
                goto end_of_function;
            }

            if (buf != configureWrite[j][0])
            {
                continue;
            }
            else
            {
                verified = TRUE;
                break;
            }
        }

        if(FALSE == verified)
        {
            CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "MPU9250 MagReadReg verification failed");
            returnBool = FALSE;
            goto end_of_function;
        }
    }

    returnBool = MPU9250_ReadReg(MPU9250_REG_I2C_SLV4_CTRL, &buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Enable transfer. */
    buf = MPU9250_SLAVE_EN | buf;
    returnBool = MPU9250_WriteReg(MPU9250_REG_I2C_SLV4_CTRL, buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    verified = FALSE;
    /* Check for completion. */
    for(i = 0; i < 1000; ++i)
    {
        usleep(1000);
        returnBool = MPU9250_ReadReg(MPU9250_REG_I2C_MST_STATUS, &buf);
        if(FALSE == returnBool)
        {
            goto end_of_function;
        }
        if(buf & MPU9250_I2C_SLV4_DONE)
        {
            verified = TRUE;
            break;
        }
    }

    if(FALSE == verified)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 write to mag did not complete");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = MPU9250_ReadReg(MPU9250_REG_I2C_SLV4_DI, &buf);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    *returnVal = buf;

end_of_function:
    return returnBool;
}


boolean MPU9250_SetAccScale(uint8 Scale, float *AccDivider)
{
    boolean returnBool = TRUE;
    uint8 value = 0;

    /* Null pointer check */
    if(0 == AccDivider)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 SetAccScale Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    switch (Scale)
    {
        case 2:
            *AccDivider = 16384;
            value = MPU9250_BITS_FS_2G;
            break;

        case 4:
            *AccDivider = 8192;
            value = MPU9250_BITS_FS_4G;
            break;

        case 8:
            *AccDivider = 4096;
            value = MPU9250_BITS_FS_8G;
            break;

        case 16:
            *AccDivider = 2048;
            value = MPU9250_BITS_FS_16G;
            break;

        default:
            returnBool = FALSE;
            goto end_of_function;
    }

    returnBool = MPU9250_WriteReg(MPU9250_REG_ACCEL_CONFIG, value);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}


boolean MPU9250_SetGyroScale(uint32 Scale, float *GyroDivider)
{
    boolean returnBool = TRUE;
    uint8 value = 0;

    /* Null pointer check */
    if(0 == GyroDivider)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 SetGyroScale Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    switch (Scale)
    {
        case 250:
            *GyroDivider = 131;
            value = MPU9250_BITS_FS_250DPS;
            break;

        case 500:
            *GyroDivider = 65.5;
            value = MPU9250_BITS_FS_500DPS;
            break;

        case 1000:
            *GyroDivider = 32.8;
            value = MPU9250_BITS_FS_1000DPS;
            break;

        case 2000:
            *GyroDivider = 16.4;
            value = MPU9250_BITS_FS_2000DPS;
            break;

        default:
            returnBool = FALSE;
            goto end_of_function;
    }

    returnBool = MPU9250_WriteReg(MPU9250_REG_GYRO_CONFIG, value);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}


boolean MPU9250_Read_WhoAmI(uint8 *Value)
{
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == Value)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Read_WhoAmI Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    returnBool = MPU9250_ReadReg(MPU9250_REG_WHOAMI, Value);
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 read error in WhoAmI");
    }

end_of_function:
    return returnBool;
}


boolean MPU9250_Perform_AccelSelfTest(void)
{
    return TRUE;
}


boolean MPU9250_Perform_GyroSelfTest(void)
{
    return TRUE;
}


boolean MPU9250_Perform_MagSelfTest(void)
{
    return TRUE;
}


boolean MPU9250_Custom_Read_MagAdj(void)
{
    boolean returnBool = TRUE;
    uint8 validateX = 0;
    uint8 validateY = 0;
    uint8 validateZ = 0;

    /* Set power down mode. */
    returnBool = MPU9250_MagWriteReg(MPU9250_AK8963_CNTL1, MPU9250_MAG_CNTL1_MODE_POWER_DOWN);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set fuse rom access mode. */
    returnBool = MPU9250_MagWriteReg(MPU9250_AK8963_CNTL1, 
        MPU9250_MAG_CNTL1_FUSE_ROM_ACCESS_MODE | MPU9250_MAG_CNTL1_16_BITS);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    returnBool = MPU9250_MagReadReg(MPU9250_AK8963_ASAX, &validateX);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    /* TODO validate X*/
    MPU9250_AppCustomData.MagAdjX = validateX;
    returnBool = MPU9250_MagReadReg(MPU9250_AK8963_ASAY, &validateY);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    /* TODO validate Y*/
    MPU9250_AppCustomData.MagAdjY = validateY;
    returnBool = MPU9250_MagReadReg(MPU9250_AK8963_ASAZ, &validateZ);
    if(FALSE == returnBool)
    {
        returnBool = FALSE;
        goto end_of_function;
    }
    /* TODO validate Z*/
    MPU9250_AppCustomData.MagAdjZ = validateZ;

end_of_function:
    if (FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 error reading MagAdj values");
    }
    return returnBool;
}


boolean MPU9250_Read_MagAdj(uint8 *X, uint8 *Y, uint8 *Z)
{
    boolean returnBool = TRUE;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Read_MagAdj Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    *X = MPU9250_AppCustomData.MagAdjX;
    *Y = MPU9250_AppCustomData.MagAdjY;
    *Z = MPU9250_AppCustomData.MagAdjZ;

end_of_function:

    return returnBool;
}


boolean MPU9250_Custom_Max_Events_Not_Reached(int32 ind)
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


int32 MPU9250_Custom_Init_EventFilters(int32 ind, CFE_EVS_BinFilter_t *EventTbl)
{
    int32 customEventCount = ind;
    
    /* Null check */
    if(0 == EventTbl)
    {
        customEventCount = -1;
        goto end_of_function;
    }

    if(TRUE == MPU9250_Custom_Max_Events_Not_Reached(customEventCount))
    {
        EventTbl[  customEventCount].EventID = MPU9250_DEVICE_ERR_EID;
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


void MPU9250_Get_Rotation(uint8 *Rotation)
{
    
    /* Null pointer check */
    if(0 == Rotation)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Get_Rotation Null Pointer");
        goto end_of_function;
    }
    
    /* TODO move to a table */
    *Rotation = ROTATION_ROLL_180_YAW_90;

end_of_function:
    return;
}


void MPU9250_Get_Mag_Rotation(uint8 *Rotation)
{
    
    /* Null pointer check */
    if(0 == Rotation)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Get_Mag_Rotation Null Pointer");
        goto end_of_function;
    }
    
    /* TODO move to a table */
    *Rotation = ROTATION_NONE;

end_of_function:
    return;
}


boolean MPU9250_Apply_Platform_Rotation(float *X, float *Y, float *Z)
{
    boolean returnBool = TRUE;
    float temp;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Apply_Platform_Rotation Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }
    /* ROTATION_ROLL_180_YAW_90 */
    temp = *X; 
    *X = *Y; 
    *Y = temp; 
    *Z = -*Z;

end_of_function:

    return returnBool;
}


boolean MPU9250_Apply_Mag_Platform_Rotation(float *X, float *Y, float *Z)
{
    boolean returnBool = TRUE;
    float temp;

    /* Null pointer check */
    if(0 == X || 0 == Y || 0 == Z)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 Apply_Mag_Platform_Rotation Null Pointer");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* No Rotation */

end_of_function:

    return returnBool;
}


boolean MPU9250_Measure(MPU9250_SampleQueue_t *SampleQueue)
{
    uint8 intStatus = 0;
    boolean returnBool = TRUE;
    uint16 fifoByteCount = 0;
    uint16 index = 0;
    uint8 magStatus1 = 0;
    uint8 magStatus2 = 0;

    /* Null pointer check */
    if(0 == SampleQueue)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "Null pointer in MPU9250_Measure.");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Check data ready interrupt bit. */
    returnBool = MPU9250_ReadReg(MPU9250_REG_INT_STATUS, &intStatus);
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 failed to read MPU9250_REG_INT_STATUS");
        goto end_of_function;
    }

    /* Check for overflow. */
    if(intStatus & MPU9250_INT_STATUS_FIFO_OVERFLOW)
    {
        /* Reset fifo Queue. */
        MPU9250_Fifo_Reset();
        /* Fifo should have overflowed on the first read after SCH
         * startup sync. */
        if(MPU9250_AppCustomData.firstMeasureFlag != FALSE)
        {
            CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "MPU9250 FIFO overflow.");
        }
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Get the number of bytes in the FIFO queue. */
    fifoByteCount = MPU9250_GetFifoCount();

    if(fifoByteCount > 0)
    {
        /* Read the fifo queue. */
        returnBool = MPU9250_ReadBlock(MPU9250_REG_FIFO_R_W, &MPU9250_AppCustomData.samples[0], fifoByteCount);
        if(FALSE == returnBool)
        {
            CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 FIFO read failed.");
            goto end_of_function;
        }
        /* Calculate filtered fifo samples per cycle. This value should
         * stay close to 4. */
        MPU9250_AppCustomData.FifoSamplesPerCycle = 
                (0.95f * MPU9250_AppCustomData.FifoSamplesPerCycle) + 
                (0.05f * (fifoByteCount / sizeof(Fifo_Sample_t)));
        
    }
    else
    {
        /* Data not ready skipping measurement. */
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 FIFO empty.");
        returnBool = FALSE;
        goto end_of_function;
    }

    /* Calculate the number of samples in the fifo queue. */
    SampleQueue->SampleCount = fifoByteCount / sizeof(Fifo_Sample_t);
    /* Calculate the sampling interval in micro seconds. */
    SampleQueue->SampleIntervalUs = round(1000 / MPU9250_AppCustomData.FifoSamplesPerCycle);

    for(index = 0; index < SampleQueue->SampleCount; ++index)
    {
        SampleQueue->Samples[index].AX   = bswap16(MPU9250_AppCustomData.samples[index].accel_x);
        SampleQueue->Samples[index].AY   = bswap16(MPU9250_AppCustomData.samples[index].accel_y);
        SampleQueue->Samples[index].AZ   = bswap16(MPU9250_AppCustomData.samples[index].accel_z);
        SampleQueue->Samples[index].Temp = bswap16(MPU9250_AppCustomData.samples[index].temp);
        SampleQueue->Samples[index].GX   = bswap16(MPU9250_AppCustomData.samples[index].gyro_x);
        SampleQueue->Samples[index].GY   = bswap16(MPU9250_AppCustomData.samples[index].gyro_y);
        SampleQueue->Samples[index].GZ   = bswap16(MPU9250_AppCustomData.samples[index].gyro_z);
        SampleQueue->Samples[index].MX   = bswap16(MPU9250_AppCustomData.samples[index].mag_x);
        SampleQueue->Samples[index].MY   = bswap16(MPU9250_AppCustomData.samples[index].mag_y);
        SampleQueue->Samples[index].MZ   = bswap16(MPU9250_AppCustomData.samples[index].mag_z);

        //returnBool = MPU9250_sampleChecks(&SampleQueue->Samples[index]);
        //if(FALSE == returnBool)
        //{
            //goto end_of_function;
        //}

        /* Check for data ready. */
        if(MPU9250_AppCustomData.samples[index].mag_st1 & MPU9250_ST1_DRDY_MASK)
        {
            SampleQueue->Samples[index].MagDataValid = TRUE;
        }

        /* Check for magnetic overflow. */
        if(MPU9250_AppCustomData.samples[index].mag_st2 & MPU9250_ST2_HOFL_MASK)
        {
            SampleQueue->Samples[index].MagDataValid = FALSE;
            /* Magnetic sensor overflow. */
            CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 mag sensor overflow.");
        }
    }

end_of_function:
    /* First read should have overflowed. */
    if (FALSE == returnBool && MPU9250_AppCustomData.firstMeasureFlag != FALSE)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "MPU9250 read error in Measure");
    }
    MPU9250_AppCustomData.firstMeasureFlag = TRUE;
    return returnBool;
}


uint16 MPU9250_GetFifoCount(void)
{
    uint16 bytes = 0;
    uint16 completeSamples = 0;
    boolean returnBool = FALSE;

    returnBool = MPU9250_ReadBlock(MPU9250_REG_FIFO_COUNTH, &bytes, sizeof(bytes));
    if(FALSE == returnBool)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Get FIFO count failed.");
        bytes = 0;
    }

    bytes = bswap16(bytes);

    /* Ensure a complete set of samples from all sensors. */
    completeSamples = bytes / sizeof(Fifo_Sample_t);
    bytes = completeSamples * sizeof(Fifo_Sample_t);

    return bytes;
}


boolean MPU9250_sampleChecks(MPU9250_Measurement_t *sample)
{
    boolean returnBool = TRUE;

    if(0 == sample)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
            "Null pointer in MPU9250_sampleChecks.");
        goto end_of_function;
    }

    const float TempC = (float)sample->Temp / 340.0f + 36.53f;

    /* Check acceleration in the range for min/max. */
    if (sample->AX == INT16_MIN  || sample->AY == INT16_MIN  
            || sample->AZ == INT16_MIN )
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Acceleration sample hit a minimum");
    }

    if (sample->AX == INT16_MAX || sample->AY == INT16_MAX  
            || sample->AZ == INT16_MAX)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Acceleration sample hit a maximum");
    }

    /* Check gyro in the range for min/max. */
    if (sample->GX == INT16_MIN  || sample->GY == INT16_MIN  
            || sample->GZ == INT16_MIN )
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Gyro sample hit a minimum");
    }

    if (sample->GX == INT16_MAX || sample->GY == INT16_MAX  
            || sample->GZ == INT16_MAX)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Gyro sample hit a maximum");
    }

    /* Check mag in range min/max. */
    if (sample->MX == INT16_MIN  || sample->MY == INT16_MIN  
            || sample->MZ == INT16_MIN )
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Mag sample hit a minimum");
    }

    if (sample->MX == INT16_MAX || sample->MY == INT16_MAX  
            || sample->MZ == INT16_MAX)
    {
        CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                "Mag sample hit a maximum");
    }

    if(FALSE == MPU9250_AppCustomData.TempInitialized)
    {
        if(TempC > -40.0f && TempC < 85.0f)
        {
            MPU9250_AppCustomData.TempInitialized = TRUE;
            MPU9250_AppCustomData.FifoLastTemp = TempC;
        }
    }
    else
    {
        if (fabsf(TempC - MPU9250_AppCustomData.FifoLastTemp) > 2.0f)
        {
            CFE_EVS_SendEvent(MPU9250_DEVICE_ERR_EID, CFE_EVS_ERROR,
                    "Fifo corruption detected. Reset queue.");
            MPU9250_AppCustomData.TempInitialized = FALSE;
            MPU9250_ResetFifo();
            returnBool = FALSE;
            goto end_of_function;
        }
    }

    MPU9250_AppCustomData.FifoLastTemp = TempC;

end_of_function:
    return returnBool;
}
