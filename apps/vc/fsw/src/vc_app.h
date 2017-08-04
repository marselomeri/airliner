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

#ifndef _vc_app_
#define _vc_app_

#include "cfe.h"
#include "vc_msg.h"
#include "vc_events.h"
#include "vc_mission_cfg.h"
#include "vc_platform_cfg.h"
#include "vc_config.h" /* move to platform_cfg */
#include "vc_version.h"
#include "vc_transmit.h"
#include "vc_dev_io.h"

/* VC command pipe parameters */
#define VC_PIPE_DEPTH         12 /* Depth of the Command Pipe for Application */

/* VC app specific definitions */
#define VC_SB_PIPE_1_NAME     "VC_CMD_PIPE"

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
    CFE_EVS_BinFilter_t      EventFilters[VC_EVT_COUNT];

} VC_AppData_t;


/**
 * \brief VC application entry point and main process loop
 */
void VC_AppMain(void);


/**
 * \brief VC app initialization
 */
int32 VC_AppInit(void);


/**
 * \brief Process command pipe message
 */
void VC_AppPipe(CFE_SB_MsgPtr_t msg);

/* Exported Data */
extern VC_AppData_t     VC_AppData;


#endif /* _vc_app_ */

