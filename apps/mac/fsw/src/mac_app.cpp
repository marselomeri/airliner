/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
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
#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <errno.h>

#include "cfe.h"

#include "mac_app.h"
#include "mac_msg.h"
#include "mac_version.h"
#include <math.h>
#include "cfs_utils.h"

#include "Quaternion.hpp"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MAC oMAC;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MAC::MAC()
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
MAC::~MAC()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    uint32  ind = 0;

    /* Initialize the event filter table.
     * Note: 0 is the CFE_EVS_NO_FILTER mask and event 0 is reserved (not used) */
    memset((void*)EventTbl, 0x00, sizeof(EventTbl));

    /* TODO: Choose the events you want to filter.  CFE_EVS_MAX_EVENT_FILTERS
     * limits the number of filters per app.  An explicit CFE_EVS_NO_FILTER 
     * (the default) has been provided as an example. */
    EventTbl[  ind].EventID = MAC_RESERVED_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EventTbl[  ind].EventID = MAC_INF_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EventTbl[  ind].EventID = MAC_CONFIG_TABLE_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EventTbl[  ind].EventID = MAC_CDS_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EventTbl[  ind].EventID = MAC_PIPE_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EventTbl[  ind].EventID = MAC_MSGID_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    EventTbl[  ind].EventID = MAC_MSGLEN_ERR_EID;
    EventTbl[ind++].Mask    = CFE_EVS_NO_FILTER;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(EventTbl,
                               MAC_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("MAC - Failed to register with EVS (0x%08X)\n", (unsigned int)iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
                                 MAC_SCH_PIPE_DEPTH,
                                 MAC_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(MAC_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, MAC_SCH_PIPE_SEND_HK_RESERVED);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to MAC_SEND_HK_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(MAC_RUN_CONTROLLER_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to MAC_RUN_CONTROLLER_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_ARMED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_ACTUATOR_ARMED_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_CONTROLS_0_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_ACTUATOR_CONTROLS_0_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_BATTERY_STATUS_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_BATTERY_STATUS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_CONTROL_STATE_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_CONTROL_STATE_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_MANUAL_CONTROL_SETPOINT_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_MANUAL_CONTROL_SETPOINT_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_MC_ATT_CTRL_STATUS_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_MC_ATT_CTRL_STATUS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_MULTIROTOR_MOTOR_LIMITS_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_MULTIROTOR_MOTOR_LIMITS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_SENSOR_CORRECTION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_SENSOR_CORRECTION_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_SENSOR_GYRO_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_SENSOR_GYRO_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_ATTITUDE_SETPOINT_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_VEHICLE_ATTITUDE_SETPOINT_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_CONTROL_MODE_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_VEHICLE_CONTROL_MODE_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_RATES_SETPOINT_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_VEHICLE_RATES_SETPOINT_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_STATUS_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_VEHICLE_STATUS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create SCH pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
                                 MAC_CMD_PIPE_DEPTH,
                                 MAC_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(MAC_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to MAC_CMD_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto MAC_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create CMD pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitPipe_Exit_Tag;
    }

    /* Init data pipe and subscribe to messages on the data pipe */
    iStatus = CFE_SB_CreatePipe(&DataPipeId,
                                 MAC_DATA_PIPE_DEPTH,
                                 MAC_DATA_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, DataPipeId);
        */
    }
    else
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create Data pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitPipe_Exit_Tag;
    }

MAC_InitPipe_Exit_Tag:
    return (iStatus);
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init actuator outputs message */
    CFE_SB_InitMsg(&ActuatorOutputs,
            PX4_ACTUATOR_OUTPUTS_MID, sizeof(ActuatorOutputs), TRUE);

    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
                   MAC_HK_TLM_MID, sizeof(HkTlm), TRUE);

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MAC initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("MAC - Failed to init events (0x%08X)\n", (unsigned int)iStatus);
        goto MAC_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init pipes (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitApp_Exit_Tag;
    }

    iStatus = InitData();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init data (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitApp_Exit_Tag;
    }

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init config tables (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitApp_Exit_Tag;
    }

    PwmLimit_Init(&PwmLimit);

MAC_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(MAC_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
                                 MAC_MAJOR_VERSION,
                                 MAC_MINOR_VERSION,
                                 MAC_REVISION,
                                 MAC_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR, "Application failed to initialize");
        }
        else
        {
            (void) CFE_ES_WriteToSysLog("MAC - Application failed to initialize\n");
        }
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 MAC::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(MAC_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(MAC_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case MAC_SEND_HK_MID:
                ReportHousekeeping();
                break;

            case MAC_RUN_CONTROLLER_MID:
                RunController();
                break;

            case PX4_ACTUATOR_ARMED_MID:
                memcpy(&CVT.Armed, MsgPtr, sizeof(CVT.Armed));
                RunController();
                break;

            case PX4_ACTUATOR_CONTROLS_0_MID:
                memcpy(&CVT.Actuators, MsgPtr, sizeof(CVT.Actuators));
                break;

            case PX4_BATTERY_STATUS_MID:
                memcpy(&CVT.BatteryStatus, MsgPtr, sizeof(CVT.BatteryStatus));
                break;

            case PX4_CONTROL_STATE_MID:
            	OS_printf("PX4_CONTROL_STATE_MID\n");
                memcpy(&CVT.ControlState, MsgPtr, sizeof(CVT.ControlState));
                break;

            case PX4_MANUAL_CONTROL_SETPOINT_MID:
            	OS_printf("PX4_MANUAL_CONTROL_SETPOINT_MID\n");
                memcpy(&CVT.ManualControlSp, MsgPtr, sizeof(CVT.ManualControlSp));
                break;

            case PX4_MC_ATT_CTRL_STATUS_MID:
                memcpy(&CVT.ControllerStatus, MsgPtr, sizeof(CVT.ControllerStatus));
                break;

            case PX4_MULTIROTOR_MOTOR_LIMITS_MID:
            	OS_printf("PX4_MULTIROTOR_MOTOR_LIMITS_MID\n");
                memcpy(&CVT.MotorLimits, MsgPtr, sizeof(CVT.MotorLimits));
                break;

            case PX4_SENSOR_CORRECTION_MID:
            	OS_printf("PX4_SENSOR_CORRECTION_MID\n");
                memcpy(&CVT.SensorCorrection, MsgPtr, sizeof(CVT.SensorCorrection));
                break;

            case PX4_SENSOR_GYRO_MID:
                memcpy(&CVT.SensorGyro, MsgPtr, sizeof(CVT.SensorGyro));
                break;

            case PX4_VEHICLE_ATTITUDE_SETPOINT_MID:
            	OS_printf("PX4_VEHICLE_ATTITUDE_SETPOINT_MID\n");
                memcpy(&CVT.VAttSp, MsgPtr, sizeof(CVT.VAttSp));
                break;

            case PX4_VEHICLE_CONTROL_MODE_MID:
                memcpy(&CVT.VControlMode, MsgPtr, sizeof(CVT.VControlMode));
                break;

            case PX4_VEHICLE_RATES_SETPOINT_MID:
                memcpy(&CVT.VRatesSp, MsgPtr, sizeof(CVT.VRatesSp));
                break;

            case PX4_VEHICLE_STATUS_MID:
                memcpy(&CVT.VehicleStatus, MsgPtr, sizeof(CVT.VehicleStatus));
                break;

            default:
                (void) CFE_EVS_SendEvent(MAC_MSGID_ERR_EID, CFE_EVS_ERROR,
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
        /* TODO: This is an example of exiting on an error (either CFE_SB_BAD_ARGUMENT, or
         * CFE_SB_PIPE_RD_ERROR).
         */
        (void) CFE_EVS_SendEvent(MAC_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "SB pipe read error (0x%08X), app will exit", (unsigned int)iStatus);
        uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MAC::ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case MAC_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(MAC_MSGID_ERR_EID, CFE_EVS_ERROR,
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
            (void) CFE_EVS_SendEvent(MAC_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08X)", (unsigned int)iStatus);
            uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process MAC Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MAC::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case MAC_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(MAC_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd NOOP cmd (%u), Version %d.%d.%d.%d",
                                  (unsigned int)uiCmdCode,
                                  MAC_MAJOR_VERSION,
                                  MAC_MINOR_VERSION,
                                  MAC_REVISION,
                                  MAC_MISSION_REV);
                break;

            case MAC_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                (void) CFE_EVS_SendEvent(MAC_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "Recvd RESET cmd (%u)", (unsigned int)uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the MAC commands here */

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(MAC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid cmdId (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send MAC Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MAC::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void MAC::SendActuatorOutputs()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ActuatorOutputs);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&ActuatorOutputs);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean MAC::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            (void) CFE_EVS_SendEvent(MAC_MSGLEN_ERR_EID, CFE_EVS_ERROR,
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
/* MAC Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MAC_AppMain()
{
    oMAC.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MAC Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MAC::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("MAC - Failed to register the app (0x%08X)\n", (unsigned int)iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(MAC_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(MAC_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(MAC_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(MAC_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(MAC_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(MAC_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}

void MAC::RunController(void)
{
	OS_printf("MAC::RunController()\n");

	static uint64 last_run = 0;
	float dt = (CFE_TIME_GetTimeInMicros() - last_run) / 1000000.0f;

	/* guard against too small (< 2ms) and too large (> 20ms) dt's */
	if (dt < 0.002f)
	{
		dt = 0.002f;
	}
	else if (dt > 0.02f)
	{
		dt = 0.02f;
	}

//	/* check for updates in other topics */
//	parameter_update_poll();

	/* Check if we are in rattitude mode and the pilot is above the threshold on pitch
	 * or roll (yaw can rotate 360 in normal att control).  If both are true don't
	 * even bother running the attitude controllers */
	if (CVT.VControlMode.ControlRattitudeEnabled)
	{
		if (fabsf(CVT.ManualControlSp.Y) > ParamTblPtr->rattitude_thres ||
		    fabsf(CVT.ManualControlSp.X) > ParamTblPtr->rattitude_thres)
		{
			CVT.VControlMode.ControlAttitudeEnabled = FALSE;
		}
	}

	if (CVT.VControlMode.ControlAttitudeEnabled)
	{
//		if (_ts_opt_recovery == nullptr) {
//			// the  tailsitter recovery instance has not been created, thus, the vehicle
//			// is not a tailsitter, do normal attitude control
			ControlAttitude(dt);
//		}
//		else
//		{
//			vehicle_attitude_setpoint_poll();
//			_thrust_sp = _v_att_sp.thrust;
//			math::Quaternion q(_ctrl_state.q[0], _ctrl_state.q[1], _ctrl_state.q[2], _ctrl_state.q[3]);
//			math::Quaternion q_sp(&_v_att_sp.q_d[0]);
//			_ts_opt_recovery->setAttGains(_params.att_p, _params.yaw_ff);
//			_ts_opt_recovery->calcOptimalRates(q, q_sp, _v_att_sp.yaw_sp_move_rate, _rates_sp);
//
//			/* limit rates */
//			for (int i = 0; i < 3; i++) {
//				_rates_sp(i) = math::constrain(_rates_sp(i), -_params.mc_rate_max(i), _params.mc_rate_max(i));
//			}
//		}

//		/* publish attitude rates setpoint */
//		_v_rates_sp.roll = _rates_sp(0);
//		_v_rates_sp.pitch = _rates_sp(1);
//		_v_rates_sp.yaw = _rates_sp(2);
//		_v_rates_sp.thrust = _thrust_sp;
//		_v_rates_sp.timestamp = hrt_absolute_time();
//
//		if (_v_rates_sp_pub != nullptr) {
//			orb_publish(_rates_sp_id, _v_rates_sp_pub, &_v_rates_sp);
//
//		} else if (_rates_sp_id) {
//			_v_rates_sp_pub = orb_advertise(_rates_sp_id, &_v_rates_sp);
//		}
//
//		}

	}
	else
	{
//		/* attitude controller disabled, poll rates setpoint topic */
//		if (_v_control_mode.flag_control_manual_enabled) {
//			/* manual rates control - ACRO mode */
//			_rates_sp = math::Vector<3>(_manual_control_sp.y, -_manual_control_sp.x,
//						    _manual_control_sp.r).emult(_params.acro_rate_max);
//			_thrust_sp = math::min(_manual_control_sp.z, MANUAL_THROTTLE_MAX_MULTICOPTER);
//
//			/* publish attitude rates setpoint */
//			_v_rates_sp.roll = _rates_sp(0);
//			_v_rates_sp.pitch = _rates_sp(1);
//			_v_rates_sp.yaw = _rates_sp(2);
//			_v_rates_sp.thrust = _thrust_sp;
//			_v_rates_sp.timestamp = hrt_absolute_time();
//
//			if (_v_rates_sp_pub != nullptr) {
//				orb_publish(_rates_sp_id, _v_rates_sp_pub, &_v_rates_sp);
//
//			} else if (_rates_sp_id) {
//				_v_rates_sp_pub = orb_advertise(_rates_sp_id, &_v_rates_sp);
//			}
//
//		} else {
//			/* attitude controller disabled, poll rates setpoint topic */
//			vehicle_rates_setpoint_poll();
//			_rates_sp(0) = _v_rates_sp.roll;
//			_rates_sp(1) = _v_rates_sp.pitch;
//			_rates_sp(2) = _v_rates_sp.yaw;
//			_thrust_sp = _v_rates_sp.thrust;
//		}
	}

	if (CVT.VControlMode.ControlRatesEnabled)
	{
		ControlAttitudeRates(dt);
//
//		/* publish actuator controls */
//		_actuators.control[0] = (PX4_ISFINITE(_att_control(0))) ? _att_control(0) : 0.0f;
//		_actuators.control[1] = (PX4_ISFINITE(_att_control(1))) ? _att_control(1) : 0.0f;
//		_actuators.control[2] = (PX4_ISFINITE(_att_control(2))) ? _att_control(2) : 0.0f;
//		_actuators.control[3] = (PX4_ISFINITE(_thrust_sp)) ? _thrust_sp : 0.0f;
//		_actuators.control[7] = _v_att_sp.landing_gear;
//		_actuators.timestamp = hrt_absolute_time();
//		_actuators.timestamp_sample = _ctrl_state.timestamp;
//
//		/* scale effort by battery status */
//		if (_params.bat_scale_en && _battery_status.scale > 0.0f) {
//			for (int i = 0; i < 4; i++) {
//				_actuators.control[i] *= _battery_status.scale;
//			}
//		}
//
//		_controller_status.roll_rate_integ = _rates_int(0);
//		_controller_status.pitch_rate_integ = _rates_int(1);
//		_controller_status.yaw_rate_integ = _rates_int(2);
//		_controller_status.timestamp = hrt_absolute_time();
//
//		if (!_actuators_0_circuit_breaker_enabled) {
//			if (_actuators_0_pub != nullptr) {
//
//				orb_publish(_actuators_id, _actuators_0_pub, &_actuators);
//				perf_end(_controller_latency_perf);
//
//			} else if (_actuators_id) {
//				_actuators_0_pub = orb_advertise(_actuators_id, &_actuators);
//			}
//
//		}
//
//		/* publish controller status */
//		if (_controller_status_pub != nullptr) {
//			orb_publish(ORB_ID(mc_att_ctrl_status), _controller_status_pub, &_controller_status);
//
//		} else {
//			_controller_status_pub = orb_advertise(ORB_ID(mc_att_ctrl_status), &_controller_status);
//		}
	}

	if (CVT.VControlMode.ControlTerminationEnabled)
	{
		if (!CVT.VehicleStatus.IsVtol)
		{
//			_rates_sp.zero();
//			_rates_int.zero();
//			_thrust_sp = 0.0f;
//			_att_control.zero();
//
//
//			/* publish actuator controls */
//			_actuators.control[0] = 0.0f;
//			_actuators.control[1] = 0.0f;
//			_actuators.control[2] = 0.0f;
//			_actuators.control[3] = 0.0f;
//			_actuators.timestamp = hrt_absolute_time();
//			_actuators.timestamp_sample = _ctrl_state.timestamp;
//
//			if (!_actuators_0_circuit_breaker_enabled) {
//				if (_actuators_0_pub != nullptr) {
//
//					orb_publish(_actuators_id, _actuators_0_pub, &_actuators);
//					perf_end(_controller_latency_perf);
//
//				} else if (_actuators_id) {
//					_actuators_0_pub = orb_advertise(_actuators_id, &_actuators);
//				}
//			}
//
//			_controller_status.roll_rate_integ = _rates_int(0);
//			_controller_status.pitch_rate_integ = _rates_int(1);
//			_controller_status.yaw_rate_integ = _rates_int(2);
//			_controller_status.timestamp = hrt_absolute_time();
//
//			/* publish controller status */
//			if (_controller_status_pub != nullptr) {
//				orb_publish(ORB_ID(mc_att_ctrl_status), _controller_status_pub, &_controller_status);
//
//			} else {
//				_controller_status_pub = orb_advertise(ORB_ID(mc_att_ctrl_status), &_controller_status);
//			}
//
//			/* publish attitude rates setpoint */
//			_v_rates_sp.roll = _rates_sp(0);
//			_v_rates_sp.pitch = _rates_sp(1);
//			_v_rates_sp.yaw = _rates_sp(2);
//			_v_rates_sp.thrust = _thrust_sp;
//			_v_rates_sp.timestamp = hrt_absolute_time();
//
//			if (_v_rates_sp_pub != nullptr) {
//				orb_publish(_rates_sp_id, _v_rates_sp_pub, &_v_rates_sp);
//
//			} else if (_rates_sp_id) {
//				_v_rates_sp_pub = orb_advertise(_rates_sp_id, &_v_rates_sp);
//			}
		}
	}
}


void MAC::ControlAttitude(float dt)
{

//	vehicle_attitude_setpoint_poll();
//
	ThrustSp = CVT.VAttSp.Thrust;

	/* construct attitude setpoint rotation matrix */
	math::Quaternion q_sp(
			CVT.VAttSp.Q_D[0],
			CVT.VAttSp.Q_D[1],
			CVT.VAttSp.Q_D[2],
			CVT.VAttSp.Q_D[3]);

	math::Matrix3F3 R_sp = q_sp.RotationMatrix();

	/* get current rotation matrix from control state quaternions */
	math::Quaternion q_att(CVT.ControlState.Q[0], CVT.ControlState.Q[1], CVT.ControlState.Q[2], CVT.ControlState.Q[3]);
	math::Matrix3F3 R = q_att.RotationMatrix();

	/* all input data is ready, run controller itself */

	/* try to move thrust vector shortest way, because yaw response is slower than roll/pitch */
	math::Vector3F R_z(R[0][2], R[1][2], R[2][2]);
	math::Vector3F R_sp_z(R_sp[0][2], R_sp[1][2], R_sp[2][2]);

	/* axis and sin(angle) of desired rotation */
	math::Vector3F e_R = R.Transpose() * (R_z % R_sp_z);

	/* calculate angle error */
	float e_R_z_sin = e_R.length();
	float e_R_z_cos = R_z * R_sp_z;

	/* calculate weight for yaw control */
	float yaw_w = R_sp[2][2] * R_sp[2][2];

	/* calculate rotation matrix after roll/pitch only rotation */
	math::Matrix3F3 R_rp;

	if (e_R_z_sin > 0.0f) {
		/* get axis-angle representation */
		float e_R_z_angle = atan2f(e_R_z_sin, e_R_z_cos);
		math::Vector3F e_R_z_axis = e_R / e_R_z_sin;

		e_R = e_R_z_axis * e_R_z_angle;

		/* cross product matrix for e_R_axis */
		math::Matrix3F3 e_R_cp;
		e_R_cp.Zero();
		e_R_cp[0][1] = -e_R_z_axis[2];
		e_R_cp[0][2] = e_R_z_axis[1];
		e_R_cp[1][0] = e_R_z_axis[2];
		e_R_cp[1][2] = -e_R_z_axis[0];
		e_R_cp[2][0] = -e_R_z_axis[1];
		e_R_cp[2][1] = e_R_z_axis[0];

		/* rotation matrix for roll/pitch only rotation */
		R_rp = R * (math::Matrix3F3::Identity() + e_R_cp * e_R_z_sin + e_R_cp * e_R_cp * (1.0f - e_R_z_cos));

	} else {
		/* zero roll/pitch rotation */
		R_rp = R;
	}

	/* R_rp and R_sp has the same Z axis, calculate yaw error */
	math::Vector3F R_sp_x(R_sp[0][0], R_sp[1][0], R_sp[2][0]);
	math::Vector3F R_rp_x(R_rp[0][0], R_rp[1][0], R_rp[2][0]);
	e_R[2] = atan2f((R_rp_x % R_sp_x) * R_sp_z, R_rp_x * R_sp_x) * yaw_w;

	if (e_R_z_cos < 0.0f) {
		/* for large thrust vector rotations use another rotation method:
		 * calculate angle and axis for R -> R_sp rotation directly */
		math::Quaternion q_error(R.Transpose() * R_sp);
		math::Vector3F e_R_d = q_error[0] >= 0.0f ? q_error.Imaginary()  * 2.0f : -q_error.Imaginary() * 2.0f;

		/* use fusion of Z axis based rotation and direct rotation */
		float direct_w = e_R_z_cos * e_R_z_cos * yaw_w;
		e_R = e_R * (1.0f - direct_w) + e_R_d * direct_w;
	}

	/* calculate angular rates setpoint */
//	_rates_sp = _params.att_p.emult(e_R);

	/* limit rates */
//	for (int i = 0; i < 3; i++) {
//		if ((_v_control_mode.flag_control_velocity_enabled || _v_control_mode.flag_control_auto_enabled) &&
//		    !_v_control_mode.flag_control_manual_enabled) {
//			_rates_sp(i) = math::constrain(_rates_sp(i), -_params.auto_rate_max(i), _params.auto_rate_max(i));
//
//		} else {
//			_rates_sp(i) = math::constrain(_rates_sp(i), -_params.mc_rate_max(i), _params.mc_rate_max(i));
//		}
//	}
//
	/* feed forward yaw setpoint rate */
//	_rates_sp(2) += _v_att_sp.yaw_sp_move_rate * yaw_w * _params.yaw_ff;
//
//	/* weather-vane mode, dampen yaw rate */
//	if ((_v_control_mode.flag_control_velocity_enabled || _v_control_mode.flag_control_auto_enabled) &&
//	    _v_att_sp.disable_mc_yaw_control == true && !_v_control_mode.flag_control_manual_enabled) {
//		float wv_yaw_rate_max = _params.auto_rate_max(2) * _params.vtol_wv_yaw_rate_scale;
//		_rates_sp(2) = math::constrain(_rates_sp(2), -wv_yaw_rate_max, wv_yaw_rate_max);
//		// prevent integrator winding up in weathervane mode
//		_rates_int(2) = 0.0f;
//	}
}


void MAC::ControlAttitudeRates(float dt)
{
}

#ifdef __cplusplus
}
#endif

/************************/
/*  End of File Comment */
/************************/
