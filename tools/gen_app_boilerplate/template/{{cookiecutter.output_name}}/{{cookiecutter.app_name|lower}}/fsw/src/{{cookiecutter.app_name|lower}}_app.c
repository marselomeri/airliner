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

{{cookiecutter.app_name|lower}}_app.c
*/

#include "{{cookiecutter.app_name|lower}}_app.h"
#include "{{cookiecutter.app_name|lower}}_cmds.h"
#include "{{cookiecutter.app_name|lower}}_msgids.h"
#include "{{cookiecutter.app_name|lower}}_perfids.h"
#include <string.h>

{{cookiecutter.app_name}}_AppData_t {{cookiecutter.app_name}}_AppData;

void {{cookiecutter.app_name}}_AppMain(void)
{
    int32 Status = CFE_SUCCESS;
   
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Create the first Performance Log entry */
    CFE_ES_PerfLogEntry({{cookiecutter.app_name}}_APPMAIN_PERF_ID); 
   
    /* Perform application specific initialization */
    Status = {{cookiecutter.app_name}}_AppInit();
   
    if (Status != CFE_SUCCESS)
    {
        {{cookiecutter.app_name}}_AppData.RunStatus = CFE_ES_APP_ERROR;
    }
   
   /* Application main loop */
    while(CFE_ES_RunLoop(&{{cookiecutter.app_name}}_AppData.RunStatus) == TRUE)
    {
        /* Performance Log exit stamp */
        CFE_ES_PerfLogExit({{cookiecutter.app_name}}_APPMAIN_PERF_ID);
        
        /* Wait for the next Software Bus message */
        Status = CFE_SB_RcvMsg(&{{cookiecutter.app_name}}_AppData.MsgPtr, {{cookiecutter.app_name}}_AppData.CmdPipe, {{cookiecutter.app_name}}_SB_TIMEOUT);

        /* Performance Log Entry Stamp */
        CFE_ES_PerfLogEntry({{cookiecutter.app_name}}_APPMAIN_PERF_ID);

        if (Status == CFE_SUCCESS)
        {
            /*
             * Process Software Bus message. If there are fatal errors
             * in command processing the command can alter the global
             * RunStatus variable to exit the main event loop.
             */
            {{cookiecutter.app_name}}_AppPipe({{cookiecutter.app_name}}_AppData.MsgPtr);
        }
        else
        {
           /* 
            * This is an example of exiting on an error.
            * Note that a SB read error is not always going to
            * result in an app quitting.
            */
            CFE_EVS_SendEvent({{cookiecutter.app_name}}_PIPE_ERR_EID, CFE_EVS_ERROR, \
                              "SB Pipe Read Error, {{cookiecutter.app_name}} App will exit. RC = 0x%08X", (unsigned int)Status);

            {{cookiecutter.app_name}}_AppData.RunStatus = CFE_ES_APP_ERROR;
        }

   } /* end CFS_ES_RunLoop while */
   
   /* Performance Log exit stamp */
   CFE_ES_PerfLogExit({{cookiecutter.app_name}}_APPMAIN_PERF_ID);
   
   /* Exit the application */
   CFE_ES_ExitApp({{cookiecutter.app_name}}_AppData.RunStatus);
} /* end {{cookiecutter.app_name}}_AppMain */


int32 {{cookiecutter.app_name}}_AppInit(void)
{
    int32  Status = CFE_SUCCESS;

    /* Setup the RunStatus variable */
    {{cookiecutter.app_name}}_AppData.RunStatus = CFE_ES_APP_RUN;

    /* Initialize app command execution counters */
    {{cookiecutter.app_name}}_AppData.CmdCounter = 0;
    {{cookiecutter.app_name}}_AppData.ErrCounter = 0;

    /* Initialize app configuration data */
    strcpy({{cookiecutter.app_name}}_AppData.PipeName, {{cookiecutter.app_name}}_SB_PIPE_1_NAME);

    {{cookiecutter.app_name}}_AppData.PipeDepth = {{cookiecutter.app_name}}_PIPE_DEPTH;

    /* Register event filter table */
    Status = CFE_EVS_Register(NULL, 0, CFE_EVS_BINARY_FILTER);

    if (Status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("{{cookiecutter.app_name}} App: Error Registering Events, RC = 0x%08X\n", (unsigned int)Status);
        return (Status);
    }
    /* Initialize housekeeping packet (clear user data area) */
    CFE_SB_InitMsg(&{{cookiecutter.app_name}}_AppData.HkPacket, {{cookiecutter.app_name}}_HK_TLM_MID, sizeof({{cookiecutter.app_name}}_HkPacket_t), TRUE);

    /* Create Software Bus message pipe */
    Status = CFE_SB_CreatePipe(&{{cookiecutter.app_name}}_AppData.CmdPipe, {{cookiecutter.app_name}}_AppData.PipeDepth, {{cookiecutter.app_name}}_AppData.PipeName);
    
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent({{cookiecutter.app_name}}_PIPE_ERR_EID, CFE_EVS_ERROR, \
                              "SB Pipe Creation Error, {{cookiecutter.app_name}} App will exit. RC = 0x%08X", (unsigned int)Status);
    return (Status);
    }
    
    /* Subscribe to Housekeeping request commands */
    Status = CFE_SB_Subscribe({{cookiecutter.app_name}}_SEND_HK_MID, {{cookiecutter.app_name}}_AppData.CmdPipe);

    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent({{cookiecutter.app_name}}_PIPE_ERR_EID, CFE_EVS_ERROR, \
                            "Error Subscribing to HK Request, {{cookiecutter.app_name}} App will exit. RC = 0x%08X", (unsigned int)Status);
        return (Status);
    }
    
    /* Subscribe to {{cookiecutter.app_name}} ground command packets */
    Status = CFE_SB_Subscribe({{cookiecutter.app_name}}_CMD_MID, {{cookiecutter.app_name}}_AppData.CmdPipe);
    if (Status != CFE_SUCCESS)
    {
       CFE_EVS_SendEvent({{cookiecutter.app_name}}_PIPE_ERR_EID, CFE_EVS_ERROR, \
                            "Error Subscribing to {{cookiecutter.app_name}} Command, {{cookiecutter.app_name}} App will exit. RC = 0x%08X", (unsigned int)Status);
       return (Status);
    }
    
    /* Application startup event message */
    CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_INF_EID, CFE_EVS_INFORMATION, "{{cookiecutter.app_name}}: Application Initialized");
                         
    return(CFE_SUCCESS);

}

void {{cookiecutter.app_name}}_AppPipe(CFE_SB_MsgPtr_t msg)
{
    CFE_SB_MsgId_t MessageID = 0;
    uint16 CommandCode = 0;

    MessageID = CFE_SB_GetMsgId(msg);
    switch (MessageID)
    {
        /* Housekeeping telemetry request */
        case {{cookiecutter.app_name}}_SEND_HK_MID:
            {{cookiecutter.app_name}}_HousekeepingCmd(msg);
            break;

        /* {{cookiecutter.app_name}} ground commands */
        case {{cookiecutter.app_name}}_CMD_MID:

            CommandCode = CFE_SB_GetCmdCode(msg);
            switch (CommandCode)
            {
                case {{cookiecutter.app_name}}_NOOP_CC:
                    {{cookiecutter.app_name}}_NoopCmd(msg);
                    break;

                case {{cookiecutter.app_name}}_RESET_CC:
                    {{cookiecutter.app_name}}_ResetCmd(msg);
                    break; 

                case {{cookiecutter.app_name}}_HELLOWORLD_CC: 
                    {{cookiecutter.app_name}}_HelloWorldCmd(msg); 
                    break;

                default:
                    CFE_EVS_SendEvent({{cookiecutter.app_name}}_CC1_ERR_EID, CFE_EVS_ERROR, \
                    "Invalid ground command code: ID = 0x%X, CC = %d", \
                                    MessageID, CommandCode);
                    break;
            }
            break;

        default:
            {{cookiecutter.app_name}}_AppData.ErrCounter++;
            CFE_EVS_SendEvent({{cookiecutter.app_name}}_MID_ERR_EID, CFE_EVS_ERROR,
                            "Invalid command pipe message ID: 0x%X",
                            MessageID);
            break;
    }

    return;

} /* End of {{cookiecutter.app_name}}_AppPipe() */

