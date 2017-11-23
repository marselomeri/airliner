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

#ifndef RCIN_SBUS_H
#define RCIN_SBUS_H

/************************************************************************
** Includes
*************************************************************************/
#include "rcin_custom.h"
#include "px4_msgs.h"

#include <asm-generic/termbits.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif
/************************************************************************
** Local Defines
*************************************************************************/
/** \brief I2C slave address of the TCA62724FMG LED driver in hex.
**
**  \par Description:
**       8-bit address in little-endian format is 1010101(R/W) where R/W
**       bit-0 indicates read (bit set to "H") or write mode (bit set to 
**       "L"). This is the 7-bit address without the R/W bit.
*/
#define RGBLED_I2C_ADDRESS              (0x55)

/** \brief Device path.
**
**  \par Description:
**       The serial interface device path.
*/
#define RCIN_DEVICE_PATH                "/dev/ttyS2"

/** \brief Input speed.
**
**  \par Description:
**       The serial input speed.
*/
#define RCIN_SERIAL_INPUT_SPEED         (100000)

/** \brief Output speed.
**
**  \par Description:
**       The serial ouput speed.
*/
#define RCIN_SERIAL_OUTPUT_SPEED        (100000)

/** \brief Size of the raw RCIN message block.
**
**  \par Description:
**       The size of 
*/
#define RCIN_SERIAL_READ_SIZE           (25)

/** \brief Serial c_cc VMIN setting.
**
**  \par Description:
**       Minimum number of characters for noncanonical read (MIN).
*/
#define RCIN_SERIAL_VMIN_SETTING        RCIN_SERIAL_READ_SIZE

/** \brief Serial c_cc VTIME setting.
**
**  \par Description:
**       Timeout in deciseconds for noncanonical read (TIME).
*/
#define RCIN_SERIAL_VTIME_SETTING       (0)

/** \brief SBUS channels
**
**  \par Description:
**       The SBUS channel count.
*/
#define RCIN_SBUS_CHANNEL_COUNT         (10)

/* define range mapping here, -+100% -> 1000..2000 */
#define RCIN_SBUS_RANGE_MIN             (200.0f)
#define RCIN_SBUS_RANGE_MAX             (1800.0f)
#define RCIN_SBUS_TARGET_MIN            (1000.0f)
#define RCIN_SBUS_TARGET_MAX            (2000.0f)
/* pre-calculate the floating point stuff as far as possible at compile time */
#define RCIN_SBUS_SCALE_FACTOR ((RCIN_SBUS_TARGET_MAX - RCIN_SBUS_TARGET_MIN) / (RCIN_SBUS_RANGE_MAX - RCIN_SBUS_RANGE_MIN))
#define RCIN_SBUS_SCALE_OFFSET (int)(RCIN_SBUS_TARGET_MIN - (RCIN_SBUS_SCALE_FACTOR * RCIN_SBUS_RANGE_MIN + 0.5f))


/** \brief Max device path.
**
**  \par Description:
**       None.
*/
#define RCIN_MAX_DEVICE_PATH          OS_MAX_LOCAL_PATH_LEN

/** \brief Retry attemps for interrupted ioctl calls.
**
**  \par Limits:
**       None.
*/
#define RCIN_MAX_RETRY_ATTEMPTS         (2)

/** \brief Sleep time micro seconds for interrupted calls.
**
**  \par Limits:
**       None.
*/
#define RCIN_MAX_RETRY_SLEEP_USEC       (10)
/* Timeout settings */

/** \brief Wait time for data in seconds.
**
**  \par Limits:
**       None.
*/
#define RCIN_BUFFER_FILL_TIMEOUT_SEC    (0)

/** \brief Wait time for data in microseconds.
**
**  \par Limits:
**       None.
*/
#define RCIN_BUFFER_FILL_TIMEOUT_USEC   (14000)

/** \brief Streaming task priority
**
**  \par Limits:
**       0 to MAX_PRIORITY (usually 255)
*/
#define RCIN_STREAMING_TASK_PRIORITY    (50)

/** \brief RCIN shared data mutex name. */
#define RCIN_MUTEX_NAME                "RCIN_MUTEX"

/** \brief Streaming task name
**
**  \par Limits:
**       OS_MAX_API_NAME
*/
#define RCIN_STREAMING_TASK_NAME       "RCIN_STREAM"

/************************************************************************
** Structure Declarations
*************************************************************************/

/**
 * \brief Device status
 */
typedef enum
{
    /*! Status uninitialized */
    RCIN_CUSTOM_UNINITIALIZED   = 0,
    /*! Status initialized */
    RCIN_CUSTOM_INITIALIZED     = 1,
    /*! Status initialized */
    RCIN_CUSTOM_ENABLED         = 2,
    /*! Status not streaming */
    RCIN_CUSTOM_NOTSTREAMING    = 3,
    /*! Status streaming */
    RCIN_CUSTOM_STREAMING       = 4,
    /*! Status out of sync */
    RCIN_OUT_OF_SYNC            = 5
} RCIN_Custom_Status_t;


/**
 * \brief Device status
 */
typedef enum
{
    /*! State unknown */
    RCIN_PARSER_STATE_UNKNOWN             = 0,
    /*! State waiting for header  */
    RCIN_PARSER_STATE_WAITING_FOR_HEADER  = 1,
    /*! State waiting for data1  */
    RCIN_PARSER_STATE_WAITING_FOR_DATA1   = 2,
    RCIN_PARSER_STATE_WAITING_FOR_DATA2   = 3,
    RCIN_PARSER_STATE_WAITING_FOR_DATA3   = 4,
    RCIN_PARSER_STATE_WAITING_FOR_DATA4   = 5,
    RCIN_PARSER_STATE_WAITING_FOR_DATA5   = 6,
    RCIN_PARSER_STATE_WAITING_FOR_DATA6   = 7,
    RCIN_PARSER_STATE_WAITING_FOR_DATA7   = 8,
    RCIN_PARSER_STATE_WAITING_FOR_DATA8   = 9,
    RCIN_PARSER_STATE_WAITING_FOR_DATA9   = 10,
    RCIN_PARSER_STATE_WAITING_FOR_DATA10  = 11,
    RCIN_PARSER_STATE_WAITING_FOR_DATA11  = 12,
    RCIN_PARSER_STATE_WAITING_FOR_DATA12  = 13,
    RCIN_PARSER_STATE_WAITING_FOR_DATA13  = 14,
    RCIN_PARSER_STATE_WAITING_FOR_DATA14  = 15,
    RCIN_PARSER_STATE_WAITING_FOR_DATA15  = 16,
    RCIN_PARSER_STATE_WAITING_FOR_DATA16  = 17,
    RCIN_PARSER_STATE_WAITING_FOR_DATA17  = 18,
    RCIN_PARSER_STATE_WAITING_FOR_DATA18  = 19,
    RCIN_PARSER_STATE_WAITING_FOR_DATA19  = 20,
    RCIN_PARSER_STATE_WAITING_FOR_DATA20  = 21,
    RCIN_PARSER_STATE_WAITING_FOR_DATA21  = 22,
    RCIN_PARSER_STATE_WAITING_FOR_DATA22  = 23,
    RCIN_PARSER_STATE_WAITING_FOR_FLAGS   = 24,
    /*! State waiting for footer  */
    RCIN_PARSER_STATE_WAITING_FOR_FOOTER  = 25
} RCIN_Custom_ParserState_t;


typedef struct
{
    /*! Device file descriptor */
    int                             DeviceFd;
    /*! Path to device */
    char                            DevName[RCIN_MAX_DEVICE_PATH];
    /*! The terminal configuration */
    struct termios2                 TerminalConfig;
    /*! The current device status */
    RCIN_Custom_Status_t            Status;
    /*! The current device parser state */
    RCIN_Custom_ParserState_t       ParserState;
    /*! Flag to start and stop streaming */
    boolean                         ContinueFlag;
    /*! Streaming task priority */
    uint8                           Priority;
    /*! Streaming child task identifier */
    uint32                          ChildTaskID;
    /*! Streaming task function pointer */
    CFE_ES_ChildTaskMainFuncPtr_t   StreamingTask;
    /*! RCInput message for storing SBUS data */
    PX4_InputRcMsg_t                Measure;
    /*! The shared data mutex */
    uint32                          Mutex;
    /*! Current raw SBUS data */
    uint8 sbusData[RCIN_SERIAL_READ_SIZE];
} RCIN_AppCustomData_t;


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
int32 RCIN_Ioctl(int fh, int request, void *arg);


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
boolean RCIN_Custom_Max_Events_Not_Reached(int32 ind);

CFE_TIME_SysTime_t RCIN_Custom_Get_Time(void);

void RCIN_Stream_Task(void);

void RCIN_Custom_Read(void);

void RCIN_Custom_SetDefaultValues(void);

//void RCIN_Custom_Sync(void);

boolean RCIN_Custom_Validate(uint8 *data, int size);

boolean RCIN_Custom_PWM_Translate(uint8 *data, int size);

#ifdef __cplusplus
}
#endif 

#endif /* RCIN_SBUS_H */
