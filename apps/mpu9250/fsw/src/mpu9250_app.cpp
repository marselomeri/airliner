/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "mpu9250_app.h"
#include "mpu9250_msg.h"
#include "mpu9250_version.h"


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
MPU9250::MPU9250()
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
    /* Init output message magnetometer */
    CFE_SB_InitMsg(&SensorMag,
            PX4_SENSOR_MAG_MID, sizeof(PX4_SensorMagMsg_t), TRUE);
    /* Init output message gyroscope */
    CFE_SB_InitMsg(&SensorGyro,
            PX4_SENSOR_GYRO_MID, sizeof(PX4_SensorGyroMsg_t), TRUE);

    //Diag.AccDivider      = 1.0;
    //Diag.GyroDivider     = 1.0;
    Diag.AccXCoef        = 1.0;
    Diag.AccYCoef        = 1.0;
    Diag.AccZCoef        = 1.0;
    //Diag.AccXBias = 0.0;
    //Diag.AccYBias = 0.0;
    //Diag.AccZBias = 0.0;
    Diag.GyroXCoef       = 1.0;
    Diag.GyroYCoef       = 1.0;
    Diag.GyroZCoef       = 1.0;
    //Diag.GyroXBias = 0.0;
    //Diag.GyroYBias = 0.0;
    //Diag.GyroZBias = 0.0;
    Diag.MagXCoef        = 1.0;
    Diag.MagYCoef        = 1.0;
    Diag.MagZCoef        = 1.0;
    //Diag.MagXBias = 0.0;
    //Diag.MagYBias = 0.0;
    //Diag.MagZBias = 0.0;
    //Diag.RoomTempOffset = 0.0;
    Diag.TempSensitivity = 333.87;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MPU9250 initialization                                              */
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

    InitData();

    returnBool = MPU9250_Custom_Init();
    if (FALSE == returnBool)
    {
        iStatus = -1;
        goto MPU9250_InitApp_Exit_Tag;
    }

    returnBool = MPU9250_SetAccScale(MPU9250_ACC_SCALE, &Diag.AccDivider);
    if(FALSE == returnBool)
    {
        iStatus = -1;
        goto MPU9250_InitApp_Exit_Tag;
    }

    returnBool = MPU9250_SetGyroScale(MPU9250_GYRO_SCALE, &Diag.GyroDivider);
    if(FALSE == returnBool)
    {
        iStatus = -1;
        goto MPU9250_InitApp_Exit_Tag;
    }

    /* TODO Add Gyroscope Self-Test */
    /* TODO Add Accelerometer Self-Test */
    /* TODO Add Magnetometer Self-Test */

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
                /* TODO:  Do something here. */
                break;

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
void MPU9250::SendSensorMag()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SensorMag);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&SensorMag);
}
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
    MPU9250_RawMeasMsg_t rawMsg;
    MPU9250_CalMeasMsg_t calMsg;
    boolean returnBool =  TRUE;

    returnBool = MPU9250_Read_Gyro(&rawMsg.GyroX, &rawMsg.GyroY, &rawMsg.GyroZ);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    returnBool = MPU9250_Read_Accel(&rawMsg.AccelX, &rawMsg.AccelY, &rawMsg.AccelZ);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    returnBool = MPU9250_Read_Mag(&rawMsg.MagX, &rawMsg.MagY, &rawMsg.MagZ);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    returnBool = MPU9250_Read_Temp(&rawMsg.Temp);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    returnBool = MPU9250_Read_ImuStatus(&rawMsg.WOM, &rawMsg.FifoOvflw, &rawMsg.Fsync, &rawMsg.ImuDataReady);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    returnBool = MPU9250_Read_MagStatus(&rawMsg.Overrun, &rawMsg.MagDataReady, &rawMsg.Overflow, &rawMsg.Output16Bit);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    returnBool = MPU9250_Read_MagAdj(&rawMsg.MagXAdj, &rawMsg.MagYAdj, &rawMsg.MagZAdj);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    //CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &rawMsg);
    //CFE_SB_SendMsg((CFE_SB_Msg_t *) &rawMsg);

    calMsg.AccelX = ((rawMsg.AccelX / Diag.AccDivider) * Diag.AccXCoef) + Diag.AccXBias;
    calMsg.AccelY = ((rawMsg.AccelY / Diag.AccDivider) * Diag.AccYCoef) + Diag.AccYBias;
    calMsg.AccelZ = ((rawMsg.AccelZ / Diag.AccDivider) * Diag.AccZCoef) + Diag.AccZBias;

    calMsg.GyroX = ((rawMsg.GyroX / Diag.GyroDivider) * Diag.GyroXCoef) + Diag.GyroXBias;
    calMsg.GyroY = ((rawMsg.GyroY / Diag.GyroDivider) * Diag.GyroYCoef) + Diag.GyroYBias;
    calMsg.GyroZ = ((rawMsg.GyroZ / Diag.GyroDivider) * Diag.GyroZCoef) + Diag.GyroZBias;

    calMsg.MagX = (rawMsg.MagX * ((((rawMsg.MagXAdj - 128) * 0.5) / 128) + 1) * Diag.MagXCoef) + Diag.MagXBias;
    calMsg.MagY = (rawMsg.MagY * ((((rawMsg.MagYAdj - 128) * 0.5) / 128) + 1) * Diag.MagYCoef) + Diag.MagYBias;
    calMsg.MagZ = (rawMsg.MagZ * ((((rawMsg.MagZAdj - 128) * 0.5) / 128) + 1) * Diag.MagZCoef) + Diag.MagZBias;

    calMsg.Temp = ((rawMsg.Temp - Diag.RoomTempOffset) / Diag.TempSensitivity) + 21.0;

    //CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &calMsg);
    //CFE_SB_SendMsg((CFE_SB_Msg_t *) &calMsg);
    
end_of_function:

    if(FALSE == returnBool)
    {
        (void) CFE_EVS_SendEvent(MPU9250_READ_ERR_EID, CFE_EVS_ERROR,
                "MPU9250 read failed";
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
