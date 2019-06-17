/************************************************************************
 ** Includes
 *************************************************************************/
#include <string.h>
#include <cmath>
#include <math.h>
#include <float.h>
#include "cfe.h"

#include "ld_app.h"
#include "ld_msg.h"
#include "ld_version.h"
#include "px4lib_msgids.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LD oLD;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LD::LD() {

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LD::~LD() {

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 LD::InitEvent() {
    int32 iStatus = CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog(
                "LD - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 LD::InitPipe() {
    int32 iStatus = CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    LD_SCH_PIPE_DEPTH,
    LD_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS) {
        iStatus = CFE_SB_SubscribeEx(LD_WAKEUP_MID, SchPipeId,
                CFE_SB_Default_Qos, LD_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "Sch Pipe failed to subscribe to LD_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(LD_SEND_HK_MID, SchPipeId,
                CFE_SB_Default_Qos, LD_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to LD_SEND_HK_MID. (0x%08X)",
                    (unsigned int) iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_ARMED_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_ACTUATOR_ARMED_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_AIRSPEED_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_AIRSPEED_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_CONTROLS_0_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_ACTUATOR_CONTROLS_0_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_CONTROL_STATE_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_CONTROL_STATE_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_BATTERY_STATUS_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_BATTERY_STATUS_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_ATTITUDE_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_ATTITUDE_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_MANUAL_CONTROL_SETPOINT_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_MANUAL_CONTROL_SETPOINT_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LOCAL_POSITION_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_LOCAL_POSITION_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_CONTROL_MODE_MID, SchPipeId,
                CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to PX4_VEHICLE_CONTROL_MODE_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
    } else {
        (void) CFE_EVS_SendEvent(LD_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
                "Failed to create SCH pipe (0x%08lX)", iStatus);
        goto LD_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    LD_CMD_PIPE_DEPTH,
    LD_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS) {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(LD_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS) {
            (void) CFE_EVS_SendEvent(LD_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to LD_CMD_MID. (0x%08lX)",
                    iStatus);
            goto LD_InitPipe_Exit_Tag;
        }
    } else {
        (void) CFE_EVS_SendEvent(LD_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
                "Failed to create CMD pipe (0x%08lX)", iStatus);
        goto LD_InitPipe_Exit_Tag;
    }

    LD_InitPipe_Exit_Tag: return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LD::InitData() {
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
    LD_HK_TLM_MID, sizeof(HkTlm), TRUE);
    /* Init output messages */
    CFE_SB_InitMsg(&VehicleLandDetectedMsg, PX4_VEHICLE_LAND_DETECTED_MID,
            sizeof(PX4_VehicleLandDetectedMsg_t), TRUE);
            
    CFE_SB_InitMsg(&DiagTlm, LD_DIAG_TLM_MID, sizeof(DiagTlm), TRUE);
    
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* LD initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 LD::InitApp() {
    int32 iStatus = CFE_SUCCESS;
    int8 hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog("LD - Failed to init events (0x%08lX)\n",
                iStatus);
        goto LD_InitApp_Exit_Tag;
    } else {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS) {
        goto LD_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS) {
        goto LD_InitApp_Exit_Tag;
    }

    /* Updating application params from platform-nav-config-table */
    UpdateParamsFromTable();

    LD_InitApp_Exit_Tag: if (iStatus == CFE_SUCCESS) {
        (void) CFE_EVS_SendEvent(LD_INIT_INF_EID, CFE_EVS_INFORMATION,
                "Initialized.  Version %d.%d.%d.%d",
                LD_MAJOR_VERSION,
                LD_MINOR_VERSION,
                LD_REVISION,
                LD_MISSION_REV);
    } else {
        if (hasEvents == 1) {
            (void) CFE_ES_WriteToSysLog(
                    "LD - Application failed to initialize\n");
        }
    }

    return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 LD::RcvSchPipeMsg(int32 iBlocking) {
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t* MsgPtr = NULL;
    CFE_SB_MsgId_t MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(LD_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(LD_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS) {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId) {
        case LD_WAKEUP_MID: {
            Execute();
            break;
        }

        case LD_SEND_HK_MID: {
            ProcessCmdPipe();
            ReportHousekeeping();
            break;
        }
        case PX4_ACTUATOR_ARMED_MID: {
            memcpy(&CVT.ActuatorArmedMsg, MsgPtr, sizeof(CVT.ActuatorArmedMsg));
            break;
        }

        case PX4_AIRSPEED_MID: {
            memcpy(&CVT.AirspeedMsg, MsgPtr, sizeof(CVT.AirspeedMsg));
            break;
        }
        case PX4_ACTUATOR_CONTROLS_0_MID: {
            memcpy(&CVT.ActuatorControls0Msg, MsgPtr,
                    sizeof(CVT.ActuatorControls0Msg));
            break;
        }

        case PX4_CONTROL_STATE_MID: {
            memcpy(&CVT.ControlStateMsg, MsgPtr, sizeof(CVT.ControlStateMsg));
            break;
        }

        case PX4_BATTERY_STATUS_MID: {
            memcpy(&CVT.BatteryStatusMsg, MsgPtr, sizeof(CVT.BatteryStatusMsg));
            break;
        }

        case PX4_VEHICLE_ATTITUDE_MID: {
            memcpy(&CVT.VehicleAttitudeMsg, MsgPtr,
                    sizeof(CVT.VehicleAttitudeMsg));
            break;
        }

        case PX4_MANUAL_CONTROL_SETPOINT_MID: {
            memcpy(&CVT.ManualControlSetpointMsg, MsgPtr,
                    sizeof(CVT.ManualControlSetpointMsg));
            break;
        }

        case PX4_VEHICLE_LOCAL_POSITION_MID: {
            memcpy(&CVT.VehicleLocalPositionMsg, MsgPtr,
                    sizeof(CVT.VehicleLocalPositionMsg));
            break;
        }

        case PX4_VEHICLE_CONTROL_MODE_MID: {
            memcpy(&CVT.VehicleControlModeMsg, MsgPtr,
                    sizeof(CVT.VehicleControlModeMsg));
            break;
        }

        default: {
            (void) CFE_EVS_SendEvent(LD_MSGID_ERR_EID, CFE_EVS_ERROR,
                    "Recvd invalid SCH msgId (0x%04X)", MsgId);
        }
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
        (void) CFE_EVS_SendEvent(LD_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void LD::ProcessCmdPipe() {
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t* CmdMsgPtr = NULL;
    CFE_SB_MsgId_t CmdMsgId;

    /* Process command messages until the pipe is empty */
    while (1) {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, CmdPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS) {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId) {
            case LD_CMD_MID:
                ProcessAppCmds(CmdMsgPtr);
                break;

            default:
                /* Bump the command error counter for an unknown command.
                 * (This should only occur if it was subscribed to with this
                 *  pipe, but not handled in this switch-case.) */
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(LD_MSGID_ERR_EID, CFE_EVS_ERROR,
                        "Recvd invalid CMD msgId (0x%04X)",
                        (unsigned short) CmdMsgId);
                break;
            }
        } else if (iStatus == CFE_SB_NO_MESSAGE) {
            break;
        } else {
            (void) CFE_EVS_SendEvent(LD_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                    "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process LD Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void LD::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr) {
    uint32 uiCmdCode = 0;

    if (MsgPtr != NULL) {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode) {
        case LD_NOOP_CC:
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(LD_CMD_NOOP_EID, CFE_EVS_INFORMATION,
                    "Recvd NOOP. Version %d.%d.%d.%d",
                    LD_MAJOR_VERSION,
                    LD_MINOR_VERSION,
                    LD_REVISION,
                    LD_MISSION_REV);
            break;

        case LD_RESET_CC:
            HkTlm.usCmdCnt = 0;
            HkTlm.usCmdErrCnt = 0;
            break;

        default:
            HkTlm.usCmdErrCnt++;
            (void) CFE_EVS_SendEvent(LD_CC_ERR_EID, CFE_EVS_ERROR,
                    "Recvd invalid command code (%u)",
                    (unsigned int) uiCmdCode);
            break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send LD Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void LD::ReportHousekeeping() {
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &HkTlm);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LD::SendVehicleLandDetectedMsg() {
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &VehicleLandDetectedMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &VehicleLandDetectedMsg);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish LD Diag                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LD::SendDiag() {
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &DiagTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &DiagTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr, uint16 usExpectedLen) {
    boolean bResult = TRUE;
    uint16 usMsgLen = 0;

    if (MsgPtr != NULL) {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen) {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent(LD_MSGLEN_ERR_EID, CFE_EVS_ERROR,
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
/* LD Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void LD_AppMain() {
    oLD.AppMain();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* LD Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LD::AppMain() {
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog(
                "LD - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(LD_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS) {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS) {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(LD_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(LD_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(LD_MAIN_TASK_PERF_ID);
    } else {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE) {
        RcvSchPipeMsg(LD_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if (iStatus != CFE_SUCCESS) {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(LD_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Detect if vehicle in free fall.                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::DetectFreeFall() {
    boolean inFreefall = false;
    if (!(ld_params.lndmc_ffall_thr < 0.1f || ld_params.lndmc_ffall_thr > 10.0f)
            && !(CVT.ControlStateMsg.Timestamp == 0)) {
        float net_acc = CVT.ControlStateMsg.AccX * CVT.ControlStateMsg.AccX
                + CVT.ControlStateMsg.AccY * CVT.ControlStateMsg.AccY
                + CVT.ControlStateMsg.AccZ * CVT.ControlStateMsg.AccZ;
        net_acc = sqrtf(net_acc);
        if (net_acc < ld_params.lndmc_ffall_thr) {
            /* Free fall event */
            inFreefall = true;
        }
    }
    return inFreefall;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Get ground contact state.                                          */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::DetectGroundContactState() {

    const uint64 now = PX4LIB_GetPX4TimeUs();
    float armingThreshFactor = 1.0f;

    boolean inGroundContact = false;
    boolean minimal_thrust = false;
    boolean altitude_lock = false;
    boolean position_lock = false;
    boolean in_descent = false;
    boolean hit_ground = false;
    boolean horizontal_movement = false;
    boolean vertical_movement = false;

    /* If vehicle is disarmed, ground contact is always true */
    if (!CVT.ActuatorArmedMsg.Armed)
    {
        arming_time = 0;
        inGroundContact = true;
    }
    else if (arming_time == 0)
    {
        arming_time = PX4LIB_GetPX4TimeUs();
    }

    if (!inGroundContact)
    {

        /* Land speed threshold */
        float land_speed_threshold = 0.9f * ld_params.landing_speed;

        const boolean manual_control_idling = (ManualControlPresent() && CVT.ManualControlSetpointMsg.Z  < ld_params.manual_stick_down_threshold);
        const boolean manual_control_idling_or_automatic = manual_control_idling || !CVT.VehicleControlModeMsg.ControlManualEnabled;

        /* Vertical movement */
        if ((PX4LIB_GetPX4TimeUs() - arming_time) < LAND_DETECTOR_ARM_PHASE_TIME_US)
        {
            armingThreshFactor = 2.5f;
            vertical_movement = fabsf(CVT.VehicleLocalPositionMsg.VZ) > (ld_params.lndmc_z_vel_max * armingThreshFactor);
        }
        else
        {
            float max_climb_rate = (land_speed_threshold * 0.5f) < ld_params.lndmc_z_vel_max ? (0.5f * land_speed_threshold) : ld_params.lndmc_z_vel_max;
            vertical_movement = fabsf(CVT.VehicleLocalPositionMsg.VZ) > max_climb_rate;
        }

        /* Horizontal movement */
        horizontal_movement = sqrtf(CVT.VehicleLocalPositionMsg.VX * CVT.VehicleLocalPositionMsg.VX + CVT.VehicleLocalPositionMsg.VY * CVT.VehicleLocalPositionMsg.VY) > ld_params.lndmc_xy_vel_max;

        minimal_thrust = MinimalThrust();
        altitude_lock = AltitudeLock();
        position_lock = altitude_lock && CVT.VehicleLocalPositionMsg.XY_Valid;
        in_descent = (CVT.VehicleLocalPositionMsg.VZ >= land_speed_threshold);
        hit_ground = in_descent && !vertical_movement;
        
        DiagTlm.GC_MinThrust = minimal_thrust;
        DiagTlm.GC_AltitudeLock = altitude_lock;
        DiagTlm.GC_PositionLock = position_lock;
        DiagTlm.GC_InDescent = in_descent;
        DiagTlm.GC_HitGround = hit_ground;
        DiagTlm.GC_HorMovement = horizontal_movement;
        DiagTlm.GC_VertMovement = vertical_movement;
        DiagTlm.GC_ManualControlIdlingOrAutomatic = manual_control_idling_or_automatic;
        
        if ((minimal_thrust || hit_ground) && (!horizontal_movement || !position_lock) && (!vertical_movement || !altitude_lock) 
            && manual_control_idling_or_automatic)
        {
            inGroundContact = true;
        }
        else
        {
            inGroundContact = false;
        }

        DiagTlm.GroundContact = inGroundContact;
    }

    return inGroundContact;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Get landed state.                                                  */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::DetectLandedState() {
    boolean isLandDetected = false;
    const uint64 now = PX4LIB_GetPX4TimeUs();
    float armingThreshFactor = 1.0f;

    if (!CVT.ActuatorArmedMsg.Armed) {
        isLandDetected = true;
        //return true;
    }

    if (!isLandDetected && state == LandDetectionState::LANDED
            && ManualControlPresent()) {
        if (CVT.ManualControlSetpointMsg.Z < TakeoffThrottle()) {
            isLandDetected = true;
            //return true;
        }

        else {
            ground_contact_history.setState(false);
            isLandDetected = false;
            //return false;
        }
    }
    if (!isLandDetected) {
        if (MinimalThrust()) {
            if (min_thrust_start == 0) {
                min_thrust_start = now;
            }
        } else {
            min_thrust_start = 0;
        }

        if (!AltitudeLock()) {
            if ((min_thrust_start > 0)
                    && ((PX4LIB_GetPX4TimeUs() - min_thrust_start) > 8000000)) {
                isLandDetected = true;
                //return true;
            } else {
                isLandDetected = false;
                //return false;
            }
        }

        if (!isLandDetected
                && (PX4LIB_GetPX4TimeUs() - now)
                        < LAND_DETECTOR_ARM_PHASE_TIME_US) {
            armingThreshFactor = 2.5f;
        }

        boolean horizontal_movement = sqrtf(
                CVT.VehicleLocalPositionMsg.VX * CVT.VehicleLocalPositionMsg.VX
                        + CVT.VehicleLocalPositionMsg.VY
                                * CVT.VehicleLocalPositionMsg.VY)
                > ld_params.lndmc_xy_vel_max;

        float max_rotation_scaled = ld_params.lndmc_rot_max
                * armingThreshFactor;

        boolean rotation =
                (fabsf(CVT.VehicleAttitudeMsg.RollSpeed) > max_rotation_scaled)
                        || (fabsf(CVT.VehicleAttitudeMsg.PitchSpeed)
                                > max_rotation_scaled)
                        || (fabsf(CVT.VehicleAttitudeMsg.YawSpeed)
                                > max_rotation_scaled);

        DiagTlm.LD_GC_history_state = ground_contact_history.getState();
        DiagTlm.LD_MinThrust = MinimalThrust();
        DiagTlm.LD_Rotation = rotation;
        DiagTlm.LD_HorMovement = horizontal_movement;
        DiagTlm.LD_PositionLock = PositionLock();

        if (ground_contact_history.getState() && MinimalThrust() && !rotation
                && (!horizontal_movement || !PositionLock())) {
            isLandDetected = true;
            //return true;
        }

        DiagTlm.Landed = isLandDetected;

    }
    return isLandDetected;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Get take off throttle.                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float LD::TakeoffThrottle() {
    float toThrottle = 0.0f;
    if (CVT.VehicleControlModeMsg.ControlManualEnabled
            && CVT.VehicleControlModeMsg.ControlAltitudeEnabled) {
        toThrottle = ld_params.manual_stick_up_position_takeoff_threshold;

    }
    if (CVT.VehicleControlModeMsg.ControlManualEnabled
            && CVT.VehicleControlModeMsg.ControlAttitudeEnabled) {
        toThrottle = 0.15f;
    }
    return toThrottle;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Get maximum altitude.                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float LD::MaxAltitude() {

    float max_alt = ld_params.lndmc_alt_max;

    if (CVT.BatteryStatusMsg.Warning == 1) {
        max_alt = ld_params.lndmc_alt_max * 0.75f;
    }

    if (CVT.BatteryStatusMsg.Warning == 2) {
        max_alt = ld_params.lndmc_alt_max * 0.5f;
    }

    if (CVT.BatteryStatusMsg.Warning == 3) {
        max_alt = ld_params.lndmc_alt_max * 0.25f;
    }

    return max_alt;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Check altitude lock presence.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::AltitudeLock() {

    return CVT.VehicleLocalPositionMsg.Timestamp != 0
            && (PX4LIB_GetPX4TimeUs() - CVT.VehicleLocalPositionMsg.Timestamp)
                    < 500000 && CVT.VehicleLocalPositionMsg.Z_Valid;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Check position lock presence.                                      */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::PositionLock() {
    return AltitudeLock() && CVT.VehicleLocalPositionMsg.XY_Valid;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/*  Check manual control presence.                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::ManualControlPresent() {
    return CVT.VehicleControlModeMsg.ControlManualEnabled
            && CVT.ManualControlSetpointMsg.Timestamp > 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Check for minimum thrust.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean LD::MinimalThrust() {

    float min_throttle = ld_params.lowThrottleThreshold;

    if (!CVT.VehicleControlModeMsg.ControlAltitudeEnabled) {
        min_throttle = (ld_params.minManThrottle + 0.01f);
    }
    return CVT.ActuatorControls0Msg.Control[3] <= min_throttle;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Update State.                                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LD::UpdateState() {

    freefall_history.setState(DetectFreeFall());
    landed_history.setState(DetectLandedState());
    ground_contact_history.setState(
            landed_history.getState() || DetectGroundContactState());

    if (freefall_history.getState()) {
        state = LandDetectionState::FREEFALL;
    } else if (landed_history.getState()) {
        state = LandDetectionState::LANDED;
    } else if (ground_contact_history.getState()) {
        state = LandDetectionState::GROUND_CONTACT;
    } else {
        state = LandDetectionState::FLYING;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Execute                                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LD::Execute() {
    if (publish_counter == 0) {
        VehicleLandDetectedMsg.Freefall = false;
        VehicleLandDetectedMsg.Landed = false;
        VehicleLandDetectedMsg.GroundContact = false;
        publish_counter += 1;
    }
    uint64 now = PX4LIB_GetPX4TimeUs();

    UpdateState();

    float prev_altitude_max = altitude_max;
    altitude_max = MaxAltitude();

    boolean ffd = (state == LandDetectionState::FREEFALL);
    boolean ld = (state == LandDetectionState::LANDED);
    boolean gcd = (state == LandDetectionState::GROUND_CONTACT);

    if ((VehicleLandDetectedMsg.Freefall != ffd)
            || (VehicleLandDetectedMsg.Landed != ld)
            || (VehicleLandDetectedMsg.GroundContact != gcd)
            || (fabsf(VehicleLandDetectedMsg.AltMax - prev_altitude_max)
                    > FLT_EPSILON)) {
        /*if((!gcd && !ld) && ffd){
         ffd=false;
         }*/
        if (!ld && VehicleLandDetectedMsg.Landed) {
            takeoff_time = now;
        } else if (takeoff_time != 0 && ld && !VehicleLandDetectedMsg.Landed) {
            total_flight_time += now - takeoff_time;
            takeoff_time = 0;

            uint32 flight_time = (total_flight_time >> 32) & 0xffffffff;
            ld_params.lnd_flight_t_hi = flight_time;
            flight_time = total_flight_time & 0xffffffff;
            ld_params.lnd_flight_t_lo = flight_time;
        }
        VehicleLandDetectedMsg.Timestamp = PX4LIB_GetPX4TimeUs();
        VehicleLandDetectedMsg.AltMax = altitude_max;
        VehicleLandDetectedMsg.Freefall =
                (state == LandDetectionState::FREEFALL);
        VehicleLandDetectedMsg.Landed = (state == LandDetectionState::LANDED);
        VehicleLandDetectedMsg.GroundContact = (state
                == LandDetectionState::GROUND_CONTACT);
        HkTlm.state = state;
    }

    DetectStateChange();
    SendVehicleLandDetectedMsg();
    SendDiag();
}
void LD::DetectStateChange() {
    /* When there is a change in state this function will return true flag */
    PX4_VehicleLandDetectedMsg_t CurrentLandDetectedMsg = VehicleLandDetectedMsg;

    if (&PreviousLandDetectedMsg == nullptr) {
        PreviousLandDetectedMsg = CurrentLandDetectedMsg;
    } else if (PreviousLandDetectedMsg.Landed == CurrentLandDetectedMsg.Landed
            && PreviousLandDetectedMsg.Freefall
                    == CurrentLandDetectedMsg.Freefall
            && PreviousLandDetectedMsg.GroundContact
                    == CurrentLandDetectedMsg.GroundContact) {
        PreviousLandDetectedMsg = CurrentLandDetectedMsg;
    } else {
        if (CurrentLandDetectedMsg.Landed) {
            (void) CFE_EVS_SendEvent(LD_LAND_DETECTED_EID, CFE_EVS_INFORMATION,
                    "Land detected");
        } else if (CurrentLandDetectedMsg.Freefall) {
            (void) CFE_EVS_SendEvent(LD_GROUNDCONTACT_DETECTED_EID,
            CFE_EVS_INFORMATION, "Freefall detected");
        } else if (CurrentLandDetectedMsg.GroundContact) {
            (void) CFE_EVS_SendEvent(LD_FREEFALL_DETECTED_EID,
            CFE_EVS_INFORMATION, "Ground contact detected");
        }
        /*else{
         (void) CFE_EVS_SendEvent(LD_FLIGHT_DETECTED_EID, CFE_EVS_INFORMATION,"Vehicle in flight");
         }*/
        PreviousLandDetectedMsg = CurrentLandDetectedMsg;
    }
}

void LD::UpdateParamsFromTable() {

    /* Use Trigger time when transitioning from in-air (false) to landed (true) / ground contact (true) */
    landed_history.setTimeSince(false, LAND_DETECTOR_TRIGGER_TIME_US);
    ground_contact_history.setTimeSince(false, GROUND_CONTACT_TRIGGER_TIME_US);

    /* Initialize Params */
    if (ConfigTblPtr != nullptr) {

        ld_params.lndmc_z_vel_max = ConfigTblPtr->LD_Z_VEL_MAX;
        ld_params.lndmc_xy_vel_max = ConfigTblPtr->LD_XY_VEL_MAX;
        ld_params.lndmc_rot_max = ConfigTblPtr->LD_ROT_MAX;
        ld_params.lndmc_ffall_thr = ConfigTblPtr->LD_FFALL_THR;
        ld_params.lndmc_thr_range = ConfigTblPtr->LD_THR_RANGE;
        ld_params.lndmc_ffall_ttri = ConfigTblPtr->LD_FFALL_TTRI;
        ld_params.lndmc_man_dwnthr = ConfigTblPtr->LD_MAN_DWNTHR;
        ld_params.lndmc_pos_upthr = ConfigTblPtr->LD_POS_UPTHR;
        ld_params.lnd_flight_t_hi = ConfigTblPtr->LD_FLT_TME_HI;
        ld_params.lnd_flight_t_lo = ConfigTblPtr->LD_FLT_TME_LO;
        ld_params.lndmc_alt_max = ConfigTblPtr->LD_ALT_MAX;
        ld_params.lowThrottleThreshold = ConfigTblPtr->LD_LOW_T_THR;
        ld_params.minManThrottle = ConfigTblPtr->LD_MAN_MIN_THR;
        ld_params.manual_stick_up_position_takeoff_threshold =
                ConfigTblPtr->LD_POS_STK_UP_THRES;
        ld_params.manual_stick_down_threshold =
                ConfigTblPtr->LD_POS_STK_DW_THRES;
        ld_params.landing_speed = ConfigTblPtr->LD_LANDSPEED;

    }

}

/************************/
/*  End of File Comment */
/************************/
