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

#include "cfe_time_msg.h"

/* Telemetry messages. */
CFE_TIME_HkPacket_t          CFE_TIME_HkPacket_S;
CFE_TIME_DiagPacket_t        CFE_TIME_DiagPacket_S;

/* Command messages. */
CFE_TIME_Noop_t              CFE_TIME_Noop_S;
CFE_TIME_ResetCounters_t     CFE_TIME_ResetCounters_S;
CFE_TIME_SendDiagnosticTlm_t CFE_TIME_SendDiagnosticTlm_S;
CFE_TIME_SetState_t          CFE_TIME_SetState_S;
CFE_TIME_SetSource_t         CFE_TIME_SetSource_S;
CFE_TIME_SetSignal_t         CFE_TIME_SetSignal_S;
CFE_TIME_AddDelay_t          CFE_TIME_AddDelay_S;
CFE_TIME_SubDelay_t          CFE_TIME_SubDelay_S;
CFE_TIME_SetTime_t           CFE_TIME_SetTime_S;
CFE_TIME_SetMET_t            CFE_TIME_SetMET_S;
CFE_TIME_SetSTCF_t           CFE_TIME_SetSTCF_S;
CFE_TIME_SetLeapSeconds_t    CFE_TIME_SetLeapSeconds_S;
CFE_TIME_AddAdjust_t         CFE_TIME_AddAdjust_S;
CFE_TIME_SubAdjust_t         CFE_TIME_SubAdjust_S;
CFE_TIME_Add1HZAdjustment_t  CFE_TIME_Add1HZAdjustment_S;
CFE_TIME_Sub1HZAdjustment_t  CFE_TIME_Sub1HZAdjustment_S;











