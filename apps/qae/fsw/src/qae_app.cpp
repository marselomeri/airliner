/************************************************************************
** Includes
*************************************************************************/
#include <string.h>
#include <math.h>

#include "cfe.h"

#include "qae_app.hpp"
#include "qae_msg.h"
#include "qae_version.h"
#include "lib/px4lib.h"

#include "geo_mag_declination.h"
#include "Limits.hpp"

#include "lib/mathlib/math/Limits.hpp"


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

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
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
        iStatus = CFE_SB_SubscribeEx(QAE_WAKEUP_MID, SchPipeId, CFE_SB_Default_Qos, QAE_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(QAE_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
            		"Sch Pipe failed to subscribe to QAE_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto QAE_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(QAE_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, QAE_SEND_HK_MID_MAX_MSG_COUNT);
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
        iStatus = CFE_SB_Subscribe(QAE_CMD_MID, CmdPipeId);

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
    		QAE_HK_TLM_MID, sizeof(HkTlm), TRUE);
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
      /* Init members */
      m_Quaternion.Zero();
      m_gyro.Zero();
      m_accel.Zero();
      m_mag.Zero();
      m_LastVelocity.Zero();
      m_LastVelocityTime = 0;
      m_PositionAcc.Zero();
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
            case QAE_WAKEUP_MID:
                /* TODO:  Do something here. */
                break;

            case QAE_SEND_HK_MID:
                ProcessCmdPipe();
                ReportHousekeeping();
                break;
            case PX4_SENSOR_COMBINED_MID:
                memcpy(&CVT.SensorCombinedMsg, MsgPtr, sizeof(CVT.SensorCombinedMsg));
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
                case QAE_CMD_MID:
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
    /* Apply initial declination or trivial rotations without changing estimation */
    if (HkTlm.State == QAE_UNINITIALIZED || fabsf(new_declination - m_Params.mag_declination) < 0.0001f) 
    {
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
    float length_check = 0.0f;
    float delta_time_velocity = 0.0f;
    uint64 delta_time_gps = 0;
    uint64 time_now = 0;
    float delta_time = 0;
    uint64 time_last = 0;
    /* If there is a new sensor combined message */
    if(CVT.SensorCombinedMsg.Timestamp > CVT.LastSensorCombinedTime)
    {
        /* TODO is this state possible? */
        if(CVT.SensorCombinedMsg.Timestamp > 0)
        {
            /* No lowpass filter here, filtering is in the driver */
            m_gyro[0] = CVT.SensorCombinedMsg.GyroRad[0];
            m_gyro[1] = CVT.SensorCombinedMsg.GyroRad[1];
            m_gyro[2] = CVT.SensorCombinedMsg.GyroRad[2];
        }
        
        if(CVT.SensorCombinedMsg.AccRelTimeInvalid != FALSE)
        {
            /* No lowpass filter here, filtering is in the driver */
            m_accel[0] = CVT.SensorCombinedMsg.Acc[0];
            m_accel[1] = CVT.SensorCombinedMsg.Acc[1];
            m_accel[2] = CVT.SensorCombinedMsg.Acc[2];
            
            length_check = m_accel.Length();
            if(length_check < 0.01f)
            {
                (void) CFE_EVS_SendEvent(QAE_DEGENERATE_ACC_ERR_EID, CFE_EVS_ERROR,
                              "Degenerate input data accel vector length %f",
                               length_check);
            }
        }
        
        if(CVT.SensorCombinedMsg.MagRelTimeInvalid != FALSE)
        {
            /* No lowpass filter here, filtering is in the driver */
            m_mag[0] = CVT.SensorCombinedMsg.Mag[0];
            m_mag[1] = CVT.SensorCombinedMsg.Mag[1];
            m_mag[2] = CVT.SensorCombinedMsg.Mag[2];

            length_check = m_mag.Length();
            if(length_check < 0.01f)
            {
                (void) CFE_EVS_SendEvent(QAE_DEGENERATE_MAG_ERR_EID, CFE_EVS_ERROR,
                              "Degenerate input data mag vector length %f",
                               length_check);
            }
        }
        /* Update the application state */
        HkTlm.State = QAE_SENSOR_DATA_RCVD;
    }
    else
    {
        /* Update the application state */
        HkTlm.State = QAE_INITIALIZED;
    }
    /* If there is a new GPS message */
    if(CVT.VehicleGlobalPositionMsg.Timestamp > CVT.LastGlobalPositionTime)
    {
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
           HkTlm.State == QAE_INITIALIZED)
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
            m_PositionAcc.Zero();
            m_LastVelocity.Zero();
            m_LastVelocityTime = 0;
        }
    }

    time_now = PX4LIB_GetPX4TimeUs();
    delta_time = (time_last > 0) ? ((time_now - time_last) / 1000000.0f) : 0.00001f;
    time_last = time_now;
    
    if(delta_time > QAE_DELTA_TIME_MAX)
    {
        delta_time = QAE_DELTA_TIME_MAX;
    }

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
    k = -m_accel;
    k.Normalize();
    
    /* 'i' is Earth X axis (North) unit vector in body frame, 
     * orthogonal with 'k' 
     */
    i = (m_mag - k * (m_mag * k));
    i.Normalize();
    
    /* 'j' is Earth Y axis (East) unit vector in body frame, orthogonal
     * with 'k' and 'i' */
    j = k % i;
    
    /* Fill rotation matrix */
    math::Matrix3F3 R(i, j, k);
    
    /* Convert to quaternion */
    m_Quaternion.FromDCM(R);
    
    /* Compensate for magnetic declination */
    math::Quaternion decl_rotation(0.0f, 0.0f, 0.0f, 0.0f);
    decl_rotation.FromYaw(m_Params.mag_declination);
    m_Quaternion = decl_rotation * m_Quaternion;
    m_Quaternion.Normalize();
    
    if(isfinite(m_Quaternion[0]) && isfinite(m_Quaternion[1]) &&
       isfinite(m_Quaternion[2]) && isfinite(m_Quaternion[3]) &&
       m_Quaternion.Length() > 0.95f && m_Quaternion.Length() < 1.05f)
    {
        HkTlm.State = QAE_INITIALIZED;
        return_bool = TRUE;
    }
    else
    {
        HkTlm.State = QAE_UNINITIALIZED;
    }

    return return_bool;
}


boolean QAE::UpdateEstimateAttitude(float dt)
{
    if (HkTlm.State != QAE_INITIALIZED)
    {
        if(HkTlm.State != QAE_SENSOR_DATA_RCVD)
        {
            return FALSE;
        }
        return InitEstimateAttitude();
    }
    
    return TRUE;
}

/************************/
/*  End of File Comment */
/************************/
