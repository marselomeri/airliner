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
#include "mpu9250_map.h"

/************************************************************************
** Local Defines
*************************************************************************/

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

#define MPU9250_SPI_DEVICE_PATH              "/dev/spidev1.0"
#define MPU9250_SPI_DEVICE_MODE              (3)
#define MPU9250_SPI_DEVICE_BITS              (8)
#define MPU9250_SPI_DEVICE_SPEED             (1000000)
#define MPU9250_SPI_TX_DELAY                 (0)
#define MPU9250_SPI_RX_DELAY                 (0)
#define MPU9250_SPI_MAX_BUFFER               (128)

/** \brief Array initializer. */
#define MPU_InitRegNum                       (13)

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
    uint8                           MagAdjX;
    uint8                           MagAdjY;
    uint8                           MagAdjZ;
    uint8                           BufSpi[MPU9250_SPI_MAX_BUFFER];
} MPU9250_AppCustomData_t;


#pragma pack(push, 1)
typedef struct 
{
    int16 accel_x;
    int16 accel_y;
    int16 accel_z;
    int16 temp;
    int16 gyro_x;
    int16 gyro_y;
    int16 gyro_z;
    uint8 mag_st1;
    int16 mag_x;
    int16 mag_y;
    int16 mag_z;
    uint8 mag_st2;
} Fifo_Sample_t;
#pragma pack(pop)

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

boolean MPU9250_I2C_Master_Reset(void);
boolean MPU9250_Clear_Interrupt(void);
int32 MPU9250_ResetDevice(void);
boolean MPU9250_WriteReg(uint8 Addr, uint8 Data);
boolean MPU9250_Custom_Max_Events_Not_Reached(int32 ind);
boolean MPU9250_ReadBlock(uint8 Addr, void *Buf, size_t Len);

boolean MPU9250_Custom_MagInit(void);
boolean MPU9250_MagWriteReg(uint8 Addr, uint8 Data);
boolean MPU9250_MagReadReg(uint8 Addr, uint8 *returnVal);
boolean MPU9250_Fifo_Reset(void);

#endif /* MPU9250_SPI_H */
