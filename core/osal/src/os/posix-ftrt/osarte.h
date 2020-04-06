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

#ifndef OSARTE_H
#define OSARTE_H

/************************************************************************
** Includes
*************************************************************************/

#include "common_types.h"
#include "ccsds.h"
#include <netinet/in.h>

#ifdef __cplusplus
   extern "C" {
#endif

/************************************************************************
** Defines
*************************************************************************/
#define OS_ARTE_SERVER_IP           "127.0.0.1"
#define OS_ARTE_SERVER_PORT         (9999)
#define OS_ARTE_LOCAL_IP            "0"
#define OS_ARTE_MAX_MESSAGE_LENGTH  (32)

/************************************************************************
** Structure Declarations
*************************************************************************/
/**
 * Connection handle for ARTE server.
 */
typedef struct
{
    /*! ARTE server port */
    uint16              ArtePort;
    /*! ARTE server IP address */
    char                ArteIP[INET_ADDRSTRLEN];
    /*! Socket file descriptor  */
    int                 SocketFd;
    /*! The current sequence count from ARTE server */
    uint16              SequenceCount;
    /*! The current frame count from ARTE server */
    uint16              FrameCount;
    /*! The "ready" telemetry packet to send to ARTE server */
    CCSDS_TlmPkt_t ready_notification;
    /*! The "step" command packet from ARTE server */
    CCSDS_CmdPkt_t step_command;
    /*! A "shutdown" success telemetry packet to send to ARTE server */
    CCSDS_TlmPkt_t shutdown_notification;
    /*! A buffer for receiving step commands from ARTE server */
    char buffer[OS_ARTE_MAX_MESSAGE_LENGTH];
} OS_Arte_Handle_t;

/************************************************************************
** Function Prototypes
*************************************************************************/
/************************************************************************/
/** \brief Initialize data for OSAL ARTE.
**
**  \par Description
**       This function initializes Arte_Handle data.
**
**  \par Assumptions, External Events, and Notes:
**       None.
**
*************************************************************************/
void OS_ArteInitData(void);


/************************************************************************/
/** \brief Initialize a connection to ARTE server.
**
**  \par Description
**       This function connects via a TCP socket to ARTE server and 
**       spawns a thread that pends on receive. 
**
**  \par Assumptions, External Events, and Notes:
**       None.
**
**\returns
**       OS_SUCCESS for success or -1 for failure.
**
*************************************************************************/
int32 OS_ArteInit(void);


/************************************************************************/
/** \brief Send a ready notification to ARTE server.
**
**  \par Description
**       This function sends a CCSDS telemetry packet to ARTE server
**       as a notification that it is ready to proceed to the next 
**       frame. 
**
**  \par Assumptions, External Events, and Notes:
**       A connection must be setup by calling OS_ArteInit before this 
**       this function is called.
**
**\returns
**       TRUE for success or FALSE for failure.
**
*************************************************************************/
boolean OS_ArteSendReady(void);


/************************************************************************/
/** \brief Send a shutdown notification to ARTE server.
**
**  \par Description
**       This function sends a CCSDS telemetry packet to ARTE server
**       with a APID of 1 as a notification that it should shutdown. 
**
**  \par Assumptions, External Events, and Notes:
**       A connection must be setup by calling OS_ArteInit before this 
**       this function is called.
**
**  \param [in]   success, the status to return to ARTE server. TRUE for
**                success, FALSE for failure.
**
**
**\returns
**       TRUE for success or FALSE for failure.
**
*************************************************************************/
boolean OS_ArteSendShutdown(boolean success);


/************************************************************************/
/** \brief Verify the received .
**
**  \par Description
**       This function verifies a CCSDS command packet from ARTE server.
**
**  \par Assumptions, External Events, and Notes:
**       Not yet implemented. 
**
**  \param [in]   buffer, the buffer containing the CCSDS command 
**                packet from ARTE server.
**
**\returns
**       TRUE for success or FALSE for failure.
**
*************************************************************************/
boolean OS_ArteVerifyCommand(char *buffer);


/************************************************************************/
/** \brief Pend on receive and wait for a next step command from ARTE
**         server.
**
**  \par Description
**       This function pends forever on recv waiting for a next step
**       command.
**
**  \par Assumptions, External Events, and Notes:
**       A ready notification must be sent to ARTE server to notify it
**       that a client is passed initialization before waiting for a 
**       next step command.
**
**\returns
**       TRUE for success or FALSE for failure.
**
*************************************************************************/
boolean OS_ArteRecvNextStep(void);


/************************************************************************/
/** \brief Send a ready notification to ARTE server and pend on receive 
**         and wait for a next step command from ARTE server.
**
**  \par Description
**       This function pends forever on recv waiting for a next step
**       command and should be called by OSAL RTM OS_RtmEndFrame.
**
**  \par Assumptions, External Events, and Notes:
**       A connection must be setup by calling OS_ArteInit before this 
**       this function is called.
**
**  \param [in]   sequence, pointer to the sequence count to set.
**  \param [in]   frame, pointer to the frame count to set.
**
**\returns
**       0 for success -1 for failure.
**
*************************************************************************/
int32 OS_ArteStepNext(uint32 *sequence, uint32 *frame);


/************************************************************************/
/** \brief Close and cleanup any allocated resources. 
**
**  \par Description
**       This function should be called on shutdown.
**
**  \par Assumptions, External Events, and Notes:
**       None.
**
**\returns
**       OS_SUCCESS for success or -1 for failure.
**
*************************************************************************/
int32 OS_ArteCleanup(void);


extern OS_Arte_Handle_t Arte_Handle;

#ifdef __cplusplus
   }
#endif

#endif
