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

#ifndef MS5611_SPI_H
#define MS5611_SPI_H
/************************************************************************
** Includes
*************************************************************************/
#include "ms5611_custom.h"
#include "cfe.h"

/************************************************************************
** Local Defines
*************************************************************************/
#define MS5611_SPI_DEVICE_PATH              "/dev/spidev32766.1"
#define MS5611_SPI_DEVICE_MODE              (3)
#define MS5611_SPI_DEVICE_BITS              (8)
#define MS5611_SPI_DEVICE_SPEED             (1000000)
#define MS5611_SPI_TX_DELAY                 (0)
#define MS5611_SPI_RX_DELAY                 (0)
// SPI Commands
#define MS5611_SPI_CMD_RESET                (0x1e)
#define MS5611_SPI_CMD_CONVERT_D1_MASK      (0x40)
#define MS5611_SPI_CMD_CONVERT_D2_MASK      (0x50)
#define MS5611_SPI_CMD_OSR_256_MASK         (0x00)
#define MS5611_SPI_CMD_OSR_512_MASK         (0x02)
#define MS5611_SPI_CMD_OSR_1024_MASK        (0x04)
#define MS5611_SPI_CMD_OSR_2048_MASK        (0x06)
#define MS5611_SPI_CMD_OSR_4096_MASK        (0x08)
#define MS5611_SPI_CMD_ADC_READ             (0x00)
#define MS5611_SPI_CMD_PROM_READ_MASK       (0xa0)
#define MS5611_SPI_CMD_PROM_ADDR_SHIFT      (1)

#define MS5611_ADDR                         (0xee) /* Module address write mode 1110 1110 bit1=CSB bit0=0 write */
#define MS5611_ADDR_PROM_SETUP              (0xa0)

#define MS5611_SPI_CMD_CONVERT_D1           (MS5611_SPI_CMD_CONVERT_D1_MASK + MS5611_SPI_CMD_OSR_4096_MASK)
#define MS5611_SPI_CMD_CONVERT_D2           (MS5611_SPI_CMD_CONVERT_D2_MASK + MS5611_SPI_CMD_OSR_4096_MASK)

#define MS5611_READ_FLAG                    (0x80)

/** \brief Retry attemps for interrupted ioctl calls.
**
**  \par Limits:
**       None.
*/
#define MS5611_MAX_RETRY_ATTEMPTS           (2)

/** \brief Sleep time micro seconds for interrupted calls.
**
**  \par Limits:
**       None.
*/
#define MS5611_MAX_RETRY_SLEEP_USEC         (10)



/************************************************************************
** Structure Declarations
*************************************************************************/
/**
 * \brief MS5611 device status
 */
typedef enum
{
    /*! MS5611 status uninitialized */
    MS5611_CUSTOM_UNINITIALIZED  = 0,
    /*! RGBLED status initialized */
    MS5611_CUSTOM_INITIALIZED   = 1
} MS5611_Custom_Status_t;


typedef struct
{
    /*! Device file descriptor */
    int                             DeviceFd;
    /*! The current device status */
    MS5611_Custom_Status_t          Status;
} MS5611_AppCustomData_t;


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
int32 MS5611_Ioctl(int fh, int request, void *arg);


int32 MS5611_ResetDevice(void);
uint8 MS5611_ReadReg(uint8 Addr);
void MS5611_DisplayRegisters(void);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif 

#endif /* MS5611_SPI_H */