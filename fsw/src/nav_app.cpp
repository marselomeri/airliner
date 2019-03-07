/************************************************************************
 ** Includes
 *************************************************************************/
#include <string.h>

#include "cfe.h"

#include "nav_app.h"
#include "nav_msg.h"
#include "nav_version.h"
#include <math/Limits.hpp>

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
NAV::NAV() {

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV::~NAV() {

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitEvent() {
    int32 iStatus = CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog(
                "NAV - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitPipe() {
    int32 iStatus = CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    NAV_SCH_PIPE_DEPTH,
    NAV_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS) {
        iStatus = CFE_SB_SubscribeEx(NAV_WAKEUP_MID, SchPipeId,
                CFE_SB_Default_Qos, NAV_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "Sch Pipe failed to subscribe to NAV_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(NAV_SEND_HK_MID, SchPipeId,
                CFE_SB_Default_Qos, NAV_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to NAV_SEND_HK_MID. (0x%08X)",
                    (unsigned int) iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_HOME_POSITION_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_HOME_POSITION_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_SENSOR_COMBINED_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_SENSOR_COMBINED_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_MISSION_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_MISSION_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GPS_POSITION_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_GPS_POSITION_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GLOBAL_POSITION_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_GLOBAL_POSITION_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_STATUS_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_STATUS_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LAND_DETECTED_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_LAND_DETECTED_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LOCAL_POSITION_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_LOCAL_POSITION_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_COMMAND_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_COMMAND_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }
    } else {
        (void) CFE_EVS_SendEvent(NAV_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
                "Failed to create SCH pipe (0x%08lX)", iStatus);
        goto NAV_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    NAV_CMD_PIPE_DEPTH,
    NAV_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS) {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(NAV_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to NAV_CMD_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }
    } else {
        (void) CFE_EVS_SendEvent(NAV_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
                "Failed to create CMD pipe (0x%08lX)", iStatus);
        goto NAV_InitPipe_Exit_Tag;
    }

    NAV_InitPipe_Exit_Tag: return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::InitData() {
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
    NAV_HK_TLM_MID, sizeof(HkTlm), TRUE);

    /* Init output messages */
    /*CFE_SB_InitMsg(&VehicleLandDetectedMsg,
     PX4_VEHICLE_LAND_DETECTED_MID, sizeof(PX4_VehicleLandDetectedMsg_t), TRUE);*/

    /* Init output messages */
    /*CFE_SB_InitMsg(&FenceMsg,
     PX4_FENCE_MID, sizeof(PX4_FenceMsg_t), TRUE);*/

    /* Init output messages */
    /*CFE_SB_InitMsg(&ActuatorControls3Msg,
     PX4_ACTUATOR_CONTROLS_3_MID, sizeof(PX4_ActuatorControlsMsg_t), TRUE);*/

    /* Init output messages */
    CFE_SB_InitMsg(&MissionResultMsg, PX4_MISSION_RESULT_MID,
            sizeof(PX4_MissionResultMsg_t), TRUE);

    /* Init output messages */
    /*CFE_SB_InitMsg(&GeofenceResultMsg,
     PX4_GEOFENCE_RESULT_MID, sizeof(PX4_GeofenceResultMsg_t), TRUE);*/

    /* Init output messages */
    CFE_SB_InitMsg(&PositionSetpointTripletMsg,
            PX4_POSITION_SETPOINT_TRIPLET_MID,
            sizeof(PX4_PositionSetpointTripletMsg_t), TRUE);

    /* Init output messages */
    /*CFE_SB_InitMsg(&VehicleCommandMsgOut,
     PX4_POSITION_SETPOINT_TRIPLET_MID, sizeof(PX4_VehicleCommandMsg_t), TRUE);*/

    HkTlm.NavState = PX4_NAVIGATION_STATE_MANUAL;
	HkTlm.RtlState = RTL_STATE_NONE;
    HkTlm.MissionItemReached = FALSE;
    HkTlm.WaypointPositionReached = FALSE;
	HkTlm.WaypointYawReached = FALSE;
	HkTlm.RtlForceDescentExecuting = FALSE;
	HkTlm.RtlForceDescentCompleted = FALSE;
	HkTlm.LandForceDescentExecuting = FALSE;
	HkTlm.LandForceDescentCompleted = FALSE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitApp() {
    int32 iStatus = CFE_SUCCESS;
    int8 hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to init events (0x%08lX)\n",
                iStatus);
        goto NAV_InitApp_Exit_Tag;
    } else {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS) {
        goto NAV_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS) {
        goto NAV_InitApp_Exit_Tag;
    }

    /* Updating application params from platform-nav-config-table */
    UpdateParamsFromTable();

    NAV_InitApp_Exit_Tag: if (iStatus == CFE_SUCCESS) {
        (void) CFE_EVS_SendEvent(NAV_INIT_INF_EID, CFE_EVS_INFORMATION,
                "Initialized.  Version %d.%d.%d.%d",
                NAV_MAJOR_VERSION,
                NAV_MINOR_VERSION,
                NAV_REVISION,
                NAV_MISSION_REV);
    } else {
        if (hasEvents == 1) {
            (void) CFE_ES_WriteToSysLog(
                    "NAV - Application failed to initialize\n");
        }
    }

    return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 NAV::RcvSchPipeMsg(int32 iBlocking) {
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t* MsgPtr = NULL;
    CFE_SB_MsgId_t MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS) {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId) {
        case NAV_WAKEUP_MID:

            /* Check global position availability */
            if (!CVT.VehicleGlobalPosition.Timestamp == 0) {
                Execute();
            }

            break;

        case NAV_SEND_HK_MID:
            ProcessCmdPipe();
            ReportHousekeeping();
            break;

        case PX4_HOME_POSITION_MID:
            memcpy(&CVT.HomePositionMsg, MsgPtr, sizeof(CVT.HomePositionMsg));
            break;

        case PX4_SENSOR_COMBINED_MID:
            memcpy(&CVT.SensorCombinedMsg, MsgPtr,
                    sizeof(CVT.SensorCombinedMsg));
            break;

        case PX4_MISSION_MID:
            memcpy(&CVT.MissionMsg, MsgPtr, sizeof(CVT.MissionMsg));
            break;

        case PX4_VEHICLE_GPS_POSITION_MID:
            memcpy(&CVT.VehicleGpsPositionMsg, MsgPtr,
                    sizeof(CVT.VehicleGpsPositionMsg));
            break;

        case PX4_VEHICLE_GLOBAL_POSITION_MID:
            memcpy(&CVT.VehicleGlobalPosition, MsgPtr,
                    sizeof(CVT.VehicleGlobalPosition));
            break;

        case PX4_VEHICLE_STATUS_MID:
            memcpy(&CVT.VehicleStatusMsg, MsgPtr, sizeof(CVT.VehicleStatusMsg));
            break;

        case PX4_VEHICLE_LAND_DETECTED_MID:
            memcpy(&CVT.VehicleLandDetectedMsg, MsgPtr,
                    sizeof(CVT.VehicleLandDetectedMsg));
            break;

        case PX4_VEHICLE_LOCAL_POSITION_MID:
            memcpy(&CVT.VehicleLocalPositionMsg, MsgPtr,
                    sizeof(CVT.VehicleLocalPositionMsg));
            break;

        case PX4_VEHICLE_COMMAND_MID:
            new_command_arrived = true;
            memcpy(&CVT.VehicleCommandMsg, MsgPtr,
                    sizeof(CVT.VehicleCommandMsg));
            break;

        case PX4_DISTANCE_SENSOR_MID:
            memcpy(&CVT.DistanceSensorMsg, MsgPtr,
                    sizeof(CVT.DistanceSensorMsg));
            break;

        default:
            (void) CFE_EVS_SendEvent(NAV_MSGID_ERR_EID, CFE_EVS_ERROR,
                    "Recvd invalid SCH msgId (0x%04X)", MsgId);
        }
    } else if (iStatus == CFE_SB_NO_MESSAGE) {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    } else if (iStatus == CFE_SB_TIME_OUT) {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    } else {
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

void NAV::ProcessCmdPipe() {
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t* CmdMsgPtr = NULL;
    CFE_SB_MsgId_t CmdMsgId;

    /* Process command messages until the pipe is empty */
    while (1) {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, CmdPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS) {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId) {
            case NAV_CMD_MID:
                ProcessAppCmds(CmdMsgPtr);
                break;

            default:
                /* Bump the command error counter for an unknown command.
                 * (This should only occur if it was subscribed to with this
                 *  pipe, but not handled in this switch-case.) */
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(NAV_MSGID_ERR_EID, CFE_EVS_ERROR,
                        "Recvd invalid CMD msgId (0x%04X)",
                        (unsigned short) CmdMsgId);
                break;
            }
        } else if (iStatus == CFE_SB_NO_MESSAGE) {
            break;
        } else {
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

void NAV::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr) {
    uint32 uiCmdCode = 0;

    if (MsgPtr != NULL) {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode) {
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
                    "Recvd invalid command code (%u)",
                    (unsigned int) uiCmdCode);
            break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send NAV Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ReportHousekeeping() {
	HkTlm.NavState = CVT.VehicleStatusMsg.NavState;
	HkTlm.RtlState = rtl_state;

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &HkTlm);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::SendVehicleLandDetectedMsg() {
    /*CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VehicleLandDetectedMsg);
     CFE_SB_SendMsg((CFE_SB_Msg_t*)&VehicleLandDetectedMsg);*/
}

void NAV::SendFenceMsg() {
    /*CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&FenceMsg);
     CFE_SB_SendMsg((CFE_SB_Msg_t*)&FenceMsg);*/
}

void NAV::SendActuatorControls3Msg() {
    /*CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ActuatorControls3Msg);
     CFE_SB_SendMsg((CFE_SB_Msg_t*)&ActuatorControls3Msg);*/
}

void NAV::SendMissionResultMsg() {
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &MissionResultMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &MissionResultMsg);
}

void NAV::SendGeofenceResultMsg() {
    /*CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&GeofenceResultMsg);
     CFE_SB_SendMsg((CFE_SB_Msg_t*)&GeofenceResultMsg);*/
}

void NAV::SendPositionSetpointTripletMsg() {
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &PositionSetpointTripletMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &PositionSetpointTripletMsg);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean NAV::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 usExpectedLen) {
    boolean bResult = TRUE;
    uint16 usMsgLen = 0;

    if (MsgPtr != NULL) {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen) {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent(NAV_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                    "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                            "msgLen=%d, expectedLen=%d", MsgId, usCmdCode,
                    usMsgLen, usExpectedLen);
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
extern "C" void NAV_AppMain() {
    oNAV.AppMain();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::AppMain() {
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog(
                "NAV - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS) {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS) {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(NAV_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);
    } else {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE) {
        RcvSchPipeMsg(NAV_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if (iStatus != CFE_SUCCESS) {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}

int NAV::Execute() {

    /* Set vehicle arming state */
    if (CVT.VehicleStatusMsg.Timestamp != 0 && !vehicle_status_update_once) {
        CVT.VehicleStatusMsg.ArmingState =
                PX4_ArmingState_t::PX4_ARMING_STATE_STANDBY;
        vehicle_status_update_once = true;
    }

    /* Execute only on command event*/
    if (new_command_arrived) {
        /* Reset new command flag*/
        new_command_arrived = false;
        /* Configure messages on command receipt */
        if (CVT.VehicleCommandMsg.Command
                == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_REPOSITION) {
            /* EVENT: DO REPOSITION
             * store current position as previous and goal as next */
            PX4_PositionSetpointTripletMsg_t* RepositionTriplet_ptr =
                    GetRepositionTripletMsg();

            RepositionTriplet_ptr->Previous.Yaw = CVT.VehicleGlobalPosition.Yaw;
            RepositionTriplet_ptr->Previous.Lat = CVT.VehicleGlobalPosition.Lat;
            RepositionTriplet_ptr->Previous.Lon = CVT.VehicleGlobalPosition.Lon;
            RepositionTriplet_ptr->Previous.Alt = CVT.VehicleGlobalPosition.Alt;

            /* Store new current position */
            RepositionTriplet_ptr->Current.LoiterRadius =
                    nav_params.nav_loiter_rad;
            RepositionTriplet_ptr->Current.LoiterDirection = 1;
            RepositionTriplet_ptr->Current.Type =
                    PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER;

            /* Assign yaw to current position set point */
            if (PX4_ISFINITE(CVT.VehicleCommandMsg.Param4)) {
                RepositionTriplet_ptr->Current.Yaw =
                        CVT.VehicleCommandMsg.Param4;
            } else {
                RepositionTriplet_ptr->Current.Yaw = NAN;
            }

            /* Assign latitude and longitude to current set point */
            if (PX4_ISFINITE(
                    CVT.VehicleCommandMsg.Param5) && PX4_ISFINITE(CVT.VehicleCommandMsg.Param6)) {
                RepositionTriplet_ptr->Current.Lat =
                        (CVT.VehicleCommandMsg.Param5 < 1000) ?
                                CVT.VehicleCommandMsg.Param5 :
                                CVT.VehicleCommandMsg.Param5 / (double) 1e7;
                RepositionTriplet_ptr->Current.Lon =
                        (CVT.VehicleCommandMsg.Param6 < 1000) ?
                                CVT.VehicleCommandMsg.Param6 :
                                CVT.VehicleCommandMsg.Param6 / (double) 1e7;

            } else {
                RepositionTriplet_ptr->Current.Lat =
                        CVT.VehicleGlobalPosition.Lat;
                RepositionTriplet_ptr->Current.Lon =
                        CVT.VehicleGlobalPosition.Lon;
            }

            /* Assign altitude to current set point */
            if (PX4_ISFINITE(CVT.VehicleCommandMsg.Param7)) {
                RepositionTriplet_ptr->Current.Alt =
                        CVT.VehicleCommandMsg.Param7;
            } else {
                RepositionTriplet_ptr->Current.Alt =
                        CVT.VehicleGlobalPosition.Alt;
            }
            /* Assign set point triplet validity */
            RepositionTriplet_ptr->Previous.Valid = true;
            RepositionTriplet_ptr->Current.Valid = true;
            RepositionTriplet_ptr->Next.Valid = false;

        } else if (CVT.VehicleCommandMsg.Command
                == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF) {
            /* EVENT: TAKEOFF
             * store of command hist */
            CommandEventHist();

            /* Avoid subsequent takeoffs */
            if (!subsequent_takeoffs
                    && CVT.VehicleCommandMsg.Command == previous_command.Command
                    && !CVT.VehicleLandDetectedMsg.Landed) {
                (void) CFE_EVS_SendEvent(NAV_SUBSEQ_TAKEOFF_EID, CFE_EVS_ERROR,
                        "Subsequent takeoff should not allowed while flying");

            } else {
                PX4_PositionSetpointTripletMsg_t *TakeoffTriplet_ptr =
                        GetTakeoffTripletMsg();
                /* Store current position as previous and goal as next */
                TakeoffTriplet_ptr->Previous.Yaw =
                        CVT.VehicleGlobalPosition.Yaw;
                TakeoffTriplet_ptr->Previous.Lat =
                        CVT.VehicleGlobalPosition.Lat;
                TakeoffTriplet_ptr->Previous.Lon =
                        CVT.VehicleGlobalPosition.Lon;
                TakeoffTriplet_ptr->Previous.Alt =
                        CVT.VehicleGlobalPosition.Alt;

                /* Store new current position */
                TakeoffTriplet_ptr->Current.LoiterRadius =
                        nav_params.nav_loiter_rad;
                TakeoffTriplet_ptr->Current.LoiterDirection = 1;
                TakeoffTriplet_ptr->Current.Type =
                        PX4_SetpointType_t::PX4_SETPOINT_TYPE_TAKEOFF;

                /* Check if home position is valid, set current yaw and previous valid accordingly */
                if (CVT.HomePositionMsg.Timestamp > 0) {
                    TakeoffTriplet_ptr->Current.Yaw =
                            CVT.VehicleCommandMsg.Param4;
                    TakeoffTriplet_ptr->Previous.Valid = true;
                } else {
                    TakeoffTriplet_ptr->Current.Yaw =
                            CVT.VehicleLocalPositionMsg.Yaw;
                    TakeoffTriplet_ptr->Previous.Valid = false;
                }

                /*  Check if param5 and param6 is finite, set Latitude, Longitude, Altitude and current and next position set point validity */
                if (PX4_ISFINITE(
                        CVT.VehicleCommandMsg.Param5) && PX4_ISFINITE(CVT.VehicleCommandMsg.Param6)) {
                    TakeoffTriplet_ptr->Current.Lat =
                            (CVT.VehicleCommandMsg.Param5 < 1000) ?
                                    CVT.VehicleCommandMsg.Param5 :
                                    CVT.VehicleCommandMsg.Param5 / (double) 1e7;
                    TakeoffTriplet_ptr->Current.Lon =
                            (CVT.VehicleCommandMsg.Param6 < 1000) ?
                                    CVT.VehicleCommandMsg.Param6 :
                                    CVT.VehicleCommandMsg.Param6 / (double) 1e7;
                } else {
                    TakeoffTriplet_ptr->Current.Lat = NAN;
                    TakeoffTriplet_ptr->Current.Lon = NAN;
                }
                /* Assign set point triplet validity */
                TakeoffTriplet_ptr->Current.Alt = CVT.VehicleCommandMsg.Param7;
                TakeoffTriplet_ptr->Current.Valid = true;
                TakeoffTriplet_ptr->Next.Valid = false;
            }
        }
    }

    /* Detect events for navigation actions
     * find if a state is seen for first time or has been active since a while */
    PX4_NavigationState_t CurrentState = CVT.VehicleStatusMsg.NavState;
    boolean first_run = StateChangeDetect();
    boolean active = false;
    if (!first_run) {
        active = true;
    }

    /* If a state is inactive */
    if (CurrentState
            != PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LOITER) {
        LoiterPositionSet = false;
    }

    if (CurrentState != PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL) {
        rtl_state = RTLState::RTL_STATE_NONE;
    }

    /* First run in a navigation mode */
    if (first_run) {
        if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF) {
            (void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION,
                    "Commencing %s", "Takeoff");
            Takeoff();
        } else if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LOITER) {
            (void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION,
                    "Commencing %s", "Loiter");
            Loiter();
        } else if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LAND) {
            (void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION,
                    "Commencing %s", "Land");
            Land();
        } else if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL) {
            (void) CFE_EVS_SendEvent(NAV_ACTION_ST_EID, CFE_EVS_INFORMATION,
                    "Commencing %s", "Return to Launch");
            Rtl();

        } else {
            CanLoiterAtSetpoint = false;

            /* Clear hk values revelant to mission if not in auto mode */
            HkTlm.MissionItemReached = FALSE;
            HkTlm.WaypointPositionReached = FALSE;
	        HkTlm.WaypointYawReached = FALSE;
        }
    }

    /* If the mode is active */
    if (active) {

        if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF) {
            TakeoffActive();
        } else if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LOITER) {
            LoiterActive();
        } else if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_LAND) {
            LandActive();
        } else if (CurrentState
                == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL) {
            RtlActive();
        } else {
            CanLoiterAtSetpoint = false;
        }
    }

    /* If we landed and have not received takeoff setpoint then stay in idle */
    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    if (CVT.VehicleLandDetectedMsg.Landed
            && !((CVT.VehicleStatusMsg.NavState
                    == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF)
                    || (CVT.VehicleStatusMsg.NavState
                            == PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_MISSION))) {
        PositionSetpointTriplet_ptr->Current.Type =
                PX4_SetpointType_t::PX4_SETPOINT_TYPE_IDLE;
        PositionSetpointTriplet_ptr->Current.Valid = true;
        PositionSetpointTriplet_ptr->Previous.Valid = false;
        PositionSetpointTriplet_ptr->Next.Valid = false;
    }

    /* Time stamp out going messages */
    const uint64 now = PX4LIB_GetPX4TimeUs();
    PositionSetpointTripletMsg.Timestamp = now;
    MissionResultMsg.Timestamp = now;

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

void NAV::Takeoff() {
    /* Initialize pointers to messages */
    PX4_PositionSetpointTripletMsg_t *TakeoffTriplet_ptr =
            GetTakeoffTripletMsg();
    PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr =
            GetVehicleGlobalPositionMsg();

    float AbsoluteAltitude = 0.0f;
    float MinPitch = 0.0f;
    float MinAbsoluteAltitude;

    /* Use home position if valid */
    boolean hpv = HomePositionValid();
    if (hpv) {
        MinAbsoluteAltitude = VehicleGlobalPosition_ptr->Alt
                + nav_params.nav_mis_takeoff_alt;
    } else {
        MinAbsoluteAltitude = nav_params.nav_mis_takeoff_alt;
    }

    /* Use altitude if it is already set.
     * if home position is invalid use MinAbsoluteAltitude */
    boolean hpv2 = HomePositionValid();
    if (TakeoffTriplet_ptr->Current.Valid
            && PX4_ISFINITE(TakeoffTriplet_ptr->Current.Alt) && hpv2) {
        AbsoluteAltitude = TakeoffTriplet_ptr->Current.Alt;

        /* If set altitude is less than minimum clearance raise it to that level and throw a warning */
        if (AbsoluteAltitude < MinAbsoluteAltitude) {
            AbsoluteAltitude = MinAbsoluteAltitude;
            (void) CFE_EVS_SendEvent(NAV_LOW_CLEARANCE_ALT_EID,
            CFE_EVS_INFORMATION,
                    "Set altitude lower than minimum clearance : %.2f meters",
                    AbsoluteAltitude);
        }
    } else {
        /* Raise to minimum clearance */
        AbsoluteAltitude = MinAbsoluteAltitude;
        (void) CFE_EVS_SendEvent(NAV_LOW_CLEARANCE_ALT_EID, CFE_EVS_INFORMATION,
                "Set altitude lower than minimum clearance : %.2f meters",
                AbsoluteAltitude);
    }

    /* If new altitude is lower than current altitude, don't go down */
    if (AbsoluteAltitude < VehicleGlobalPosition_ptr->Alt) {
        AbsoluteAltitude = VehicleGlobalPosition_ptr->Alt;
        (void) CFE_EVS_SendEvent(NAV_HIGH_ALT_EID, CFE_EVS_INFORMATION,
                "Set altitude already higher than take off altitude");
    }

    /* Set mission item to takeoff */
    mission_item.NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF;

    /* Use current position */
    mission_item.Lat = VehicleGlobalPosition_ptr->Lat;
    mission_item.Lon = VehicleGlobalPosition_ptr->Lon;
    mission_item.Yaw = VehicleGlobalPosition_ptr->Yaw;
    mission_item.Altitude = AbsoluteAltitude;
    mission_item.AltitudeIsRelative = false;
    mission_item.LoiterRadius = nav_params.nav_loiter_rad;
    mission_item.PitchMin = MinPitch;
    mission_item.AutoContinue = false;
    mission_item.Origin = NAV_Origin_t::ORIGIN_ONBOARD;

    /* Set mission result message */
    PX4_MissionResultMsg_t *MissionResultMsg_ptr = GetMissionResultMsg();
    MissionResultMsg_ptr->Reached = false;
    MissionResultMsg_ptr->Finished = false;

    /* Record mission update event in boolean */
    MissionResultUpdated = true;

    /* Reset mission item reached */
    WaypointPositionReached = false;
    WaypointYawReached = false;
    TimeFirstInsideOrbit = 0;
    TimeWpReached = 0;

    /* Convert mission item to current set point */
    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,
            &mission_item);
    PositionSetpointTriplet_ptr->Previous.Valid = false;
    PositionSetpointTriplet_ptr->Current.YawValid = true;
    PositionSetpointTriplet_ptr->Next.Valid = false;

    if (TakeoffTriplet_ptr->Current.Valid) {
        if (PX4_ISFINITE(TakeoffTriplet_ptr->Current.Yaw)) {
            PositionSetpointTriplet_ptr->Current.Yaw =
                    TakeoffTriplet_ptr->Current.Yaw;
        }

        if (PX4_ISFINITE(
                TakeoffTriplet_ptr->Current.Lat) && PX4_ISFINITE(TakeoffTriplet_ptr -> Current.Lon)) {
            PositionSetpointTriplet_ptr->Current.Lat =
                    TakeoffTriplet_ptr->Current.Lat;
            PositionSetpointTriplet_ptr->Current.Lon =
                    TakeoffTriplet_ptr->Current.Lon;
        }

        /* Mark this as done */
        memset(TakeoffTriplet_ptr, 0, sizeof(*TakeoffTriplet_ptr));

    }

    CanLoiterAtSetpoint = true;
    PositionSetpointTripletUpdated = true;

}

void NAV::TakeoffActive() {

    /* Initialize pointers to messages */
    PX4_PositionSetpointTripletMsg_t *TakeoffTriplet_ptr =
            GetTakeoffTripletMsg();
    PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();
    boolean is_mission_item_reached = IsMissionItemReached();

    if (TakeoffTriplet_ptr->Current.Valid) {
        Takeoff();
    } else if (is_mission_item_reached && !MissionResult_ptr->Finished) {
        MissionResult_ptr->Finished = true;

        /* Set loiter item so position controllers stop doing takeoff logic */
        SetLoiterItem(&mission_item);
        PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
                &PositionSetpointTripletMsg;
        ConvertMissionItemToCurrentSetpoint(
                &PositionSetpointTriplet_ptr->Current, &mission_item);
    }
}

void NAV::Land() {

    PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr =
            GetVehicleGlobalPositionMsg();
    PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
    PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();
    NAV_MissionItem_t * item = &mission_item;
    boolean at_current_position = true;

    /* Set the land item */
    item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND;

    /* Use current position */
    if (at_current_position) {
        /* Descend at current position */
        item->Lat = NAN;
        item->Lon = NAN;
        item->Yaw = VehicleGlobalPosition_ptr->Yaw;

    } else {
        /* Use home position */
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

    /* Set current mission item to Land */
    MissionResult_ptr->Reached = false;
    MissionResult_ptr->Finished = false;
    /* Update mission result and reset mission item reached */
    MissionResultUpdated = true;
    WaypointPositionReached = false;
    WaypointYawReached = false;
    TimeFirstInsideOrbit = 0;
    TimeWpReached = 0;

    /* Convert mission item to current setpoint */
    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    PositionSetpointTriplet_ptr->Previous.Valid = false;
    ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,
            item);
    PositionSetpointTriplet_ptr->Next.Valid = false;

    CanLoiterAtSetpoint = false;
    PositionSetpointTripletUpdated = true;

}

void NAV::LandActive() {
    boolean is_mission_item_reached = IsMissionItemReached();
    PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();
    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
    PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
    NAV_MissionItem_t * item = &mission_item;
    PX4_VehicleGlobalPositionMsg_t* VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();

    /* Bogus Land */
    if(!CVT.VehicleLandDetectedMsg.Landed && !CVT.VehicleLandDetectedMsg.GroundContact &&
            CVT.VehicleLocalPositionMsg.DistBottom < 0.1)
    {
        if(!ForceDescentCompleted && !ForceDescentExecuting){
            ForceDescentExecuting = true;

            item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND;
            item->Lat = NAN;
            item->Lon = NAN;
            item->AltitudeIsRelative = false;
            /* move down 1 m */
            ForceDescentTarget = VehicleGlobalPosition_ptr->Alt - 1;
            item->Altitude = ForceDescentTarget;
            item->Yaw = NAN;
            item->LoiterRadius = nav_params.nav_loiter_rad;
            item->AcceptanceRadius = nav_params.nav_acc_rad;
            item->TimeInside = 0.0f;
            item->AutoContinue = true;
            item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
            ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current, item);
            PositionSetpointTripletUpdated = true;
        }
        else if(!ForceDescentCompleted && ForceDescentExecuting){
            if(fabsf(VehicleGlobalPosition_ptr->Alt - ForceDescentTarget)<0.1){

                ForceDescentExecuting = false;
                ForceDescentCompleted = false;
                ForceDescentTarget = 0;
            }
        }



    }
    else if(CVT.VehicleLandDetectedMsg.Landed || CVT.VehicleLandDetectedMsg.GroundContact){
        ForceDescentExecuting = false;
        ForceDescentCompleted = false;
        ForceDescentTarget = 0;
    }
    else
    {
        if (is_mission_item_reached && !MissionResult_ptr->Finished) {
            PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
                    GetPositionSetpointTripletMsg();
            PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
            NAV_MissionItem_t * item = &mission_item;

            MissionResult_ptr->Reached = true;
            item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
            item->Lat = NAN;
            item->Lon = NAN;
            item->AltitudeIsRelative = false;
            item->Altitude = VehicleGlobalPosition_ptr->Alt - CVT.VehicleLocalPositionMsg.DistBottom - 0.5f; // TODO: Make this a parameter
            item->Yaw = NAN;
            item->LoiterRadius = nav_params.nav_loiter_rad;
            item->AcceptanceRadius = nav_params.nav_acc_rad;
            item->TimeInside = 0.0f;
            item->AutoContinue = true;
            item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
            ConvertMissionItemToCurrentSetpoint(
                    &PositionSetpointTriplet_ptr->Current, item);
            PositionSetpointTripletUpdated = true;

        }
    }

    HkTlm.LandForceDescentExecuting = ForceDescentExecuting;
    HkTlm.LandForceDescentCompleted = ForceDescentCompleted;

}

void NAV::Loiter() {

    PX4_PositionSetpointTripletMsg_t *RepositionTriplet_ptr =
            GetRepositionTripletMsg();

    if (RepositionTriplet_ptr->Current.Valid) {
        LoiterReposition();
    } else {
        LoiterSetPosition();
    }
}

void NAV::LoiterActive() {

    PX4_PositionSetpointTripletMsg_t *RepositionTriplet_ptr =
            GetRepositionTripletMsg();
    PX4_VehicleStatusMsg_t *VehicleStatus_ptr = GetVehicleStatusMsg();

    if (RepositionTriplet_ptr->Current.Valid) {
        LoiterReposition();
    }

    /* Reset loiter position if we get disarmed */
    if (VehicleStatus_ptr->ArmingState
            != PX4_ArmingState_t::PX4_ARMING_STATE_ARMED) {
        LoiterPositionSet = false;
    }
}

void NAV::LoiterReposition() {

    PX4_PositionSetpointTripletMsg_t *RepositionTriplet_ptr =
            GetRepositionTripletMsg();
    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    PX4_VehicleStatusMsg_t *VehicleStatus_ptr = GetVehicleStatusMsg();
    PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr =
            GetVehicleGlobalPositionMsg();

    /* Cannot reposition if not armed */
    if (VehicleStatus_ptr->ArmingState
            == PX4_ArmingState_t::PX4_ARMING_STATE_ARMED) {

        if (RepositionTriplet_ptr->Current.Valid) {

            PositionSetpointTriplet_ptr->Current.VelocityValid = false;
            PositionSetpointTriplet_ptr->Previous.Yaw =
                    VehicleGlobalPosition_ptr->Yaw;
            PositionSetpointTriplet_ptr->Previous.Lat =
                    VehicleGlobalPosition_ptr->Lat;
            PositionSetpointTriplet_ptr->Previous.Lon =
                    VehicleGlobalPosition_ptr->Lon;
            PositionSetpointTriplet_ptr->Previous.Alt =
                    VehicleGlobalPosition_ptr->Alt;
            memcpy(&PositionSetpointTriplet_ptr->Current,
                    &RepositionTriplet_ptr->Current,
                    sizeof(RepositionTriplet_ptr->Current));
            PositionSetpointTriplet_ptr->Next.Valid = false;

            /* Set yaw */
            float travel_dist = get_distance_to_next_waypoint(
                    VehicleGlobalPosition_ptr->Lat,
                    VehicleGlobalPosition_ptr->Lon,
                    PositionSetpointTriplet_ptr->Current.Lat,
                    PositionSetpointTriplet_ptr->Current.Lon);
            if (travel_dist > 1.0f) {
                /* Calculate direction the vehicle should point to */
                PositionSetpointTriplet_ptr->Current.Yaw =
                        get_bearing_to_next_waypoint(
                                VehicleGlobalPosition_ptr->Lat,
                                VehicleGlobalPosition_ptr->Lon,
                                PositionSetpointTriplet_ptr->Current.Lat,
                                PositionSetpointTriplet_ptr->Current.Lon);
            }

            if (PositionSetpointTriplet_ptr->Current.Type
                    == PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER) {
                CanLoiterAtSetpoint = true;
            }
            PositionSetpointTripletUpdated = true;
            memset(RepositionTriplet_ptr, 0, sizeof(*RepositionTriplet_ptr));
        }
    }
}

void NAV::LoiterSetPosition() {

    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    PX4_VehicleStatusMsg_t *VehicleStatus_ptr = GetVehicleStatusMsg();
    PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr =
            GetVehicleGlobalPositionMsg();
    PX4_VehicleLandDetectedMsg_t* VehicleLandDetected_ptr =
            GetVehicleLandDetectedMsg();
    PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
    NAV_MissionItem_t * item = &mission_item;

    float min_clearance = nav_params.nav_mis_ltrmin_alt;
    boolean stopFuncExec = false;

    if (VehicleStatus_ptr->ArmingState
            != PX4_ArmingState_t::PX4_ARMING_STATE_ARMED
            && VehicleLandDetected_ptr->Landed) {
        /* Not setting loiter position if disarmed and landed, instead mark the current
         * setpoint as invalid and idle (both, just to be sure) */
        CanLoiterAtSetpoint = false;
        PositionSetpointTriplet_ptr->Current.Type =
                PX4_SetpointType_t::PX4_SETPOINT_TYPE_IDLE;
        PositionSetpointTripletUpdated = true;
        LoiterPositionSet = false;
        stopFuncExec = true;
    } else if (LoiterPositionSet) {
        /* Already set, nothing to do */
        stopFuncExec = true;
    }

    if (!stopFuncExec) {
        LoiterPositionSet = true;

        /* Set current mission item to loiter */
        if (VehicleLandDetected_ptr->Landed) {
            /* Landed, don't takeoff, but switch to IDLE mode */
            item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
        } else {
            item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM;

            if (CanLoiterAtSetpoint
                    && PositionSetpointTriplet_ptr->Current.Valid) {
                /* Use current position setpoint */
                item->Lat = PositionSetpointTriplet_ptr->Current.Lat;
                item->Lon = PositionSetpointTriplet_ptr->Current.Lon;
                item->Altitude = PositionSetpointTriplet_ptr->Current.Alt;

            } else {
                /* Use current position and use return altitude as clearance */
                item->Lat = VehicleGlobalPosition_ptr->Lat;
                item->Lon = VehicleGlobalPosition_ptr->Lon;
                item->Altitude = VehicleGlobalPosition_ptr->Alt;

                if (min_clearance > 0.0f
                        && item->Altitude
                                < HomePosition_ptr->Alt + min_clearance) {
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
        /* Convert mission item to current setpoint */
        PositionSetpointTriplet_ptr->Current.VelocityValid = false;
        PositionSetpointTriplet_ptr->Previous.Valid = false;
        ConvertMissionItemToCurrentSetpoint(
                &PositionSetpointTriplet_ptr->Current, item);
        PositionSetpointTriplet_ptr->Next.Valid = false;

        if (PositionSetpointTriplet_ptr->Current.Type
                == PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER) {
            CanLoiterAtSetpoint = true;
        }
        PositionSetpointTripletUpdated = true;
    }
}

void NAV::Rtl() {

    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr =
            GetVehicleGlobalPositionMsg();
    PX4_VehicleLandDetectedMsg_t* VehicleLandDetected_ptr =
            GetVehicleLandDetectedMsg();
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
    ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,
            item);
    PositionSetpointTriplet_ptr->Previous.Valid = false;
    PositionSetpointTriplet_ptr->Next.Valid = false;

    float rtl_altitude =
            (nav_params.nav_rtl_return_alt < VehicleLandDetected_ptr->AltMax) ?
                    nav_params.nav_rtl_return_alt :
                    VehicleLandDetected_ptr->AltMax;

    /* For safety reasons don't go into RTL if landed */
    if (VehicleLandDetected_ptr->Landed) {
        rtl_state = RTLState::RTL_STATE_LANDED;
        (void) CFE_EVS_SendEvent(NAV_RTL_LND_SFGA_EID, CFE_EVS_INFORMATION,
                "Already landed, not executing RTL");

    } else if (VehicleGlobalPosition_ptr->Alt
            < (HomePosition_ptr->Alt + rtl_altitude)) {
        /* If lower than return altitude, climb up first */
        rtl_state = RTLState::RTL_STATE_CLIMB;
    } else {
        rtl_state = RTLState::RTL_STATE_RETURN;
        item->AltitudeIsRelative = false;
        item->Altitude = VehicleGlobalPosition_ptr->Alt;
    }
    SetRtlItem();

}

void NAV::SetRtlItem() {

    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
            GetPositionSetpointTripletMsg();
    PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr =
            GetVehicleGlobalPositionMsg();
    PX4_VehicleLandDetectedMsg_t* VehicleLandDetected_ptr =
            GetVehicleLandDetectedMsg();
    PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
    NAV_MissionItem_t * item = &mission_item;

    CanLoiterAtSetpoint = false;

    switch (rtl_state) {

    case RTLState::RTL_STATE_CLIMB: {
        /* Check if we are pretty close to home already */
        float home_distance = get_distance_to_next_waypoint(
                HomePosition_ptr->Lat, HomePosition_ptr->Lon,
                VehicleGlobalPosition_ptr->Lat, VehicleGlobalPosition_ptr->Lon);
        /* If we are close to home we do not climb as high, otherwise we climb to return alt */
        float rtl_altitude =
                (nav_params.nav_rtl_return_alt < VehicleLandDetected_ptr->AltMax) ?
                        nav_params.nav_rtl_return_alt :
                        VehicleLandDetected_ptr->AltMax;
        float climb_alt = HomePosition_ptr->Alt + rtl_altitude;
        /* We are close to home, limit climb to min */
        if (home_distance < nav_params.nav_rtl_min_dist) {
            climb_alt = HomePosition_ptr->Alt + nav_params.nav_rtl_descend_alt;
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
                "RTL: Commencing climb to %d m (%d m above home)",
                (int) climb_alt, (int) (climb_alt - HomePosition_ptr->Alt));
        break;
    }
    case RTLState::RTL_STATE_RETURN: {
        item->Lat = HomePosition_ptr->Lat;
        item->Lon = HomePosition_ptr->Lon;
        /* Check if we are pretty close to home already */
        float home_distance = get_distance_to_next_waypoint(
                HomePosition_ptr->Lat, HomePosition_ptr->Lon,
                VehicleGlobalPosition_ptr->Lat, VehicleGlobalPosition_ptr->Lon);
        if (home_distance < nav_params.nav_rtl_min_dist) {
            item->Yaw = HomePosition_ptr->Yaw;
        } else {
            /* Use current heading to home */
            item->Yaw = get_bearing_to_next_waypoint(
                    VehicleGlobalPosition_ptr->Lat,
                    VehicleGlobalPosition_ptr->Lon, HomePosition_ptr->Lat,
                    HomePosition_ptr->Lon);
        }
        item->LoiterRadius = nav_params.nav_loiter_rad;
        item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT;
        item->AcceptanceRadius = nav_params.nav_acc_rad;
        item->TimeInside = 0.0f;
        item->AutoContinue = true;
        item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
        (void) CFE_EVS_SendEvent(NAV_RTL_RETURN_ST_EID, CFE_EVS_INFORMATION,
                "RTL: Commencing return at %d m (%d m above home)",
                (int) item->Altitude,
                (int) (item->Altitude - HomePosition_ptr->Alt));
        break;
    }
    case RTLState::RTL_STATE_DESCEND: {
        item->Lat = HomePosition_ptr->Lat;
        item->Lon = HomePosition_ptr->Lon;
        item->AltitudeIsRelative = false;
        item->Altitude = HomePosition_ptr->Alt + nav_params.nav_rtl_descend_alt;
        /* Check if we are already lower - then we will just stay there */
        if (item->Altitude > VehicleGlobalPosition_ptr->Alt) {
            item->Altitude = VehicleGlobalPosition_ptr->Alt;
        }
        item->Yaw = HomePosition_ptr->Yaw;
        float d_current = get_distance_to_next_waypoint(
                VehicleGlobalPosition_ptr->Lat, VehicleGlobalPosition_ptr->Lon,
                item->Lat, item->Lon);
        item->LoiterRadius = nav_params.nav_loiter_rad;
        item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT;
        item->AcceptanceRadius = nav_params.nav_acc_rad;
        item->TimeInside = 0.0f;
        item->AutoContinue = true;
        item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;

        /* Disable previous setpoint to prevent drift */
        PositionSetpointTriplet_ptr->Previous.Valid = false;
        (void) CFE_EVS_SendEvent(NAV_RTL_RETURN_ST_EID, CFE_EVS_INFORMATION,
                "RTL: Commencing descend to %d m (%d m above home)",
                (int) item->Altitude,
                (int) (item->Altitude - HomePosition_ptr->Alt));
        break;
    }
    case RTLState::RTL_STATE_LOITER: {
        bool autoland = nav_params.nav_rtl_land_delay > -DELAY_SIGMA;

        item->Lat = HomePosition_ptr->Lat;
        item->Lon = HomePosition_ptr->Lon;
        /* Don't change altitude */
        item->Yaw = HomePosition_ptr->Yaw;
        item->LoiterRadius = nav_params.nav_loiter_rad;
        item->NavCmd =
                autoland ?
                        PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME :
                        PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM;
        item->AcceptanceRadius = nav_params.nav_acc_rad;
        item->TimeInside =
                nav_params.nav_rtl_land_delay < 0.0f ?
                        0.0f : nav_params.nav_rtl_land_delay;
        item->AutoContinue = autoland;
        item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
        CanLoiterAtSetpoint = true;

        float time_inside = GetTimeInside(item);
        if (autoland && (time_inside > FLT_EPSILON)) {
            (void) CFE_EVS_SendEvent(NAV_RTL_LOITER_ST_EID,
            CFE_EVS_INFORMATION, "RTL: Commencing loiter for %.1fs",
                    time_inside);
        } else {
            (void) CFE_EVS_SendEvent(NAV_RTL_RETURN_ST_EID,
            CFE_EVS_INFORMATION, "RTL: Loiter completed");
        }
        break;
    }
    case RTLState::RTL_STATE_LAND: {
        /* Set the land item */
        item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND;
        /* Use current position */
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

    ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current,
            item);
    PositionSetpointTriplet_ptr->Next.Valid = false;
    PositionSetpointTripletUpdated = true;
}

void NAV::AdvanceRtl() {
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
        /* Only go to land if autoland is enabled */
        if (nav_params.nav_rtl_land_delay < -DELAY_SIGMA
                || nav_params.nav_rtl_land_delay > DELAY_SIGMA) {
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

void NAV::RtlActive() {

    boolean is_mission_item_reached = IsMissionItemReached();
    PX4_MissionResultMsg_t* MissionResult_ptr = GetMissionResultMsg();
    PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = GetPositionSetpointTripletMsg();
    PX4_HomePositionMsg_t* HomePosition_ptr = GetHomePosition();
    NAV_MissionItem_t * item = &mission_item;
    PX4_VehicleGlobalPositionMsg_t* VehicleGlobalPosition_ptr = GetVehicleGlobalPositionMsg();

    /* Bogus Land */
    if(!CVT.VehicleLandDetectedMsg.Landed && !CVT.VehicleLandDetectedMsg.GroundContact &&
            CVT.VehicleLocalPositionMsg.DistBottom < 0.1 && rtl_state == RTLState::RTL_STATE_LANDED)
    {
        if(!ForceDescentCompleted && !ForceDescentExecuting){
            ForceDescentExecuting = true;

            item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND;
            item->Lat = NAN;
            item->Lon = NAN;
            item->AltitudeIsRelative = false;
            /* move down 1 m */
            ForceDescentTarget = VehicleGlobalPosition_ptr->Alt - 1;
            item->Altitude = ForceDescentTarget;
            item->Yaw = NAN;
            item->LoiterRadius = nav_params.nav_loiter_rad;
            item->AcceptanceRadius = nav_params.nav_acc_rad;
            item->TimeInside = 0.0f;
            item->AutoContinue = true;
            item->Origin = NAV_Origin_t::ORIGIN_ONBOARD;
            ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr->Current, item);
            PositionSetpointTripletUpdated = true;
        }
        else if(!ForceDescentCompleted && ForceDescentExecuting){
            if(fabsf(VehicleGlobalPosition_ptr->Alt - ForceDescentTarget)<0.1){

                ForceDescentExecuting = false;
                ForceDescentCompleted = false;
                ForceDescentTarget = 0;
            }
        }



    }
    else if(CVT.VehicleLandDetectedMsg.Landed || CVT.VehicleLandDetectedMsg.GroundContact){
        ForceDescentExecuting = false;
        ForceDescentCompleted = false;
        ForceDescentTarget = 0;
    }
    else
    {
        boolean is_mission_item_reached = IsMissionItemReached();
        if (is_mission_item_reached && rtl_state != RTLState::RTL_STATE_LANDED) {

            AdvanceRtl();
            SetRtlItem();
        }

    }

    HkTlm.RtlForceDescentExecuting = ForceDescentExecuting;
    HkTlm.RtlForceDescentCompleted = ForceDescentCompleted;
}

boolean NAV::StateChangeDetect() {
    /* When there is a change in state reset fail safe flag */
    PX4_VehicleStatusMsg_t current_state = CVT.VehicleStatusMsg;
    boolean stateChange = false;
    if (&previous_state == nullptr) {
        PX4_MissionResultMsg_t* gmr = GetMissionResultMsg();
        gmr->StayInFailsafe = false;

        previous_state = current_state;
        stateChange = true;
    } else if (previous_state.NavState != current_state.NavState) {
        PX4_MissionResultMsg_t* gmr = GetMissionResultMsg();
        gmr->StayInFailsafe = false;

        previous_state = current_state;
        stateChange = true;
    }

    return stateChange;
}

void NAV::CommandEventHist() {
    /* Holds command history one level deep */
    PX4_VehicleCommandMsg_t current_command = CVT.VehicleCommandMsg;
    previous_command = current_command;
}

boolean NAV::IsMissionItemReached() {
    /* Fall through */
    boolean isMissionItemReached = false;
    switch (mission_item.NavCmd) {
    case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_SET_SERVO:
        isMissionItemReached = true;
    case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND:
    case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM:
        isMissionItemReached = false;
    case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_CHANGE_SPEED:
        isMissionItemReached = true;
    default:
        /* Do nothing, this is a 3D waypoint */
        break;
    }
    //return isMissionItemReached;

    uint64 now = PX4LIB_GetPX4TimeUs();
    PX4_PositionSetpointTripletMsg_t* pst = GetPositionSetpointTripletMsg();
    PX4_VehicleLandDetectedMsg_t* vld = GetVehicleLandDetectedMsg();
    PX4_VehicleGlobalPositionMsg_t* vgp = GetVehicleGlobalPositionMsg();
    PX4_HomePositionMsg_t* hp = GetHomePosition();
    PX4_VehicleStatusMsg_t* vs = GetVehicleStatusMsg();

    if (!vld->Landed && !WaypointPositionReached) {

        float dist = -1.0f;
        float dist_xy = -1.0f;
        float dist_z = -1.0f;

        float altitude_amsl =
                mission_item.AltitudeIsRelative ?
                        mission_item.Altitude + hp->Alt : mission_item.Altitude;
        dist = get_distance_to_point_global_wgs84(mission_item.Lat,
                mission_item.Lon, altitude_amsl, vgp->Lat, vgp->Lon, vgp->Alt,
                &dist_xy, &dist_z);
        if (mission_item.NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF
                && vs->IsRotaryWing) {
            /* We want to avoid the edge case where the acceptance radius is bigger or equal than
             * the altitude of the takeoff waypoint above home. Otherwise, we do not really follow
             * take-off procedures like leaving the landing gear down. */

            float takeoff_alt =
                    mission_item.AltitudeIsRelative ?
                            mission_item.Altitude :
                            (mission_item.Altitude - hp->Alt);
            float altitude_acceptance_radius = GetAltitudeAcceptedRadius();

            /* It should be safe to takeoff using half of the takeoff_alt as accepted radius */
            if (takeoff_alt > 0 && takeoff_alt < altitude_acceptance_radius) {
                altitude_acceptance_radius = takeoff_alt / 2.0f;
            }

            /* Require only altitude for takeoff for mc */
            if (vgp->Alt > altitude_amsl - altitude_acceptance_radius) {
                WaypointPositionReached = true;
            }
        } else if (mission_item.NavCmd
                == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF) {
            /* For takeoff mission items use the parameter for the takeoff acceptance radius */
            if (dist >= 0.0f && dist <= nav_params.nav_acc_rad
                    && dist_z <= nav_params.nav_acc_rad) {
                WaypointPositionReached = true;
            }
        }

        else {

            /* For normal mission items used their acceptance radius */
            float mission_acceptance_radius = mission_item.AcceptanceRadius;
            /* If set to zero use the default instead */
            if (mission_acceptance_radius < NAV_EPSILON_POSITION) {
                mission_acceptance_radius = nav_params.nav_acc_rad;
            }
            if (dist >= 0.0f && dist <= mission_acceptance_radius
                    && dist_z <= nav_params.nav_alt_rad) {
                WaypointPositionReached = true;
            }
        }
        if (WaypointPositionReached) {
            TimeWpReached = now;
        }
    }

    if (WaypointPositionReached && !WaypointYawReached) {
        /* Added PX4_VEHICLE_CMD_NAV_LOITER_TO_ALT to PX4_VehicleCmd_t */
        if ((vs->IsRotaryWing
                || (mission_item.NavCmd
                        == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TO_ALT
                        && mission_item.ForceHeading))
                && PX4_ISFINITE(mission_item.Yaw)) {

            /* Check course if defined only for rotary wing except takeoff */
            float cog =
                    vs->IsRotaryWing ? vgp->Yaw : atan2f(vgp->VelE, vgp->VelN);
            float yaw_err = _wrap_pi(mission_item.Yaw - cog);

            /* Accept yaw if reached or if timeout is set then we dont ignore force headings */
            if (fabsf(yaw_err)
                    < math::radians((float) nav_params.nav_mis_yaw_err)
                    || (nav_params.nav_mis_yaw_tmt >= FLT_EPSILON
                            && !mission_item.ForceHeading)) {
                WaypointYawReached = true;
            }

            /* If heading needs to be reached, the timeout is enabled and we don't make it we abort */
            if (!WaypointYawReached && mission_item.ForceHeading
                    && (nav_params.nav_mis_yaw_tmt >= FLT_EPSILON)
                    && (now - TimeWpReached
                            >= (uint64) nav_params.nav_mis_yaw_tmt * 1e6f)) {
                SetMissionFaliure("did not reach waypoint before timeout");
            }
        } else {
            WaypointYawReached = true;
        }
    }

    /* Once the position and yaw waypoint have been set we can start the loiter time countdown */
    if (WaypointPositionReached && WaypointYawReached) {
        if (TimeFirstInsideOrbit == 0) {
            TimeFirstInsideOrbit = now;
        }

        /* Check if the MAV was long enough inside the waypoint orbit */
        float time_inside = GetTimeInside(&mission_item);
        if ((time_inside < FLT_EPSILON)
                || now - TimeFirstInsideOrbit >= (uint64) time_inside * 1e6f) {
            /* Exit xtrack location */
            if (mission_item.LoiterExitXTrack
                    && (mission_item.NavCmd
                            == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TO_ALT
                            || mission_item.NavCmd
                                    == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME)) {
                /* Reset lat/lon of loiter waypoint so wehicle follows tangent */
                PX4_PositionSetpoint_t * curr_sp = &pst->Current;
                PX4_PositionSetpoint_t * next_sp = &pst->Next;

                float range = get_distance_to_next_waypoint(curr_sp->Lat,
                        curr_sp->Lon, next_sp->Lat, next_sp->Lon);
                float bearing = get_bearing_to_next_waypoint(curr_sp->Lat,
                        curr_sp->Lon, next_sp->Lat, next_sp->Lon);
                float inner_angle = M_PI_2_F
                        - asinf(mission_item.LoiterRadius / range);

                /* Compute ideal tangent origin */
                if (curr_sp->LoiterDirection > 0) {
                    bearing -= inner_angle;

                } else {
                    bearing += inner_angle;
                }

                /* Replace current setpoint Lat/Lon with tangent coordinate */
                waypoint_from_heading_and_distance(curr_sp->Lat, curr_sp->Lon,
                        bearing, curr_sp->LoiterRadius, &curr_sp->Lat,
                        &curr_sp->Lon);
            }
            isMissionItemReached = true;
        }
    }

    /* Copy values to HK */
    HkTlm.MissionItemReached = isMissionItemReached;
    HkTlm.WaypointPositionReached = WaypointPositionReached;
	HkTlm.WaypointYawReached = WaypointYawReached;

    /* All acceptance criteria must be met in the same iteration */
    WaypointPositionReached = false;
    WaypointYawReached = false;
    return isMissionItemReached;

}

void NAV::SetMissionFaliure(const char* reason) {
    PX4_MissionResultMsg_t* mr = GetMissionResultMsg();
    if (!mr->Failure) {
        mr->Failure = true;
        (void) CFE_EVS_SendEvent(NAV_MSN_FAILED_ERR_EID, CFE_EVS_CRITICAL,
                "Mission failed (%s)", reason);
    }
}

void NAV::ConvertMissionItemToCurrentSetpoint(PX4_PositionSetpoint_t *ps,
        NAV_MissionItem_t *mi) {

    if (!(!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT
            || !mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM
            || !mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME
            || !mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND
            || !mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF)) {

        PX4_HomePositionMsg_t *HomePositionMsg_ptr = GetHomePosition();

        ps->Lat = mi->Lat;
        ps->Lon = mi->Lon;
        ps->Alt =
                mi->AltitudeIsRelative ?
                        mi->Altitude + HomePositionMsg_ptr->Alt : mi->Altitude;
        ps->Yaw = mi->Yaw;
        ps->LoiterRadius =
                (fabsf(mi->LoiterRadius) > NAV_EPSILON_POSITION) ?
                        fabsf(mi->LoiterRadius) : nav_params.nav_loiter_rad;
        ps->LoiterDirection = (mi->LoiterRadius > 0) ? 1 : -1;
        ps->AcceptanceRadius = mi->AcceptanceRadius;
        ps->DisableMcYawControl = mi->DisableMcYaw;

        ps->CruisingSpeed = GetCruisingSpeed();
        ps->CruisingThrottle = GetCruisingThrottle();

        switch (mi->NavCmd) {

        case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF: {
            PX4_VehicleStatusMsg_t* gvs = GetVehicleStatusMsg();
            PX4_VehicleLandDetectedMsg_t* gvld = GetVehicleLandDetectedMsg();
            if (gvs->ArmingState == PX4_ArmingState_t::PX4_ARMING_STATE_ARMED
                    && !(gvld->Landed)) {
                ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_POSITION;
            } else {
                ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_TAKEOFF;
                /* Set pitch and ensure that the hold time is zero */
                ps->PitchMin = mi->PitchMin;
            }

            break;
        }
        case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND: {
            ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_LAND;
            break;
        }
        case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME: {

        }
        case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM: {
            ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER;
            break;
        }
        default: {
            ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_POSITION;
            break;
        }
            ps->Valid = true;
        }
    }
}

void NAV::SetLoiterItem(NAV_MissionItem_t * item) {
    float min_clearance = -1.0f;
    PX4_VehicleLandDetectedMsg_t * vld = GetVehicleLandDetectedMsg();
    boolean land_detected = vld->Landed;
    if (land_detected) {
        item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_CUSTOM_0;
    } else {
        item->NavCmd = PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM;
        PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr =
                &PositionSetpointTripletMsg;
        if (CanLoiterAtSetpoint && PositionSetpointTriplet_ptr->Current.Valid) {
            /* Use current position setpoint */
            item->Lat = PositionSetpointTriplet_ptr->Current.Lat;
            item->Lon = PositionSetpointTriplet_ptr->Current.Lon;
            item->Altitude = PositionSetpointTriplet_ptr->Current.Alt;
        } else {
            /* Use current position and use return altitude as clearance */
            PX4_VehicleGlobalPositionMsg_t* vgp = GetVehicleGlobalPositionMsg();
            PX4_HomePositionMsg_t* hp = GetHomePosition();
            item->Lat = vgp->Lat;
            item->Lon = vgp->Lon;
            item->Altitude = vgp->Alt;
            if (min_clearance > 0.0f
                    && item->Altitude < hp->Alt + min_clearance) {
                item->Altitude = hp->Alt = min_clearance;
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

float NAV::GetTimeInside(NAV_MissionItem_t * mi) {
    float time = 0.0f;
    if (mi->NavCmd != PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF) {
        time = mi->TimeInside;
    }
    return time;
}

boolean NAV::HomePositionValid() {
    PX4_HomePositionMsg_t* ghp = GetHomePosition();
    boolean hpv = (ghp->Timestamp > 0);
    return hpv;
}

float NAV::GetDefaultAcceptedRadius() {
    return nav_params.nav_acc_rad;
}

void NAV::SetAcceptedRadius(float mission_radius) {
    nav_params.nav_acc_rad = mission_radius;
}

float NAV::GetAltitudeAcceptedRadius() {
    return nav_params.nav_alt_rad;
}

float NAV::GetCruisingThrottle() {
    float msnThrottle = -1.0f;
    if (MissionThrottle > FLT_EPSILON) {
        msnThrottle = MissionThrottle;
    } else {
        return msnThrottle;
    }
}

float NAV::GetCruisingSpeed() {
    boolean is_planned = IsPlannedMission();
    float msnCruisingSpeed = -1.0f;
    if (is_planned && MissionCruisingSpeed > 0.0f) {
        msnCruisingSpeed = MissionCruisingSpeed;
    } else {
        return msnCruisingSpeed;
    }

}

void NAV::UpdateParamsFromTable() {
    if (ConfigTblPtr != nullptr) {

        nav_params.nav_acc_rad = ConfigTblPtr->NAV_ACC_RAD;
        nav_params.nav_alt_rad = ConfigTblPtr->NAV_ALT_RAD;
        nav_params.nav_loiter_rad = ConfigTblPtr->NAV_LOITER_RAD;
        nav_params.nav_mis_takeoff_alt = ConfigTblPtr->NAV_MIS_TAKEOFF_ALT;
        nav_params.nav_mis_yaw_err = ConfigTblPtr->NAV_MIS_YAW_ERR;
        nav_params.nav_mis_yaw_tmt = ConfigTblPtr->NAV_MIS_YAW_TMT;
        nav_params.nav_mis_ltrmin_alt = ConfigTblPtr->NAV_MIS_LTRMIN_ALT;
        nav_params.nav_rtl_return_alt = ConfigTblPtr->NAV_RTL_RETURN_ALT;
        nav_params.nav_rtl_descend_alt = ConfigTblPtr->NAV_RTL_DESCEND_ALT;
        nav_params.nav_rtl_land_delay = ConfigTblPtr->NAV_RTL_LAND_DELAY;
        nav_params.nav_rtl_min_dist = ConfigTblPtr->NAV_RTL_MIN_DIST;
    }

}

/************************/
/*  End of File Comment */
/************************/
