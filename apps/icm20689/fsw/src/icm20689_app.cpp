/****************************************************************************
*
*   Copyright (c) 2020 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include <string.h>
#include "cfe.h"
#include "icm20689_app.h"
#include "icm20689_device.h"
#include "icm20689_msg.h"
#include "icm20689_version.h"
#include "icm20689_map.h"
#include "icm20689_spi.h"
#include "math/Vector3F.hpp"
#include "px4lib.h"
#include "px4lib_msgids.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ICM20689 oICM20689;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ICM20689::ICM20689() :
    _accel_filter_x(ICM20689_ACCEL_SAMPLE_RATE, ICM20689_ACCEL_FILTER_CUTOFF_FREQ),
    _accel_filter_y(ICM20689_ACCEL_SAMPLE_RATE, ICM20689_ACCEL_FILTER_CUTOFF_FREQ),
    _accel_filter_z(ICM20689_ACCEL_SAMPLE_RATE, ICM20689_ACCEL_FILTER_CUTOFF_FREQ),
    _gyro_filter_x(ICM20689_GYRO_SAMPLE_RATE, ICM20689_GYRO_FILTER_CUTOFF_FREQ),
    _gyro_filter_y(ICM20689_GYRO_SAMPLE_RATE, ICM20689_GYRO_FILTER_CUTOFF_FREQ),
    _gyro_filter_z(ICM20689_GYRO_SAMPLE_RATE, ICM20689_GYRO_FILTER_CUTOFF_FREQ),
    _accel_int(ICM20689_ACCEL_INT_PUB_RATE, TRUE),
    _gyro_int(ICM20689_GYRO_INT_PUB_RATE, TRUE)
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ICM20689::~ICM20689()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 ICM20689::InitEvent()
{
    int32  iStatus         = CFE_SUCCESS;
    int32  ind             = 0;
    
    CFE_EVS_BinFilter_t   EventTbl[CFE_EVS_MAX_EVENT_FILTERS];

    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset(EventTbl, 0x00, sizeof(EventTbl));
    
    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    EventTbl[  ind].EventID = ICM20689_RESERVED_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;
    EventTbl[  ind].EventID = ICM20689_READ_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_FIRST_16_STOP;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(EventTbl, ind , CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("ICM20689 - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

end_of_function:

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 ICM20689::InitPipe()
{
    int32  iStatus = CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
            ICM20689_SCH_PIPE_DEPTH,
            ICM20689_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(ICM20689_MEASURE_MID, SchPipeId, CFE_SB_Default_Qos, ICM20689_MEASURE_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(ICM20689_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "Sch Pipe failed to subscribe to ICM20689_MEASURE_MID. (0x%08lX)",
                    iStatus);
            goto ICM20689_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(ICM20689_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, ICM20689_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(ICM20689_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                    "CMD Pipe failed to subscribe to ICM20689_SEND_HK_MID. (0x%08X)",
                    (unsigned int)iStatus);
            goto ICM20689_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(ICM20689_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
            "Failed to create SCH pipe (0x%08lX)",
            iStatus);
        goto ICM20689_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
            ICM20689_CMD_PIPE_DEPTH,
            ICM20689_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(ICM20689_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(ICM20689_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                "CMD Pipe failed to subscribe to ICM20689_CMD_MID. (0x%08lX)",
                iStatus);
            goto ICM20689_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(ICM20689_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
            "Failed to create CMD pipe (0x%08lX)",
            iStatus);
        goto ICM20689_InitPipe_Exit_Tag;
    }

ICM20689_InitPipe_Exit_Tag:
    return (iStatus);
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ICM20689::InitData()
{
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm, ICM20689_HK_TLM_MID, sizeof(HkTlm), TRUE);
    
    /* Init diagnostic message */
    CFE_SB_InitMsg(&Diag,
            ICM20689_DIAG_TLM_MID, sizeof(ICM20689_DiagPacket_t), TRUE);

    /* Init output message accelerometer */
    CFE_SB_InitMsg(&SensorAccel,
            PX4_SENSOR_ACCEL_MID, sizeof(PX4_SensorAccelMsg_t), TRUE);

    /* Init output message gyroscope */
    CFE_SB_InitMsg(&SensorGyro,
            PX4_SENSOR_GYRO_MID, sizeof(PX4_SensorGyroMsg_t), TRUE);

    /* Start initialization of user calibration values */
    UpdateParamsFromTable();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* ICM20689 initialization                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 ICM20689::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;
    boolean returnBool = TRUE;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("ICM20689 - Failed to init events (0x%08lX)\n", iStatus);
        goto ICM20689_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto ICM20689_InitApp_Exit_Tag;
    }

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto ICM20689_InitApp_Exit_Tag;
    }

    InitData();

    /* Initialize the SPI interface. */
    returnBool = ICM20689_Spi_Init(ConfigTblPtr);
    if (FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(ICM20689_INIT_ERR_EID, CFE_EVS_ERROR,
                "SPI init failed");
        goto ICM20689_InitApp_Exit_Tag;
    }

    /* Check the WhoAmI Register. */
    returnBool = ValidateDevice();
    if (FALSE == returnBool)
    {
        iStatus = -1;
        (void) CFE_EVS_SendEvent(ICM20689_INIT_ERR_EID, CFE_EVS_ERROR,
                "Validate device failed");
        goto ICM20689_InitApp_Exit_Tag;
    }

    /* Initialize the device. */
    returnBool = ICM20689_Device_Init(ConfigTblPtr);
    if (FALSE == returnBool)
    {
        iStatus = -1;
        CFE_EVS_SendEvent(ICM20689_INIT_ERR_EID, CFE_EVS_ERROR,
                "Device init failed");
        goto ICM20689_InitApp_Exit_Tag;
    }

    HkTlm.State = ICM20689_INITIALIZED;

    /* Register the cleanup callback */
    iStatus = OS_TaskInstallDeleteHandler(&ICM20689_CleanupCallback);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(ICM20689_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init register cleanup callback (0x%08X)",
                                 (unsigned int)iStatus);
        goto ICM20689_InitApp_Exit_Tag;
    }

    /* Get the rotation for diag */
    ICM20689_Get_Rotation(&Diag.Calibration.Rotation);

ICM20689_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(ICM20689_INIT_INF_EID, CFE_EVS_INFORMATION,
                                "Initialized. Version %d.%d.%d.%d",
                                ICM20689_MAJOR_VERSION,
                                ICM20689_MINOR_VERSION,
                                ICM20689_REVISION,
                                ICM20689_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("ICM20689 - Application failed to initialize\n");
        }
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 ICM20689::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr  = NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(ICM20689_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(ICM20689_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case ICM20689_MEASURE_MID:
            {
                ReadDevice();
                SendSensorGyro();
                SendSensorAccel();
                break;
            }

            case ICM20689_SEND_HK_MID:
            {
                ProcessCmdPipe();
                ReportHousekeeping();
                break;
            }
            default:
            {
                (void) CFE_EVS_SendEvent(ICM20689_MSGID_ERR_EID, CFE_EVS_ERROR,
                     "Recvd invalid SCH msgId (0x%04X)", MsgId);
            }
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* If there's no incoming message, do nothing here, 
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* If there's no incoming message within a specified time (via 
         * the iBlocking arg, you can do nothing here.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else
    {
        (void) CFE_EVS_SendEvent(ICM20689_RCVMSG_ERR_EID, CFE_EVS_ERROR,
              "SCH pipe read error (0x%08lX).", iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ICM20689::ProcessCmdPipe()
{
    int32 iStatus             = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr = NULL;
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
                case ICM20689_CMD_MID:
                {
                    ProcessAppCmds(CmdMsgPtr);
                    break;
                }
                default:
                {
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(ICM20689_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid CMD msgId (0x%04X)", (unsigned short)CmdMsgId);
                    break;
                }
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(ICM20689_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
    return;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process ICM20689 Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ICM20689::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode = 0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case ICM20689_NOOP_CC:
            {
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(ICM20689_CMD_NOOP_EID, CFE_EVS_INFORMATION,
                    "Recvd NOOP. Version %d.%d.%d.%d",
                    ICM20689_MAJOR_VERSION,
                    ICM20689_MINOR_VERSION,
                    ICM20689_REVISION,
                    ICM20689_MISSION_REV);
                break;
            }
            case ICM20689_RESET_CC:
            {
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;
            }
            case ICM20689_SEND_DIAG_CC:
            {
                SendDiag();
                break;
            }
            case ICM20689_SET_CALIBRATION_CC:
            {
                if(CFE_SUCCESS == UpdateCalibrationValues((ICM20689_SetCalibrationCmd_t *) MsgPtr))
                {
                    UpdateParamsFromTable();
                    HkTlm.usCmdCnt++;
                    (void) CFE_EVS_SendEvent(ICM20689_CALIBRATE_INF_EID, CFE_EVS_INFORMATION,
                                  "Calibration values updated");
                }
                else
                {
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(ICM20689_CALIBRATE_ERR_EID, CFE_EVS_ERROR,
                                  "Calibration values failed to update");
                }
                break;
            }
            default:
            {
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(ICM20689_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
            }
        }
    }
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send ICM20689 Housekeeping                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void ICM20689::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
    return;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ICM20689::SendSensorAccel()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SensorAccel);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&SensorAccel);
    return;
}


void ICM20689::SendSensorGyro()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SensorGyro);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&SensorGyro);
    return;
}


void ICM20689::SendDiag()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&Diag);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&Diag);
    return;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean ICM20689::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(ICM20689_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* ICM20689 Application C style main entry point.                   */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void ICM20689_AppMain()
{
    oICM20689.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* ICM20689 Application C++ style main entry point.                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ICM20689::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("ICM20689 - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(ICM20689_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(ICM20689_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(ICM20689_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(ICM20689_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(ICM20689_SCH_PIPE_PEND_TIME);
        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(ICM20689_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Read from the device                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ICM20689::ReadDevice(void)
{
    float rawX_f       = 0;
    float rawY_f       = 0;
    float rawZ_f       = 0;
    float calX_f       = 0;
    float calY_f       = 0;
    float calZ_f       = 0;
    uint64 timeStamp   = 0;
    uint16 rawTemp     = 0;
    int16 calTemp      = 0;
    boolean returnBool = TRUE;
    math::Vector3F gval;
    math::Vector3F gval_integrated;
    math::Vector3F aval;
    math::Vector3F aval_integrated;

    /* Get a timestamp */
    timeStamp = PX4LIB_GetPX4TimeUs();

    /* Set measurement timestamps */
    SensorGyro.Timestamp  = timeStamp;
    SensorAccel.Timestamp = timeStamp;

    /* Gyro */
    returnBool = ICM20689_Read_Gyro(&SensorGyro.XRaw, &SensorGyro.YRaw, &SensorGyro.ZRaw);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    rawX_f = SensorGyro.XRaw;
    rawY_f = SensorGyro.YRaw;
    rawZ_f = SensorGyro.ZRaw;

    returnBool = ICM20689_Apply_Platform_Rotation(&rawX_f, &rawY_f, &rawZ_f);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    
    /* Gyro unit conversion */
    calX_f = rawX_f * (ConfigTblPtr->GyroUnit / ConfigTblPtr->GyroDivider);
    calY_f = rawY_f * (ConfigTblPtr->GyroUnit / ConfigTblPtr->GyroDivider);
    calZ_f = rawZ_f * (ConfigTblPtr->GyroUnit / ConfigTblPtr->GyroDivider); 
    
    /* Gyro Calibrate */
    calX_f = (calX_f - ConfigTblPtr->GyroXOffset) * ConfigTblPtr->GyroXScale;
    calY_f = (calY_f - ConfigTblPtr->GyroYOffset) * ConfigTblPtr->GyroYScale;
    calZ_f = (calZ_f - ConfigTblPtr->GyroZOffset) * ConfigTblPtr->GyroZScale;

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

    _gyro_int.put(timeStamp, gval, gval_integrated, SensorGyro.IntegralDt);
    
    SensorGyro.XIntegral = gval_integrated[0];
    SensorGyro.YIntegral = gval_integrated[1];
    SensorGyro.ZIntegral = gval_integrated[2];
    
    /* Gyro Scale, Range, DeviceID */
    SensorGyro.Scaling = (ConfigTblPtr->GyroUnit / ConfigTblPtr->GyroDivider);
    SensorGyro.Range   = (ConfigTblPtr->AccScale * ConfigTblPtr->GyroUnit);

    /* TODO deviceID */
    //SensorGyro.DeviceID = ICM20689_GYRO_PX4_DEVICE_ID;

    /* Accel */
    returnBool = ICM20689_Read_Accel(&SensorAccel.XRaw, &SensorAccel.YRaw, &SensorAccel.ZRaw);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    rawX_f = SensorAccel.XRaw;
    rawY_f = SensorAccel.YRaw;
    rawZ_f = SensorAccel.ZRaw;

    returnBool = ICM20689_Apply_Platform_Rotation(&rawX_f, &rawY_f, &rawZ_f);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    /* Accel unit conversion */
    calX_f = rawX_f * (Diag.Conversion.AccUnit / Diag.Conversion.AccDivider);
    calY_f = rawY_f * (Diag.Conversion.AccUnit / Diag.Conversion.AccDivider);
    calZ_f = rawZ_f * (Diag.Conversion.AccUnit / Diag.Conversion.AccDivider);
    
    /* Accel Calibrate */
    calX_f = (calX_f - m_Params.AccXOffset) * m_Params.AccXScale;
    calY_f = (calY_f - m_Params.AccYOffset) * m_Params.AccYScale;
    calZ_f = (calZ_f - m_Params.AccZOffset) * m_Params.AccZScale;

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

    _accel_int.put(timeStamp, aval, aval_integrated, SensorAccel.IntegralDt);
    
    SensorAccel.XIntegral = aval_integrated[0];
    SensorAccel.YIntegral = aval_integrated[1];
    SensorAccel.ZIntegral = aval_integrated[2];

    /* Accel Scale, Range, DeviceID */
    SensorAccel.Scaling = (ConfigTblPtr->AccUnit / ConfigTblPtr->AccDivider);
    SensorAccel.Range_m_s2 = (ConfigTblPtr->AccScale * ConfigTblPtr->AccUnit);

    /* TODO deviceID */
    //SensorAccel.DeviceID = ICM20689_ACCEL_PX4_DEVICE_ID;

    /* Temperature */
    returnBool = ICM20689_Read_Temp(&rawTemp);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }

    SensorGyro.TemperatureRaw = SensorAccel.TemperatureRaw = (int16) rawTemp;

    calTemp = (SensorAccel.TemperatureRaw / ConfigTblPtr->TempSensitivity) + ConfigTblPtr->TempOffset;
    SensorGyro.Temperature  = calTemp;
    SensorAccel.Temperature = calTemp;

end_of_function:

    if(FALSE == returnBool)
    {
        (void) CFE_EVS_SendEvent(ICM20689_READ_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 read failed");
    }
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate the Device via the Device ID                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean ICM20689::ValidateDevice(void)
{
    uint8 value = 0;
    boolean returnBool =  TRUE;
    
    returnBool = ICM20689_Read_WhoAmI(&value);
    if(FALSE == returnBool)
    {
        goto end_of_function;
    }
    if (ConfigTblPtr->WhoAmIValue != value)
    {
        (void) CFE_EVS_SendEvent(ICM20689_VALIDATE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 device ID match failed");
        returnBool = FALSE;
    }

end_of_function:
    if(FALSE == returnBool)
    {
        (void) CFE_EVS_SendEvent(ICM20689_VALIDATE_ERR_EID, CFE_EVS_ERROR,
                "ICM20689 validate failed");
    }
    return (returnBool);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Cleanup before exit                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ICM20689_CleanupCallback(void)
{
    oICM20689.HkTlm.State = ICM20689_UNINITIALIZED;
    ICM20689_Spi_Cleanup();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Update Params from the Config Table                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ICM20689::UpdateParamsFromTable(void)
{
    if(0 != ConfigTblPtr)
    {
        /* Copy to m_Params from the config table */
        m_Params.AccXScale      = ConfigTblPtr->AccXScale;
        m_Params.AccYScale      = ConfigTblPtr->AccYScale;
        m_Params.AccZScale      = ConfigTblPtr->AccZScale;
        m_Params.AccXOffset     = ConfigTblPtr->AccXOffset;
        m_Params.AccYOffset     = ConfigTblPtr->AccYOffset;
        m_Params.AccZOffset     = ConfigTblPtr->AccZOffset;
        m_Params.GyroXScale     = ConfigTblPtr->GyroXScale;
        m_Params.GyroYScale     = ConfigTblPtr->GyroYScale;
        m_Params.GyroZScale     = ConfigTblPtr->GyroZScale;
        m_Params.GyroXOffset    = ConfigTblPtr->GyroXOffset;
        m_Params.GyroYOffset    = ConfigTblPtr->GyroYOffset;
        m_Params.GyroZOffset    = ConfigTblPtr->GyroZOffset;
        
        /* Copy to the diag message for downlink */
        Diag.Calibration.AccXScale       = m_Params.AccXScale;
        Diag.Calibration.AccYScale       = m_Params.AccYScale;
        Diag.Calibration.AccZScale       = m_Params.AccZScale;
        Diag.Calibration.AccXOffset      = m_Params.AccXOffset;
        Diag.Calibration.AccYOffset      = m_Params.AccYOffset;
        Diag.Calibration.AccZOffset      = m_Params.AccZOffset;
        Diag.Calibration.GyroXScale      = m_Params.GyroXScale;
        Diag.Calibration.GyroYScale      = m_Params.GyroYScale;
        Diag.Calibration.GyroZScale      = m_Params.GyroZScale;
        Diag.Calibration.GyroXOffset     = m_Params.GyroXOffset;
        Diag.Calibration.GyroYOffset     = m_Params.GyroYOffset;
        Diag.Calibration.GyroZOffset     = m_Params.GyroZOffset;

        /* Also copy the conversion values. */
        Diag.Conversion.AccDivider       = ConfigTblPtr->AccDivider;
        Diag.Conversion.AccScale         = ConfigTblPtr->AccScale;
        Diag.Conversion.AccUnit          = ConfigTblPtr->AccUnit;
        Diag.Conversion.GyroDivider      = ConfigTblPtr->GyroDivider;
        Diag.Conversion.GyroScale        = ConfigTblPtr->GyroScale;
        Diag.Conversion.GyroUnit         = ConfigTblPtr->GyroUnit;
        Diag.Conversion.TempOffset       = ConfigTblPtr->TempOffset;
        Diag.Conversion.TempSensitivity  = ConfigTblPtr->TempSensitivity;
    }
    return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Update Calibration Values                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 ICM20689::UpdateCalibrationValues(ICM20689_SetCalibrationCmd_t *CalibrationMsgPtr) 
{
    int32 Status = -1;
    
    if(0 != ConfigTblPtr)
    {
        ConfigTblPtr->AccXScale = CalibrationMsgPtr->Calibration.AccXScale;
        ConfigTblPtr->AccYScale = CalibrationMsgPtr->Calibration.AccYScale;
        ConfigTblPtr->AccZScale = CalibrationMsgPtr->Calibration.AccZScale;
        ConfigTblPtr->AccXOffset = CalibrationMsgPtr->Calibration.AccXOffset;
        ConfigTblPtr->AccYOffset = CalibrationMsgPtr->Calibration.AccYOffset;
        ConfigTblPtr->AccZOffset = CalibrationMsgPtr->Calibration.AccZOffset;
        ConfigTblPtr->GyroXScale = CalibrationMsgPtr->Calibration.GyroXScale;
        ConfigTblPtr->GyroYScale = CalibrationMsgPtr->Calibration.GyroYScale;
        ConfigTblPtr->GyroZScale = CalibrationMsgPtr->Calibration.GyroZScale;
        ConfigTblPtr->GyroXOffset = CalibrationMsgPtr->Calibration.GyroXOffset;
        ConfigTblPtr->GyroYOffset = CalibrationMsgPtr->Calibration.GyroYOffset;
        ConfigTblPtr->GyroZOffset = CalibrationMsgPtr->Calibration.GyroZOffset;

        Status = CFE_TBL_Modified(ConfigTblHdl);
    }
    
    return Status;
}


/************************/
/*  End of File Comment */
/************************/
