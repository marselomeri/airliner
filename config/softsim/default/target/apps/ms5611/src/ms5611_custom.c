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
#include "ms5611_spi.h"
#include "cfe.h"
#include "ms5611_events.h"
#include "ms5611_perfids.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/wait.h>
#include <errno.h>

/************************************************************************
** Local Defines
*************************************************************************/

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
    MS5611_DEVICE_ERR_EID = MS5611_EVT_CNT,

/** \brief <tt> 'RGBLED - ' </tt>
**  \event <tt> 'RGBLED - ' </tt>
**  
**  \par Type: Info
**
**  \par Cause:
**
**  This event message is issued when a device successfully complete a
**  self test.
**
*/
    MS5611_DEVICE_INF_EID,
/** \brief Number of custom events 
**
**  \par Limits:
**       int32
*/
    MS5611_CUSTOM_EVT_CNT
} RGBLED_CustomEventIds_t;


/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
struct spi_ioc_transfer MS5611_SPI_Xfer[2];

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


void MS5611_Custom_InitData(void)
{
    
}


boolean MS5611_Custom_Init(void)
{
    
}


boolean MS5611_Custom_Uninit(void)
{
    
}


int32 MS5611_ResetDevice(void)
{
    int ret;

    unsigned char   txBuf[2];
    unsigned char   rxBuf[2];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = MS5611_SPI_CMD_RESET;

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 2;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    return ret;
};


int32 MS5611_WriteReg(uint8 reg, uint8 val)
{
    int ret;

    unsigned char   txBuf[2];
    unsigned char   rxBuf[2];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = reg;

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 2;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    return ret;
}


uint8 MS5611_ReadReg(uint8 Addr)
{
    int ret;

    unsigned char   txBuf[2];
    unsigned char   rxBuf[2];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = Addr | MS5611_READ_FLAG;

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 2;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    /* TODO - Add error checking. */

    return (uint8) rxBuf[1];
};


uint16 MS5611_ReadPROM(uint8 Addr)
{
    int ret;
    uint32 i = 0;

    unsigned char   txBuf[30];
    unsigned char   rxBuf[30];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = MS5611_SPI_CMD_PROM_READ_MASK + (Addr << MS5611_SPI_CMD_PROM_ADDR_SHIFT);

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 30;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    return (rxBuf[1] << 8) + rxBuf[2];
}


void MS5611_D1Conversion(void)
{
    int ret;
    int32 result = 0;

    unsigned char   txBuf[1];
    unsigned char   rxBuf[1];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = MS5611_SPI_CMD_CONVERT_D1;

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 1;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    else
    {
    usleep(20000);
    }
}


void MS5611_D2Conversion(void)
{
    int ret;
    int32 result = 0;

    unsigned char   txBuf[1];
    unsigned char   rxBuf[1];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = MS5611_SPI_CMD_CONVERT_D2;

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 1;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    else
    {
    usleep(20000);
    }
}


int32 MS5611_ReadADCResult(void)
{
    int ret;
    int32 result = 0;
    uint32 i = 0;

    unsigned char   txBuf[30];
    unsigned char   rxBuf[30];

    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));
    txBuf[0] = MS5611_SPI_CMD_ADC_READ;

    MS5611_SPI_Xfer[0].tx_buf = (unsigned long)txBuf;
    MS5611_SPI_Xfer[0].rx_buf = (unsigned long)rxBuf;
    MS5611_SPI_Xfer[0].len = 30;

    ret = RGBLED_Ioctl(MS5611_AppData.FD, SPI_IOC_MESSAGE(1), MS5611_SPI_Xfer);
    if (-1 == ret) 
    {            
        CFE_EVS_SendEvent(MS5611_DEVICE_ERR_EID, CFE_EVS_ERROR,
                        "MS5611 ioctl returned %i", errno);
    }
    result = (rxBuf[1] << 16) + (rxBuf[2] << 8) + rxBuf[3];

    return result;
}

