/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "nav_app.h"
#include "nav_msg.h"
#include "nav_version.h"
#include <math/Limits.hpp>

#include "nav_take_off.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV oNAV;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV::NAV()
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV::~NAV()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    		NAV_SCH_PIPE_DEPTH,
			NAV_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(NAV_WAKEUP_MID, SchPipeId, CFE_SB_Default_Qos, NAV_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
            		"Sch Pipe failed to subscribe to NAV_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(NAV_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, NAV_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to NAV_SEND_HK_MID. (0x%08X)",
					 (unsigned int)iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_HOME_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_HOME_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_SENSOR_COMBINED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_SENSOR_COMBINED_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_MISSION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_MISSION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GPS_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_GPS_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GLOBAL_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_GLOBAL_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_STATUS_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_STATUS_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LAND_DETECTED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_LAND_DETECTED_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LOCAL_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_LOCAL_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_COMMAND_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_COMMAND_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(NAV_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create SCH pipe (0x%08lX)",
			 iStatus);
        goto NAV_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    		NAV_CMD_PIPE_DEPTH,
			NAV_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(NAV_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
				 "CMD Pipe failed to subscribe to NAV_CMD_MID. (0x%08lX)",
				 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(NAV_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create CMD pipe (0x%08lX)",
			 iStatus);
        goto NAV_InitPipe_Exit_Tag;
    }

NAV_InitPipe_Exit_Tag:
    return iStatus;
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::InitData()
{
	/* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
    		NAV_HK_TLM_MID, sizeof(HkTlm), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&VehicleLandDetectedMsg,
		PX4_VEHICLE_LAND_DETECTED_MID, sizeof(PX4_VehicleLandDetectedMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&FenceMsg,
		PX4_FENCE_MID, sizeof(PX4_FenceMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&ActuatorControls3Msg,
		PX4_ACTUATOR_CONTROLS_3_MID, sizeof(PX4_ActuatorControlsMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&MissionResultMsg,
		PX4_MISSION_RESULT_MID, sizeof(PX4_MissionResultMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&GeofenceResultMsg,
		PX4_GEOFENCE_RESULT_MID, sizeof(PX4_GeofenceResultMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&PositionSetpointTripletMsg,
		PX4_POSITION_SETPOINT_TRIPLET_MID, sizeof(PX4_PositionSetpointTripletMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&VehicleCommandMsgOut,
		PX4_POSITION_SETPOINT_TRIPLET_MID, sizeof(PX4_VehicleCommandMsg_t), TRUE);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to init events (0x%08lX)\n", iStatus);
        goto NAV_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto NAV_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto NAV_InitApp_Exit_Tag;
    }

NAV_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(NAV_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
								 NAV_MAJOR_VERSION,
								 NAV_MINOR_VERSION,
								 NAV_REVISION,
								 NAV_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("NAV - Application failed to initialize\n");
        }
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 NAV::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case NAV_WAKEUP_MID:
                /* TODO:  Do something here. */
            	Execute();
                break;

            case NAV_SEND_HK_MID:
            	//Execute();
                ProcessCmdPipe();
                ReportHousekeeping();
                break;

            case PX4_HOME_POSITION_MID:
                memcpy(&CVT.HomePositionMsg, MsgPtr, sizeof(CVT.HomePositionMsg));
                break;

            case PX4_SENSOR_COMBINED_MID:
                memcpy(&CVT.SensorCombinedMsg, MsgPtr, sizeof(CVT.SensorCombinedMsg));
                break;

            case PX4_MISSION_MID:
                memcpy(&CVT.MissionMsg, MsgPtr, sizeof(CVT.MissionMsg));
                break;

            case PX4_VEHICLE_GPS_POSITION_MID:
                memcpy(&CVT.VehicleGpsPositionMsg, MsgPtr, sizeof(CVT.VehicleGpsPositionMsg));
                break;

            case PX4_VEHICLE_GLOBAL_POSITION_MID:
                memcpy(&CVT.VehicleGlobalPosition, MsgPtr, sizeof(CVT.VehicleGlobalPosition));
                break;

            case PX4_VEHICLE_STATUS_MID:
                memcpy(&CVT.VehicleStatusMsg, MsgPtr, sizeof(CVT.VehicleStatusMsg));
                break;

            case PX4_VEHICLE_LAND_DETECTED_MID:
                memcpy(&CVT.VehicleLandDetectedMsg, MsgPtr, sizeof(CVT.VehicleLandDetectedMsg));
                break;

            case PX4_VEHICLE_LOCAL_POSITION_MID:
                memcpy(&CVT.VehicleLocalPositionMsg, MsgPtr, sizeof(CVT.VehicleLocalPositionMsg));
                break;

            case PX4_VEHICLE_COMMAND_MID:
            	new_command_arrived = true;
                memcpy(&CVT.VehicleCommandMsg, MsgPtr, sizeof(CVT.VehicleCommandMsg));
                break;

            default:
                (void) CFE_EVS_SendEvent(NAV_MSGID_ERR_EID, CFE_EVS_ERROR,
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
        (void) CFE_EVS_SendEvent(NAV_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ProcessCmdPipe()
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
                case NAV_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    //OS_printf("command msg pointer %ld ",CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(NAV_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(NAV_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process NAV Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case NAV_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(NAV_CMD_NOOP_EID, CFE_EVS_INFORMATION,
					"Recvd NOOP. Version %d.%d.%d.%d",
					NAV_MAJOR_VERSION,
					NAV_MINOR_VERSION,
					NAV_REVISION,
					NAV_MISSION_REV);
                break;

            case NAV_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(NAV_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send NAV Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::SendVehicleLandDetectedMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VehicleLandDetectedMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&VehicleLandDetectedMsg);
}

void NAV::SendFenceMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&FenceMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&FenceMsg);
}

void NAV::SendActuatorControls3Msg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ActuatorControls3Msg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&ActuatorControls3Msg);
}

void NAV::SendMissionResultMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&MissionResultMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&MissionResultMsg);
}

void NAV::SendGeofenceResultMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&GeofenceResultMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&GeofenceResultMsg);
}

void NAV::SendPositionSetpointTripletMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PositionSetpointTripletMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&PositionSetpointTripletMsg);
}

void NAV::SendVehicleCommandMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VehicleCommandMsgOut);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&VehicleCommandMsgOut);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean NAV::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(NAV_MSGLEN_ERR_EID, CFE_EVS_ERROR,
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
/* NAV Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void NAV_AppMain()
{
    oNAV.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(NAV_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(NAV_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}


int NAV::Execute(){

	/* Check global position availability */
	if (CVT.VehicleGlobalPosition.Timestamp==0){
		return 0;
	}

	/*Set vehicle arming state */
	if(CVT.VehicleStatusMsg.Timestamp!=0 && !vehicle_status_update_once ){
		CVT.VehicleStatusMsg.ArmingState = PX4_ArmingState_t::PX4_ARMING_STATE_STANDBY;
		vehicle_status_update_once = true;
	}

	/*execute only on command event*/
	if(new_command_arrived){
		// reset new command flag
		new_command_arrived = false;
		/* Configure messages on command receipt */
		if(CVT.VehicleCommandMsg.Command == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_REPOSITION){
			//EVENT: DO REPOSITION
			//store current position as previous and goal as next
			PX4_PositionSetpointTripletMsg_t* RepositionTriplet_ptr = GetRepositionTripletMsg();

			RepositionTriplet_ptr->Previous.Yaw = CVT.VehicleGlobalPosition.Yaw;
			RepositionTriplet_ptr->Previous.Lat = CVT.VehicleGlobalPosition.Lat;
			RepositionTriplet_ptr->Previous.Lon = CVT.VehicleGlobalPosition.Lon;
			RepositionTriplet_ptr->Previous.Alt = CVT.VehicleGlobalPosition.Alt;

			//store new current position
			RepositionTriplet_ptr->Current.LoiterRadius = nav_params.nav_loiter_rad;
			RepositionTriplet_ptr->Current.LoiterDirection = 1;
			RepositionTriplet_ptr->Current.Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER;

			//assign yaw to current position set point
			if(PX4_ISFINITE(CVT.VehicleCommandMsg.Param4)){
				RepositionTriplet_ptr->Current.Yaw = CVT.VehicleCommandMsg.Param4;
			}else{
				RepositionTriplet_ptr->Current.Yaw = NAN;
			}

			//assign latitude and longitude to current set point
			if(PX4_ISFINITE(CVT.VehicleCommandMsg.Param5) && PX4_ISFINITE(CVT.VehicleCommandMsg.Param6)){
				RepositionTriplet_ptr->Current.Lat = (CVT.VehicleCommandMsg.Param5 < 1000) ? CVT.VehicleCommandMsg.Param5 : CVT.VehicleCommandMsg.Param5 /(double) 1e7;
				RepositionTriplet_ptr->Current.Lon = (CVT.VehicleCommandMsg.Param6 < 1000) ? CVT.VehicleCommandMsg.Param6 : CVT.VehicleCommandMsg.Param6 /(double) 1e7;

			}else{
				RepositionTriplet_ptr->Current.Lat = CVT.VehicleGlobalPosition.Lat;
				RepositionTriplet_ptr->Current.Lon = CVT.VehicleGlobalPosition.Lon;
			}

			//assign altitude to current set point
			if (PX4_ISFINITE(CVT.VehicleCommandMsg.Param7)){
				RepositionTriplet_ptr->Current.Alt = CVT.VehicleCommandMsg.Param7;
			}else{
				RepositionTriplet_ptr->Current.Alt = CVT.VehicleGlobalPosition.Alt;
			}
			//assign set point triplet validity
			RepositionTriplet_ptr->Previous.Valid = true;
			RepositionTriplet_ptr->Current.Valid = true;
			RepositionTriplet_ptr->Next.Valid = false;

		}
		else if(CVT.VehicleCommandMsg.Command == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF ){
			//EVENT: TAKEOFF

			// store of command hist
			CommandEventHist();

			// avoid subsequent takeoffs
			if(!subsequent_takeoffs){

				if(CVT.VehicleCommandMsg.Command == previous_command.Command){
					(void) CFE_EVS_SendEvent(NAV_SUBSEQ_TAKEOFF_EID, CFE_EVS_ERROR, "Subsequent takeoff is not allowed");
					return 0;
				}
			}

			PX4_PositionSetpointTripletMsg_t *TakeoffTriplet_ptr = GetTakeoffTripletMsg();
			//store current position as previous and goal as next
			TakeoffTriplet_ptr->Previous.Yaw = CVT.VehicleGlobalPosition.Yaw;
			TakeoffTriplet_ptr->Previous.Lat = CVT.VehicleGlobalPosition.Lat;
			TakeoffTriplet_ptr->Previous.Lon = CVT.VehicleGlobalPosition.Lon;
			TakeoffTriplet_ptr->Previous.Alt = CVT.VehicleGlobalPosition.Alt;

			//store new current position
			TakeoffTriplet_ptr->Current.LoiterRadius = nav_params.nav_loiter_rad;
			TakeoffTriplet_ptr->Current.LoiterDirection = 1;
			TakeoffTriplet_ptr->Current.Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_TAKEOFF;

			//check if home position is valid, set current yaw and previous valid accordingly
			if (CVT.HomePositionMsg.Timestamp>0){
				TakeoffTriplet_ptr->Current.Yaw = CVT.VehicleCommandMsg.Param4;
				TakeoffTriplet_ptr->Previous.Valid = true;
			}else{
				TakeoffTriplet_ptr->Current.Yaw = CVT.VehicleLocalPositionMsg.Yaw;
				TakeoffTriplet_ptr->Previous.Valid = false;
			}

			// check if param5 and param6 is finite, set Latitude, Longitude, Altitude and current and next position set point validity
			if(PX4_ISFINITE(CVT.VehicleCommandMsg.Param5) && PX4_ISFINITE(CVT.VehicleCommandMsg.Param6)){
				TakeoffTriplet_ptr->Current.Lat = (CVT.VehicleCommandMsg.Param5 < 1000) ? CVT.VehicleCommandMsg.Param5 : CVT.VehicleCommandMsg.Param5 /(double) 1e7;
				TakeoffTriplet_ptr->Current.Lon = (CVT.VehicleCommandMsg.Param6 < 1000) ? CVT.VehicleCommandMsg.Param6 : CVT.VehicleCommandMsg.Param6 /(double) 1e7;
			}else{
				TakeoffTriplet_ptr->Current.Lat = NAN;
				TakeoffTriplet_ptr->Current.Lon = NAN;
			}
			//assign set point triplet validity
			TakeoffTriplet_ptr->Current.Alt = CVT.VehicleCommandMsg.Param7;
			TakeoffTriplet_ptr->Current.Valid = true;
			TakeoffTriplet_ptr->Next.Valid = false;
		}
	}



	/* Detect events for navigation actions */
	/* find if a state is seen for first time or has been active since a while*/
	PX4_NavigationState_t CurrentState = CVT.VehicleStatusMsg.NavState;
	boolean first_run = StateChangeDetect();
	boolean active = false;
	if (!first_run){
		active = true;
	}

	/* if a state is inactive */
	if(CurrentState != PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LOITER){
		LoiterPositionSet = false;
	}

	if(CurrentState != PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL){
		rtl_state = RTLState::RTL_STATE_NONE;
	}

	/* first run in a navigation mode */
	if(first_run){
		if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF){
			(void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION, "Commencing %s","Takeoff");
			Takeoff();
		}
		else if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LOITER){
			(void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION, "Commencing %s","Loiter");
			Loiter();
		}
		else if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LAND){
			(void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION, "Commencing %s","Land");
			Land();
		}
		else if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL){
			(void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION, "Commencing %s","Return to Launch");
			Rtl();

		}
		else{
			CanLoiterAtSetpoint = false;
		}
	}

	/* if the mode is active */
	if(active){

		if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF){
			TakeoffActive();
		}
		else if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LOITER){
			LoiterActive();
		}
		else if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LAND){
			LandActive();
		}
		else if(CurrentState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL){
			RtlActive();
		}
		else{
			CanLoiterAtSetpoint = false;
		}
	}

	/* if we landed and have not received takeoff setpoint then stay in idle */
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	if(CVT.VehicleLandDetectedMsg.Landed && !((CVT.VehicleStatusMsg.NavState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF )||(CVT.VehicleStatusMsg.NavState == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_MISSION ))){
		PositionSetpointTriplet_ptr->Current.Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_IDLE;
		PositionSetpointTriplet_ptr->Current.Valid = true;
		PositionSetpointTriplet_ptr->Previous.Valid = false;
		PositionSetpointTriplet_ptr->Next.Valid = false;
	}

	/* if nothing is running, set position setpoint triplet invalid once */
//	if (_navigation_mode == nullptr && !_pos_sp_triplet_published_invalid_once) {
//		_pos_sp_triplet_published_invalid_once = true;
//		_pos_sp_triplet.previous.valid = false;
//		_pos_sp_triplet.current.valid = false;
//		_pos_sp_triplet.next.valid = false;
//		_pos_sp_triplet_updated = true;
//	}


	/* Time stamp out going messages */
	const uint64 now = PX4LIB_GetPX4TimeUs();

	VehicleCommandMsgOut.Timestamp = now;
	PositionSetpointTripletMsg.Timestamp = now;
	VehicleLandDetectedMsg.Timestamp = now;
	ActuatorControls3Msg.Timestamp = now;
	MissionResultMsg.Timestamp = now;
	//GeofenceResultMsg.Timestamp = now;
	//FenceMsg.Timestamp = now;

	if (PositionSetpointTripletUpdated) {
		PositionSetpointTriplet_ptr->Timestamp = PX4LIB_GetPX4TimeUs();
		SendPositionSetpointTripletMsg();
		PositionSetpointTripletUpdated = false;
	}

	if (MissionResultUpdated) {
		SendMissionResultMsg();
		MissionResultUpdated = false;
	}

	return 0;
}

void NAV::Takeoff(){
	//initialize pointers to messages
	PX4_PositionSetpointTripletMsg_t *TakeoffTriplet_ptr = GetTakeoffTripletMsg();
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();

	float AbsoluteAltitude = 0.0f;
	float MinPitch = 0.0f;
	float MinAbsoluteAltitude;


	//use home position if valid
	boolean hpv = HomePositionValid();
	if(hpv){
		MinAbsoluteAltitude = VehicleGlobalPosition_ptr->Alt + nav_params.nav_mis_takeoff_alt;
	}
	else{
		MinAbsoluteAltitude = nav_params.nav_mis_takeoff_alt;
	}

	//use altitude if it is already set.
	//if home position is invalid use MinAbsoluteAltitude

	boolean hpv2 = HomePositionValid();
	if (TakeoffTriplet_ptr->Current.Valid && PX4_ISFINITE(TakeoffTriplet_ptr->Current.Alt) && hpv2){
		AbsoluteAltitude = TakeoffTriplet_ptr->Current.Alt;

		// if set altitude is less than minimum clearance raise it to that level and throw a warning
		if(AbsoluteAltitude < MinAbsoluteAltitude){
			AbsoluteAltitude = MinAbsoluteAltitude;
			(void) CFE_EVS_SendEvent(NAV_LOW_CLEARANCE_ALT_EID, CFE_EVS_INFORMATION,
					"Set altitude lower than minimum clearance : %.2f meters",AbsoluteAltitude);

		}
	}
	else{
		// raise to minimum clearance
		AbsoluteAltitude = MinAbsoluteAltitude;
		(void) CFE_EVS_SendEvent(NAV_LOW_CLEARANCE_ALT_EID, CFE_EVS_INFORMATION,
				"Set altitude lower than minimum clearance : %.2f meters",AbsoluteAltitude);
	}

	//if new altitude is lower than current altitude, don't go down.
	if(AbsoluteAltitude < VehicleGlobalPosition_ptr->Alt){
		AbsoluteAltitude = VehicleGlobalPosition_ptr->Alt;
		(void) CFE_EVS_SendEvent(NAV_HIGH_ALT_EID, CFE_EVS_INFORMATION,
						"Set altitude already higher than take off altitude");
	}

	//set mission item to takeoff
	mission_item.NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF;

	// use current position
	mission_item.Lat = VehicleGlobalPosition_ptr->Lat;
	mission_item.Lon = VehicleGlobalPosition_ptr->Lon;
	mission_item.Yaw = VehicleGlobalPosition_ptr->Yaw;
	mission_item.Altitude = AbsoluteAltitude;
	mission_item.AltitudeIsRelative = false;
	mission_item.LoiterRadius = nav_params.nav_loiter_rad;
	mission_item.PitchMin = MinPitch;
	mission_item.AutoContinue = false;
	mission_item.Origin = NAV_Origin_t::ORIGIN_ONBOARD;

	//set mission result message
	PX4_MissionResultMsg_t *MissionResultMsg_ptr = GetMissionResultMsg();
	MissionResultMsg_ptr->Reached = false;
	MissionResultMsg_ptr->Finished = false;

	//record mission update event in boolean
	MissionResultUpdated = true;

	//reset mission item reached
	WaypointPositionReached = false;
	WaypointYawReached = false;
	TimeFirstInsideOrbit = 0;
	TimeWpReached = 0;

	//convert mission item to current set point
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,&mission_item );
	PositionSetpointTriplet_ptr -> Previous.Valid = false;
	PositionSetpointTriplet_ptr -> Current.YawValid = true;
	PositionSetpointTriplet_ptr -> Next.Valid = false;

	if(TakeoffTriplet_ptr -> Current.Valid){
		if (PX4_ISFINITE(TakeoffTriplet_ptr -> Current.Yaw)) {
			PositionSetpointTriplet_ptr -> Current.Yaw = TakeoffTriplet_ptr -> Current.Yaw;
		}

		if (PX4_ISFINITE(TakeoffTriplet_ptr -> Current.Lat) && PX4_ISFINITE(TakeoffTriplet_ptr -> Current.Lon)) {
			PositionSetpointTriplet_ptr -> Current.Lat = TakeoffTriplet_ptr -> Current.Lat;
			PositionSetpointTriplet_ptr -> Current.Lon = TakeoffTriplet_ptr -> Current.Lon;
		}

		// mark this as done
		memset(TakeoffTriplet_ptr, 0, sizeof(*TakeoffTriplet_ptr));

	}

	CanLoiterAtSetpoint = true;
	PositionSetpointTripletUpdated =true;

}

void NAV::TakeoffActive(){

	//initialize pointers to messages
	PX4_PositionSetpointTripletMsg_t *TakeoffTriplet_ptr = GetTakeoffTripletMsg();
	PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();
	boolean is_mission_item_reached = IsMissionItemReached();

	if(TakeoffTriplet_ptr->Current.Valid){
		Takeoff();
	}
	else if (is_mission_item_reached && !MissionResult_ptr->Finished){
		MissionResult_ptr->Finished = true;

		// set loiter item so position controllers stop doing takeoff logic
		SetLoiterItem(&mission_item);
		PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = &PositionSetpointTripletMsg;
		ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,&mission_item);
	}
}

void NAV::Land(){
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();
	PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
	PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();
	NAV_MissionItem_t * item = &mission_item;
	boolean at_current_position = true;

	/* set the land item */
	item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND;

	/* use current position */
	if (at_current_position) {
		item->Lat = NAN; //descend at current position
		item->Lon = NAN; //descend at current position
		item->Yaw = VehicleGlobalPosition_ptr->Yaw;

	} else {
		/* use home position */
		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		item->Yaw = HomePosition_ptr->Yaw;
	}

	item->Altitude = 0;
	item->AltitudeIsRelative = false;
	item->LoiterRadius = nav_params.nav_loiter_rad;
	item->AcceptanceRadius = nav_params.nav_acc_rad;
	item->TimeInside = 0.0f;
	item->AutoContinue = true;
	item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;

	/* set current mission item to Land */
	MissionResult_ptr->Reached = false;
	MissionResult_ptr->Finished = false;
	/*update mission result and reset mission item reached*/
	MissionResultUpdated = true;
	WaypointPositionReached = false;
	WaypointYawReached = false;
	TimeFirstInsideOrbit = 0;
	TimeWpReached = 0;

	/* convert mission item to current setpoint */
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	PositionSetpointTriplet_ptr->Previous.Valid = false;
	ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,item );
	PositionSetpointTriplet_ptr->Next.Valid = false;

	CanLoiterAtSetpoint=false;
	PositionSetpointTripletUpdated=true;



}

void NAV::LandActive(){

	boolean is_mission_item_reached = IsMissionItemReached();
	PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();


	if (is_mission_item_reached && !MissionResult_ptr->Finished){
		PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
		PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
		NAV_MissionItem_t * item = &mission_item;

		MissionResult_ptr->Reached = true;
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		item->AltitudeIsRelative = false;
		item->Altitude = HomePosition_ptr->Alt;
		item->Yaw = NAN;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->AcceptanceRadius = nav_params.nav_acc_rad;;
		item->TimeInside = 0.0f;
		item->AutoContinue = true;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
		ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,item );
		PositionSetpointTripletUpdated=true;

	}

}

void NAV::Loiter(){
	PX4_PositionSetpointTripletMsg_t *RepositionTriplet_ptr = GetRepositionTripletMsg();

	if(RepositionTriplet_ptr->Current.Valid){
		LoiterReposition();
	}
	else{
		LoiterSetPosition();
	}
}

void NAV::LoiterActive(){

	PX4_PositionSetpointTripletMsg_t *RepositionTriplet_ptr = GetRepositionTripletMsg();
	PX4_VehicleStatusMsg_t *VehicleStatus_ptr = GetVehicleStatusMsg();

	if(RepositionTriplet_ptr->Current.Valid){
		LoiterReposition();
	}

	// reset loiter position if we get disarmed
	if(VehicleStatus_ptr->ArmingState != PX4_ArmingState_t::PX4_ARMING_STATE_ARMED){
		LoiterPositionSet = false;
	}
}

void NAV::LoiterReposition(){
	PX4_PositionSetpointTripletMsg_t *RepositionTriplet_ptr = GetRepositionTripletMsg();
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	PX4_VehicleStatusMsg_t *VehicleStatus_ptr = GetVehicleStatusMsg();
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();


	// cannot reposition if not armed
	if(VehicleStatus_ptr->ArmingState != PX4_ArmingState_t::PX4_ARMING_STATE_ARMED){
		return;
	}
	if(RepositionTriplet_ptr->Current.Valid){

		PositionSetpointTriplet_ptr->Current.VelocityValid = false;
		PositionSetpointTriplet_ptr->Previous.Yaw = VehicleGlobalPosition_ptr->Yaw;
		PositionSetpointTriplet_ptr->Previous.Lat = VehicleGlobalPosition_ptr->Lat;
		PositionSetpointTriplet_ptr->Previous.Lon = VehicleGlobalPosition_ptr->Lon;
		PositionSetpointTriplet_ptr->Previous.Alt = VehicleGlobalPosition_ptr->Alt;
		memcpy(&PositionSetpointTriplet_ptr->Current, &RepositionTriplet_ptr->Current, sizeof(RepositionTriplet_ptr->Current));
		PositionSetpointTriplet_ptr->Next.Valid = false;

		// set yaw
		float travel_dist = get_distance_to_next_waypoint(VehicleGlobalPosition_ptr->Lat,VehicleGlobalPosition_ptr->Lon,PositionSetpointTriplet_ptr->Current.Lat, PositionSetpointTriplet_ptr->Current.Lon);
		if (travel_dist > 1.0f) {
			// calculate direction the vehicle should point to.
			PositionSetpointTriplet_ptr->Current.Yaw = get_bearing_to_next_waypoint(VehicleGlobalPosition_ptr->Lat,VehicleGlobalPosition_ptr->Lon,PositionSetpointTriplet_ptr->Current.Lat, PositionSetpointTriplet_ptr->Current.Lon);
		}

		if(PositionSetpointTriplet_ptr->Current.Type == PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER){
			CanLoiterAtSetpoint = true;
		}
		PositionSetpointTripletUpdated = true;
		memset(RepositionTriplet_ptr, 0, sizeof(*RepositionTriplet_ptr));
	}

}

void NAV::LoiterSetPosition(){

	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	PX4_VehicleStatusMsg_t *VehicleStatus_ptr = GetVehicleStatusMsg();
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();
	PX4_VehicleLandDetectedMsg_t* VehicleLandDetected_ptr = GetVehicleLandDetectedMsg();
	PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
	NAV_MissionItem_t * item = &mission_item;

	float min_clearance = nav_params.nav_mis_ltrmin_alt;

	if (VehicleStatus_ptr->ArmingState != PX4_ArmingState_t::PX4_ARMING_STATE_ARMED && VehicleLandDetected_ptr->Landed){
		// Not setting loiter position if disarmed and landed, instead mark the current
		// setpoint as invalid and idle (both, just to be sure).
		CanLoiterAtSetpoint = false;
		PositionSetpointTriplet_ptr->Current.Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_IDLE;
		PositionSetpointTripletUpdated = true;
		LoiterPositionSet = false;
		return;
	}
	else if(LoiterPositionSet){
		// Already set, nothing to do.
		return;
	}

	LoiterPositionSet = true;

	// set current mission item to loiter
	if (VehicleLandDetected_ptr->Landed) {
		/* landed, don't takeoff, but switch to IDLE mode */
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
	} else {
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM;

		if (CanLoiterAtSetpoint && PositionSetpointTriplet_ptr->Current.Valid) {
			/* use current position setpoint */
			item->Lat = PositionSetpointTriplet_ptr->Current.Lat;
			item->Lon = PositionSetpointTriplet_ptr->Current.Lon;
			item->Altitude = PositionSetpointTriplet_ptr->Current.Alt;

		} else {
			/* use current position and use return altitude as clearance */
			item->Lat = VehicleGlobalPosition_ptr->Lat;
			item->Lon = VehicleGlobalPosition_ptr->Lon;
			item->Altitude = VehicleGlobalPosition_ptr->Alt;

			if (min_clearance > 0.0f && item->Altitude < HomePosition_ptr->Alt + min_clearance) {
				item->Altitude = HomePosition_ptr->Alt + min_clearance;
			}
		}

		item->AltitudeIsRelative = false;
		item->Yaw = NAN;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = false;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
	}
	// convert mission item to current setpoint
	PositionSetpointTriplet_ptr->Current.VelocityValid = false;
	PositionSetpointTriplet_ptr->Previous.Valid = false;
	ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,item );
	PositionSetpointTriplet_ptr->Next.Valid = false;

	if(PositionSetpointTriplet_ptr->Current.Type == PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER){
		CanLoiterAtSetpoint = true;
	}
	PositionSetpointTripletUpdated = true;
}

void NAV::Rtl(){
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();
	PX4_VehicleLandDetectedMsg_t* VehicleLandDetected_ptr = GetVehicleLandDetectedMsg();
	PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
	NAV_MissionItem_t * item = &mission_item;

	/* Sets current position item */
	item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT;
	item->Lat = VehicleGlobalPosition_ptr->Lat;
	item->Lon = VehicleGlobalPosition_ptr->Lon;
	item->AltitudeIsRelative = false;
	item->Altitude = VehicleGlobalPosition_ptr->Alt;
	item->Yaw = NAN;
	item->LoiterRadius = nav_params.nav_loiter_rad;
	item->AcceptanceRadius = nav_params.nav_acc_rad;
	item->TimeInside = 0.0f;
	item->AutoContinue = true;
	item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
	ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,item );
	PositionSetpointTriplet_ptr->Previous.Valid = false;
	PositionSetpointTriplet_ptr->Next.Valid = false;


	float rtl_altitude = (nav_params.nav_rtl_return_alt < VehicleLandDetected_ptr->AltMax) ? nav_params.nav_rtl_return_alt : VehicleLandDetected_ptr->AltMax;

	/* for safety reasons don't go into RTL if landed */
	if(VehicleLandDetected_ptr->Landed){
		rtl_state = RTLState::RTL_STATE_LANDED;
		(void) CFE_EVS_SendEvent(NAV_RTL_LND_SFGA_EID, CFE_EVS_INFORMATION,
							"Already landed, not executing RTL");

	}
	else if(VehicleGlobalPosition_ptr->Alt < (HomePosition_ptr->Alt + rtl_altitude)){
		/* if lower than return altitude, climb up first */
		rtl_state = RTLState::RTL_STATE_CLIMB;
	}
	else{
		rtl_state = RTLState::RTL_STATE_RETURN;
		item->AltitudeIsRelative = false;
		item->Altitude = VehicleGlobalPosition_ptr->Alt;
	}
	SetRtlItem();

}

void NAV::SetRtlItem(){

	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();
	PX4_VehicleLandDetectedMsg_t* VehicleLandDetected_ptr = GetVehicleLandDetectedMsg();
	PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
	NAV_MissionItem_t * item = &mission_item;

	CanLoiterAtSetpoint = false;

	switch(rtl_state){

	case RTLState::RTL_STATE_CLIMB:{
		// check if we are pretty close to home already
		float home_distance = get_distance_to_next_waypoint(HomePosition_ptr->Lat,HomePosition_ptr->Lon,VehicleGlobalPosition_ptr->Lat,VehicleGlobalPosition_ptr->Lon);
		// if we are close to home we do not climb as high, otherwise we climb to return alt
		float rtl_altitude = (nav_params.nav_rtl_return_alt <VehicleLandDetected_ptr->AltMax) ? nav_params.nav_rtl_return_alt : VehicleLandDetected_ptr->AltMax;
		float climb_alt = HomePosition_ptr->Alt + rtl_altitude;
		// we are close to home, limit climb to min
		if (home_distance < nav_params.nav_rtl_min_dist) {
			climb_alt = HomePosition_ptr->Alt + nav_params.nav_rtl_descent_alt;
		}
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT;
		item->Lat = VehicleGlobalPosition_ptr->Lat;
		item->Lon = VehicleGlobalPosition_ptr->Lon;
		item->AltitudeIsRelative = false;
		item->Altitude = climb_alt;
		item->Yaw = NAN;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = true;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
		(void) CFE_EVS_SendEvent(NAV_RTL_CLIMB_ST_EID, CFE_EVS_INFORMATION,
				"RTL: Commencing climb to %d m (%d m above home)",(int)climb_alt,(int)(climb_alt - HomePosition_ptr->Alt));
		break;
	}
	case RTLState::RTL_STATE_RETURN:{
		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		// check if we are pretty close to home already
		float home_distance = get_distance_to_next_waypoint(HomePosition_ptr->Lat,HomePosition_ptr->Lon,VehicleGlobalPosition_ptr->Lat,VehicleGlobalPosition_ptr->Lon);
		if (home_distance < nav_params.nav_rtl_min_dist) {
			item->Yaw = HomePosition_ptr->Yaw;
		} else {
			// use current heading to home
			item->Yaw = get_bearing_to_next_waypoint(VehicleGlobalPosition_ptr->Lat,VehicleGlobalPosition_ptr->Lon,HomePosition_ptr->Lat,HomePosition_ptr->Lon);
		}
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = true;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
		(void) CFE_EVS_SendEvent(NAV_RTL_RETURN_ST_EID, CFE_EVS_INFORMATION,
				"RTL: Commencing return at %d m (%d m above home)",(int)item->Altitude,(int)(item->Altitude - HomePosition_ptr->Alt));
		break;
	}
	case RTLState::RTL_STATE_DESCEND: {
		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		item->AltitudeIsRelative = false;
		item->Altitude = HomePosition_ptr->Alt + nav_params.nav_rtl_descent_alt;
		// check if we are already lower - then we will just stay there
		if (item->Altitude > VehicleGlobalPosition_ptr->Alt) {
			item->Altitude = VehicleGlobalPosition_ptr->Alt;
		}
		item->Yaw = HomePosition_ptr->Yaw;
		float d_current = get_distance_to_next_waypoint(VehicleGlobalPosition_ptr->Lat, VehicleGlobalPosition_ptr->Lon,item->Lat, item->Lon);
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = true;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;

		/* disable previous setpoint to prevent drift */
		PositionSetpointTriplet_ptr->Previous.Valid = false;
		(void) CFE_EVS_SendEvent(NAV_RTL_RETURN_ST_EID, CFE_EVS_INFORMATION,
				"RTL: Commencing descend to %d m (%d m above home)",(int)item->Altitude, (int)(item->Altitude - HomePosition_ptr->Alt));
		break;
	}
	case RTLState::RTL_STATE_LOITER: {
		bool autoland = nav_params.nav_rtl_land_delay > -DELAY_SIGMA;

		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		// don't change altitude
		item->Yaw = HomePosition_ptr->Yaw;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->NavCmd = autoland ? PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME : PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = nav_params.nav_rtl_land_delay < 0.0f ? 0.0f : nav_params.nav_rtl_land_delay;
		item->AutoContinue =  autoland;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
		CanLoiterAtSetpoint = true;

		float time_inside = GetTimeInside(item);
		if(autoland && (time_inside > FLT_EPSILON)){
			(void) CFE_EVS_SendEvent(NAV_RTL_LOITER_ST_EID, CFE_EVS_INFORMATION,
					"RTL: Commencing loiter for %.1fs",time_inside);
		}
		else{
			(void) CFE_EVS_SendEvent(NAV_RTL_RETURN_ST_EID, CFE_EVS_INFORMATION,
					"RTL: Loiter completed");
		}
		break;
	}
	case RTLState::RTL_STATE_LAND: {
		/* set the land item */
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND;
		/* use current position */
		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		item->Yaw = HomePosition_ptr->Yaw;
		item->Altitude = 0;
		item->AltitudeIsRelative = false;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = true;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
		(void) CFE_EVS_SendEvent(NAV_RTL_LAND_ST_EID, CFE_EVS_INFORMATION,
				"RTL: Commencing land at home");
		break;
	}
	case RTLState::RTL_STATE_LANDED: {
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
		item->Lat = HomePosition_ptr->Lat;
		item->Lon = HomePosition_ptr->Lon;
		item->AltitudeIsRelative = false;
		item->Altitude = HomePosition_ptr->Alt;
		item->Yaw = NAN;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = true;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
		(void) CFE_EVS_SendEvent(NAV_RTL_LAND_EN_EID, CFE_EVS_INFORMATION,
				"RTL: Land completed");
		break;
	}
	default:
		break;
	}

	WaypointPositionReached = false;
	WaypointYawReached = false;
	TimeFirstInsideOrbit = 0;
	TimeWpReached = 0;

	ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,item );
	PositionSetpointTriplet_ptr->Next.Valid = false;
	PositionSetpointTripletUpdated =true;
}

void NAV::AdvanceRtl(){
	switch (rtl_state) {
	case RTLState::RTL_STATE_CLIMB:
		rtl_state = RTLState::RTL_STATE_RETURN;
		break;
	case RTLState::RTL_STATE_RETURN:
		rtl_state = RTLState::RTL_STATE_DESCEND;
		break;
	case RTLState::RTL_STATE_TRANSITION_TO_MC:
		rtl_state = RTLState::RTL_STATE_RETURN;
		break;
	case RTLState::RTL_STATE_DESCEND:
		/* only go to land if autoland is enabled */
		if (nav_params.nav_rtl_land_delay < -DELAY_SIGMA || nav_params.nav_rtl_land_delay > DELAY_SIGMA) {
			rtl_state = RTLState::RTL_STATE_LOITER;
		} else {
			rtl_state = RTLState::RTL_STATE_LAND;
		}
		break;
	case RTLState::RTL_STATE_LOITER:
		rtl_state = RTLState::RTL_STATE_LAND;
		break;
	case RTLState::RTL_STATE_LAND:
		rtl_state = RTLState::RTL_STATE_LANDED;
		break;
	default:
		break;
	}
}

void NAV::RtlActive(){

	boolean is_mission_item_reached = IsMissionItemReached();
	if (is_mission_item_reached && rtl_state!=RTLState::RTL_STATE_LANDED){

		AdvanceRtl();
		SetRtlItem();
	}
}

boolean NAV::StateChangeDetect(){
	//when there is a change in state reset fail safe flag
	PX4_VehicleStatusMsg_t current_state = CVT.VehicleStatusMsg;

	if(&previous_state==nullptr){
		PX4_MissionResultMsg_t* gmr = GetMissionResultMsg();
		gmr->StayInFailsafe = false;

		previous_state = current_state;
		return true;
	}
	else if(previous_state.NavState != current_state.NavState){
		PX4_MissionResultMsg_t* gmr = GetMissionResultMsg();
		gmr->StayInFailsafe = false;

		previous_state = current_state;
		return true;
	}

	return false;
}


void NAV::CommandEventHist(){
	// holds command history one level deep
	PX4_VehicleCommandMsg_t current_command = CVT.VehicleCommandMsg;
	previous_command = current_command;
}

PX4_NavigationState_t NAV::DetectNavStateEvent(boolean state_change_event){
	if (state_change_event){
		return CVT.VehicleStatusMsg.NavState;
	}
}

boolean NAV::IsMissionItemReached(){
	//huge file form mission_block line 73
	//temporary fix for now
	switch(mission_item.NavCmd){
	case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_SET_SERVO:
		return true;
	case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND: /* fall through */
	case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM:
		return false;
	case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_CHANGE_SPEED:
		return true;
	default:
		/* do nothing, this is a 3D waypoint */
		break;
	}

	uint64 now = PX4LIB_GetPX4TimeUs();
	PX4_PositionSetpointTripletMsg_t* pst =  GetPositionSetpointTripletMsg();
	PX4_VehicleLandDetectedMsg_t* vld = GetVehicleLandDetectedMsg();
	PX4_VehicleGlobalPositionMsg_t* vgp = GetVehicleGlobalPositionMsg();
	PX4_HomePositionMsg_t* hp = GetHomePosition();
	PX4_VehicleStatusMsg_t* vs = GetVehicleStatusMsg();

	if(!vld->Landed && !WaypointPositionReached){

		float dist = -1.0f;
		float dist_xy = -1.0f;
		float dist_z = -1.0f;

		float altitude_amsl = mission_item.AltitudeIsRelative ? mission_item.Altitude + hp->Alt : mission_item.Altitude;
		dist =get_distance_to_point_global_wgs84(
				mission_item.Lat,mission_item.Lon,altitude_amsl,
				vgp->Lat,
				vgp->Lon,
				vgp->Alt,
				&dist_xy,&dist_z);
	    if(mission_item.NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF && vs->IsRotaryWing){
	    	/* We want to avoid the edge case where the acceptance radius is bigger or equal than
			 * the altitude of the takeoff waypoint above home. Otherwise, we do not really follow
			 * take-off procedures like leaving the landing gear down. */

	    	float takeoff_alt = mission_item.AltitudeIsRelative ? mission_item.Altitude : (mission_item.Altitude - hp->Alt);
	    	float altitude_acceptance_radius = GetAltitudeAcceptedRadius();

	    	/*it should be safe to takeoff using half of the takeoff_alt as accepted radius*/
	    	if(takeoff_alt>0 && takeoff_alt < altitude_acceptance_radius){
	    		altitude_acceptance_radius = takeoff_alt/2.0f;
	    	}

	    	/*require only altitude for takeoff for mc*/
	    	if(vgp->Alt > altitude_amsl - altitude_acceptance_radius){
	    		WaypointPositionReached=true;
	    	}


	    }
	    else if(mission_item.NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF){
	    	/* for takeoff mission items use the parameter for the takeoff acceptance radius */
			if (dist >= 0.0f && dist <= nav_params.nav_acc_rad && dist_z <= nav_params.nav_acc_rad) {
				WaypointPositionReached = true;
			}
	    }

	    else{

	    	/* for normal mission items used their acceptance radius */
			float mission_acceptance_radius = mission_item.AcceptanceRadius;
			/* if set to zero use the default instead */
			if (mission_acceptance_radius < NAV_EPSILON_POSITION) {
				mission_acceptance_radius = nav_params.nav_acc_rad;
			}
			if (dist >= 0.0f && dist <= mission_acceptance_radius && dist_z <= nav_params.nav_mc_alt_rad) {
				WaypointPositionReached = true;
			}


	    }
	    if (WaypointPositionReached){
	    	TimeWpReached = now;
	    }
	}



	if(WaypointPositionReached && !WaypointYawReached){
		/*added PX4_VEHICLE_CMD_NAV_LOITER_TO_ALT to PX4_VehicleCmd_t*/
		if((vs->IsRotaryWing || (mission_item.NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TO_ALT && mission_item.ForceHeading)) && PX4_ISFINITE(mission_item.Yaw)){
			/*check course if defined only for rotary wing except takeoff*/
			float cog = vs->IsRotaryWing ? vgp->Yaw : atan2f(vgp->VelE,vgp->VelN);
			float yaw_err = _wrap_pi(mission_item.Yaw -cog);
			/* accept yaw if reached or if timeout is set then we dont ignore force headings*/
			if(fabsf(yaw_err) < math::radians((float)nav_params.nav_mis_yaw_err)
				||(nav_params.nav_mis_yaw_tmt >= FLT_EPSILON && !mission_item.ForceHeading)){
				WaypointYawReached=true;
			}
			/*if heading needs to be reached, the timeout is enabled and we don't make it we abort.*/
			if(!WaypointYawReached && mission_item.ForceHeading && (nav_params.nav_mis_yaw_tmt >= FLT_EPSILON) && (now - TimeWpReached >= (uint64)nav_params.nav_mis_yaw_tmt * 1e6f)){
				SetMissionFaliure("did not reach waypoint before timeout");
			}
		}
		else{
			WaypointYawReached = true;
		}
	}

	/*once the position and yaw waypoint have been set we can start the loiter time countdown*/
	if(WaypointPositionReached && WaypointYawReached){
		if(TimeFirstInsideOrbit == 0){
			TimeFirstInsideOrbit = now;
		}

		/*check if the MAV was long enough inside the waypoint orbit*/

		float time_inside = GetTimeInside(&mission_item);
		if((time_inside < FLT_EPSILON)|| now - TimeFirstInsideOrbit >= (uint64) time_inside * 1e6f){
			// exit xtrack location
			if(mission_item.LoiterExitXTrack && (mission_item.NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TO_ALT || mission_item.NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME)){
				// reset lat/lon of loiter waypoint so wehicle follows tangent
				PX4_PositionSetpoint_t * curr_sp = &pst->Current;
				PX4_PositionSetpoint_t * next_sp = &pst->Next;

				float range = get_distance_to_next_waypoint(curr_sp->Lat, curr_sp->Lon, next_sp->Lat, next_sp->Lon);
				float bearing = get_bearing_to_next_waypoint(curr_sp->Lat, curr_sp->Lon, next_sp->Lat, next_sp->Lon);
				float inner_angle = M_PI_2_F - asinf(mission_item.LoiterRadius / range);

				// Compute "ideal" tangent origin
				if (curr_sp->LoiterDirection > 0) {
					bearing -= inner_angle;

				} else {
					bearing += inner_angle;
				}


				// Replace current setpoint Lat/Lon with tangent coordinate
				waypoint_from_heading_and_distance(curr_sp->Lat, curr_sp->Lon,
								   bearing, curr_sp->LoiterRadius,
								   &curr_sp->Lat, &curr_sp->Lon);
			}
			return true;
		}
	}


	// all acceptance criteria must be met in the same iteration
	WaypointPositionReached = false;
	WaypointYawReached =false;
	return false;

}

void NAV::SetMissionFaliure(const char* reason){
	PX4_MissionResultMsg_t* mr = GetMissionResultMsg();
	if(! mr->MissionFailure){
		mr->MissionFailure = true;
		(void) CFE_EVS_SendEvent(NAV_MSN_FAILED_ERR_EID, CFE_EVS_CRITICAL,
		            		"Mission failed (%s)",
							reason);

	}
}

void NAV::ConvertMissionItemToCurrentSetpoint(PX4_PositionSetpoint_t *ps, NAV_MissionItem_t *mi){

	if (!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF) {
		return;
	}
	PX4_HomePositionMsg_t *HomePositionMsg_ptr = GetHomePosition();

	ps->Lat = mi->Lat;
	ps->Lon = mi->Lon;
	ps->Alt = mi->AltitudeIsRelative ? mi->Altitude + HomePositionMsg_ptr->Alt : mi->Altitude;
	ps->Yaw = mi->Yaw;
	ps->LoiterRadius = (fabsf(mi->LoiterRadius) > NAV_EPSILON_POSITION) ? fabsf(mi->LoiterRadius) :	nav_params.nav_loiter_rad;
	ps->LoiterDirection = (mi->LoiterRadius > 0) ? 1 : -1;
	ps->AcceptanceRadius = mi->AcceptanceRadius;
	ps->DisableMcYawControl = mi->DisableMcYaw;

	ps->CruisingSpeed = GetCruisingSpeed();
	ps->CruisingThrottle = GetCruisingThrottle();

	switch(mi->NavCmd){

		case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF:{
			PX4_VehicleStatusMsg_t* gvs = GetVehicleStatusMsg();
			PX4_VehicleLandDetectedMsg_t* gvld =  GetVehicleLandDetectedMsg();
			if(gvs->ArmingState == PX4_ArmingState_t::PX4_ARMING_STATE_ARMED &&
					!(gvld->Landed)){
				ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_POSITION;
			}
			else{
				ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_TAKEOFF;
				// set pitch and ensure that the hold time is zero
				ps->PitchMin = mi->PitchMin;
			}

			break;
		}
		case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND:{

		}
		case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME:{

		}
		case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM:{
			ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER;
			break;
		}
		default:{
			ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_POSITION;
			break;
		}
		ps->Valid = true;
	}

}

void NAV::SetLoiterItem(NAV_MissionItem_t * item){
	float min_clearance = -1.0f;
	PX4_VehicleLandDetectedMsg_t * vld = GetVehicleLandDetectedMsg();
	boolean land_detected = vld->Landed;
	if (land_detected){
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
	}
	else{
		item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM;
		PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = &PositionSetpointTripletMsg;
		if(CanLoiterAtSetpoint && PositionSetpointTriplet_ptr->Current.Valid){
			/* use current position setpoint */
			item->Lat = PositionSetpointTriplet_ptr->Current.Lat;
			item->Lon = PositionSetpointTriplet_ptr->Current.Lon;
			item->Altitude = PositionSetpointTriplet_ptr->Current.Alt;
		}
		else{
			/* use current position and use return altitude as clearance */
			PX4_VehicleGlobalPositionMsg_t* vgp = GetVehicleGlobalPositionMsg();
			PX4_HomePositionMsg_t* hp =  GetHomePosition();
			item->Lat = vgp->Lat;
			item->Lon = vgp->Lon;
			item->Altitude = vgp->Alt;
			if(min_clearance>0.0f && item->Altitude < hp->Alt+min_clearance){
				item->Altitude = hp->Alt=min_clearance;
			}

		}
		item->AltitudeIsRelative = false;
		item->Yaw = NAN;
		item->LoiterRadius = nav_params.nav_loiter_rad;
		item->AcceptanceRadius = nav_params.nav_acc_rad;
		item->TimeInside = 0.0f;
		item->AutoContinue = false;
		item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
	}

}

float NAV::GetTimeInside(NAV_MissionItem_t * mi){
	if(mi->NavCmd != PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF){
		return mi->TimeInside;
	}
	return 0.0f;
}

boolean NAV::HomePositionValid(){
	PX4_HomePositionMsg_t* ghp = GetHomePosition();
	return (ghp->Timestamp>0);
}

float NAV::GetDefaultAcceptedRadius(){
	return nav_params.nav_acc_rad;
}

void NAV::SetAcceptedRadius(float mission_radius){
	nav_params.nav_acc_rad = mission_radius;
}

float NAV::GetAltitudeAcceptedRadius(){
	return nav_params.nav_mc_alt_rad;
}

float NAV::GetCruisingThrottle(){
	if (MissionThrottle > FLT_EPSILON) {
			return MissionThrottle;
	}
	else{
			return -1.0f;
	}
}

float NAV::GetCruisingSpeed(){
	boolean is_planned = IsPlannedMission();
	if(is_planned && MissionCruisingSpeed > 0.0f){
		return MissionCruisingSpeed;
	}
	else{
		return -1.0f;
	}

}

//void NAV::DisplayInputs(int n){
//	OS_printf("NAV::DisplayInputs  *************\n");
//
//	if(n==1 || n==10){
//		OS_printf("  HomePositionMsg.Timestamp:           %llu\n", CVT.HomePositionMsg.Timestamp);
//		OS_printf("  HomePositionMsg.Lat:            	  %lld\n", CVT.HomePositionMsg.Lat);
//		OS_printf("  HomePositionMsg.Lon:                 %lld\n", CVT.HomePositionMsg.Lon);
//		OS_printf("  HomePositionMsg.Alt:                 %f\n", CVT.HomePositionMsg.Alt);
//		OS_printf("  HomePositionMsg.X:                   %f\n", CVT.HomePositionMsg.X);
//		OS_printf("  HomePositionMsg.Y:                   %f\n", CVT.HomePositionMsg.Y);
//		OS_printf("  HomePositionMsg.Z:                   %f\n", CVT.HomePositionMsg.Z);
//		OS_printf("  HomePositionMsg.Yaw:                 %f\n", CVT.HomePositionMsg.Yaw);
//		OS_printf("  HomePositionMsg.DirectionX:          %f\n", CVT.HomePositionMsg.DirectionX);
//		OS_printf("  HomePositionMsg.DirectionY:          %f\n", CVT.HomePositionMsg.DirectionY);
//		OS_printf("  HomePositionMsg.DirectionZ:          %f\n", CVT.HomePositionMsg.DirectionZ);
//		OS_printf("\n");
//	}
//
//	if(n==2 || n==10){
//		OS_printf("  SensorCombinedMsg.Timestamp:                %llu\n", CVT.SensorCombinedMsg.Timestamp);
//		OS_printf("  SensorCombinedMsg.GyroRad[3]:               [%f,%f,%f]\n", CVT.SensorCombinedMsg.GyroRad[0],CVT.SensorCombinedMsg.GyroRad[1],CVT.SensorCombinedMsg.GyroRad[2]);
//		OS_printf("  SensorCombinedMsg.GyroIntegralDt:           %f\n", CVT.SensorCombinedMsg.GyroIntegralDt);
//		OS_printf("  SensorCombinedMsg.AccTimestampRelative:     %llu\n", CVT.SensorCombinedMsg.AccTimestampRelative);
//		OS_printf("  SensorCombinedMsg.AccRelTimeInvalid:        %d\n", CVT.SensorCombinedMsg.AccRelTimeInvalid);
//		OS_printf("  SensorCombinedMsg.Acc[3]:                   [%f,%f,%f]\n", CVT.SensorCombinedMsg.Acc[0],CVT.SensorCombinedMsg.Acc[1],CVT.SensorCombinedMsg.Acc[2]);
//		OS_printf("  SensorCombinedMsg.AccIntegralDt:            %f\n", CVT.SensorCombinedMsg.AccIntegralDt);
//		OS_printf("  SensorCombinedMsg.MagTimestampRelative:     %llu\n", CVT.SensorCombinedMsg.MagTimestampRelative);
//		OS_printf("  SensorCombinedMsg.MagRelTimeInvalid:        %d\n", CVT.SensorCombinedMsg.MagRelTimeInvalid);
//		OS_printf("  SensorCombinedMsg.Mag[3]:                   [%f,%f,%f]\n", CVT.SensorCombinedMsg.Mag[0],CVT.SensorCombinedMsg.Mag[1],CVT.SensorCombinedMsg.Mag[2]);
//		OS_printf("  SensorCombinedMsg.BaroTimestampRelative:    %llu\n", CVT.SensorCombinedMsg.BaroTimestampRelative);
//		OS_printf("  SensorCombinedMsg.BaroRelTimeInvalid:       %d\n", CVT.SensorCombinedMsg.BaroRelTimeInvalid);
//		OS_printf("  SensorCombinedMsg.BaroAlt:                  %f\n", CVT.SensorCombinedMsg.BaroAlt);
//		OS_printf("  SensorCombinedMsg.BaroTemp:                 %f\n", CVT.SensorCombinedMsg.BaroTemp);
//		OS_printf("\n");
//	}
//
//	if(n==3 || n==10){
//		OS_printf("  MissionMsg.Timestamp:            %llu\n", CVT.MissionMsg.Timestamp);
//		OS_printf("  MissionMsg.DatamanID:            %llu\n", CVT.MissionMsg.DatamanID);
//		OS_printf("  MissionMsg.Count:            	  %llu\n", CVT.MissionMsg.Count);
//		OS_printf("  MissionMsg.CurrentSeq:           %llu\n", CVT.MissionMsg.CurrentSeq);
//		OS_printf("\n");
//	}
//
//	if(n==4 || n==10){
//		OS_printf("  VehicleGpsPositionMsg.Timestamp:            %llu\n", CVT.VehicleGpsPositionMsg.Timestamp);
//		OS_printf("  VehicleGpsPositionMsg.TimeUtcUsec:          %llu\n", CVT.VehicleGpsPositionMsg.TimeUtcUsec);
//		OS_printf("  VehicleGpsPositionMsg.Lat:            		 %ld\n", CVT.VehicleGpsPositionMsg.Lat);
//		OS_printf("  VehicleGpsPositionMsg.Lon:                  %ld\n", CVT.VehicleGpsPositionMsg.Lon);
//		OS_printf("  VehicleGpsPositionMsg.Alt:                  %ld\n", CVT.VehicleGpsPositionMsg.Alt);
//		OS_printf("  VehicleGpsPositionMsg.AltEllipsoid:         %ld\n", CVT.VehicleGpsPositionMsg.AltEllipsoid);
//		OS_printf("  VehicleGpsPositionMsg.SVariance:            %f\n", CVT.VehicleGpsPositionMsg.SVariance);
//		OS_printf("  VehicleGpsPositionMsg.CVariance:            %f\n", CVT.VehicleGpsPositionMsg.CVariance);
//		OS_printf("  VehicleGpsPositionMsg.EpH:                  %f\n", CVT.VehicleGpsPositionMsg.EpH);
//		OS_printf("  VehicleGpsPositionMsg.EpV:                  %f\n", CVT.VehicleGpsPositionMsg.EpV);
//		OS_printf("  VehicleGpsPositionMsg.HDOP:                 %f\n", CVT.VehicleGpsPositionMsg.HDOP);
//		OS_printf("  VehicleGpsPositionMsg.VDOP:                 %f\n", CVT.VehicleGpsPositionMsg.VDOP);
//		OS_printf("  VehicleGpsPositionMsg.NoisePerMs:           %ld\n", CVT.VehicleGpsPositionMsg.NoisePerMs);
//		OS_printf("  VehicleGpsPositionMsg.JammingIndicator:     %ld\n", CVT.VehicleGpsPositionMsg.JammingIndicator);
//		OS_printf("  VehicleGpsPositionMsg.Vel_m_s:              %f\n", CVT.VehicleGpsPositionMsg.Vel_m_s);
//		OS_printf("  VehicleGpsPositionMsg.Vel_n_m_s:            %f\n", CVT.VehicleGpsPositionMsg.Vel_n_m_s);
//		OS_printf("  VehicleGpsPositionMsg.Vel_e_m_s:            %f\n", CVT.VehicleGpsPositionMsg.Vel_e_m_s);
//		OS_printf("  VehicleGpsPositionMsg.Vel_d_m_s:            %f\n", CVT.VehicleGpsPositionMsg.Vel_d_m_s);
//		OS_printf("  VehicleGpsPositionMsg.COG:                  %f\n", CVT.VehicleGpsPositionMsg.COG);
//		OS_printf("  VehicleGpsPositionMsg.TimestampTimeRelative:%ld\n", CVT.VehicleGpsPositionMsg.TimestampTimeRelative);
//		OS_printf("  VehicleGpsPositionMsg.FixType:              %u\n", CVT.VehicleGpsPositionMsg.FixType);
//		OS_printf("  VehicleGpsPositionMsg.VelNedValid:          %d\n", CVT.VehicleGpsPositionMsg.VelNedValid);
//		OS_printf("  VehicleGpsPositionMsg.SatellitesUsed:       %u\n", CVT.VehicleGpsPositionMsg.SatellitesUsed);
//		OS_printf("\n");
//	}
//
//	if(n==5 || n==10){
//		OS_printf("  VehicleGlobalPosition.Timestamp:            %llu\n", CVT.VehicleGlobalPosition.Timestamp);
//		OS_printf("  VehicleGlobalPosition.TimeUtcUsec:          %llu\n", CVT.VehicleGlobalPosition.TimeUtcUsec);
//		OS_printf("  VehicleGlobalPosition.Lat:                  %lld\n", CVT.VehicleGlobalPosition.Lat);
//		OS_printf("  VehicleGlobalPosition.Lon:                  %lld\n", CVT.VehicleGlobalPosition.Lon);
//		OS_printf("  VehicleGlobalPosition.Alt:                  %f\n", CVT.VehicleGlobalPosition.Alt);
//		OS_printf("  VehicleGlobalPosition.VelN:                 %f\n", CVT.VehicleGlobalPosition.VelN);
//		OS_printf("  VehicleGlobalPosition.VelE:                 %f\n", CVT.VehicleGlobalPosition.VelE);
//		OS_printf("  VehicleGlobalPosition.VelD:                 %f\n", CVT.VehicleGlobalPosition.VelD);
//		OS_printf("  VehicleGlobalPosition.Yaw:                  %f\n", CVT.VehicleGlobalPosition.Yaw);
//		OS_printf("  VehicleGlobalPosition.EpH:                  %f\n", CVT.VehicleGlobalPosition.EpH);
//		OS_printf("  VehicleGlobalPosition.EpV:                  %f\n", CVT.VehicleGlobalPosition.EpV);
//		OS_printf("  VehicleGlobalPosition.TerrainAlt:           %f\n", CVT.VehicleGlobalPosition.TerrainAlt);
//		OS_printf("  VehicleGlobalPosition.PressureAlt:          %f\n", CVT.VehicleGlobalPosition.PressureAlt);
//		OS_printf("  VehicleGlobalPosition.TerrainAltValid:      %d\n", CVT.VehicleGlobalPosition.TerrainAltValid);
//		OS_printf("  VehicleGlobalPosition.DeadReckoning:        %d\n", CVT.VehicleGlobalPosition.DeadReckoning);
//		OS_printf("\n");
//	}
//
//	if(n==6 || n==10){
//		OS_printf("  VehicleStatusMsg.Timestamp:                    %llu\n", CVT.VehicleStatusMsg.Timestamp);
//		OS_printf("  VehicleStatusMsg.SystemID:                     %u\n", CVT.VehicleStatusMsg.SystemID);
//		OS_printf("  VehicleStatusMsg.ComponentID:                  %u\n", CVT.VehicleStatusMsg.ComponentID);
//		OS_printf("  VehicleStatusMsg.OnboardControlSensorsPresent: %u\n", CVT.VehicleStatusMsg.OnboardControlSensorsPresent);
//		OS_printf("  VehicleStatusMsg.OnboardControlSensorsEnabled: %u\n", CVT.VehicleStatusMsg.OnboardControlSensorsEnabled);
//		OS_printf("  VehicleStatusMsg.OnboardControlSensorsHealth:  %u\n", CVT.VehicleStatusMsg.OnboardControlSensorsHealth);
//		OS_printf("  VehicleStatusMsg.NavState:                     %u\n", CVT.VehicleStatusMsg.NavState);
//		OS_printf("  VehicleStatusMsg.ArmingState:                  %u\n", CVT.VehicleStatusMsg.ArmingState);
//		OS_printf("  VehicleStatusMsg.HilState:                     %u\n", CVT.VehicleStatusMsg.HilState);
//		OS_printf("  VehicleStatusMsg.Failsafe:                     %u\n", CVT.VehicleStatusMsg.Failsafe);
//		OS_printf("  VehicleStatusMsg.SystemType:                   %u\n", CVT.VehicleStatusMsg.SystemType);
//		OS_printf("  VehicleStatusMsg.IsRotaryWing:                 %u\n", CVT.VehicleStatusMsg.IsRotaryWing);
//		OS_printf("  VehicleStatusMsg.IsVtol:                       %u\n", CVT.VehicleStatusMsg.IsVtol);
//		OS_printf("  VehicleStatusMsg.VtolFwPermanentStab:          %u\n", CVT.VehicleStatusMsg.VtolFwPermanentStab);
//		OS_printf("  VehicleStatusMsg.InTransitionMode:             %u\n", CVT.VehicleStatusMsg.InTransitionMode);
//		OS_printf("  VehicleStatusMsg.RcSignalLost:                 %u\n", CVT.VehicleStatusMsg.RcSignalLost);
//		OS_printf("  VehicleStatusMsg.RcInputMode:                  %u\n", CVT.VehicleStatusMsg.RcInputMode);
//		OS_printf("  VehicleStatusMsg.DataLinkLost:                 %u\n", CVT.VehicleStatusMsg.DataLinkLost);
//		OS_printf("  VehicleStatusMsg.DataLinkLostCounter:          %u\n", CVT.VehicleStatusMsg.DataLinkLostCounter);
//		OS_printf("  VehicleStatusMsg.EngineFailure:                %u\n", CVT.VehicleStatusMsg.EngineFailure);
//		OS_printf("  VehicleStatusMsg.EngineFailureCmd:             %u\n", CVT.VehicleStatusMsg.EngineFailureCmd);
//		OS_printf("  VehicleStatusMsg.MissionFailure:               %u\n", CVT.VehicleStatusMsg.MissionFailure);
//		OS_printf("\n");
//	}
//
//	if(n==7 || n==10){
//		OS_printf("  VehicleLandDetectedMsg.Timestamp:            %llu\n", CVT.VehicleLandDetectedMsg.Timestamp);
//		OS_printf("  VehicleLandDetectedMsg.AltMax:               %f\n", CVT.VehicleLandDetectedMsg.AltMax);
//		OS_printf("  VehicleLandDetectedMsg.Landed:               %d\n", CVT.VehicleLandDetectedMsg.Landed);
//		OS_printf("  VehicleLandDetectedMsg.Freefall:             %d\n", CVT.VehicleLandDetectedMsg.Freefall);
//		OS_printf("  VehicleLandDetectedMsg.GroundContact:        %d\n", CVT.VehicleLandDetectedMsg.GroundContact);
//		OS_printf("\n");
//	}
//
//	if(n==8 || n==10){
//		OS_printf("  VehicleLocalPositionMsg.Timestamp:               %llu\n", CVT.VehicleLocalPositionMsg.Timestamp);
//		OS_printf("  VehicleLocalPositionMsg.RefTimestamp:            %llu\n", CVT.VehicleLocalPositionMsg.RefTimestamp);
//		OS_printf("  VehicleLocalPositionMsg.RefLat:                  %lld\n", CVT.VehicleLocalPositionMsg.RefLat);
//		OS_printf("  VehicleLocalPositionMsg.RefLon:                  %lld\n", CVT.VehicleLocalPositionMsg.RefLon);
//		OS_printf("  VehicleLocalPositionMsg.SurfaceBottomTimestamp:  %llu\n", CVT.VehicleLocalPositionMsg.SurfaceBottomTimestamp);
//		OS_printf("  VehicleLocalPositionMsg.X:                       %f\n", CVT.VehicleLocalPositionMsg.X);
//		OS_printf("  VehicleLocalPositionMsg.Y:                       %f\n", CVT.VehicleLocalPositionMsg.Y);
//		OS_printf("  VehicleLocalPositionMsg.Z:                       %f\n", CVT.VehicleLocalPositionMsg.Z);
//		OS_printf("  VehicleLocalPositionMsg.Delta_XY[2]:             [%f,%f]\n", CVT.VehicleLocalPositionMsg.Delta_XY[0],CVT.VehicleLocalPositionMsg.Delta_XY[1]);
//		OS_printf("  VehicleLocalPositionMsg.Delta_Z:            	  %f\n", CVT.VehicleLocalPositionMsg.Delta_Z);
//		OS_printf("  VehicleLocalPositionMsg.VX:                      %f\n", CVT.VehicleLocalPositionMsg.VX);
//		OS_printf("  VehicleLocalPositionMsg.VY:                      %f\n", CVT.VehicleLocalPositionMsg.VY);
//		OS_printf("  VehicleLocalPositionMsg.VZ:                      %f\n", CVT.VehicleLocalPositionMsg.VZ);
//		OS_printf("  VehicleLocalPositionMsg.Delta_VXY[2]:            [%f,%f]\n", CVT.VehicleLocalPositionMsg.Delta_VXY[0],CVT.VehicleLocalPositionMsg.Delta_VXY[1]);
//		OS_printf("  VehicleLocalPositionMsg.Delta_VZ:                %f\n", CVT.VehicleLocalPositionMsg.Delta_VZ);
//		OS_printf("  VehicleLocalPositionMsg.AX:                      %f\n", CVT.VehicleLocalPositionMsg.AX);
//		OS_printf("  VehicleLocalPositionMsg.AY:                      %f\n", CVT.VehicleLocalPositionMsg.AY);
//		OS_printf("  VehicleLocalPositionMsg.AZ:                      %f\n", CVT.VehicleLocalPositionMsg.AZ);
//		OS_printf("  VehicleLocalPositionMsg.Yaw:                     %f\n", CVT.VehicleLocalPositionMsg.Yaw);
//		OS_printf("  VehicleLocalPositionMsg.RefAlt:                  %f\n", CVT.VehicleLocalPositionMsg.RefAlt);
//		OS_printf("  VehicleLocalPositionMsg.DistBottom:              %f\n", CVT.VehicleLocalPositionMsg.DistBottom);
//		OS_printf("  VehicleLocalPositionMsg.DistBottomRate:          %f\n", CVT.VehicleLocalPositionMsg.DistBottomRate);
//		OS_printf("  VehicleLocalPositionMsg.EpH:                     %f\n", CVT.VehicleLocalPositionMsg.EpH);
//		OS_printf("  VehicleLocalPositionMsg.EpV:                     %f\n", CVT.VehicleLocalPositionMsg.EpV);
//		OS_printf("  VehicleLocalPositionMsg.EvH:                     %f\n", CVT.VehicleLocalPositionMsg.EvH);
//		OS_printf("  VehicleLocalPositionMsg.EvV:                     %f\n", CVT.VehicleLocalPositionMsg.EvV);
//		OS_printf("  VehicleLocalPositionMsg.EstimatorType:           %u\n", CVT.VehicleLocalPositionMsg.EstimatorType);
//		OS_printf("  VehicleLocalPositionMsg.XY_Valid:                %d\n", CVT.VehicleLocalPositionMsg.XY_Valid);
//		OS_printf("  VehicleLocalPositionMsg.Z_Valid:                 %d\n", CVT.VehicleLocalPositionMsg.Z_Valid);
//		OS_printf("  VehicleLocalPositionMsg.V_XY_Valid:              %d\n", CVT.VehicleLocalPositionMsg.V_XY_Valid);
//		OS_printf("  VehicleLocalPositionMsg.V_Z_Valid:               %d\n", CVT.VehicleLocalPositionMsg.V_Z_Valid);
//		OS_printf("  VehicleLocalPositionMsg.XY_ResetCounter:         %u\n", CVT.VehicleLocalPositionMsg.XY_ResetCounter);
//		OS_printf("  VehicleLocalPositionMsg.Z_ResetCounter:          %u\n", CVT.VehicleLocalPositionMsg.Z_ResetCounter);
//		OS_printf("  VehicleLocalPositionMsg.VXY_ResetCounter:        %u\n", CVT.VehicleLocalPositionMsg.VXY_ResetCounter);
//		OS_printf("  VehicleLocalPositionMsg.VZ_ResetCounter:         %u\n", CVT.VehicleLocalPositionMsg.VZ_ResetCounter);
//		OS_printf("  VehicleLocalPositionMsg.XY_Global:               %d\n", CVT.VehicleLocalPositionMsg.XY_Global);
//		OS_printf("  VehicleLocalPositionMsg.Z_Global:                %d\n", CVT.VehicleLocalPositionMsg.Z_Global);
//		OS_printf("  VehicleLocalPositionMsg.DistBottomValid:         %d\n", CVT.VehicleLocalPositionMsg.DistBottomValid);
//		OS_printf("\n");
//	}
//
//	if(n==9 || n==10){
//		OS_printf("  VehicleCommandMsg.Timestamp:         %llu\n", CVT.VehicleCommandMsg.Timestamp);
//		OS_printf("  VehicleCommandMsg.Param5:            %lld\n", CVT.VehicleCommandMsg.Param5);
//		OS_printf("  VehicleCommandMsg.Param6:            %lld\n", CVT.VehicleCommandMsg.Param6);
//		OS_printf("  VehicleCommandMsg.Param1:            %f\n", CVT.VehicleCommandMsg.Param1);
//		OS_printf("  VehicleCommandMsg.Param2:            %f\n", CVT.VehicleCommandMsg.Param2);
//		OS_printf("  VehicleCommandMsg.Param3:            %f\n", CVT.VehicleCommandMsg.Param3);
//		OS_printf("  VehicleCommandMsg.Param4:            %f\n", CVT.VehicleCommandMsg.Param4);
//		OS_printf("  VehicleCommandMsg.Param7:            %f\n", CVT.VehicleCommandMsg.Param7);
//		OS_printf("  VehicleCommandMsg.Command:           %d\n", CVT.VehicleCommandMsg.Command);
//		OS_printf("  VehicleCommandMsg.TargetSystem:      %lu\n", CVT.VehicleCommandMsg.TargetSystem);
//		OS_printf("  VehicleCommandMsg.TargetComponent:   %lu\n", CVT.VehicleCommandMsg.TargetComponent);
//		OS_printf("  VehicleCommandMsg.SourceSystem:      %lu\n", CVT.VehicleCommandMsg.SourceSystem);
//		OS_printf("  VehicleCommandMsg.SourceComponent:   %lu\n", CVT.VehicleCommandMsg.SourceComponent);
//		OS_printf("  VehicleCommandMsg.Confirmation:      %u\n", CVT.VehicleCommandMsg.Confirmation);
//		OS_printf("\n\n");
//	}
//}
//
//void NAV::DisplayOutputs(int n){
//	OS_printf("NAV::DisplayOutputs  *************\n");
//
//	if(n==1 || n==10){
//		OS_printf("  PositionSetpointTripletMsg.Timestamp:           %llu\n", PositionSetpointTripletMsg.Timestamp);
//		OS_printf("   Previous - PositionSetpoint.Timestamp:          %llu\n", PositionSetpointTripletMsg.Previous.Timestamp);
//		OS_printf("   Previous - PositionSetpoint.Lat:                %lld\n", PositionSetpointTripletMsg.Previous.Lat);
//		OS_printf("   Previous - PositionSetpoint.Lon:                %lld\n", PositionSetpointTripletMsg.Previous.Lon);
//		OS_printf("   Previous - PositionSetpoint.X:                  %f\n", PositionSetpointTripletMsg.Previous.X);
//		OS_printf("   Previous - PositionSetpoint.Y:                  %f\n", PositionSetpointTripletMsg.Previous.Y);
//		OS_printf("   Previous - PositionSetpoint.Z:                  %f\n", PositionSetpointTripletMsg.Previous.Z);
//		OS_printf("   Previous - PositionSetpoint.VX:                 %f\n", PositionSetpointTripletMsg.Previous.VX);
//		OS_printf("   Previous - PositionSetpoint.VY:                 %f\n", PositionSetpointTripletMsg.Previous.VY);
//		OS_printf("   Previous - PositionSetpoint.VZ:                 %f\n", PositionSetpointTripletMsg.Previous.VZ);
//		OS_printf("   Previous - PositionSetpoint.Alt:            	  %f\n", PositionSetpointTripletMsg.Previous.Alt);
//		OS_printf("   Previous - PositionSetpoint.Yaw:                %f\n", PositionSetpointTripletMsg.Previous.Yaw);
//		OS_printf("   Previous - PositionSetpoint.Yawspeed:           %f\n", PositionSetpointTripletMsg.Previous.Yawspeed);
//		OS_printf("   Previous - PositionSetpoint.LoiterRadius:       %f\n", PositionSetpointTripletMsg.Previous.LoiterRadius);
//		OS_printf("   Previous - PositionSetpoint.PitchMin:           %f\n", PositionSetpointTripletMsg.Previous.PitchMin);
//		OS_printf("   Previous - PositionSetpoint.AX:                 %f\n", PositionSetpointTripletMsg.Previous.AX);
//		OS_printf("   Previous - PositionSetpoint.AY:                 %f\n", PositionSetpointTripletMsg.Previous.AY);
//		OS_printf("   Previous - PositionSetpoint.AZ:                 %f\n", PositionSetpointTripletMsg.Previous.AZ);
//		OS_printf("   Previous - PositionSetpoint.AcceptanceRadius:   %f\n", PositionSetpointTripletMsg.Previous.AcceptanceRadius);
//		OS_printf("   Previous - PositionSetpoint.CruisingSpeed:      %f\n", PositionSetpointTripletMsg.Previous.CruisingSpeed);
//		OS_printf("   Previous - PositionSetpoint.CruisingThrottle:   %f\n", PositionSetpointTripletMsg.Previous.CruisingThrottle);
//		OS_printf("   Previous - PositionSetpoint.Valid:              %d\n", PositionSetpointTripletMsg.Previous.Valid);
//		OS_printf("   Previous - PositionSetpoint.Type:               %d\n", PositionSetpointTripletMsg.Previous.Type);
//		OS_printf("   Previous - PositionSetpoint.PositionValid:      %d\n", PositionSetpointTripletMsg.Previous.PositionValid);
//		OS_printf("   Previous - PositionSetpoint.VelocityFrame:      %d\n", PositionSetpointTripletMsg.Previous.VelocityFrame);
//		OS_printf("   Previous - PositionSetpoint.AltValid:           %d\n", PositionSetpointTripletMsg.Previous.AltValid);
//		OS_printf("   Previous - PositionSetpoint.YawValid:           %d\n", PositionSetpointTripletMsg.Previous.YawValid);
//		OS_printf("   Previous - PositionSetpoint.DisableMcYawControl:%d\n", PositionSetpointTripletMsg.Previous.DisableMcYawControl);
//		OS_printf("   Previous - PositionSetpoint.YawspeedValid:      %d\n", PositionSetpointTripletMsg.Previous.YawspeedValid);
//		OS_printf("   Previous - PositionSetpoint.LoiterDirection:    %d\n", PositionSetpointTripletMsg.Previous.LoiterDirection);
//		OS_printf("   Previous - PositionSetpoint.AccelerationValid:  %d\n", PositionSetpointTripletMsg.Previous.AccelerationValid);
//		OS_printf("   Previous - PositionSetpoint.AccelerationIsForce:%d\n", PositionSetpointTripletMsg.Previous.AccelerationIsForce);
//
//		OS_printf("   Current - PositionSetpoint.Timestamp:          %llu\n", PositionSetpointTripletMsg.Current.Timestamp);
//		OS_printf("   Current - PositionSetpoint.Lat:                %lld\n", PositionSetpointTripletMsg.Current.Lat);
//		OS_printf("   Current - PositionSetpoint.Lon:                %lld\n", PositionSetpointTripletMsg.Current.Lon);
//		OS_printf("   Current - PositionSetpoint.X:                  %f\n", PositionSetpointTripletMsg.Current.X);
//		OS_printf("   Current - PositionSetpoint.Y:                  %f\n", PositionSetpointTripletMsg.Current.Y);
//		OS_printf("   Current - PositionSetpoint.Z:                  %f\n", PositionSetpointTripletMsg.Current.Z);
//		OS_printf("   Current - PositionSetpoint.VX:                 %f\n", PositionSetpointTripletMsg.Current.VX);
//		OS_printf("   Current - PositionSetpoint.VY:                 %f\n", PositionSetpointTripletMsg.Current.VY);
//		OS_printf("   Current - PositionSetpoint.VZ:                 %f\n", PositionSetpointTripletMsg.Current.VZ);
//		OS_printf("   Current - PositionSetpoint.Alt:            	 %f\n", PositionSetpointTripletMsg.Current.Alt);
//		OS_printf("   Current - PositionSetpoint.Yaw:                %f\n", PositionSetpointTripletMsg.Current.Yaw);
//		OS_printf("   Current - PositionSetpoint.Yawspeed:           %f\n", PositionSetpointTripletMsg.Current.Yawspeed);
//		OS_printf("   Current - PositionSetpoint.LoiterRadius:       %f\n", PositionSetpointTripletMsg.Current.LoiterRadius);
//		OS_printf("   Current - PositionSetpoint.PitchMin:           %f\n", PositionSetpointTripletMsg.Current.PitchMin);
//		OS_printf("   Current - PositionSetpoint.AX:                 %f\n", PositionSetpointTripletMsg.Current.AX);
//		OS_printf("   Current - PositionSetpoint.AY:                 %f\n", PositionSetpointTripletMsg.Current.AY);
//		OS_printf("   Current - PositionSetpoint.AZ:                 %f\n", PositionSetpointTripletMsg.Current.AZ);
//		OS_printf("   Current - PositionSetpoint.AcceptanceRadius:   %f\n", PositionSetpointTripletMsg.Current.AcceptanceRadius);
//		OS_printf("   Current - PositionSetpoint.CruisingSpeed:      %f\n", PositionSetpointTripletMsg.Current.CruisingSpeed);
//		OS_printf("   Current - PositionSetpoint.CruisingThrottle:   %f\n", PositionSetpointTripletMsg.Current.CruisingThrottle);
//		OS_printf("   Current - PositionSetpoint.Valid:              %d\n", PositionSetpointTripletMsg.Current.Valid);
//		OS_printf("   Current - PositionSetpoint.Type:               %d\n", PositionSetpointTripletMsg.Current.Type);
//		OS_printf("   Current - PositionSetpoint.PositionValid:      %d\n", PositionSetpointTripletMsg.Current.PositionValid);
//		OS_printf("   Current - PositionSetpoint.VelocityFrame:      %d\n", PositionSetpointTripletMsg.Current.VelocityFrame);
//		OS_printf("   Current - PositionSetpoint.AltValid:           %d\n", PositionSetpointTripletMsg.Current.AltValid);
//		OS_printf("   Current - PositionSetpoint.YawValid:           %d\n", PositionSetpointTripletMsg.Current.YawValid);
//		OS_printf("   Current - PositionSetpoint.DisableMcYawControl:%d\n", PositionSetpointTripletMsg.Current.DisableMcYawControl);
//		OS_printf("   Current - PositionSetpoint.YawspeedValid:      %d\n", PositionSetpointTripletMsg.Current.YawspeedValid);
//		OS_printf("   Current - PositionSetpoint.LoiterDirection:    %d\n", PositionSetpointTripletMsg.Current.LoiterDirection);
//		OS_printf("   Current - PositionSetpoint.AccelerationValid:  %d\n", PositionSetpointTripletMsg.Current.AccelerationValid);
//		OS_printf("   Current - PositionSetpoint.AccelerationIsForce:%d\n", PositionSetpointTripletMsg.Current.AccelerationIsForce);
//
//		OS_printf("   Next - PositionSetpoint.Timestamp:          %llu\n", PositionSetpointTripletMsg.Next.Timestamp);
//		OS_printf("   Next - PositionSetpoint.Lat:                %lld\n", PositionSetpointTripletMsg.Next.Lat);
//		OS_printf("   Next - PositionSetpoint.Lon:                %lld\n", PositionSetpointTripletMsg.Next.Lon);
//		OS_printf("   Next - PositionSetpoint.X:                  %f\n", PositionSetpointTripletMsg.Next.X);
//		OS_printf("   Next - PositionSetpoint.Y:                  %f\n", PositionSetpointTripletMsg.Next.Y);
//		OS_printf("   Next - PositionSetpoint.Z:                  %f\n", PositionSetpointTripletMsg.Next.Z);
//		OS_printf("   Next - PositionSetpoint.VX:                 %f\n", PositionSetpointTripletMsg.Next.VX);
//		OS_printf("   Next - PositionSetpoint.VY:                 %f\n", PositionSetpointTripletMsg.Next.VY);
//		OS_printf("   Next - PositionSetpoint.VZ:                 %f\n", PositionSetpointTripletMsg.Next.VZ);
//		OS_printf("   Next - PositionSetpoint.Alt:            	  %f\n", PositionSetpointTripletMsg.Next.Alt);
//		OS_printf("   Next - PositionSetpoint.Yaw:                %f\n", PositionSetpointTripletMsg.Next.Yaw);
//		OS_printf("   Next - PositionSetpoint.Yawspeed:           %f\n", PositionSetpointTripletMsg.Next.Yawspeed);
//		OS_printf("   Next - PositionSetpoint.LoiterRadius:       %f\n", PositionSetpointTripletMsg.Next.LoiterRadius);
//		OS_printf("   Next - PositionSetpoint.PitchMin:           %f\n", PositionSetpointTripletMsg.Next.PitchMin);
//		OS_printf("   Next - PositionSetpoint.AX:                 %f\n", PositionSetpointTripletMsg.Next.AX);
//		OS_printf("   Next - PositionSetpoint.AY:                 %f\n", PositionSetpointTripletMsg.Next.AY);
//		OS_printf("   Next - PositionSetpoint.AZ:                 %f\n", PositionSetpointTripletMsg.Next.AZ);
//		OS_printf("   Next - PositionSetpoint.AcceptanceRadius:   %f\n", PositionSetpointTripletMsg.Next.AcceptanceRadius);
//		OS_printf("   Next - PositionSetpoint.CruisingSpeed:      %f\n", PositionSetpointTripletMsg.Next.CruisingSpeed);
//		OS_printf("   Next - PositionSetpoint.CruisingThrottle:   %f\n", PositionSetpointTripletMsg.Next.CruisingThrottle);
//		OS_printf("   Next - PositionSetpoint.Valid:              %d\n", PositionSetpointTripletMsg.Next.Valid);
//		OS_printf("   Next - PositionSetpoint.Type:               %d\n", PositionSetpointTripletMsg.Next.Type);
//		OS_printf("   Next - PositionSetpoint.PositionValid:      %d\n", PositionSetpointTripletMsg.Next.PositionValid);
//		OS_printf("   Next - PositionSetpoint.VelocityFrame:      %d\n", PositionSetpointTripletMsg.Next.VelocityFrame);
//		OS_printf("   Next - PositionSetpoint.AltValid:           %d\n", PositionSetpointTripletMsg.Next.AltValid);
//		OS_printf("   Next - PositionSetpoint.YawValid:           %d\n", PositionSetpointTripletMsg.Next.YawValid);
//		OS_printf("   Next - PositionSetpoint.DisableMcYawControl:%d\n", PositionSetpointTripletMsg.Next.DisableMcYawControl);
//		OS_printf("   Next - PositionSetpoint.YawspeedValid:      %d\n", PositionSetpointTripletMsg.Next.YawspeedValid);
//		OS_printf("   Next - PositionSetpoint.LoiterDirection:    %d\n", PositionSetpointTripletMsg.Next.LoiterDirection);
//		OS_printf("   Next - PositionSetpoint.AccelerationValid:  %d\n", PositionSetpointTripletMsg.Next.AccelerationValid);
//		OS_printf("   Next - PositionSetpoint.AccelerationIsForce:%d\n", PositionSetpointTripletMsg.Next.AccelerationIsForce);
//		OS_printf("\n");
//	}
//
//
//	if(n==2 || n==10){
//		OS_printf("  GeofenceResultMsg.Timestamp:            %llu\n", GeofenceResultMsg.Timestamp);
//		OS_printf("  GeofenceResultMsg.GeofenceViolated:     %d\n", GeofenceResultMsg.GeofenceViolated);
//		OS_printf("  GeofenceResultMsg.GeofenceAction:       %d\n", GeofenceResultMsg.GeofenceAction);
//		OS_printf("\n");
//	}
//
//	if(n==3 || n==10){
//		OS_printf("  ActuatorControls3Msg.Timestamp:            %llu\n", ActuatorControls3Msg.Timestamp);
//		OS_printf("  ActuatorControls3Msg.SampleTime:           %llu\n", ActuatorControls3Msg.SampleTime);
//		for(int c=0;c<sizeof(ActuatorControls3Msg.Control);c++){
//			OS_printf("  ActuatorControls3Msg.Control[%d]:          %f\n", c,ActuatorControls3Msg.Control[c]);
//		}
//		OS_printf("\n");
//	}
//
//	if(n==4 || n==10){
//		OS_printf("  FenceMsg.Timestamp:                    %llu\n", FenceMsg.Timestamp);
//		OS_printf("  FenceMsg.Count:                        %ld\n", FenceMsg.Count);
//		for(int v=0;v<sizeof(FenceMsg.Vertices);v++){
//			OS_printf("  FenceMsg.Vertices[%d].Lat:             %f\n", v,FenceMsg.Vertices[v].Lat);
//			OS_printf("  FenceMsg.Vertices[%d].Lon:             %f\n", v,FenceMsg.Vertices[v].Lon);
//		}
//		OS_printf("\n");
//	}
//
//	if(n==5 || n==10){
//		OS_printf("  VehicleLandDetectedMsg.Timestamp:            %llu\n", VehicleLandDetectedMsg.Timestamp);
//		OS_printf("  VehicleLandDetectedMsg.AltMax:               %f\n", VehicleLandDetectedMsg.AltMax);
//		OS_printf("  VehicleLandDetectedMsg.Landed:               %d\n", VehicleLandDetectedMsg.Landed);
//		OS_printf("  VehicleLandDetectedMsg.Freefall:             %d\n", VehicleLandDetectedMsg.Freefall);
//		OS_printf("  VehicleLandDetectedMsg.GroundContact:        %d\n", VehicleLandDetectedMsg.GroundContact);
//		OS_printf("\n");
//	}
//
//	if(n==6 || n==10){
//		OS_printf("  MissionResultMsg.Timestamp:               %llu\n", MissionResultMsg.Timestamp);
//		OS_printf("  MissionResultMsg.InstanceCount:           %ld\n", MissionResultMsg.InstanceCount);
//		OS_printf("  MissionResultMsg.SeqReached:              %ld\n", MissionResultMsg.SeqReached);
//		OS_printf("  MissionResultMsg.ItemChangedIndex:        %ld\n", MissionResultMsg.ItemChangedIndex);
//		OS_printf("  MissionResultMsg.ItemDoJumpRemaining:     %ld\n", MissionResultMsg.ItemDoJumpRemaining);
//		OS_printf("  MissionResultMsg.Valid:                   %d\n", MissionResultMsg.Valid);
//		OS_printf("  MissionResultMsg.Warning:                 %d\n", MissionResultMsg.Warning);
//		OS_printf("  MissionResultMsg.Reached:                 %d\n", MissionResultMsg.Reached);
//		OS_printf("  MissionResultMsg.Finished:                %d\n", MissionResultMsg.Finished);
//		OS_printf("  MissionResultMsg.StayInFailsafe:          %d\n", MissionResultMsg.StayInFailsafe);
//		OS_printf("  MissionResultMsg.FlightTermination:       %d\n", MissionResultMsg.FlightTermination);
//		OS_printf("  MissionResultMsg.ItemDoJumpChanged:       %d\n", MissionResultMsg.ItemDoJumpChanged);
//		OS_printf("  MissionResultMsg.MissionFailure:          %d\n", MissionResultMsg.MissionFailure);
//		OS_printf("\n");
//	}
//
//	if(n==7 || n==10){
//		OS_printf("  VehicleCommandMsgOut.Timestamp:         %llu\n", VehicleCommandMsgOut.Timestamp);
//		OS_printf("  VehicleCommandMsgOut.Param5:            %lld\n", VehicleCommandMsgOut.Param5);
//		OS_printf("  VehicleCommandMsgOut.Param6:            %lld\n", VehicleCommandMsgOut.Param6);
//		OS_printf("  VehicleCommandMsgOut.Param1:            %f\n", VehicleCommandMsgOut.Param1);
//		OS_printf("  VehicleCommandMsgOut.Param2:            %f\n", VehicleCommandMsgOut.Param2);
//		OS_printf("  VehicleCommandMsgOut.Param3:            %f\n", VehicleCommandMsgOut.Param3);
//		OS_printf("  VehicleCommandMsgOut.Param4:            %f\n", VehicleCommandMsgOut.Param4);
//		OS_printf("  VehicleCommandMsgOut.Param7:            %f\n", VehicleCommandMsgOut.Param7);
//		OS_printf("  VehicleCommandMsgOut.Command:           %d\n", VehicleCommandMsgOut.Command);
//		OS_printf("  VehicleCommandMsgOut.TargetSystem:      %lu\n", VehicleCommandMsgOut.TargetSystem);
//		OS_printf("  VehicleCommandMsgOut.TargetComponent:   %lu\n", VehicleCommandMsgOut.TargetComponent);
//		OS_printf("  VehicleCommandMsgOut.SourceSystem:      %lu\n", VehicleCommandMsgOut.SourceSystem);
//		OS_printf("  VehicleCommandMsgOut.SourceComponent:   %lu\n", VehicleCommandMsgOut.SourceComponent);
//		OS_printf("  VehicleCommandMsgOut.Confirmation:      %u\n", VehicleCommandMsgOut.Confirmation);
//		OS_printf("\n\n");
//	}
//}
//
//

/************************/
/*  End of File Comment */
/************************/
