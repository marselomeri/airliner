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

#include "cfe_sb_msg.h"

/* Command messages. */
CFE_SB_Noop_t                CFE_SB_Noop_S;
CFE_SB_ResetCounters_t       CFE_SB_ResetCounters_S;
CFE_SB_SendSbStats_t         CFE_SB_SendSbStats_S;
CFE_SB_SendRoutingInfo_t     CFE_SB_SendRoutingInfo_S;
CFE_SB_EnableRoute_t         CFE_SB_EnableRoute_S;
CFE_SB_DisableRoute_t        CFE_SB_DisableRoute_S;
CFE_SB_SendPipeInfo_t        CFE_SB_SendPipeInfo_S;
CFE_SB_SendMapInfo_t         CFE_SB_SendMapInfo_S;
CFE_SB_SendPrevSubs_t        CFE_SB_SendPrevSubs_S;
CFE_SB_EnableSubReporting_t  CFE_SB_EnableSubReporting_S;
CFE_SB_DisableSubReporting_t CFE_SB_DisableSubReporting_S;

/* Telemetry messages. */
CFE_SB_PrevSubMsg_t          CFE_SB_PrevSubMsg_S;
CFE_SB_SubRprtMsg_t          CFE_SB_SubRprtMsg_S;
CFE_SB_HKMsg_t               CFE_SB_HKMsg_S;
CFE_SB_StatMsg_t             CFE_SB_StatMsg_S;
