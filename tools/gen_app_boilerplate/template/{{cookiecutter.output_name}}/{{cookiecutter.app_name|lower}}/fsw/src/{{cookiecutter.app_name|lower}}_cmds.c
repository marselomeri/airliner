/*==============================================================================
Copyright (c) 2015, Windhover Labs
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
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

{{cookiecutter.app_name|lower}}_cmds.c
*/

#include "{{cookiecutter.app_name|lower}}_cmds.h"
#include "{{cookiecutter.app_name|lower}}_app.h"

void {{cookiecutter.app_name}}_HousekeepingCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof({{cookiecutter.app_name}}_NoArgsCmd_t); 
    uint16 i;
    
    /* Verify command packet length */
    if ({{cookiecutter.app_name}}_VerifyCmdLength(msg, ExpectedLength))
    {
       /* Get command execution counters */
        {{cookiecutter.app_name}}_AppData.HkPacket.CmdCounter = {{cookiecutter.app_name}}_AppData.CmdCounter;
        {{cookiecutter.app_name}}_AppData.HkPacket.ErrCounter = {{cookiecutter.app_name}}_AppData.ErrCounter;
        
        CFE_EVS_SendEvent({{cookiecutter.app_name}}_PROCCESS_INF_EID,CFE_EVS_INFORMATION, "{{cookiecutter.app_name}}: Hello Housekeeping!");
        
        /* Send housekeeping telemetry packet */
        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &{{cookiecutter.app_name}}_AppData.HkPacket);
        CFE_SB_SendMsg((CFE_SB_Msg_t *) &{{cookiecutter.app_name}}_AppData.HkPacket);

        /* This command does not affect the command execution counter */
    }

    return;

} /* End of {{cookiecutter.app_name}}_HousekeepingCmd() */


void {{cookiecutter.app_name}}_NoopCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof({{cookiecutter.app_name}}_NoArgsCmd_t);

    /* Verify command packet length */
    if ({{cookiecutter.app_name}}_VerifyCmdLength(msg, ExpectedLength))
    {
        {{cookiecutter.app_name}}_AppData.CmdCounter++;

        CFE_EVS_SendEvent({{cookiecutter.app_name}}_NOOP_INF_EID, CFE_EVS_INFORMATION, \
                         "No-op command");
    }

    return;

} /* End of {{cookiecutter.app_name}}_NoopCmd() */


void {{cookiecutter.app_name}}_ResetCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof({{cookiecutter.app_name}}_NoArgsCmd_t); 

    /* Verify command packet length */
    if ({{cookiecutter.app_name}}_VerifyCmdLength(msg, ExpectedLength))
    {
        {{cookiecutter.app_name}}_AppData.CmdCounter = 0;
        {{cookiecutter.app_name}}_AppData.ErrCounter = 0;

        CFE_EVS_SendEvent({{cookiecutter.app_name}}_RESET_INF_EID, CFE_EVS_INFORMATION, \
                         "Reset Counters command received");
    }

    return;

} /* End of {{cookiecutter.app_name}}_ResetCmd() */


void {{cookiecutter.app_name}}_HelloWorldCmd(CFE_SB_MsgPtr_t msg)
{
    uint16 ExpectedLength = sizeof({{cookiecutter.app_name}}_NoArgsCmd_t);

    /* Verify command packet length */
    if ({{cookiecutter.app_name}}_VerifyCmdLength(msg, ExpectedLength))
    {
        CFE_EVS_SendEvent({{cookiecutter.app_name}}_PROCCESS_INF_EID,CFE_EVS_INFORMATION, "{{cookiecutter.app_name}}: Hello World!");
    }

    return;

} /* End of {{cookiecutter.app_name}}_HelloWorldCmd() */


boolean {{cookiecutter.app_name}}_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{
    boolean result = TRUE;
    uint16 ActualLength = CFE_SB_GetTotalMsgLength(msg);

    /* Verify the command packet length */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID = CFE_SB_GetMsgId(msg);
        uint16 CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent({{cookiecutter.app_name}}_LEN_ERR_EID, CFE_EVS_ERROR, \
           "Invalid cmd pkt: ID = 0x%X,  CC = %d, Len = %d", \
                          MessageID, CommandCode, ActualLength);
        result = FALSE;
        {{cookiecutter.app_name}}_AppData.ErrCounter++;
    }

    return(result);

} /* End of {{cookiecutter.app_name}}_VerifyCmdLength() */
