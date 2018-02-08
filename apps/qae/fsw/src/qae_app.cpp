/************************************************************************
** Includes
*************************************************************************/
#include <string.h>
#include <math.h>

#include "cfe.h"

#include "qae_app.hpp"
#include "qae_msg.h"
#include "qae_version.h"

#include <geo_lookup/geo_mag_declination.h>
#include <geo/geo.h>
#include <math/Limits.hpp>
#include <px4lib.h>



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
QAE oQAE;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
QAE::QAE()
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
QAE::~QAE()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 QAE::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    int32  ind = 0;

    CFE_EVS_BinFilter_t   EventTbl[CFE_EVS_MAX_EVENT_FILTERS];
    
    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset(EventTbl, 0x00, sizeof(EventTbl));
    
    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    EventTbl[  ind].EventID = QAE_RESERVED_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;
    EventTbl[  ind].EventID = QAE_DEGENERATE_ACC_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;
    EventTbl[  ind].EventID = QAE_DEGENERATE_MAG_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;
    EventTbl[  ind].EventID = QAE_UPDATE_EST_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;
    
    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(EventTbl, ind, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("QAE - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 QAE::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    		QAE_SCH_PIPE_DEPTH,
			QAE_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(AE_WAKEUP_MID, SchPipeId, CFE_SB_Default_Qos, QAE_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(QAE_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
            		"Sch Pipe failed to subscribe to QAE_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto QAE_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(AE_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, QAE_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(QAE_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to QAE_SEND_HK_MID. (0x%08X)",
					 (unsigned int)iStatus);
            goto QAE_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_SENSOR_COMBINED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(QAE_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_SENSOR_COMBINED_MID. (0x%08lX)",
					 iStatus);
            goto QAE_InitPipe_Exit_Tag;
        }
        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GLOBAL_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(QAE_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_GLOBAL_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto QAE_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(QAE_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create SCH pipe (0x%08lX)",
			 iStatus);
        goto QAE_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    		QAE_CMD_PIPE_DEPTH,
			QAE_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(AE_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(QAE_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
				 "CMD Pipe failed to subscribe to QAE_CMD_MID. (0x%08lX)",
				 iStatus);
            goto QAE_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(QAE_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create CMD pipe (0x%08lX)",
			 iStatus);
        goto QAE_InitPipe_Exit_Tag;
    }

QAE_InitPipe_Exit_Tag:
    return iStatus;
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void QAE::InitData()
{
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
    		AE_HK_TLM_MID, sizeof(HkTlm), TRUE);
      /* Init output messages */
      CFE_SB_InitMsg(&VehicleAttitudeMsg,
      		PX4_VEHICLE_ATTITUDE_MID, sizeof(PX4_VehicleAttitudeMsg_t), TRUE);
      /* Init output messages */
      CFE_SB_InitMsg(&ControlStateMsg,
      		PX4_CONTROL_STATE_MID, sizeof(PX4_ControlStateMsg_t), TRUE);
      /* Init current value table to zero */
      memset(&CVT, 0, sizeof(CVT));
      /* Init params table to zero */
      memset(&m_Params, 0, sizeof(m_Params));
      /* Set params default values */
      m_Params.mag_declination_auto = TRUE;
      m_Params.acc_compensation = TRUE;
      m_Params.mag_weight = 0.1f;
      m_Params.gyro_weight = 0.1f;
      m_Params.acc_weight = 0.2f;
      /* TODO check if default value isn't actually 0 */
      m_Params.gyro_bias_max = 0.05f;
      /* Init members */
      m_Quaternion.Zero();
      m_Gyro.Zero();
      m_Accel.Zero();
      m_Mag.Zero();
      m_LastVelocity.Zero();
      m_LastVelocityTime = 0;
      m_PositionAcc.Zero();
      m_GyroBias.Zero();
      m_Rates.Zero();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* QAE initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 QAE::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("QAE - Failed to init events (0x%08lX)\n", iStatus);
        goto QAE_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto QAE_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto QAE_InitApp_Exit_Tag;
    }
    
    /* Set application state to initialized */
    HkTlm.State = QAE_INITIALIZED;

QAE_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(QAE_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
								 QAE_MAJOR_VERSION,
								 QAE_MINOR_VERSION,
								 QAE_REVISION,
								 QAE_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("QAE - Application failed to initialize\n");
        }
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 QAE::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(QAE_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(QAE_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case AE_WAKEUP_MID:
                /* TODO:  Do something here. */
                //EstimateAttitude();
                break;

            case AE_SEND_HK_MID:
                ProcessCmdPipe();
                /* Copy the current vehicle attitude message */
                memcpy(&HkTlm.VehicleAttitudeMsg, &VehicleAttitudeMsg, sizeof(VehicleAttitudeMsg));
                /* Copy the current control state message */
                memcpy(&HkTlm.ControlStateMsg, &ControlStateMsg, sizeof(ControlStateMsg));
                ReportHousekeeping();
                break;

            case PX4_SENSOR_COMBINED_MID:
                memcpy(&CVT.SensorCombinedMsg, MsgPtr, sizeof(CVT.SensorCombinedMsg));
                EstimateAttitude();
                break;

            case PX4_VEHICLE_GLOBAL_POSITION_MID:
                memcpy(&CVT.VehicleGlobalPositionMsg, MsgPtr, sizeof(CVT.VehicleGlobalPositionMsg));
                break;

            default:
                (void) CFE_EVS_SendEvent(QAE_MSGID_ERR_EID, CFE_EVS_ERROR,
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
        (void) CFE_EVS_SendEvent(QAE_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void QAE::ProcessCmdPipe()
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
                case AE_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(QAE_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(QAE_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process QAE Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void QAE::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case QAE_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(QAE_CMD_NOOP_EID, CFE_EVS_INFORMATION,
					"Recvd NOOP. Version %d.%d.%d.%d",
					QAE_MAJOR_VERSION,
					QAE_MINOR_VERSION,
					QAE_REVISION,
					QAE_MISSION_REV);
                break;

            case QAE_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(QAE_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send QAE Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void QAE::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void QAE::SendVehicleAttitudeMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VehicleAttitudeMsg);
    //OS_printf("VehicleAttitudeMsg.Timestamp %llf\n",VehicleAttitudeMsg.Timestamp);
    //OS_printf("VehicleAttitudeMsg.RollSpeed %f\n",VehicleAttitudeMsg.RollSpeed);
    //OS_printf("VehicleAttitudeMsg.PitchSpeed %f\n",VehicleAttitudeMsg.PitchSpeed);
    //OS_printf("VehicleAttitudeMsg.YawSpeed %f\n",VehicleAttitudeMsg.YawSpeed);
    //OS_printf("VehicleAttitudeMsg.Q[0] %f\n",VehicleAttitudeMsg.Q[0]);
    //OS_printf("VehicleAttitudeMsg.Q[1] %f\n",VehicleAttitudeMsg.Q[1]);
    //OS_printf("VehicleAttitudeMsg.Q[2] %f\n",VehicleAttitudeMsg.Q[2]);
    //OS_printf("VehicleAttitudeMsg.Q[3] %f\n",VehicleAttitudeMsg.Q[3]);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&VehicleAttitudeMsg);
}


void QAE::SendControlStateMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ControlStateMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&ControlStateMsg);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean QAE::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(QAE_MSGLEN_ERR_EID, CFE_EVS_ERROR,
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
/* QAE Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void QAE_AppMain()
{
    oQAE.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* QAE Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void QAE::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("QAE - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(QAE_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(QAE_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(QAE_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(QAE_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(QAE_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(QAE_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}


void QAE::UpdateMagDeclination(const float new_declination)
{
    if (HkTlm.EstimatorState == QAE_EST_UNINITIALIZED || 
        fabsf(new_declination - m_Params.mag_declination) < 0.0001f) 
    {
        /* Apply initial declination or trivial rotations without changing estimation */
        m_Params.mag_declination = new_declination;
    }
    else 
    {
        /* Immediately rotate current estimation to avoid gyro bias growth */
        math::Quaternion decl_rotation (0.0f, 0.0f, 0.0f, 0.0f);
        decl_rotation.FromYaw(new_declination - m_Params.mag_declination);
        m_Quaternion = decl_rotation * m_Quaternion;
        m_Params.mag_declination = new_declination;
    }
}


void QAE::EstimateAttitude(void)
{
    math::Vector3F euler(0.0f, 0.0f, 0.0f);
    float length_check = 0.0f;
    float delta_time_velocity = 0.0f;
    uint64 delta_time_gps = 0;
    uint64 time_now = 0;
    float delta_time = 0;
    uint64 time_last = 0;
    boolean update_success = FALSE;

    /* If there is a new sensor combined message */
    if(CVT.SensorCombinedMsg.Timestamp > CVT.LastSensorCombinedTime)
    {
        /* TODO is this state possible? */
        if(CVT.SensorCombinedMsg.Timestamp > 0)
        {
            /* No lowpass filter here, filtering is in the driver */
            m_Gyro[0] = CVT.SensorCombinedMsg.GyroRad[0];
            m_Gyro[1] = CVT.SensorCombinedMsg.GyroRad[1];
            m_Gyro[2] = CVT.SensorCombinedMsg.GyroRad[2];
        }
        
        //if(CVT.SensorCombinedMsg.AccRelTimeInvalid != FALSE)
        if(CVT.SensorCombinedMsg.AccTimestampRelative != PX4_RELATIVE_TIMESTAMP_INVALID)
        {
            /* No lowpass filter here, filtering is in the driver */
            m_Accel[0] = CVT.SensorCombinedMsg.Acc[0];
            m_Accel[1] = CVT.SensorCombinedMsg.Acc[1];
            m_Accel[2] = CVT.SensorCombinedMsg.Acc[2];
            
            length_check = m_Accel.Length();
            if(length_check < 0.01f)
            {
                (void) CFE_EVS_SendEvent(QAE_DEGENERATE_ACC_ERR_EID, CFE_EVS_ERROR,
                              "Degenerate input data accel vector length %f",
                               length_check);
                goto end_of_function;
            }
        }
        
        //if(CVT.SensorCombinedMsg.MagRelTimeInvalid != FALSE)
        if(CVT.SensorCombinedMsg.MagTimestampRelative != PX4_RELATIVE_TIMESTAMP_INVALID)
        {
            /* No lowpass filter here, filtering is in the driver */
            m_Mag[0] = CVT.SensorCombinedMsg.Mag[0];
            m_Mag[1] = CVT.SensorCombinedMsg.Mag[1];
            m_Mag[2] = CVT.SensorCombinedMsg.Mag[2];

            length_check = m_Mag.Length();
            if(length_check < 0.01f)
            {
                (void) CFE_EVS_SendEvent(QAE_DEGENERATE_MAG_ERR_EID, CFE_EVS_ERROR,
                              "Degenerate input data mag vector length %f",
                               length_check);
                goto end_of_function;
            }
        }
        /* Update the application state */
        HkTlm.State = QAE_SENSOR_DATA_RCVD;
        /* Update last timestamp */
        CVT.LastSensorCombinedTime = CVT.SensorCombinedMsg.Timestamp;
    }
    else
    {
        /* Update the application state */
        HkTlm.State = QAE_INITIALIZED;
    }

    /* If there is a new GPS message */
    if(CVT.VehicleGlobalPositionMsg.Timestamp > CVT.LastGlobalPositionTime)
    {
        /* Calculate time difference between now and gpos timestamp */
        delta_time_gps = PX4LIB_GetPX4TimeUs() - CVT.VehicleGlobalPositionMsg.Timestamp;
        if(m_Params.mag_declination_auto == TRUE && 
           CVT.VehicleGlobalPositionMsg.EpH < 20.0f &&
           delta_time_gps < 1000000)
        {
            /* set magnetic declination automatically */
            UpdateMagDeclination(math::radians(get_mag_declination(CVT.VehicleGlobalPositionMsg.Lat, CVT.VehicleGlobalPositionMsg.Lon)));
        }
        
        if(m_Params.acc_compensation == TRUE &&
           CVT.VehicleGlobalPositionMsg.Timestamp != 0 &&
           PX4LIB_GetPX4TimeUs() < CVT.VehicleGlobalPositionMsg.Timestamp + 20000 &&
           CVT.VehicleGlobalPositionMsg.EpH < 5.0f &&
           HkTlm.EstimatorState == QAE_EST_INITIALIZED)
        {
            /* position data is actual */
            math::Vector3F vel(CVT.VehicleGlobalPositionMsg.VelN,
                               CVT.VehicleGlobalPositionMsg.VelE,
                               CVT.VehicleGlobalPositionMsg.VelD);
            /* velocity updated */
            if(m_LastVelocityTime != 0 &&
               CVT.VehicleGlobalPositionMsg.Timestamp != m_LastVelocityTime)
            {
                delta_time_velocity = (CVT.VehicleGlobalPositionMsg.Timestamp - m_LastVelocityTime) / 1000000.0f;
                /* calculate acceleration in body frame */
                m_PositionAcc = m_Quaternion.ConjugateInversed((vel - m_LastVelocity) / delta_time_velocity);
            }
            m_LastVelocityTime = CVT.VehicleGlobalPositionMsg.Timestamp;
            m_LastVelocity = vel;
        }
        else
        {
            /* position data is outdate, reset acceleration */
            OS_printf("position data is outdate, reset acceleration");
            m_PositionAcc.Zero();
            m_LastVelocity.Zero();
            m_LastVelocityTime = 0;
        }
        /* Update last timestamp */
        CVT.LastGlobalPositionTime = CVT.VehicleGlobalPositionMsg.Timestamp;
    }

    time_now = PX4LIB_GetPX4TimeUs();
    delta_time = (time_last > 0) ? ((time_now - time_last) / 1000000.0f) : 0.00001f;
    time_last = time_now;
    
    if(delta_time > QAE_DELTA_TIME_MAX)
    {
        delta_time = QAE_DELTA_TIME_MAX;
    }

    update_success = UpdateEstimateAttitude(delta_time);
    if(FALSE == update_success)
    {
        (void) CFE_EVS_SendEvent(QAE_UPDATE_EST_ERR_EID, CFE_EVS_ERROR,
                "Update attitude estimate failed, reset to last state");
        /* TODO raise event here */
        goto end_of_function;
    }
    
    //math::Vector3F euler = m_Quaternion.ToEuler();
    euler = m_Quaternion.ToEuler();
    /* Populate vehicle attitude message */
    VehicleAttitudeMsg.Timestamp    = CVT.SensorCombinedMsg.Timestamp;
    VehicleAttitudeMsg.RollSpeed    = m_Rates[0];
    VehicleAttitudeMsg.PitchSpeed   = m_Rates[1];
    VehicleAttitudeMsg.YawSpeed     = m_Rates[2];
    VehicleAttitudeMsg.Q[0]         = m_Quaternion[0];
    VehicleAttitudeMsg.Q[1]         = m_Quaternion[1];
    VehicleAttitudeMsg.Q[2]         = m_Quaternion[2];
    VehicleAttitudeMsg.Q[3]         = m_Quaternion[3];

    /* Send vehicle attitude message */
    SendVehicleAttitudeMsg();
    
    /* Populate control state message */
    ControlStateMsg.Timestamp       = CVT.SensorCombinedMsg.Timestamp;
    /* attitude quaternions for control state */
    ControlStateMsg.Q[0]            = m_Quaternion[0];
    ControlStateMsg.Q[1]            = m_Quaternion[1];
    ControlStateMsg.Q[2]            = m_Quaternion[2];
    ControlStateMsg.Q[3]            = m_Quaternion[3];

    ControlStateMsg.AccX            = m_Accel[0];
    ControlStateMsg.AccY            = m_Accel[1];
    ControlStateMsg.AccZ            = m_Accel[2];
    /* attitude rates for control state */
    ControlStateMsg.RollRate        = m_Rates[0];
    ControlStateMsg.PitchRate       = m_Rates[1];
    ControlStateMsg.YawRate         = m_Rates[2];
    /* TODO get bias estimates from estimator */
    ControlStateMsg.RollRateBias    = 0.0f;
    ControlStateMsg.PitchRateBias   = 0.0f;
    ControlStateMsg.YawRateBias     = 0.0f;
    
    ControlStateMsg.AirspeedValid = FALSE;
    /* TODO params reference for this is incorrect */
    if(m_Params.airspeed_mode == PX4_AIRSPEED_MODE_EST)
    {
        if (PX4LIB_GetPX4TimeUs() - CVT.VehicleGlobalPositionMsg.Timestamp < 1e6) 
        {
            /* use estimated body velocity as airspeed estimate */
            ControlStateMsg.Airspeed = sqrtf(
                    CVT.VehicleGlobalPositionMsg.VelN * CVT.VehicleGlobalPositionMsg.VelN + 
                    CVT.VehicleGlobalPositionMsg.VelE * CVT.VehicleGlobalPositionMsg.VelE + 
                    CVT.VehicleGlobalPositionMsg.VelD * CVT.VehicleGlobalPositionMsg.VelD
            );
            ControlStateMsg.AirspeedValid = TRUE;
        }
    }
    //else if (m_Params.airspeed_mode == PX4_AIRSPEED_MODE_DISABLED)
    //{
        // do nothing, airspeed has been declared as non-valid above, controllers
        // will handle this assuming always trim airspeed
    //}
    /* Send the control state message */
    SendControlStateMsg();
    
end_of_function:
;
}


boolean QAE::InitEstimateAttitude(void)
{
    math::Vector3F k(0.0f, 0.0f, 0.0f);
    math::Vector3F i(0.0f, 0.0f, 0.0f);
    math::Vector3F j(0.0f, 0.0f, 0.0f);
    boolean return_bool = FALSE;

    /* rotation matrix can be easily constructed from acceleration
     * and mag field vectors. 'k' is Earth Z axis (Down) unit vector
     * in body frame 
     */
    k = -m_Accel;
    OS_printf("k[] %f, k[] %f, k[] %f\n", k[0], k[1], k[2]);
    k.Normalize();
    OS_printf("Normalized k[] %f, k[] %f, k[] %f\n", k[0], k[1], k[2]);
    /* 'i' is Earth X axis (North) unit vector in body frame, 
     * orthogonal with 'k' 
     */
    i = (m_Mag - k * (m_Mag * k));
    OS_printf("i[] %f, i[] %f, i[] %f\n", i[0], i[1], i[2]);
    i.Normalize();
    OS_printf("Normalized i[] %f, i[] %f, i[] %f\n", i[0], i[1], i[2]);
    /* 'j' is Earth Y axis (East) unit vector in body frame, orthogonal
     * with 'k' and 'i' */
    j = k % i;
    OS_printf("j[] %f, j[] %f, j[] %f\n", j[0], j[1], j[2]);
    /* Fill rotation matrix */
    math::Matrix3F3 R(i, j, k);
    OS_printf("R[][] %f, R[][] %f, R[][] %f, R[][] %f, R[][] %f, R[][] %f, R[][] %f, R[][] %f, R[][] %f,\n", R[0][0], R[0][1], R[0][2], R[1][0], R[1][1], R[1][2], R[2][0], R[2][1], R[2][2]);
    
    /* Convert to quaternion */
    m_Quaternion.FromDCM(R);
    OS_printf("m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, \n", m_Quaternion[0], m_Quaternion[1], m_Quaternion[2], m_Quaternion[3]);
    
    /* Compensate for magnetic declination */
    math::Quaternion decl_rotation(0.0f, 0.0f, 0.0f, 0.0f);
    decl_rotation.FromYaw(m_Params.mag_declination);
    OS_printf("decl_rotation.FromYaw [] %f, [] %f, [] %f, [] %f\n", decl_rotation[0], decl_rotation[1], decl_rotation[2], decl_rotation[3]);
    
    m_Quaternion = decl_rotation * m_Quaternion;
    OS_printf("decl_rotation * m_Quaternion m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, \n", m_Quaternion[0], m_Quaternion[1], m_Quaternion[2], m_Quaternion[3]);
    m_Quaternion.Normalize();
    OS_printf("m_Quaternion.Normalize() m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, \n", m_Quaternion[0], m_Quaternion[1], m_Quaternion[2], m_Quaternion[3]);
    OS_printf("m_Quaternion.Length() %f\n", m_Quaternion.Length());
    if(isfinite(m_Quaternion[0]) && isfinite(m_Quaternion[1]) &&
       isfinite(m_Quaternion[2]) && isfinite(m_Quaternion[3]) &&
       m_Quaternion.Length() > 0.95f && m_Quaternion.Length() < 1.05f)
    {
        OS_printf("QAE_EST_INITIALIZED\n");
        HkTlm.EstimatorState = QAE_EST_INITIALIZED;
        return_bool = TRUE;
    }
    else
    {
        HkTlm.EstimatorState = QAE_EST_UNINITIALIZED;
    }

    return return_bool;
}


boolean QAE::UpdateEstimateAttitude(float dt)
{
    math::Quaternion q_last(0.0f, 0.0f, 0.0f, 0.0f);
    math::Quaternion q_derivative(0.0f, 0.0f, 0.0f, 0.0f);
    /* Angular rate of correction */
    math::Vector3F corr(0.0f, 0.0f, 0.0f);
    math::Vector3F mag_earth(0.0f, 0.0f, 0.0f);

    float spinRate = 0.0f;
    float magErr   = 0.0f;
    float gainMult = 1.0f;
    //const float fiftyDPS = 0.873f;
    uint8 i = 0;

    if (HkTlm.EstimatorState != QAE_EST_INITIALIZED)
    {
        OS_printf("HkTlm.EstimatorState != QAE_EST_INITIALIZED\n");
        if(HkTlm.State != QAE_SENSOR_DATA_RCVD)
        {
            OS_printf("HkTlm.State != QAE_SENSOR_DATA_RCVD\n");
            return FALSE;
        }
        return InitEstimateAttitude();
    }
    
    q_last = m_Quaternion;
    spinRate = m_Gyro.Length();
    
    /* Magnetometer correction project mag field vector to global frame 
     * and extract XY component */
    mag_earth = m_Quaternion.Conjugate(m_Mag);
    magErr = _wrap_pi(atan2f(mag_earth[1], mag_earth[0]) - m_Params.mag_declination);
    
    if(spinRate > QAE_FIFTY_DPS)
    {
        gainMult = math::min(spinRate / QAE_FIFTY_DPS, 10.0f);
    }
    /* Project magnetometer correction to body frame */
    math::Vector3F magErrV3F(0.0f, 0.0f, -magErr);
    corr = corr + m_Quaternion.ConjugateInversed(magErrV3F) * m_Params.mag_weight * gainMult;
    
    m_Quaternion.Normalize();
    
    /* Accelerometer correction
     * Project 'k' unit vector of earth frame to body frame
     * Vector<3> k = _q.conjugate_inversed(Vector<3>(0.0f, 0.0f, 1.0f));
     * Optimized version with dropped zeros
     */
    math::Vector3F k(
            2.0f * (m_Quaternion[1] * m_Quaternion[3] - m_Quaternion[0] * m_Quaternion[2]),
            2.0f * (m_Quaternion[2] * m_Quaternion[3] + m_Quaternion[0] * m_Quaternion[1]),
            (m_Quaternion[0] * m_Quaternion[0] - m_Quaternion[1] * 
             m_Quaternion[1] - m_Quaternion[2] * m_Quaternion[2] + 
             m_Quaternion[3] * m_Quaternion[3])
    );
    
    math::Vector3F diff(0.0f, 0.0f, 0.0f);
    diff = m_Accel - m_PositionAcc;
    diff.Normalize();
    corr = corr + (k % diff) * m_Params.acc_weight;
    
    /* Gyro bias estimation */
    if(spinRate < 0.175f)
    {
        m_GyroBias = m_GyroBias + corr * (m_Params.gyro_weight * dt);
        for(i = 0; i < 3; i++)
        {
            m_GyroBias[i] = math::constrain(m_GyroBias[i], -m_Params.gyro_bias_max, m_Params.gyro_bias_max);
        }
    }
    
    m_Rates = m_Gyro + m_GyroBias;
    
    /* Feed forward gyro */
    corr = corr + m_Rates;

    q_derivative = m_Quaternion.Derivative(corr);

    /* Apply correction to state */
    m_Quaternion = m_Quaternion + (q_derivative * dt);
    
    /* Normalize quaternion */
    m_Quaternion.Normalize();
    
    OS_printf("before last if check %f, m_Quaternion[] %f, m_Quaternion[] %f, m_Quaternion[] %f, \n", m_Quaternion[0], m_Quaternion[1], m_Quaternion[2], m_Quaternion[3]);
    
    if (isfinite(m_Quaternion[0]) && isfinite(m_Quaternion[1]) &&
        isfinite(m_Quaternion[2]) && isfinite(m_Quaternion[3]) )
    {
        return TRUE;
    }
    else
    {
        OS_printf("reset to last good state\n");
        /* Reset quaternion to last good state */
        m_Quaternion = q_last;
        m_Rates.Zero();
        m_GyroBias.Zero();
        return FALSE;
    }
}


void QAE::UpdateParamsFromTable(void)
{
    if(0 != ConfigTblPtr)
    {
        m_Params.acc_weight           = ConfigTblPtr-> ATT_W_ACC;
        m_Params.mag_weight           = ConfigTblPtr->ATT_W_MAG;
        m_Params.gyro_weight          = ConfigTblPtr->ATT_W_GYRO_BIAS;
        m_Params.mag_declination      = ConfigTblPtr->ATT_MAG_DECL;
        m_Params.mag_declination_auto = ConfigTblPtr->ATT_MAG_DECL_A;
        m_Params.acc_compensation     = ConfigTblPtr->ATT_ACC_COMP;
        m_Params.gyro_bias_max        = ConfigTblPtr->ATT_BIAS_MAX;
        m_Params.airspeed_mode        = ConfigTblPtr->FW_ARSP_MODE;
    }
}

/************************/
/*  End of File Comment */
/************************/
