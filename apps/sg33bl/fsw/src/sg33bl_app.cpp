/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "sg33bl_app.h"
#include "sg33bl_msg.h"
#include "sg33bl_version.h"
#include "sg33bl_custom.h"
#include "sg33bl_map.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
SG33BL oSG33BL;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
SG33BL::SG33BL()
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
SG33BL::~SG33BL()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SG33BL::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("SG33BL - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SG33BL::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    		SG33BL_SCH_PIPE_DEPTH,
			SG33BL_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(SG33BL_WAKEUP_MID, SchPipeId, CFE_SB_Default_Qos, SG33BL_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(SG33BL_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
            		"Sch Pipe failed to subscribe to SG33BL_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto SG33BL_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(SG33BL_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, SG33BL_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(SG33BL_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to SG33BL_SEND_HK_MID. (0x%08X)",
					 (unsigned int)iStatus);
            goto SG33BL_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(SG33BL_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create SCH pipe (0x%08lX)",
			 iStatus);
        goto SG33BL_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    		SG33BL_CMD_PIPE_DEPTH,
			SG33BL_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(SG33BL_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(SG33BL_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
				 "CMD Pipe failed to subscribe to SG33BL_CMD_MID. (0x%08lX)",
				 iStatus);
            goto SG33BL_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(SG33BL_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create CMD pipe (0x%08lX)",
			 iStatus);
        goto SG33BL_InitPipe_Exit_Tag;
    }

SG33BL_InitPipe_Exit_Tag:
    return iStatus;
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SG33BL::InitData()
{
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm, SG33BL_HK_TLM_MID, sizeof(HkTlm), TRUE);
    SG33BL_Custom_InitData();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SG33BL initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SG33BL::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;
    boolean returnBool;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("SG33BL - Failed to init events (0x%08lX)\n", iStatus);
        goto SG33BL_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto SG33BL_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto SG33BL_InitApp_Exit_Tag;
    }

    returnBool = SG33BL_Custom_Init();
    if (FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(SG33BL_INIT_ERR_EID, CFE_EVS_ERROR,
                "Custom init failed");
        goto SG33BL_InitApp_Exit_Tag;
    }


    returnBool = SetConfiguration();
    if (FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(SG33BL_INIT_ERR_EID, CFE_EVS_ERROR,
                "Set configuration failed");
        goto SG33BL_InitApp_Exit_Tag;
    }

SG33BL_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(SG33BL_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
								 SG33BL_MAJOR_VERSION,
								 SG33BL_MINOR_VERSION,
								 SG33BL_REVISION,
								 SG33BL_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("SG33BL - Application failed to initialize\n");
        }
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 SG33BL::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;
    static int testing = 0;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(SG33BL_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(SG33BL_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case SG33BL_WAKEUP_MID:
                testing++;
                if(testing == 2000)
                {
                    setPosition(0);
                }
                if(testing == 4000)
                {
                    setPosition(2048);
                    testing = 0;
                }
                break;

            case SG33BL_SEND_HK_MID:
                ProcessCmdPipe();
                ReportHousekeeping();
                break;

            default:
                (void) CFE_EVS_SendEvent(SG33BL_MSGID_ERR_EID, CFE_EVS_ERROR,
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
        (void) CFE_EVS_SendEvent(SG33BL_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void SG33BL::ProcessCmdPipe()
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
                case SG33BL_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(SG33BL_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(SG33BL_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process SG33BL Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void SG33BL::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case SG33BL_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(SG33BL_CMD_NOOP_EID, CFE_EVS_INFORMATION,
					"Recvd NOOP. Version %d.%d.%d.%d",
					SG33BL_MAJOR_VERSION,
					SG33BL_MINOR_VERSION,
					SG33BL_REVISION,
					SG33BL_MISSION_REV);
                break;

            case SG33BL_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(SG33BL_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send SG33BL Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void SG33BL::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean SG33BL::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(SG33BL_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            HkTlm.usCmdErrCnt++;
        }
    }

    return bResult;
}


boolean SG33BL::SetPosition(const uint16 position)
{
    return SG33BL_Custom_Write(SG33BL_REG_POSITION_NEW, position);
}


boolean SG33BL::SetConfiguration(void)
{
    boolean returnBool;
    const uint16 returnDelay = 0;
    const uint16 positionSlope = 4095;
    const uint16 velocityMax = 4095;
    const uint16 torqueMax = 4095;
    const uint16 tempMax = 4095;
    const uint16 posNeutral = 2048;
    const uint16 posStart = 1025;
    const uint16 posEnd = 3071;
    const uint16 torque = 4095;
    const uint16 velocity = 4095;

    /* Set return delay. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_NORMAL_RETURN_DELAY, returnDelay);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set position slope. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_POSITION_SLOPE, positionSlope);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set max velocity. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_VELOCITY_MAX, velocityMax);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set max torque. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_TORQUE_MAX, torqueMax);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set max temp. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_TEMP_MAX, tempMax);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set neutral position. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_POS_NEUTRAL, posNeutral);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set start position. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_POS_START, posStart);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set end position. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_POS_END, posEnd);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set velocity. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_VELOCITY_NEW, velocity);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

    /* Set torque. */
    returnBool = SG33BL_Custom_Write(SG33BL_REG_TORQUE_NEW, torque);
    if (FALSE == returnBool)
    {
        goto end_of_function;
    }

end_of_function:
    return returnBool;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SG33BL Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void SG33BL_AppMain()
{
    oSG33BL.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* SG33BL Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SG33BL::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("SG33BL - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(SG33BL_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(SG33BL_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(SG33BL_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(SG33BL_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(SG33BL_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(SG33BL_MAIN_TASK_PERF_ID);

    /* Custom cleanup. */
    (void) SG33BL_Custom_Deinit();
    
    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}


/************************/
/*  End of File Comment */
/************************/
