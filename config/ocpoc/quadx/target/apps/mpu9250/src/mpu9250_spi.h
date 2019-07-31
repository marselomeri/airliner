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

/** \brief Retry attemps for interrupted ioctl calls. */
#define MPU9250_MAX_RETRY_ATTEMPTS           (2)
/** \brief Sleep time micro seconds for interrupted calls. */
#define MPU9250_MAX_RETRY_SLEEP_USEC         (10)
/** \brief SPI device path. */
#define MPU9250_SPI_DEVICE_PATH              "/dev/spidev1.0"
/** \brief SPI device mode. */
#define MPU9250_SPI_DEVICE_MODE              (3)
/** \brief SPI device bits. */
#define MPU9250_SPI_DEVICE_BITS              (8)
/** \brief SPI device speed. */
#define MPU9250_SPI_DEVICE_SPEED             (1000000)
/** \brief SPI device transmit delay. */
#define MPU9250_SPI_TX_DELAY                 (0)
/** \brief SPI device receive delay. */
#define MPU9250_SPI_RX_DELAY                 (0)
/** \brief SPI transfer maximum buffer size. */
#define MPU9250_SPI_MAX_BUFFER               (512)
/** \brief Array initializer. */
#define MPU9250_INITREGNUM                   (12)
/** \brief Maximum FIFO samples per measurement. */
#define MPU9250_MAX_FIFO_SAMPLES             (10)
/** \brief Configured measurement interval. */
#define MPU9250_MEASURE_INTERVAL_HZ          (1000)

/************************************************************************
** Structure Declarations
*************************************************************************/
/** \brief MPU9250 device status. */
typedef enum
{
    /** \brief MPU9250 status uninitialized. */
    MPU9250_CUSTOM_UNINITIALIZED  = 0,
    /** \brief MPU9250 status initialized. */
    MPU9250_CUSTOM_INITIALIZED   = 1
} MPU9250_Custom_Status_t;


#pragma pack(push, 1)
/** \brief Configured FIFO sample structure. */
typedef struct 
{
    /** \brief Raw accel measurement X. */
    int16 accel_x;
    /** \brief Raw accel measurement Y. */
    int16 accel_y;
    /** \brief Raw accel measurement Z. */
    int16 accel_z;
    /** \brief Raw temperature measurement. */
    int16 temp;
    /** \brief Raw gyro measurement X. */
    int16 gyro_x;
    /** \brief Raw gyro measurement Y. */
    int16 gyro_y;
    /** \brief Raw gyro measurement Z. */
    int16 gyro_z;
    /** \brief Mag status register 1. */
    uint8 mag_st1;
    /** \brief Raw mag measurement X. */
    int16 mag_x;
    /** \brief Raw mag measurement Y. */
    int16 mag_y;
    /** \brief Raw mag measurement Z. */
    int16 mag_z;
    /** \brief Mag status register 2. */
    uint8 mag_st2;
} Fifo_Sample_t;
#pragma pack(pop)


typedef struct
{
    /** \brief Device file descriptor. */
    int                             DeviceFd;
    /** \brief The current device status. */
    MPU9250_Custom_Status_t          Status;
    /** \brief First call flag. */
    boolean                         firstMeasureFlag;
    /** \brief Filtered samples per cycle from the fifo queue. */
    float                           FifoSamplesPerCycle;
    /** \brief Initial fifo temperature sample. */
    float                           FifoTemp;
    /** \brief Last fifo temperature sample. */
    float                           FifoLastTemp;
    /** \brief Temperature initialized flag. */
    boolean                         TempInitialized;
    /** \brief Mag sensitivity adjustment X. */
    uint8                           MagAdjX;
    /** \brief Mag sensitivity adjustment Y. */
    uint8                           MagAdjY;
    /** \brief Mag sensitivity adjustment value Z. */
    uint8                           MagAdjZ;
    /** \brief Current raw samples from the fifo queue. */
    Fifo_Sample_t                   samples[MPU9250_MAX_FIFO_SAMPLES];
    /** \brief Current SPI transfer buffer. */
    uint8                           BufSpi[MPU9250_SPI_MAX_BUFFER];
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
**  \param [in] fh, file descriptor.
**  \param [in] request, code.
**  \param [in] arg, pointer to a device specific struct.
**
**  \returns
**  usually 0 for success and -1 for failure, see ioctl man-page for 
**  more info.
**  \endreturns
**
*************************************************************************/
int32 MPU9250_Ioctl(int fh, int request, void *arg);

/************************************************************************/
/** \brief Byteswap unsigned 16-bit integer. 
**
**  \par Description
**       This function byteswaps a unsigned 16-bit integer.
**
**  \param [in] val, the 16-bit integer to swap.
**
**  \returns
**  The byteswapped 16-bit integer.
**  \endreturns
**
*************************************************************************/
uint16 bswap16(uint16 val);

/************************************************************************/
/** \brief Write to a single 8-bit register.
**
**  \par Description
**       This function writes to a single 8-bit register.
**
**  \param [in] Addr, the address to write to.
**  \param [in/out] Data, the data to write.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_WriteReg(uint8 Addr, uint8 Data);

/************************************************************************/
/** \brief Read a single 8-bit register.
**
**  \par Description
**       This function reads a single 8-bit register.
**
**  \param [in] Addr, the address to read.
**  \param [in/out] returnVal, the pointer to the 8-bit unsigned int to 
**                  write to.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_ReadReg(uint8 Addr, uint8 *returnVal);

/************************************************************************/
/** \brief Read the MPU9250 device ID.
**
**  \par Description
**       This function reads the device ID of the MPU9250.
**
**  \param [in/out] Value, the pointer to the 8-bit unsigned int to 
**                  write to.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_Read_WhoAmI(uint8 *Value);

/************************************************************************/
/** \brief Read the mag sensitivity adjustment values.
**
**  \par Description
**       This function reads the mag sensitivity adjustment values.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_Custom_Read_MagAdj(void);

/************************************************************************/
/** \brief Clear the MPU9250 interrupt.
**
**  \par Description
**       Clear the interrupt.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_Clear_Interrupt(void);

/************************************************************************/
/** \brief Reset the device.
**
**  \par Description
**       Default reset.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
int32 MPU9250_ResetDevice(void);

boolean MPU9250_Custom_Max_Events_Not_Reached(int32 ind);

/************************************************************************/
/** \brief Read a large block of data from the MPU9250.
**
**  \par Description
**       This function reads multiple bytes from the MPU9250.
**
**  \param [in] Addr, the address to read.
**  \param [in/out] Buf, the pointer to the buffer to write to. 
**  \param [in] Len, the number of bytes to read.
**
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_ReadBlock(uint8 Addr, void *Buf, size_t Len);

boolean MPU9250_Custom_MagInit(void);

/************************************************************************/
/** \brief Write to a single 8-bit mag register.
**
**  \par Description
**       This function writes to a single 8-bit mag register.
**
**  \param [in] Addr, the address to write to.
**  \param [in/out] Data, the data to write.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_MagWriteReg(uint8 Addr, uint8 Data);


/************************************************************************/
/** \brief Read a single 8-bit register of the mag.
**
**  \par Description
**       This function reads a single 8-bit mag register.
**
**  \param [in] Addr, the address to read.
**  \param [in/out] returnVal, the pointer to the 8-bit unsigned int to 
**                  write to.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_MagReadReg(uint8 Addr, uint8 *returnVal);

/************************************************************************/
/** \brief Reset the MPU9250 FIFO.
**
**  \par Description
**       Reset the FIFO queue.
** 
**  \returns
**  TRUE for success, FALSE for failure.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_Fifo_Reset(void);

/************************************************************************/
/** \brief Get the byte count from the FIFO queue.
**
**  \par Description
**       Get the number of bytes currently in the FIFO queue.
** 
**  \returns
**  The number of bytes in the FIFO queue.
**  \endreturns
**
*************************************************************************/
uint16 MPU9250_GetFifoCount(void);

/************************************************************************/
/** \brief Run sanity checks on a single FIFO measurement.
**
**  \par Description
**       Check min/max values to detect saturation and large temperature
**       changes to detect FIFO corruption which will result in a FIFO
**       reset.
** 
**  \param [in/out] Pointer to the sample the check.
**
**  \returns
**  TRUE to pass, FALSE if FIFO corruption detected.
**  \endreturns
**
*************************************************************************/
boolean MPU9250_sampleChecks(MPU9250_Measurement_t *sample);

#endif /* MPU9250_SPI_H */
