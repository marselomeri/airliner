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

#ifndef _VC_APP_H
#define _VC_APP_H
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "vc_msg.h"
#include "vc_events.h"
#include "vc_mission_cfg.h"
#include "vc_platform_cfg.h"
#include "vc_config.h" /* move to platform_cfg */
#include "vc_version.h"
#include "vc_transmit.h"
#include "vc_dev_io.h"

/************************************************************************
** Macro Definitions
*************************************************************************/

/* VC command pipe parameters */
#define VC_PIPE_DEPTH         12 /* Depth of the Command Pipe for Application */

/* VC app specific definitions */
#define VC_SB_PIPE_1_NAME     "VC_CMD_PIPE"

/************************************************************************
** Type Definitions
*************************************************************************/

/**
 * Device status
 */
typedef enum
{
    /*! VC app status uninitialized */
    VC_UNINITIALIZED = 0,
    /*! VC app status uninitialized */
    VC_INITIALIZED   = 1,
    /*! VC app status streaming */
    VC_STREAMING     = 2
} VC_Status_t;

/** 
 *  \brief VC global data structure
 */
typedef struct
{
    /* Command interface counters */
    uint8                 CmdCounter;
    uint8                 ErrCounter;

    /* Housekeeping telemetry packet */
    VC_HkPacket_t         HkPacket;

    /* Operational data (not reported in housekeeping) */
    CFE_SB_MsgPtr_t       MsgPtr;
    CFE_SB_PipeId_t       CmdPipe;

    /* Run Status variable used in the main processing loop */
    uint32                RunStatus;

    /* Initialization data (not reported in housekeeping) */
    char                  PipeName[OS_MAX_API_NAME];
    uint16                PipeDepth;
    CFE_EVS_BinFilter_t   EventTbl[VC_EVT_COUNT];
    
    /* VC app state */
    VC_Status_t           AppState;

} VC_AppData_t;


/************************************************************************/
/** \brief CFS Video Control (VC) application entry point
**
**  \par Description
**       CFS Video control application entry point.  This function
**       performs app initialization, custom transmit and device 
**       initialization, and starts streaming in a child task.
**
**  \par Assumptions, External Events, and Notes:
**       If there is an unrecoverable failure during initialization the
**       main loop is never executed and the application will exit. An
**       error includes all initialization but excludes "start 
**       streaming". If streaming fails to start VC will not exit and 
**       will indicate an initialized state.
**
**
*************************************************************************/
void VC_AppMain(void);


/************************************************************************/
/** \brief Initialize the CFS Video Control (VC) application
**
**  \par Description
**       Video Control application initialization routine. This
**       function performs all the required startup steps to
**       initialize VC data structures, custom device resources,
**       and custom transmit resources, and start streaming video.
**       Init also registers the applications with the cFE services so 
**       it can begin to receive command messages and send events.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS    \endcode
**  \retstmt Return codes from #CFE_ES_RegisterApp          \endcode
**  \retstmt Return codes from #VC_InitPipe                 \endcode
**  \retstmt Return codes from #OS_TaskInstallDeleteHandler \endcode
**  \endreturns
**
*************************************************************************/
int32 VC_AppInit(void);


/************************************************************************/
/** \brief Initialize message pipes
**
**  \par Description
**       This function performs the steps required to setup
**       initialize the cFE Software Bus message pipes and subscribe to
**       messages for the VC application.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_SB_CreatePipe        \endcode
**  \retstmt Return codes from #CFE_SB_SubscribeEx       \endcode
**  \retstmt Return codes from #CFE_SB_Subscribe         \endcode
**  \endreturns
**
*************************************************************************/
void VC_AppPipe(CFE_SB_MsgPtr_t msg);


/************************************************************************/
/** \brief Video Control (VC) cleanup prior to exit
**
**  \par Description
**       This function handles any necessary cleanup prior
**       to application exit.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void VC_CleanupCallback(void);


/************************************************************************
** External Global Variables
*************************************************************************/
extern VC_AppData_t     VC_AppData;


#endif /* _vc_app_ */

