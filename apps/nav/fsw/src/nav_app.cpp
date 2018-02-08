/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "nav_app.h"
#include "nav_msg.h"
#include "nav_version.h"


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
            	//execute();
                break;

            case NAV_SEND_HK_MID:
            	counter = counter+1;
            	OS_printf("count value : %d \n ",counter);

            	execute();
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
void NAV::execute(){
	OS_printf("===================================\n");
	OS_printf("HOME TIMESTAMP:   %lld \n",CVT.HomePositionMsg.Timestamp);
	OS_printf("HOME LATITUDE:   %ld \n",CVT.VehicleGpsPositionMsg.Lat);
	OS_printf("HOME LONGTUDE:   %ld \n",CVT.VehicleGpsPositionMsg.Lon);
	OS_printf("HOME ALTITUDE:   %ld \n",CVT.VehicleGpsPositionMsg.Alt);
	OS_printf("HOME X:   %f \n",CVT.HomePositionMsg.X);
	OS_printf("HOME Y:   %f \n",CVT.HomePositionMsg.Y);
	OS_printf("HOME Z:   %f \n",CVT.HomePositionMsg.Z);
	OS_printf("HOME YAW:   %f \n",CVT.HomePositionMsg.Yaw);
	OS_printf("HOME DirectionX:   %f \n",CVT.HomePositionMsg.DirectionX);
	OS_printf("HOME DirectionY:   %f \n",CVT.HomePositionMsg.DirectionY);
	OS_printf("HOME DirectionZ:   %f \n",CVT.HomePositionMsg.DirectionZ);


	OS_printf("===================================\n\n");

}

float NAV::getDefaultAcceptedRadius(){
	return nav_params.nav_acc_rad;
}

//this function also needs to set this variable in params table
void NAV::setAcceptedRadius(float mission_radius){
	nav_params.nav_acc_rad = mission_radius;
}

float NAV::getAltitudeAcceptedRadius(){
	return nav_params.nav_mc_alt_rad;
}

//float NAV::getCruisingSpeed(){
//
//}




/************************/
/*  End of File Comment */
/************************/
