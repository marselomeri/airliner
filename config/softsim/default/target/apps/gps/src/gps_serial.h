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

#ifndef GPS_SERIAL_H
#define GPS_SERIAL_H
/************************************************************************
** Includes
*************************************************************************/
#include "gps_custom.h"
#include "cfe.h"

#ifdef __cplusplus
extern "C" {
#endif
/************************************************************************
** Local Defines
*************************************************************************/
/** \brief GPS device path. */
#define GPS_SERIAL_DEVICE_PATH                    "/dev/ttyS3"

/** \brief IO speed.
**
**  \par Description:
**       The serial IO speed 38400 baud.
*/
#define GPS_SERIAL_IO_SPEED                       38400

/** \brief Wait time (ms) before read.
**
**  \par Description:
**       ms, wait before reading to save read() calls.
*/
#define GPS_WAIT_BEFORE_READ                      (20)

/** \brief GPS packet timeout (ms).
**
**  \par Description:
**       ms, timeout to receive packet.
*/
#define GPS_PACKET_TIMEOUT                        (2)

/** \brief GPS ack timeout.
**
**  \par Description:
**       ms, timeout to wait for ack.
*/
#define GPS_ACK_TIMEOUT                           (200)



/** \brief GPS read buffer size.
**
**  \par Description:
**       MON_VER from u-blox modules can be ~190 bytes
*/
#define GPS_READ_BUFFER_SIZE                      (250)

/* Message Classes */
/** \brief Configuration input class.
**
**  \par Description:
**       UBX class ID configuration.
*/
#define GPS_MESSAGE_CLASS_CFG                      (0x06)

/* Message IDs */
/** \brief Message ID port configuration.
**
**  \par Description:
**       Message ID for port configuration.
*/
#define GPS_MESSAGE_ID_CFG_PRT                     (0x00)


/* TX CFG-PRT message contents */
/** \brief UART 1 port number.
**
**  \par Description:
**       Port interface number.
*/
#define GPS_TX_CFG_PRT_PORTID                     (0x01)

/** \brief Mode bitfield configuration.
**
**  \par Description:
**       0b0000100011010000: 8N1
*/
#define GPS_TX_CFG_PRT_MODE                       (0x000008D0)

/** \brief Input protocol configuration.
**
**  \par Description:
**       RTCM3 in and UBX in.
*/
#define GPS_TX_CFG_PRT_INPROTOMASK_GPS            ((1<<5) | 0x01)

/** \brief Output protocol configuration.
**
**  \par Description:
**       UBX out.
*/
#define GPS_TX_CFG_PRT_OUTPROTOMASK_GPS           (0x01)

/** \brief USB port number.
**
**  \par Description:
**       Port interface number.
*/
#define UBX_TX_CFG_PRT_PORTID_USB                 (0x03)

/* UBX header contents */
/** \brief Header symbol 1.
**
**  \par Description:
**       UBX header symbol 1.
*/
#define GPS_HEADER_SYNC1_VALUE                    (0xb5)

/** \brief Header symbol 2.
**
**  \par Description:
**       UBX header symbol 2.
*/
#define GPS_HEADER_SYNC2_VALUE                    (0x62)


/* Message Classes & IDs */
#define GPS_MESSAGE_CFG_PRT          ((GPS_MESSAGE_CLASS_CFG) | GPS_MESSAGE_ID_CFG_PRT << 8)
/************************************************************************
** Structure Declarations
*************************************************************************/

/**
 * \brief GPS port configuration payload message.
 */
typedef struct 
{
    /*! Port Identifier Number */
    uint8       portID;
    /*! Reserved */
    uint8       reserved1;
    /*! TX ready PIN configuration */
    uint16      txReady;
    /*! A bit mask describing the UART mode */
    uint32      mode;
    /*! Baud rate in bits/second */
    uint32      baudRate;
    /*! A mask describing which input protocols are active. */
    uint16      inProtoMask;
    /*! A mask describing which output protocols are active. */
    uint16      outProtoMask;
    /*! Flags bit mask */
    uint16      flags;
    /*! Reserved */
    uint16      reserved2;
} GPS_Payload_TX_CFG_PRT_t;

/**
 * \brief GPS UBX protocal header.
 */
typedef struct 
{
    /*! Sync symbol 1 */
    uint8       sync1;
    /*! Sync symbol 1 */
    uint8       sync2;
    /*! Message */
    uint16      msg;
    /*! Message length */
    uint16      length;
} GPS_Header_t;

/**
 * \brief GPS UBX protocal checksum.
 */
typedef struct 
{
    /*! checksum check A*/
    uint8       ck_a;
    /*! checksum check B*/
    uint8       ck_b;
} GPS_Checksum_t;

/**
 * \brief GPS device status
 */
typedef enum
{
    /*! GPS status uninitialized */
    GPS_CUSTOM_UNINITIALIZED  = 0,
    /*! GPS status initialized */
    GPS_CUSTOM_INITIALIZED   = 1
} GPS_Custom_Status_t;


typedef struct
{
    /*! Device file descriptor */
    int                          DeviceFd;
    /*! The current device status */
    GPS_Custom_Status_t          Status;
    /*! The current baud */
    uint32                       Baud;
} GPS_AppCustomData_t;


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
int32 GPS_Ioctl(int fh, int request, void *arg);

/************************************************************************/
/** \brief Determines if the maximum of event filters has been reached.
**
**  \par Description
**       This function checks if an index has reached the maximum
**       number of events.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \param [in]    ind    The current index to check.
**                             
**
**  \returns    boolean
**
*************************************************************************/
boolean GPS_Custom_Max_Events_Not_Reached(int32 ind);


#ifdef __cplusplus
}
#endif 

#endif /* GPS_SERIAL_H */
