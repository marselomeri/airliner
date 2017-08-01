/*==============================================================================
Copyright (c) 2017, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of CmdIn nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY VCPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, VCEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @defgroup Config
 * @addtogroup Config
 * @file vc_config.h
 * @brief Configuration settings for Video Controller
 * @{
 */

#ifndef VC_CONFIG_H
#define VC_CONFIG_H

/* Custom Settings */

/*! Max channels allowed */
#define VC_MAX_OUTPUT_CHANNELS          5
/*! Max characters of an IP address */
#define INET_ADDRSTRLEN                 15

/* Camera settings */

/*! Video resolution width */
#define VC_FRAME_WIDTH                  320
/*! Video resolution height */
#define VC_FRAME_HEIGHT                 180
/*! Video frame rate */
#define VC_FRAMERATE                    30
/*! Video camera device path */
#define VC_DEVICE_PATH                  "/dev/video0"


/* Ground system settings */

/*! Ground system ip address */
#define VC_DESTINATION_IP               "10.10.0.12"
/*! Ground system port */
#define VC_DESTINATION_PORT             3000
/*! Source system ip address */
#define VC_SOURCE_IP                    "0"
/*! Source system port */
#define VC_SOURCE_PORT                  0

/* V4L settings */

/*! V4L streaming io method */
#define VC_V4L_IO_METHOD                V4L2_MEMORY_USERPTR
/*! V4L buffer type */
#define VC_V4L_BUFFER_TYPE              V4L2_BUF_TYPE_VIDEO_CAPTURE
/*! V4L video format */
#define VC_V4L_VIDEO_FORMAT             V4L2_PIX_FMT_MJPEG 
/*! V4L field order */
#define VC_V4L_VIDEO_FIELD_ORDER        V4L2_FIELD_NONE 


/* Timeout settings */

/*! Wait time for camera data in seconds */
#define VC_BUFFER_FILL_TIMEOUT_SEC      2
/*! Wait time for camera data in microseconds */
#define VC_BUFFER_FILL_TIMEOUT_USEC     0

#endif

/* @} */
