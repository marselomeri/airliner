/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "{{cookiecutter.app_name|lower}}_app.h"
#include "{{cookiecutter.app_name|lower}}_msg.h"
#include "{{cookiecutter.app_name|lower}}_version.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
{{cookiecutter.app_name}} o{{cookiecutter.app_name}};



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
{{cookiecutter.app_name}}::{{cookiecutter.app_name}}()
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
{{cookiecutter.app_name}}::~{{cookiecutter.app_name}}()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 {{cookiecutter.app_name}}::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("{{cookiecutter.app_name}} - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 {{cookiecutter.app_name}}::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    		{{cookiecutter.app_name}}_SCH_PIPE_DEPTH,
			{{cookiecutter.app_name}}_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx({{cookiecutter.wakeup_mid_macro}}, SchPipeId, CFE_SB_Default_Qos, {{cookiecutter.wakeup_mid_macro}}_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
            		"Sch Pipe failed to subscribe to {{cookiecutter.wakeup_mid_macro}}. (0x%08lX)",
                    iStatus);
            goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx({{cookiecutter.app_name}}_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, {{cookiecutter.app_name}}_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to {{cookiecutter.app_name}}_SEND_HK_MID. (0x%08X)",
					 (unsigned int)iStatus);
            goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
        }
    {% for dict,message in cookiecutter.input_messages.iteritems() %}
        iStatus = CFE_SB_SubscribeEx({{message.mid_macro}}, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to {{message.mid_macro}}. (0x%08lX)",
					 iStatus);
            goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
        }
    {% endfor %}
    }
    else
    {
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create SCH pipe (0x%08lX)",
			 iStatus);
        goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    		{{cookiecutter.app_name}}_CMD_PIPE_DEPTH,
			{{cookiecutter.app_name}}_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe({{cookiecutter.app_name}}_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
				 "CMD Pipe failed to subscribe to {{cookiecutter.app_name}}_CMD_MID. (0x%08lX)",
				 iStatus);
            goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create CMD pipe (0x%08lX)",
			 iStatus);
        goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
    }

{{cookiecutter.app_name}}_InitPipe_Exit_Tag:
    return iStatus;
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void {{cookiecutter.app_name}}::InitData()
{
  {% for dict, message in cookiecutter.output_messages.iteritems() %}
    /* Init actuator outputs message */
    CFE_SB_InitMsg(&ActuatorOutputs,
            PX4_ACTUATOR_OUTPUTS_MID, sizeof(ActuatorOutputs), TRUE);

    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
    		{{cookiecutter.app_name}}_HK_TLM_MID, sizeof(HkTlm), TRUE);
        iStatus = CFE_SB_SubscribeEx({{message.mid_macro}}, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to {{message.mid_macro}}. (0x%08lX)",
					 iStatus);
            goto {{cookiecutter.app_name}}_InitPipe_Exit_Tag;
        }
  {% endfor %}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* {{cookiecutter.app_name}} initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 {{cookiecutter.app_name}}::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("{{cookiecutter.app_name}} - Failed to init events (0x%08lX)\n", iStatus);
        goto {{cookiecutter.app_name}}_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto {{cookiecutter.app_name}}_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto {{cookiecutter.app_name}}_InitApp_Exit_Tag;
    }

{{cookiecutter.app_name}}_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
								 {{cookiecutter.app_name}}_MAJOR_VERSION,
								 {{cookiecutter.app_name}}_MINOR_VERSION,
								 {{cookiecutter.app_name}}_REVISION,
								 {{cookiecutter.app_name}}_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("{{cookiecutter.app_name}} - Application failed to initialize\n");
        }
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 {{cookiecutter.app_name}}::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit({{cookiecutter.app_name}}_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry({{cookiecutter.app_name}}_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case {{cookiecutter.wakeup_mid_macro}}:
                /* TODO:  Do something here. */
                break;

            case {{cookiecutter.app_name}}_SEND_HK_MID:
                ReportHousekeeping();
                break;


		{% for dict, message in cookiecutter.input_messages.iteritems() %}
            case {{message.mid_macro}}:
                memcpy(&CVT.{{message.var_name}}, MsgPtr, sizeof(CVT.{{message.var_name}}));
                break;
		{% endfor %}

            default:
                (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_MSGID_ERR_EID, CFE_EVS_ERROR,
                     "Recvd invalid SCH msgId (0x%04X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else
    {
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void {{cookiecutter.app_name}}::ProcessCmdPipe()
{
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages until the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case {{cookiecutter.app_name}}_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid CMD msgId (0x%04X)", (unsigned short)CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process {{cookiecutter.app_name}} Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void {{cookiecutter.app_name}}::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case {{cookiecutter.app_name}}_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CMD_NOOP_EID, CFE_EVS_INFORMATION,
					"Recvd NOOP. Version %d.%d.%d.%d",
					{{cookiecutter.app_name}}_MAJOR_VERSION,
					{{cookiecutter.app_name}}_MINOR_VERSION,
					{{cookiecutter.app_name}}_REVISION,
					{{cookiecutter.app_name}}_MISSION_REV);
                break;

            case {{cookiecutter.app_name}}_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send {{cookiecutter.app_name}} Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void {{cookiecutter.app_name}}::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
{% for dict, message in cookiecutter.output_messages.iteritems() %}
void {{cookiecutter.app_name}}::Send{{message.var_name}}()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&{{message.var_name}});
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&{{message.var_name}});
}


{% endfor %}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean {{cookiecutter.app_name}}::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult  = TRUE;
    uint16  usMsgLen = 0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            HkTlm.usCmdErrCnt++;
        }
    }

    return bResult;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* {{cookiecutter.app_name}} Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void {{cookiecutter.app_name}}_AppMain()
{
    o{{cookiecutter.app_name}}.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* {{cookiecutter.app_name}} Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void {{cookiecutter.app_name}}::{{cookiecutter.app_name}}Main()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("{{cookiecutter.app_name}} - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry({{cookiecutter.app_name}}_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit({{cookiecutter.app_name}}_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync({{cookiecutter.app_name}}_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry({{cookiecutter.app_name}}_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg({{cookiecutter.app_name}}_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit({{cookiecutter.app_name}}_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}


#ifdef __cplusplus
}
#endif

/************************/
/*  End of File Comment */
/************************/
