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
#define GPS_SERIAL_IO_SPEED                       B38400

/************************************************************************
** Structure Declarations
*************************************************************************/
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
    int                             DeviceFd;
    /*! The current device status */
    GPS_Custom_Status_t          Status;
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
