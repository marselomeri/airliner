/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"
#include "mpu9250_custom.h"

#include "mpu9250_app.h"
#include "mpu9250_msg.h"
#include "mpu9250_version.h"
#include "Vector3F.hpp"
#include "lib/px4lib.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MPU9250 oMPU9250;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MPU9250::MPU9250() :
    _accel_filter_x(MPU9250_ACCEL_SAMPLE_RATE, MPU9250_ACCEL_FILTER_CUTOFF_FREQ),
    _accel_filter_y(MPU9250_ACCEL_SAMPLE_RATE, MPU9250_ACCEL_FILTER_CUTOFF_FREQ),
    _accel_filter_z(MPU9250_ACCEL_SAMPLE_RATE, MPU9250_ACCEL_FILTER_CUTOFF_FREQ),
    _gyro_filter_x(MPU9250_GYRO_SAMPLE_RATE, MPU9250_GYRO_FILTER_CUTOFF_FREQ),
    _gyro_filter_y(MPU9250_GYRO_SAMPLE_RATE, MPU9250_GYRO_FILTER_CUTOFF_FREQ),
    _gyro_filter_z(MPU9250_GYRO_SAMPLE_RATE, MPU9250_GYRO_FILTER_CUTOFF_FREQ),
    //_accel_int(MPU9250_NEVER_AUTOPUBLISH_US, FALSE),
    //_gyro_int(MPU9250_NEVER_AUTOPUBLISH_US, TRUE)
    _accel_int(MPU9250_ACCEL_INT_PUB_RATE, TRUE),
    _gyro_int(MPU9250_GYRO_INT_PUB_RATE, TRUE)
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MPU9250::~MPU9250()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MPU9250::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    int32  ind = 0;
    int32 customEventCount = 0;
    
    CFE_EVS_BinFilter_t   EventTbl[CFE_EVS_MAX_EVENT_FILTERS];

    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset(EventTbl, 0x00, sizeof(EventTbl));
    
    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    EventTbl[  ind].EventID = MPU9250_RESERVED_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;
    EventTbl[  ind].EventID = MPU9250_READ_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;
    
    
    /* Add custom events to the filter table */
    customEventCount = MPU9250_Custom_Init_EventFilters(ind, EventTbl);
    
    if(-1 == customEventCount)
    {
        iStatus = CFE_EVS_APP_FILTER_OVERLOAD;
        (void) CFE_ES_WriteToSysLog("Failed to init custom event filters (0x%08X)\n", (unsigned int)iStatus);
        goto end_of_function;
    }

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(EventTbl, (ind + customEventCount), CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("MPU9250 - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

end_of_function:

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MPU9250::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    		MPU9250_SCH_PIPE_DEPTH,
			MPU9250_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(MPU9250_MEASURE_MID, SchPipeId, CFE_SB_Default_Qos, MPU9250_MEASURE_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MPU9250_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "Sch Pipe failed to subscribe to MPU9250_MEASURE_MID. (0x%08lX)",
                    iStatus);
            goto MPU9250_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(MPU9250_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, MPU9250_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MPU9250_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to MPU9250_SEND_HK_MID. (0x%08X)",
                    (unsigned int)iStatus);
            goto MPU9250_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(MPU9250_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
            "Failed to create SCH pipe (0x%08lX)",
            iStatus);
        goto MPU9250_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
            MPU9250_CMD_PIPE_DEPTH,
            MPU9250_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(MPU9250_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MPU9250_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                "CMD Pipe failed to subscribe to MPU9250_CMD_MID. (0x%08lX)",
                iStatus);
            goto MPU9250_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(MPU9250_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
            "Failed to create CMD pipe (0x%08lX)",
            iStatus);
        goto MPU9250_InitPipe_Exit_Tag;
    }

MPU9250_InitPipe_Exit_Tag:
    return iStatus;
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MPU9250::InitData()
{
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm, MPU9250_HK_TLM_MID, sizeof(HkTlm), TRUE);
    
    /* Init diagnostic message */
    CFE_SB_InitMsg(&Diag,
            MPU9250_DIAG_TLM_MID, sizeof(MPU9250_DiagPacket_t), TRUE);

    /* Init output message accelerometer */
    CFE_SB_InitMsg(&SensorAccel,
            PX4_SENSOR_ACCEL_MID, sizeof(PX4_SensorAccelMsg_t), TRUE);

    ///* Init output message magnetometer */
    //CFE_SB_InitMsg(&SensorMag,
            //PX4_SENSOR_MAG_MID, sizeof(PX4_SensorMagMsg_t), TRUE);

    /* Init output message gyroscope */
    CFE_SB_InitMsg(&SensorGyro,
            PX4_SENSOR_GYRO_MID, sizeof(PX4_SensorGyroMsg_t), TRUE);

    Diag.Calibration.AccDivider      = 1.0;
    Diag.Calibration.GyroDivider     = 1.0;
    Diag.Calibration.AccUnit         = MPU9250_ONE_G;
    Diag.Calibration.GyroUnit        = MPU9250_RADIANS_PER_DEGREE;
    Diag.Calibration.AccRange        = MPU9250_CALC_ACC_RANGE;
    Diag.Calibration.GyroRange       = MPU9250_CALC_GYRO_RANGE;
    Diag.Calibration.AccScale        = MPU9250_ACC_SCALE;
    Diag.Calibration.GyroScale       = MPU9250_GYRO_SCALE;
    Diag.Calibration.AccXScale       = 1.0;
    Diag.Calibration.AccYScale       = 1.0;
    Diag.Calibration.AccZScale       = 1.0;
    Diag.Calibration.AccXOffset      = 0.0;
    Diag.Calibration.AccYOffset      = 0.0;
    Diag.Calibration.AccZOffset      = 0.0;
    Diag.Calibration.GyroXScale      = 1.0;
    Diag.Calibration.GyroYScale      = 1.0;
    Diag.Calibration.GyroZScale      = 1.0;
    Diag.Calibration.GyroXOffset     = 0.0;
    Diag.Calibration.GyroYOffset     = 0.0;
    Diag.Calibration.GyroZOffset     = 0.0;
    Diag.Calibration.MagXScale       = 1.0;
    Diag.Calibration.MagYScale       = 1.0;
    Diag.Calibration.MagZScale       = 1.0;
    Diag.Calibration.MagXOffset      = 0.0;
    Diag.Calibration.MagYOffset      = 0.0;
    Diag.Calibration.MagZOffset      = 0.0;
    Diag.Calibration.RoomTempOffset  = 0.0;
    Diag.Calibration.TempSensitivity = 361.0f;
    Diag.Calibration.GyroCalcScaling = MPU9250_CALC_GYRO_SCALING;
    Diag.Calibration.AccCalcScaling  = MPU9250_CALC_ACC_SCALING;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MPU9250 initialization                                          */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MPU9250::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;
    boolean returnBool = TRUE;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("MPU9250 - Failed to init events (0x%08lX)\n", iStatus);
        goto MPU9250_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto MPU9250_InitApp_Exit_Tag;
    }

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto MPU9250_InitApp_Exit_Tag;
    }

    InitData();

    returnBool = MPU9250_Custom_Init();
    if (FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(MPU9250_INIT_ERR_EID, CFE_EVS_ERROR,
                "Custom init failed");
        goto MPU9250_InitApp_Exit_Tag;
    }

    returnBool = ValidateDevice();
    if (FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(MPU9250_INIT_ERR_EID, CFE_EVS_ERROR,
                "Validate device failed");
        goto MPU9250_InitApp_Exit_Tag;
    }

    returnBool = MPU9250_SetAccScale(Diag.Calibration.AccScale, &Diag.Calibration.AccDivider);
    if(FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(MPU9250_INIT_ERR_EID, CFE_EVS_ERROR,
                "Set accelerometer scale failed");
        goto MPU9250_InitApp_Exit_Tag;
    }

    returnBool = MPU9250_SetGyroScale(Diag.Calibration.GyroScale, &Diag.Calibration.GyroDivider);
    if(FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(MPU9250_INIT_ERR_EID, CFE_EVS_ERROR,
                "Set gyroscope scale failed");
        goto MPU9250_InitApp_Exit_Tag;
    }
    ///*  Get the factory magnetometer sensitivity adjustment values */
    //returnBool = MPU9250_Read_MagAdj(&Diag.Calibration.MagXAdj, 
            //&Diag.Calibration.MagYAdj, &Diag.Calibration.MagZAdj);
    //if(FALSE == returnBool)
    //{
        //iStatus = -1;
        //CFE_EVS_SendEvent(MPU9250_INIT_ERR_EID, CFE_EVS_ERROR,
                //"Get Mag adjustment values failed.");
        //goto MPU9250_InitApp_Exit_Tag;
    //}
    
    HkTlm.State = MPU9250_INITIALIZED;

    /* Register the cleanup callback */
    iStatus = OS_TaskInstallDeleteHandler(&MPU9250_CleanupCallback);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(MPU9250_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init register cleanup callback (0x%08X)",
                                 (unsigned int)iStatus);
        goto MPU9250_InitApp_Exit_Tag;
    }

MPU9250_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(MPU9250_INIT_INF_EID, CFE_EVS_INFORMATION,
                                "Initialized. Version %d.%d.%d.%d",
                                MPU9250_MAJOR_VERSION,
                                MPU9250_MINOR_VERSION,
                                MPU9250_REVISION,
                                MPU9250_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("MPU9250 - Application failed to initialize\n");
        }
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 MPU9250::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(MPU9250_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(MPU9250_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case MPU9250_MEASURE_MID:
            {
            	static uint32 i = 0;

                ReadDevice();
                SendSensorGyro();
                SendSensorAccel();
                //if(i >= 4)
                //{
                	//SendSensorMag();
                	//i = 0;
                //}
                //else
                //{
                	//++i;
                //}
                break;
            }

            case MPU9250_SEND_HK_MID:
                ProcessCmdPipe();
                ReportHousekeeping();
                break;
            default:
                (void) CFE_EVS_SendEvent(MPU9250_MSGID_ERR_EID, CFE_EVS_ERROR,
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
        (void) CFE_EVS_SendEvent(MPU9250_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MPU9250::ProcessCmdPipe()
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
                case MPU9250_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(MPU9250_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(MPU9250_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process MPU9250 Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MPU9250::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case MPU9250_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(MPU9250_CMD_NOOP_EID, CFE_EVS_INFORMATION,
                    "Recvd NOOP. Version %d.%d.%d.%d",
                    MPU9250_MAJOR_VERSION,
                    MPU9250_MINOR_VERSION,
                    MPU9250_REVISION,
                    MPU9250_MISSION_REV);
                break;

            case MPU9250_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(MPU9250_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send MPU9250 Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MPU9250::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MPU9250::SendSensorAccel()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SensorAccel);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&SensorAccel);
}

//void MPU9250::SendSensorMag()
//{
	//static uint32 i = 0;
	//if(i >= 4)
	//{
		//CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SensorMag);
		//CFE_SB_SendMsg((CFE_SB_Msg_t*)&SensorMag);
		//i = 0;
	//}
	//++i;
//}

void MPU9250::SendSensorGyro()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SensorGyro);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&SensorGyro);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean MPU9250::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(MPU9250_MSGLEN_ERR_EID, CFE_EVS_ERROR,
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
/* MPU9250 Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void MPU9250_AppMain()
{
    oMPU9250.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MPU9250 Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MPU9250::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("MPU9250 - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(MPU9250_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(MPU9250_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(MPU9250_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(MPU9250_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(MPU9250_SCH_PIPE_PEND_TIME);
        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(MPU9250_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}


void MPU9250::ReadDevice(void)
{
    float rawX_f = 0;
    float rawY_f = 0;
    float rawZ_f = 0;
    float calX_f = 0;
    float calY_f = 0;
    float calZ_f = 0;
    //float magXAdj_f = Diag.Calibration.MagXAdj;
    //float magYAdj_f = Diag.Calibration.MagYAdj;
    //float magZAdj_f = Diag.Calibration.MagZAdj;
    uint64 timeStamp = 0;
    CFE_TIME_SysTime_t cfeTimeStamp = {0, 0};
    uint16 rawTemp = 0;
    int16 calTemp = 0;
    boolean returnBool =  TRUE;
    math::Vector3F gval;
    math::Vector3F gval_integrated;
    math::Vector3F aval;
    math::Vector3F aval_integrated;
    static uint64 prevTimeStamp = 0;

    timeStamp = PX4LIB_GetPX4TimeUs();
    
    /* Timestamps */
    //SensorMag.Timestamp
    SensorGyro.Timestamp = SensorAccel.Timestamp = timeStamp;

    /* Gyro */
    returnBool = MPU9250_Read_Gyro(&SensorGyro.XRaw, &SensorGyro.YRaw, &SensorGyro.ZRaw);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    rawX_f = (float) SensorGyro.XRaw;
    rawY_f = (float) SensorGyro.YRaw;
    rawZ_f = (float) SensorGyro.ZRaw;

    /*TODO */
    SensorGyro.XRaw = 0;
    SensorGyro.YRaw = 0;
    SensorGyro.ZRaw = 0;

    returnBool = MPU9250_Apply_Platform_Rotation(&rawX_f, &rawY_f, &rawZ_f);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    /* Gyro Calibrate */
    calX_f = (rawX_f * (Diag.Calibration.GyroUnit / Diag.Calibration.GyroDivider) - 
            Diag.Calibration.GyroXOffset) * Diag.Calibration.GyroXScale;
    calY_f = (rawY_f * (Diag.Calibration.GyroUnit / Diag.Calibration.GyroDivider) - 
            Diag.Calibration.GyroYOffset) * Diag.Calibration.GyroYScale;
    calZ_f = (rawZ_f * (Diag.Calibration.GyroUnit / Diag.Calibration.GyroDivider) - 
            Diag.Calibration.GyroZOffset) * Diag.Calibration.GyroZScale;
    /* Gyro Filter */
    SensorGyro.X = _gyro_filter_x.apply(calX_f);
    SensorGyro.Y = _gyro_filter_y.apply(calY_f);
    SensorGyro.Z = _gyro_filter_z.apply(calZ_f);
    /* Gyro Integrate */
    gval[0] = SensorGyro.X;
    gval[1] = SensorGyro.Y;
    gval[2] = SensorGyro.Z;
    gval_integrated[0] = 0.0f;
    gval_integrated[1] = 0.0f;
    gval_integrated[2] = 0.0f;

    /* TODO:  Replace this with real code, not a temporary estimate. */
    //if(prevTimeStamp != 0)
    //{
    	//SensorGyro.IntegralDt = timeStamp - prevTimeStamp;
    //}

    _gyro_int.put(timeStamp, gval, gval_integrated, SensorGyro.IntegralDt);
    
    SensorGyro.XIntegral = gval_integrated[0];
    SensorGyro.YIntegral = gval_integrated[1];
    SensorGyro.ZIntegral = gval_integrated[2];
    
    /* Gyro Scale, Range, DeviceID */
    SensorGyro.Scaling = Diag.Calibration.GyroCalcScaling;
    SensorGyro.Range = Diag.Calibration.GyroRange;

    /* TODO deviceID */
    SensorGyro.DeviceID = MPU9250_GYRO_PX4_DEVICE_ID;

    /* Accel */
    returnBool = MPU9250_Read_Accel(&SensorAccel.XRaw, &SensorAccel.YRaw, &SensorAccel.ZRaw);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    rawX_f = (float) SensorAccel.XRaw;
    rawY_f = (float) SensorAccel.YRaw;
    rawZ_f = (float) SensorAccel.ZRaw;
    
    /*TODO */
    SensorAccel.XRaw = 0;
    SensorAccel.YRaw = 0;
    SensorAccel.ZRaw = 0;

    returnBool = MPU9250_Apply_Platform_Rotation(&rawX_f, &rawY_f, &rawZ_f);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    /* Accel Calibrate */
    calX_f = (rawX_f * (Diag.Calibration.AccUnit / Diag.Calibration.AccDivider) - 
            Diag.Calibration.AccXOffset) * Diag.Calibration.AccXScale;
    calY_f = (rawY_f * (Diag.Calibration.AccUnit / Diag.Calibration.AccDivider) - 
            Diag.Calibration.AccYOffset) * Diag.Calibration.AccYScale;
    calZ_f = (rawZ_f * (Diag.Calibration.AccUnit / Diag.Calibration.AccDivider) - 
            Diag.Calibration.AccZOffset) * Diag.Calibration.AccZScale;

    /* Accel Filter */
    SensorAccel.X = _accel_filter_x.apply(calX_f);
    SensorAccel.Y = _accel_filter_y.apply(calY_f);
    SensorAccel.Z = _accel_filter_z.apply(calZ_f);

    /* Accel Integrate */
    aval[0] = SensorAccel.X;
    aval[1] = SensorAccel.Y;
    aval[2] = SensorAccel.Z;
    aval_integrated[0] = 0.0f;
    aval_integrated[1] = 0.0f;
    aval_integrated[2] = 0.0f;

    /* TODO:  Replace this with real code, not a temporary estimate. */
    //if(prevTimeStamp != 0)
    //{
    	//SensorAccel.IntegralDt = timeStamp - prevTimeStamp;
    //}
	//prevTimeStamp = timeStamp;

    _accel_int.put(timeStamp, aval, aval_integrated, SensorAccel.IntegralDt);
    
    SensorAccel.XIntegral = aval_integrated[0];
    SensorAccel.YIntegral = aval_integrated[1];
    SensorAccel.ZIntegral = aval_integrated[2];

    /* Accel Scale, Range, DeviceID */
    /* TODO */
    SensorAccel.Scaling = Diag.Calibration.AccCalcScaling;
    SensorAccel.Range_m_s2 = Diag.Calibration.AccRange;
    //SensorAccel.Scaling = 0;
    //SensorAccel.Range_m_s2 = 0;

    /* TODO deviceID */
    SensorAccel.DeviceID = MPU9250_ACCEL_PX4_DEVICE_ID;
    ///* Mag */
    //returnBool = MPU9250_Read_Mag(&SensorMag.XRaw, &SensorMag.YRaw, &SensorMag.ZRaw);
    //if(FALSE == returnBool)
    //{
        //goto end_of_function;
    //}

    //rawX_f = (float) SensorMag.XRaw;
    //rawY_f = (float) SensorMag.YRaw;
    //rawZ_f = (float) SensorMag.ZRaw;

    //returnBool = MPU9250_Apply_Platform_Rotation(&rawX_f, &rawY_f, &rawZ_f);
    //if(FALSE == returnBool)
    //{
        //goto end_of_function;
    //}

    ///* Mag Calibrate */
    //SensorMag.X = ((rawX_f * ((((Diag.Calibration.MagXAdj - 128.0f) * 0.5f) / 128.0f) + 1.0) * Diag.Calibration.MagXScale) + Diag.Calibration.MagXOffset) / 1000.0f;
    //SensorMag.Y = ((rawY_f * ((((Diag.Calibration.MagYAdj - 128.0f) * 0.5f) / 128.0f) + 1.0) * Diag.Calibration.MagYScale) + Diag.Calibration.MagYOffset) / 1000.0f;
    //SensorMag.Z = ((rawZ_f * ((((Diag.Calibration.MagZAdj - 128.0f) * 0.5f) / 128.0f) + 1.0) * Diag.Calibration.MagZScale) + Diag.Calibration.MagZOffset) / 1000.0f;

    /////* Mag Scale, Range, DeviceID */
    //SensorMag.Scaling = -1.0f;
    //SensorMag.Range = -1.0f;
    ///* TODO deviceID */
    //SensorMag.DeviceID = MPU9250_PX4_DEVICE_ID;

    /* Temp */
    returnBool = MPU9250_Read_Temp(&rawTemp);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    SensorGyro.TemperatureRaw = SensorAccel.TemperatureRaw = (int16) rawTemp;
    calTemp = (SensorAccel.TemperatureRaw / Diag.Calibration.TempSensitivity) + 35.0 - Diag.Calibration.RoomTempOffset;
    //SensorMag.Temperature
    SensorGyro.Temperature = SensorAccel.Temperature = calTemp;

end_of_function:

    if(FALSE == returnBool)
    {
        (void) CFE_EVS_SendEvent(MPU9250_READ_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 read failed");
    }
    //return returnBool;
}

boolean MPU9250::ValidateDevice(void)
{
    uint8 value = 0;
    boolean returnBool =  TRUE;
    
    returnBool = MPU9250_Read_WhoAmI(&value);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    if (MPU9250_DEVICE_ID != value)
    {
        (void) CFE_EVS_SendEvent(MPU9250_VALIDATE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 device ID match failed");
        returnBool = FALSE;
    }

//    returnBool = MPU9250_Read_MagDeviceID(&value);
//    if(FALSE == returnBool)
//    {
//        goto end_of_function;
//    }
//    if (MPU9250_AK8963_ID != value)
//    {
//        (void) CFE_EVS_SendEvent(MPU9250_VALIDATE_ERR_EID, CFE_EVS_ERROR,
//                "AK8963 device ID match failed.  Returned 0x%02hx", value);
//        returnBool = FALSE;
//    }

end_of_function:
    if(FALSE == returnBool)
    {
        (void) CFE_EVS_SendEvent(MPU9250_VALIDATE_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 validate failed");
    }
    return returnBool;
}

void MPU9250_CleanupCallback(void)
{
    oMPU9250.HkTlm.State = MPU9250_UNINITIALIZED;
    if(MPU9250_Custom_Uninit() != TRUE)
    {
        CFE_EVS_SendEvent(MPU9250_UNINIT_ERR_EID, CFE_EVS_ERROR,"MPU9250_Uninit failed");
        oMPU9250.HkTlm.State = MPU9250_INITIALIZED;
    }
}


/************************/
/*  End of File Comment */
/************************/
