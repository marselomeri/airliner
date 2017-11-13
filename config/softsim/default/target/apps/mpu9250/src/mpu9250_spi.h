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

#ifndef MPU9250_SPI_H
#define MPU9250_SPI_H
/************************************************************************
** Includes
*************************************************************************/
#include "mpu9250_custom.h"
#include "cfe.h"

/************************************************************************
** Local Defines
*************************************************************************/
/* MPU 9250 registers */
#define MPU9250_REG_WHOAMI                  (0x75)
#define MPU9250_REG_SMPLRT_DIV              (0x19)
#define MPU9250_REG_CONFIG                  (0x1A)
#define MPU9250_REG_GYRO_CONFIG             (0x1B)
#define MPU9250_REG_ACCEL_CONFIG            (0x1C)
#define MPU9250_REG_ACCEL_CONFIG2           (0x1D)
#define MPU9250_REG_LPACCEL_ODR             (0x1E)
#define MPU9250_REG_WOM_THRESH              (0x1F)
#define MPU9250_REG_FIFO_EN                 (0x23)
#define MPU9250_REG_I2C_MST_CTRL            (0x24)
#define MPU9250_REG_I2C_SLV0_ADDR           (0x25)
#define MPU9250_REG_I2C_SLV0_REG            (0x26)
#define MPU9250_REG_I2C_SLV0_CTRL           (0x27)
#define MPU9250_REG_I2C_SLV1_ADDR           (0x28)
#define MPU9250_REG_I2C_SLV1_REG            (0x29)
#define MPU9250_REG_I2C_SLV1_CTRL           (0x2A)
#define MPU9250_REG_I2C_SLV2_ADDR           (0x2B)
#define MPU9250_REG_I2C_SLV2_REG            (0x2C)
#define MPU9250_REG_I2C_SLV2_CTRL           (0x2D)
#define MPU9250_REG_I2C_SLV3_ADDR           (0x2E)
#define MPU9250_REG_I2C_SLV3_REG            (0x2F)
#define MPU9250_REG_I2C_SLV3_CTRL           (0x30)
#define MPU9250_REG_I2C_SLV4_ADDR           (0x31)
#define MPU9250_REG_I2C_SLV4_REG            (0x32)
#define MPU9250_REG_I2C_SLV4_DO             (0x33)
#define MPU9250_REG_I2C_SLV4_CTRL           (0x34)
#define MPU9250_REG_I2C_SLV4_DI             (0x35)
#define MPU9250_REG_I2C_MST_STATUS          (0x36)
#define MPU9250_REG_INT_PIN_CFG             (0x37)
#define MPU9250_REG_INT_ENABLE              (0x38)
#define MPU9250_REG_INT_STATUS              (0x3A)
#define MPU9250_REG_ACCEL_XOUT_H            (0x3B)
#define MPU9250_REG_ACCEL_XOUT_L            (0x3C)
#define MPU9250_REG_ACCEL_YOUT_H            (0x3D)
#define MPU9250_REG_ACCEL_YOUT_L            (0x3E)
#define MPU9250_REG_ACCEL_ZOUT_H            (0x3F)
#define MPU9250_REG_ACCEL_ZOUT_L            (0x40)
#define MPU9250_REG_TEMP_OUT_H              (0x41)
#define MPU9250_REG_TEMP_OUT_L              (0x42)
#define MPU9250_REG_GYRO_XOUT_H             (0x43)
#define MPU9250_REG_GYRO_XOUT_L             (0x44)
#define MPU9250_REG_GYRO_YOUT_H             (0x45)
#define MPU9250_REG_GYRO_YOUT_L             (0x46)
#define MPU9250_REG_GYRO_ZOUT_H             (0x47)
#define MPU9250_REG_GYRO_ZOUT_L             (0x48)
#define MPU9250_REG_EXT_SENS_DATA_00        (0x49)
#define MPU9250_REG_I2C_SLV0_DO             (0x63)
#define MPU9250_REG_I2C_SLV1_DO             (0x64)
#define MPU9250_REG_I2C_SLV2_DO             (0x65)
#define MPU9250_REG_I2C_SLV3_DO             (0x66)
#define MPU9250_REG_I2C_MST_DELAY_CTRL      (0x67)
#define MPU9250_REG_SIGNAL_PATH_RESET       (0x68)
#define MPU9250_REG_MOT_DETECT_CTRL         (0x69)
#define MPU9250_REG_USER_CTRL               (0x6A)
#define MPU9250_REG_PWR_MGMT_1              (0x6B)
#define MPU9250_REG_PWR_MGMT_2              (0x6C)
#define MPU9250_REG_FIFO_COUNTH             (0x72)
#define MPU9250_REG_FIFO_COUNTL             (0x73)
#define MPU9250_REG_FIFO_R_W                (0x74)

/* Configuration bits mpu9250 */
#define MPU9250_BIT_SLEEP                   (0x40)
#define MPU9250_BIT_H_RESET                 (0x80)
#define MPU9250_BITS_CLKSEL                 (0x07)
#define MPU9250_MPU_CLK_SEL_PLLGYROX        (0x01)
#define MPU9250_MPU_CLK_SEL_PLLGYROZ        (0x03)
#define MPU9250_MPU_EXT_SYNC_GYROX          (0x02)
#define MPU9250_BITS_FS_250DPS              (0x00)
#define MPU9250_BITS_FS_500DPS              (0x08)
#define MPU9250_BITS_FS_1000DPS             (0x10)
#define MPU9250_BITS_FS_2000DPS             (0x18)
#define MPU9250_BITS_FS_2G                  (0x00)
#define MPU9250_BITS_FS_4G                  (0x08)
#define MPU9250_BITS_FS_8G                  (0x10)
#define MPU9250_BITS_FS_16G                 (0x18)
#define MPU9250_BITS_FS_MASK                (0x18)
#define MPU9250_BITS_DLPF_CFG_250HZ         (0x00)
#define MPU9250_BITS_DLPF_CFG_184HZ         (0x01)
#define MPU9250_BITS_DLPF_CFG_92HZ          (0x02)
#define MPU9250_BITS_DLPF_CFG_41HZ          (0x03)
#define MPU9250_BITS_DLPF_CFG_20HZ          (0x04)
#define MPU9250_BITS_DLPF_CFG_10HZ          (0x05)
#define MPU9250_BITS_DLPF_CFG_5HZ           (0x06)
#define MPU9250_BITS_DLPF_CFG_3600HZ        (0x07)
#define MPU9250_BITS_DLPF_CFG_MASK          (0x07)
#define MPU9250_BIT_INT_ANYRD_2CLEAR        (0x10)
#define MPU9250_BIT_RAW_RDY_EN              (0x01)
#define MPU9250_BIT_I2C_IF_DIS              (0x10)

#define MPU9250_READ_FLAG                   (0x80)
#define MPU9250_BIT_RAW_RDY_EN              (0x01)
#define MPU9250_BIT_INT_ANYRD_2CLEAR        (0x10)
#define MPU9250_WHOAMI_9250                 (0x71)
#define MPU9250_AK8963_I2C_ADDR             (0x0c)
#define MPU9250_AK8963_Device_ID            (0x48)

/* Read-only Reg */
#define MPU9250_AK8963_WIA                  (0x00)
#define MPU9250_AK8963_INFO                 (0x01)
#define MPU9250_AK8963_ST1                  (0x02)
#define MPU9250_AK8963_HXL                  (0x03)
#define MPU9250_AK8963_HXH                  (0x04)
#define MPU9250_AK8963_HYL                  (0x05)
#define MPU9250_AK8963_HYH                  (0x06)
#define MPU9250_AK8963_HZL                  (0x07)
#define MPU9250_AK8963_HZH                  (0x08)
#define MPU9250_AK8963_ST2                  (0x09)

/* Write/Read Reg */
#define MPU9250_AK8963_CNTL1                (0x0A)
#define MPU9250_AK8963_CNTL2                (0x0B)
#define MPU9250_AK8963_ASTC                 (0x0C)
#define MPU9250_AK8963_TS1                  (0x0D)
#define MPU9250_AK8963_TS2                  (0x0E)
#define MPU9250_AK8963_I2CDIS               (0x0F)

/* Read-only Reg ( ROM ) */
#define MPU9250_AK8963_ASAX                 (0x10)
#define MPU9250_AK8963_ASAY                 (0x11)
#define MPU9250_AK8963_ASAZ                 (0x12)

/* Masks */
#define MPU9250_ST1_DRDY_MASK               (0x01)
#define MPU9250_ST1_DOR_MASK                (0x02)
#define MPU9250_ST2_BITM_MASK               (0x10)
#define MPU9250_ST2_HOFL_MASK               (0x08)

/** \brief Retry attemps for interrupted ioctl calls.
**
**  \par Limits:
**       None.
*/
#define MPU9250_MAX_RETRY_ATTEMPTS           (2)

/** \brief Sleep time micro seconds for interrupted calls.
**
**  \par Limits:
**       None.
*/
#define MPU9250_MAX_RETRY_SLEEP_USEC         (10)



/************************************************************************
** Structure Declarations
*************************************************************************/
/**
 * \brief MPU9250 device status
 */
typedef enum
{
    /*! MPU9250 status uninitialized */
    MPU9250_CUSTOM_UNINITIALIZED  = 0,
    /*! MPU9250 status initialized */
    MPU9250_CUSTOM_INITIALIZED   = 1
} MPU9250_Custom_Status_t;


typedef struct
{
    /*! Device file descriptor */
    int                             DeviceFd;
    /*! The current device status */
    MPU9250_Custom_Status_t          Status;
} MPU9250_AppCustomData_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Function Prototypes
*************************************************************************/

/************************************************************************/
/** \brief ioctl with limited EINTR retry attempts. 
**
**  \par Description
**       This function is a wrapper for ioctl with retry attempts added.
**
**  \param [in] fh file descriptor.
**  \param [in] request code.
**  \param [in] arg pointer to a device specific struct.
**
**  \returns
**  usually 0 for success and -1 for failure, see ioctl man-page for 
**  more info.
**  \endreturns
**
*************************************************************************/
int32 MPU9250_Ioctl(int fh, int request, void *arg);


int32 MS5611_ResetDevice(void);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif 

#endif /* MPU9250_SPI_H */
