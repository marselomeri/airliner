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

#include "cfe_evs_extern_typedefs.h"
#include "cfe_evs_msg.h"

/* Telemetry messages. */
CFE_EVS_TlmPkt_t              CFE_EVS_TlmPkt_S;
CFE_EVS_Packet_t              CFE_EVS_Packet_S;

/* Command messages. */
CFE_EVS_Noop_t                CFE_EVS_Noop_S;
CFE_EVS_ResetCounters_t       CFE_EVS_ResetCounters_S;
CFE_EVS_EnableEventType_t     CFE_EVS_EnableEventType_S;
CFE_EVS_DisableEventType_t    CFE_EVS_DisableEventType_S;
CFE_EVS_SetEventFormatMode_t  CFE_EVS_SetEventFormatMode_S;
CFE_EVS_EnableAppEventType_t  CFE_EVS_EnableAppEventType_S;
CFE_EVS_DisableAppEventType_t CFE_EVS_DisableAppEventType_S;
CFE_EVS_EnableAppEvents_t     CFE_EVS_EnableAppEvents_S;
CFE_EVS_DisableAppEvents_t    CFE_EVS_DisableAppEvents_S;
CFE_EVS_ResetAppCounter_t     CFE_EVS_ResetAppCounter_S;
CFE_EVS_SetFilter_t           CFE_EVS_SetFilter_S;
CFE_EVS_EnablePorts_t         CFE_EVS_EnablePorts_S;
CFE_EVS_DisablePorts_t        CFE_EVS_DisablePorts_S;
CFE_EVS_ResetFilter_t         CFE_EVS_ResetFilter_S;
CFE_EVS_ResetAllFilters_t     CFE_EVS_ResetAllFilters_S;
CFE_EVS_AddEventFilter_t      CFE_EVS_AddEventFilter_S;
CFE_EVS_DeleteEventFilter_t   CFE_EVS_DeleteEventFilter_S;
CFE_EVS_WriteAppDataFile_t    CFE_EVS_WriteAppDataFile_S;
CFE_EVS_SetLogMode_t          CFE_EVS_SetLogMode_S;
CFE_EVS_ClearLog_t            CFE_EVS_ClearLog_S;
CFE_EVS_WriteLogDataFile_t    CFE_EVS_WriteLogDataFile_S;
