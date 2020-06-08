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

#include "cfe_es_msg.h"

/* Command messages. */
CFE_ES_Noop_t               CFE_ES_Noop_S;
CFE_ES_ResetCounters_t      CFE_ES_Reset_S;
CFE_ES_Restart_t            CFE_ES_Restart_S;
CFE_ES_Shell_t              CFE_ES_Shell_S;
CFE_ES_QueryAll_t           CFE_ES_QueryAll_S;
CFE_ES_QueryAllTasks_t      CFE_ES_QueryAllTasks_S;
CFE_ES_WriteSyslog_t        CFE_ES_WriteSyslog_S;
CFE_ES_ClearSyslog_t        CFE_ES_ClearSyslog_S;
CFE_ES_WriteERLog_t         CFE_ES_WriteERLog_S;
CFE_ES_ClearERLog_t         CFE_ES_ClearERLog_S;
CFE_ES_OverWriteSyslog_t    CFE_ES_OverWriteSyslog_S;
CFE_ES_ResetPRCount_t       CFE_ES_ResetPRCount_S;
CFE_ES_StartApp_t           CFE_ES_StartApp_S;
CFE_ES_StopApp_t            CFE_ES_StopApp_S;
CFE_ES_RestartApp_t         CFE_ES_RestartApp_S;
CFE_ES_AppNameCmd_t         CFE_ES_AppNameCmd_S;
CFE_ES_ReloadApp_t          CFE_ES_ReloadApp_S;
CFE_ES_QueryOne_t           CFE_ES_QueryOne_S;
CFE_ES_SetMaxPRCount_t      CFE_ES_SetMaxPRCount_S;
CFE_ES_DeleteCDS_t          CFE_ES_DeleteCDS_S;
CFE_ES_StartPerfData_t      CFE_ES_StartPerfData_S;
CFE_ES_StopPerfData_t       CFE_ES_StopPerfData_S;
CFE_ES_SetPerfFilterMask_t  CFE_ES_SetPerfFilterMask_S;
CFE_ES_SetPerfTriggerMask_t CFE_ES_SetPerfTriggerMask_S;
CFE_ES_SendMemPoolStats_t   CFE_ES_SendMemPoolStats_S;
CFE_ES_DumpCDSRegistry_t    CFE_ES_DumpCDSRegistry_S;

/* Telemetry messages. */
CFE_ES_OneAppTlm_t    CFE_ES_OneAppTlm_S;
CFE_ES_PoolStatsTlm_t CFE_ES_PoolStatsTlm_S;
CFE_ES_HkPacket_t     CFE_ES_HkPacket_S;
CFE_ES_ShellPacket_t  CFE_ES_ShellPacket_S;
