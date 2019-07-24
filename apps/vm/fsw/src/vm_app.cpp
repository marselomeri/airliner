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
 ** Includes
 *************************************************************************/
#include <string.h>
#include <float.h>
#include <math.h>
#include "cfe.h"
#include "vm_app.h"
#include "vm_msg.h"
#include "vm_version.h"
#include "px4lib.h"
#include "px4lib_msgids.h"
#include "prm_ids.h"
#include "cpp_lib.hpp"



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
VM oVM;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
VM::VM() :
        ArmingSM(*this), NavigationSM(*this)
{

}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
VM::~VM()
{

}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 VM::InitEvent()
{
    int32 iStatus = CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS) {
        (void) CFE_ES_WriteToSysLog(
                "VM - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 VM::InitPipe()
{
    int32 iStatus = CFE_SUCCESS;

    CPPLIB_PipeRegistrations_t pipes = {
    	{
    	    VM_SCH_PIPE_NAME,
		    VM_SCH_PIPE_PEND_TIME,
		    {
			    VM_WAKEUP_MID,  1, 0, sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
			    VM_SEND_HK_MID, 1, 0, sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
			    0, 0, 0, 0, 0, 0
    	    },
			0,0
    	},
		{
			{
				VM_DATA_PIPE_NAME,
				{
					PX4_SENSOR_MAG_MID,                1, 0, sizeof(PX4_SensorMagMsg_t),               CPPLIB_TLM_MSGTYPE,
					PX4_SENSOR_GYRO_MID,               1, 0, sizeof(PX4_SensorGyroMsg_t),              CPPLIB_TLM_MSGTYPE,
					PX4_BATTERY_STATUS_MID,            1, 0, sizeof(PX4_BatteryStatusMsg_t),           CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_COMMAND_MID,           1, 0, sizeof(PX4_VehicleCommandMsg_t),          CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_CONTROL_MODE_MID,      1, 0, sizeof(PX4_VehicleControlModeMsg_t),      CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_GLOBAL_POSITION_MID,   1, 0, sizeof(PX4_VehicleGlobalPositionMsg_t),   CPPLIB_TLM_MSGTYPE,
					PX4_TELEMETRY_STATUS_MID,          1, 0, sizeof(PX4_TelemetryStatusMsg_t),         CPPLIB_TLM_MSGTYPE,
					PX4_SUBSYSTEM_INFO_MID,            1, 0, sizeof(PX4_SubsystemInfoMsg_t),           CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_GPS_POSITION_MID,      1, 0, sizeof(PX4_VehicleGpsPositionMsg_t),      CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_ATTITUDE_MID,          1, 0, sizeof(PX4_VehicleAttitudeMsg_t),         CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_LOCAL_POSITION_MID,    1, 0, sizeof(PX4_VehicleLocalPositionMsg_t),    CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_LAND_DETECTED_MID,     1, 0, sizeof(PX4_VehicleLandDetectedMsg_t),     CPPLIB_TLM_MSGTYPE,
					PX4_MISSION_RESULT_MID,            1, 0, sizeof(PX4_MissionResultMsg_t),           CPPLIB_TLM_MSGTYPE,
					PX4_MANUAL_CONTROL_SETPOINT_MID,   1, 0, sizeof(PX4_ManualControlSetpointMsg_t),   CPPLIB_TLM_MSGTYPE,
					PX4_POSITION_SETPOINT_TRIPLET_MID, 1, 0, sizeof(PX4_PositionSetpointTripletMsg_t), CPPLIB_TLM_MSGTYPE,
					PX4_SENSOR_ACCEL_MID,              1, 0, sizeof(PX4_SensorAccelMsg_t),             CPPLIB_TLM_MSGTYPE,
					PX4_SAFETY_MID,                    1, 0, sizeof(PX4_SafetyMsg_t),                  CPPLIB_TLM_MSGTYPE,
					PX4_SENSOR_CORRECTION_MID,         1, 0, sizeof(PX4_SensorCorrectionMsg_t),        CPPLIB_TLM_MSGTYPE,
					PX4_VEHICLE_STATUS_MID,            1, 0, sizeof(PX4_VehicleStatusMsg_t),           CPPLIB_TLM_MSGTYPE,
					PX4_SENSOR_COMBINED_MID,           1, 0, sizeof(PX4_SensorCombinedMsg_t),          CPPLIB_TLM_MSGTYPE,
					0, 0, 0, 0, 0, 0
				}
			},
			{
				VM_CMD_PIPE_NAME,
				{
					VM_CMD_MID, 15, VM_NOOP_CC,                 sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_RESET_CC,                sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_VEHICLE_ARM_CC,          sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_VEHICLE_DISARM_CC,       sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_MANUAL_CC,       sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_ALTCTL_CC,       sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_POSCTL_CC,       sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_AUTO_LOITER_CC,  sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_AUTO_RTL_CC,     sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_ACRO_CC,         sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_STABILIZE_CC,    sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_RATTITUDE_CC,    sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_AUTO_TAKEOFF_CC, sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SET_NAV_AUTO_LAND_CC,    sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					VM_CMD_MID, 1, VM_SEND_CONFIGURATION_CC,   sizeof(VM_NoArgCmd_t), CPPLIB_CMD_MSGTYPE,
					0, 0, 0, 0, 0, 0
				}
			}
		}
    };

    iStatus = CPPApp::InitPipes(pipes);

    return iStatus;
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void VM::InitData()
{
    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm, VM_HK_TLM_MID, sizeof(HkTlm), TRUE);

    /* Init configuration message. */
    CFE_SB_InitMsg(&ConfigTlm, VM_CONFIG_TLM_MID, sizeof(ConfigTlm), TRUE);

    /* Init output messages */
    CFE_SB_InitMsg(&ActuatorArmedMsg, PX4_ACTUATOR_ARMED_MID,
            sizeof(PX4_ActuatorArmedMsg_t), TRUE);

    CFE_SB_InitMsg(&HomePositionMsg, PX4_HOME_POSITION_MID,
            sizeof(PX4_HomePositionMsg_t), TRUE);

    CFE_SB_InitMsg(&VehicleManagerStateMsg, PX4_COMMANDER_STATE_MID,
            sizeof(PX4_CommanderStateMsg_t), TRUE);

    CFE_SB_InitMsg(&MissionMsg, PX4_MISSION_MID, sizeof(PX4_MissionMsg_t), TRUE);

    CFE_SB_InitMsg(&LedControlMsg, PX4_LED_CONTROL_MID,
            sizeof(PX4_LedControlMsg_t), TRUE);

    CFE_SB_InitMsg(&VehicleStatusMsg, PX4_VEHICLE_STATUS_MID,
            sizeof(PX4_VehicleStatusMsg_t), TRUE);

    CFE_SB_InitMsg(&VehicleControlModeMsg, PX4_VEHICLE_CONTROL_MODE_MID,
            sizeof(PX4_VehicleControlModeMsg_t), TRUE);

    CFE_SB_InitMsg(&VehicleCommandMsg, PX4_VEHICLE_COMMAND_MID,
            sizeof(PX4_VehicleCommandMsg_t), TRUE);

}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* VM initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 VM::InitApp()
{
    int32 iStatus = CFE_SUCCESS;
    int8 hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("VM - Failed to init events (0x%08lX)\n",
                iStatus);
        goto VM_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto VM_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto VM_InitApp_Exit_Tag;
    }

    /* Initialize the application to use named parameters. */
    iStatus = InitParams();
    if (iStatus != CFE_SUCCESS)
    {
        goto VM_InitApp_Exit_Tag;
    }

    /* Initialize the caution and warning helper */
    m_caws.InitCAWS();

    VM_InitApp_Exit_Tag: if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(VM_INIT_INF_EID, CFE_EVS_INFORMATION,
                "Initialized.  Version %d.%d.%d.%d",
                VM_MAJOR_VERSION,
                VM_MINOR_VERSION,
                VM_REVISION,
                VM_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog(
                    "VM - Application failed to initialize\n");
        }
    }

    return iStatus;
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send VM Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void VM::ReportHousekeeping()
{
    HkTlm.ArmingState = ArmingSM.GetCurrentStateID();
    HkTlm.NavState = NavigationSM.GetCurrentStateID();

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &HkTlm);
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void VM::SendActuatorArmedMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &ActuatorArmedMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &ActuatorArmedMsg);
}



void VM::SendHomePositionMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &HomePositionMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &HomePositionMsg);
}



void VM::SendVehicleManagerStateMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &VehicleManagerStateMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &VehicleManagerStateMsg);
}



void VM::SendMissionMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &MissionMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &MissionMsg);
}



void VM::SendLedControlMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &LedControlMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &LedControlMsg);
}



void VM::SendVehicleStatusMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &VehicleStatusMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &VehicleStatusMsg);
}



void VM::SendVehicleControlModeMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &VehicleControlModeMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &VehicleControlModeMsg);

}



void VM::SendVehicleCommandMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &VehicleCommandMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &VehicleCommandMsg);
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* VM Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void VM_AppMain()
{
    oVM.AppMain();
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* VM Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void VM::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog(
                "VM - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(VM_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(VM_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(VM_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(VM_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Initialize state machine */

    ArmingSM.FSM.InitComplete();
    NavigationSM.FSM.trInitComplete();

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        CFE_SB_Msg_t* MsgPtr = NULL;
        CFE_SB_MsgId_t MsgId;

        iStatus = CPPApp::PendOnPendPipe(MsgId, MsgPtr);
        if(iStatus == CFE_SUCCESS)
        {
            switch (MsgId)
            {
				case VM_WAKEUP_MID:
				{
					CPPApp::ProcessPollPipes();

					/* Update status in caution and warning */
					m_caws.SetStatus(&VehicleStatusMsg);

					/* Initialize home position and local variables */
					if (NotInitialized)
					{
						Initialization();
						SetHomePosition();
						NotInitialized = false;
					}

					/* Cyclic maintainance loop */
					Execute();

					/* Get a common timestamp. */
					uint64 timestamp;
					timestamp = PX4LIB_GetPX4TimeUs();
					ActuatorArmedMsg.Timestamp = timestamp;
					VehicleStatusMsg.Timestamp = timestamp;
					VehicleManagerStateMsg.Timestamp = timestamp;
					VehicleControlModeMsg.Timestamp = timestamp;

					/* Execute all stateful behavior. */
					ArmingSM.DoAction();
					NavigationSM.DoAction();

					/* Publish the messages. */
					SendVehicleManagerStateMsg();
					SendVehicleControlModeMsg();
					break;
				}

				case VM_SEND_HK_MID:
				{
					CheckParams();
					ReportHousekeeping();
					break;
				}

				default:
				{
					break;
				}
            }
        }

        iStatus = AcquireConfigPointers();
        if (iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(VM_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}



osalbool VM::IsVehicleArmed()
{
    return ActuatorArmedMsg.Armed;
}



uint64 VM::TimeElapsed(uint64 *TimePtr)
{
    uint64 now = PX4LIB_GetPX4TimeUs();
    uint64 delta = now - *TimePtr;
    return delta;
}



uint64 VM::TimeNow()
{
    uint64 now = PX4LIB_GetPX4TimeUs();
    return now;
}



void VM::SetHomePosition()
{
    if (!(VehicleGlobalPositionMsg.EpH > ConfigTblPtr->COM_HOME_H_T
            || VehicleGlobalPositionMsg.EpV > ConfigTblPtr->COM_HOME_V_T))
    {
        /* Set the HomePosition message */
        float DistBottom = 0;

        /* Distance from ground should always be positive */
        if (VehicleLocalPositionMsg.DistBottom > 0)
        {
            DistBottom = VehicleLocalPositionMsg.DistBottom;
        }

        HomePositionMsg.Timestamp = TimeNow();
        HomePositionMsg.Lat = VehicleGlobalPositionMsg.Lat;
        HomePositionMsg.Lon = VehicleGlobalPositionMsg.Lon;
        HomePositionMsg.Alt = VehicleGlobalPositionMsg.Alt - DistBottom - ConfigTblPtr->HOME_POS_ALT_PADDING ;
        HomePositionMsg.X = VehicleLocalPositionMsg.X;
        HomePositionMsg.Y = VehicleLocalPositionMsg.Y;
        HomePositionMsg.Z = VehicleLocalPositionMsg.Z;

        math::Quaternion q(VehicleAttitudeMsg.Q[0], VehicleAttitudeMsg.Q[1],
                VehicleAttitudeMsg.Q[2], VehicleAttitudeMsg.Q[3]);

        math::Matrix3F3 rotationMat = math::Dcm(q);
        math::Vector3F euler = math::Euler(rotationMat);
        HomePositionMsg.Yaw = euler[2];

        (void) CFE_EVS_SendEvent(VM_HOMESET_INFO_EID, CFE_EVS_INFORMATION,
                "Home Position set. [Lat -> %.6f | Lon -> %.6f | Alt ->%.6f]",
                HomePositionMsg.Lat, HomePositionMsg.Lon, HomePositionMsg.Alt);

        SendHomePositionMsg();
    }
    else
    {
        (void) CFE_EVS_SendEvent(VM_HOMESET_INFO_EID, CFE_EVS_INFORMATION,
                "Home position cannot be set.");
    }
}



void VM::Initialization()
{
    /* Initialize status flags */
    status_flags.condition_system_sensors_initialized = true;

    /* Always accept RC input as default */
    status_flags.rc_input_blocked = false;
    status_flags.rc_signal_found_once = false;

    status_flags.usb_connected = false;

    /* Vehicle status defaults */
    VehicleStatusMsg.OnboardControlSensorsPresent = 0;
    VehicleStatusMsg.OnboardControlSensorsEnabled = 0;
    VehicleStatusMsg.OnboardControlSensorsHealth = 0;

    if (ConfigTblPtr->COM_RC_IN_MODE == 2)
    {
        VehicleStatusMsg.RcInputMode = PX4_RcInMode_t::PX4_RC_IN_MODE_GENERATED;
    }

    VehicleStatusMsg.HilState = PX4_HIL_STATE_OFF;
    VehicleStatusMsg.Failsafe = false;
    VehicleStatusMsg.SystemType = PX4_SYSTEM_TYPE_HEXAROTOR;
    VehicleStatusMsg.IsRotaryWing = true;
    VehicleStatusMsg.IsVtol = false;
    VehicleStatusMsg.VtolFwPermanentStab = false;
    VehicleStatusMsg.InTransitionMode = false;
    VehicleStatusMsg.RcSignalLost = true;
    VehicleStatusMsg.RcInputMode = PX4_RC_IN_MODE_GENERATED;
    VehicleStatusMsg.DataLinkLost = true;
    VehicleStatusMsg.DataLinkLostCounter = 0;
    VehicleStatusMsg.EngineFailure = false;
    VehicleStatusMsg.EngineFailureCmd = false;
    VehicleStatusMsg.MissionFailure = false;

    /* Onboard mission not supported, set default mission and publish */
    MissionMsg.Timestamp = TimeNow();
    MissionMsg.DatamanID = 0;
    MissionMsg.Count = 0;
    MissionMsg.CurrentSeq = 0;
    SendMissionMsg();

    /* Safety defaults */
    SafetyMsg.SafetySwitchAvailable = false;
    SafetyMsg.SafetyOff = false;

    // user adjustable duration required to assert arm/disarm via throttle/rudder stick
    ConfigTblPtr->COM_RC_ARM_HYST *= COMMANDER_MONITORING_LOOPSPERMSEC;

    VmBootTimestamp = TimeNow();

    /* update parameters */
    if (!ActuatorArmedMsg.Armed)
    {
        VehicleStatusMsg.IsRotaryWing = true;
        VehicleStatusMsg.IsVtol = false;
        VehicleStatusMsg.SystemID = ConfigTblPtr->MAV_SYS_ID;
        VehicleStatusMsg.ComponentID = ConfigTblPtr->MAV_COMP_ID;
    }

}



void VM::Execute()
{
    /* Set home position at launch */
    if (VehicleLandDetectedMsg.Landed && !VehicleLandDetectedMsg.Freefall
            && !VehicleLandDetectedMsg.GroundContact)
    {
        /* Vehicle has landed */
        if (!vh_prev_landed)
        {
            /* Rest arm and nav states */
            FlightSessionInit();
            /* Forget previous modes */
            previous_modes = {0};
        }
        vh_prev_landed = true;
        vh_prev_in_flight = false;
    }
    else if(!VehicleLandDetectedMsg.Landed && !VehicleLandDetectedMsg.Freefall && !VehicleLandDetectedMsg.GroundContact && vh_prev_landed && !vh_prev_in_flight )
    {
        /* Vehicle is launched */
        SetHomePosition();
        vh_prev_landed = false;
        vh_prev_in_flight = true;
    }

    /* Vehicle status message handle */
    VehicleStatusMsg.SystemID = ConfigTblPtr->MAV_SYS_ID;
    VehicleStatusMsg.ComponentID = ConfigTblPtr->MAV_COMP_ID;

    /* Safety message handle */
    osalbool previous_safety_off = SafetyMsg.SafetyOff;
    if(SafetyMsg.SafetySwitchAvailable && !SafetyMsg.SafetyOff && ActuatorArmedMsg.Armed && VehicleStatusMsg.ArmingState == PX4_ArmingState_t::PX4_ARMING_STATE_ARMED)
    {
        try
        {
            (void) CFE_EVS_SendEvent(VM_SAFETY_DISARM_INFO_EID, CFE_EVS_INFORMATION,
                    "Vehicle [DISARM] by safety message");
            ArmingSM.FSM.Disarm();
            HkTlm.usCmdCnt++;
            arming_state_changed = true;

        }
        catch(statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            CFE_EVS_SendEvent(VM_ARMING_ILLEGAL_TRANSITION_ERR_EID, CFE_EVS_INFORMATION,
                    "Illegal Arming transition. [%s] Command rejected.","DISARM");
        }

    }

    /* Notify the user if the status of the safety switch changes*/
    if (SafetyMsg.SafetySwitchAvailable && previous_safety_off != SafetyMsg.SafetyOff)
    {
        if (SafetyMsg.SafetyOff)
        {
            (void) CFE_EVS_SendEvent(VM_SAFETY_INFO_EID, CFE_EVS_INFORMATION,
                    "Safety OFF");
        }
        else
        {
            (void) CFE_EVS_SendEvent(VM_SAFETY_INFO_EID, CFE_EVS_INFORMATION,
                    "Safety ON");
        }
    }

    /* Battery status handle */
    /* Only consider battery voltage if system has been running 6s (usb most likely detected) and battery voltage is valid */
    if((TimeNow() > VmBootTimestamp + VM_BATTERY_VOLTAGE_CHECK_DELAY) && (BatteryStatusMsg.VoltageFiltered > (VM_MINIMUM_VALID_BATTERY_VOLTAGE * FLT_EPSILON)))
    {
        /* If battery voltage is getting lower, warn using buzzer, etc. */
        if(BatteryStatusMsg.Warning == PX4_BATTERY_WARNING_LOW && !low_battery_voltage_actions_done)
        {
            low_battery_voltage_actions_done = true;

            if (ActuatorArmedMsg.Armed)
            {
                (void) CFE_EVS_SendEvent(VM_LOW_BAT_INFO_EID, CFE_EVS_INFORMATION,
                        "Low battery, return to land");
            }
            else
            {
                (void) CFE_EVS_SendEvent(VM_LOW_BAT_INFO_EID, CFE_EVS_INFORMATION,
                        "Low battery, takeoff discouraged");
            }
        }
        else if (!status_flags.usb_connected && BatteryStatusMsg.Warning == PX4_BATTERY_WARNING_CRITICAL && !critical_battery_voltage_actions_done)
        {
            critical_battery_voltage_actions_done = true;

            if (!ActuatorArmedMsg.Armed)
            {
                (void) CFE_EVS_SendEvent(VM_CRITICAL_BAT_INFO_EID, CFE_EVS_INFORMATION,
                        "Critical battery, shutdown system");
            }
            else
            {
                if(
                		ConfigTblPtr->COM_LOW_BAT_ACT == VM_BATTERY_FAILSAFE_MODE_RETURN ||
                		ConfigTblPtr->COM_LOW_BAT_ACT == VM_BATTERY_FAILSAFE_MODE_RETURN_IF_CRIT_LOW_LAND_IF_DANGER_LOW)
                {
                    try
                    {
                        (void) CFE_EVS_SendEvent(VM_CRITICAL_BAT_INFO_EID, CFE_EVS_INFORMATION,
                                "Critical battery, return to launch");
                        NavigationSM.FSM.trAutoReturnToLaunch();
                        HkTlm.usCmdCnt++;
                    }
                    catch(statemap::TransitionUndefinedException e)
                    {
                        HkTlm.usCmdErrCnt++;
                        CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID, CFE_EVS_INFORMATION,
                                "Illegal Nav transition.  Command rejected.");
                    }
                }
                else if(ConfigTblPtr->COM_LOW_BAT_ACT == VM_BATTERY_FAILSAFE_MODE_LAND)
                {
                    try
                    {
                        (void) CFE_EVS_SendEvent(VM_CRITICAL_BAT_INFO_EID, CFE_EVS_INFORMATION,
                                "Critical battery, landing at current position");
                        NavigationSM.FSM.trAutoLand();
                        HkTlm.usCmdCnt++;
                    }
                    catch(statemap::TransitionUndefinedException e)
                    {
                        HkTlm.usCmdErrCnt++;
                        uint32 PrevState = NavigationSM.GetCurrentStateID();
                        CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
                        CFE_EVS_INFORMATION,
                                "Illegal Nav transition [%s -> %s].  Command rejected.",
                                GetNavStateAsString(PrevState), "AUTOLND");
                    }

                }
                else
                {
                    (void) CFE_EVS_SendEvent(VM_CRITICAL_BAT_INFO_EID, CFE_EVS_INFORMATION,
                            "Critical battery, return to launch advised");
                }
            }
        }
        else if(!status_flags.usb_connected && BatteryStatusMsg.Warning == PX4_BATTERY_WARNING_EMERGENCY && !emergency_battery_voltage_actions_done)
        {
            emergency_battery_voltage_actions_done = true;

            if (!ActuatorArmedMsg.Armed)
            {
                (void) CFE_EVS_SendEvent(VM_DANGER_BAT_LEVEL_INFO_EID, CFE_EVS_INFORMATION,
                        "Dangerously low battery, shutdown system");
            }
            else
            {
                if(
                		ConfigTblPtr->COM_LOW_BAT_ACT == VM_BATTERY_FAILSAFE_MODE_LAND ||
						ConfigTblPtr->COM_LOW_BAT_ACT == VM_BATTERY_FAILSAFE_MODE_RETURN_IF_CRIT_LOW_LAND_IF_DANGER_LOW)
                {
                    try
                    {
                        (void) CFE_EVS_SendEvent(VM_DANGER_BAT_LEVEL_INFO_EID, CFE_EVS_INFORMATION,
                                "Dangerously low battery, landing immediately");
                        NavigationSM.FSM.trAutoLand();
                        HkTlm.usCmdCnt++;
                    }
                    catch(statemap::TransitionUndefinedException e)
                    {
                        HkTlm.usCmdErrCnt++;
                        uint32 PrevState = NavigationSM.GetCurrentStateID();
                        CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
                        CFE_EVS_INFORMATION,
                                "Illegal Nav transition [%s -> %s].  Command rejected.",
                                GetNavStateAsString(PrevState), "AUTOLND");
                    }

                }
                else
                {
                    (void) CFE_EVS_SendEvent(VM_DANGER_BAT_LEVEL_INFO_EID, CFE_EVS_INFORMATION,
                            "Dangerously low battery, landing advised");
                }
            }
        }
    }

    /* Subsystem message handle */
    if(SubsystemInfoMsg.Present)
    {
        VehicleStatusMsg.OnboardControlSensorsPresent |= SubsystemInfoMsg.SubsystemType;
    }
    else
    {
        VehicleStatusMsg.OnboardControlSensorsPresent &= ~SubsystemInfoMsg.SubsystemType;
    }

    if(SubsystemInfoMsg.Enabled)
    {
        VehicleStatusMsg.OnboardControlSensorsEnabled |= SubsystemInfoMsg.SubsystemType;
    }
    else
    {
        VehicleStatusMsg.OnboardControlSensorsEnabled &= ~SubsystemInfoMsg.SubsystemType;
    }

    if(SubsystemInfoMsg.Ok)
    {
        VehicleStatusMsg.OnboardControlSensorsHealth |= SubsystemInfoMsg.SubsystemType;
    }
    else
    {
        VehicleStatusMsg.OnboardControlSensorsHealth &= ~SubsystemInfoMsg.SubsystemType;
    }

    /* RC input handle */
    if(!status_flags.rc_input_blocked && ManualControlSetpointMsg.Timestamp!=0 && (TimeNow() < ManualControlSetpointMsg.Timestamp + uint64(ConfigTblPtr->COM_RC_LOSS_T * 1e6f)))
    {
        if(!status_flags.rc_signal_found_once)
        {
            status_flags.rc_signal_found_once = true;
        }
        else
        {
            if(VehicleStatusMsg.RcSignalLost)
            {
                uint64 Now = TimeNow();
                (void) CFE_EVS_SendEvent(VM_RC_SIGN_REGAINED_INFO_EID, CFE_EVS_INFORMATION,
                        "Manual control regained after (%llu)ums",(Now - rc_signal_lost_timestamp));
            }
        }

        VehicleStatusMsg.RcSignalLost = false;
        const osalbool in_armed_state = (VehicleStatusMsg.ArmingState == PX4_ARMING_STATE_ARMED || VehicleStatusMsg.ArmingState == PX4_ARMING_STATE_ARMED_ERROR);
        const osalbool arm_button_pressed = (ConfigTblPtr->COM_ARM_SWISBTN == 1 && ManualControlSetpointMsg.ArmSwitch == PX4_SWITCH_POS_ON);

        /* DISARM */
        const osalbool stick_in_lower_left = false; //((ManualControlSetpointMsg.R < -STICK_ON_OFF_LIMIT) && (ManualControlSetpointMsg.Z <0.1f));
        const osalbool arm_switch_to_disarm_transition = ((ConfigTblPtr->COM_ARM_SWISBTN == 0) && (last_sp_man_arm_switch ==PX4_SWITCH_POS_ON) && (ManualControlSetpointMsg.ArmSwitch == PX4_SWITCH_POS_OFF) );

        if(in_armed_state && VehicleStatusMsg.RcInputMode != PX4_RC_IN_MODE_OFF && (stick_in_lower_left || arm_button_pressed || arm_switch_to_disarm_transition))
        {
            //current_nav_state = NavigationSM.GetCurrentStateID();//TODO
            if(VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_MANUAL &&
                    VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_ACRO &&
                    VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_STAB &&
                    VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_RATTITUDE &&
                    !VehicleLandDetectedMsg.Landed)
            {
                (void) CFE_EVS_SendEvent(VM_RC_STK_DISARM_REJ_INFO_EID, CFE_EVS_INFORMATION,
                        "Stick disarm rejected, vehicle in flight");
            }
            else if ((stick_off_counter == ConfigTblPtr->COM_RC_ARM_HYST && stick_on_counter < ConfigTblPtr->COM_RC_ARM_HYST) || arm_switch_to_disarm_transition)
            {
                try
                {
                    (void) CFE_EVS_SendEvent(VM_RC_DISARM_INFO_EID, CFE_EVS_INFORMATION,
                            "Disarm engaged by rc");
                    ArmingSM.FSM.Disarm();
                    arming_state_changed = true;
                    HkTlm.usCmdCnt++;
                }
                catch(statemap::TransitionUndefinedException e)
                {
                    HkTlm.usCmdErrCnt++;
                    CFE_EVS_SendEvent(VM_ARMING_ILLEGAL_TRANSITION_ERR_EID, CFE_EVS_INFORMATION,
                            "Illegal Arming transition. [%s] Command rejected.","DISARM");
                }
            }
            stick_off_counter++;
        }
        /* do not reset the counter when holding the arm button longer than needed */
        else if (!(ConfigTblPtr->COM_ARM_SWISBTN ==1 && ManualControlSetpointMsg.ArmSwitch == PX4_SWITCH_POS_ON))
        {
            stick_off_counter = 0;
        }

        /* ARM */
        const osalbool stick_in_lower_right = false; // (ManualControlSetpointMsg.R > STICK_ON_OFF_LIMIT  && ManualControlSetpointMsg.Z <0.1f);
        const osalbool arm_switch_to_arm_transition = ((ConfigTblPtr->COM_ARM_SWISBTN == 0) && (last_sp_man_arm_switch ==PX4_SWITCH_POS_OFF) && (ManualControlSetpointMsg.ArmSwitch == PX4_SWITCH_POS_ON) );

        if(!in_armed_state && VehicleStatusMsg.RcInputMode != PX4_RC_IN_MODE_OFF && (stick_in_lower_right || arm_button_pressed || arm_switch_to_arm_transition)) {
            if((stick_on_counter == ConfigTblPtr->COM_RC_ARM_HYST && stick_off_counter < ConfigTblPtr->COM_RC_ARM_HYST) || arm_switch_to_arm_transition) {
                if((VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_MANUAL) &&
                        (VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_ACRO) &&
                        (VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_STAB) &&
                        (VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_RATTITUDE) &&
                        (VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_POSCTL) &&
                        (VehicleStatusMsg.NavState != PX4_NAVIGATION_STATE_ALTCTL)) {
                    (void) CFE_EVS_SendEvent(VM_RC_STK_ARM_REJ_INFO_EID, CFE_EVS_INFORMATION,
                            "Stick arm rejected, vehicle not in manual mode ");
                }
                else if (VehicleStatusMsg.ArmingState == PX4_ARMING_STATE_STANDBY)
                {
                    try
                    {
                        (void) CFE_EVS_SendEvent(VM_RC_ARM_INFO_EID, CFE_EVS_INFORMATION,
                                "Arm engaged by rc ");
                        ArmingSM.FSM.Arm();
                        HkTlm.usCmdCnt++;
                    }
                    catch(statemap::TransitionUndefinedException e)
                    {
                        HkTlm.usCmdErrCnt++;
                        CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID, CFE_EVS_INFORMATION,
                                "Illegal Nav transition.  Command rejected.");
                    }

                    arming_state_changed = true;
                }
            }
            stick_on_counter++;
        }
        /* do not reset the counter when holding the arm button longer than needed */
        else if (!(ConfigTblPtr->COM_ARM_SWISBTN ==1 && ManualControlSetpointMsg.ArmSwitch == PX4_SWITCH_POS_ON))
        {
            stick_on_counter = 0;
        }

        last_sp_man_arm_switch = ManualControlSetpointMsg.ArmSwitch;

        /* KILLSWITCH */
        if(ManualControlSetpointMsg.KillSwitch == PX4_SWITCH_POS_ON)
        {
            if(!ActuatorArmedMsg.ManualLockdown)
            {
                (void) CFE_EVS_SendEvent(VM_RC_KIL_SWTCH_INFO_EID, CFE_EVS_INFORMATION,
                        "Killswitch engaged ");
                ActuatorArmedMsg.ManualLockdown = true;
                SendActuatorArmedMsg();
            }
        }
        else if(ManualControlSetpointMsg.KillSwitch == PX4_SWITCH_POS_OFF)
        {
            if(ActuatorArmedMsg.ManualLockdown)
            {
                (void) CFE_EVS_SendEvent(VM_RC_KIL_SWTCH_INFO_EID, CFE_EVS_INFORMATION,
                        "killswitch disengaged ");
                ActuatorArmedMsg.ManualLockdown = false;
                SendActuatorArmedMsg();
            }
        }

        /* Mode change routine */
        RcModes();
    }
    else if(!status_flags.rc_input_blocked && !VehicleStatusMsg.RcSignalLost )
    {
        uint64 Now = TimeNow();
        (void) CFE_EVS_SendEvent(VM_RC_SIGN_LOST_INFO_EID, CFE_EVS_INFORMATION,
                "Manual control lost at t = (%llu)ums", (Now));
        try
        {
			if(VehicleStatusMsg.NavState != PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_RTL)
			{
                NavigationSM.FSM.trAutoLoiter();
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(VM_RC_MAN_INFO_EID, CFE_EVS_INFORMATION,
                    "Mode switched to auto loiter autonomously ");
            }
            else
            {
				(void) CFE_EVS_SendEvent(VM_RC_MAN_INFO_EID, CFE_EVS_INFORMATION,
                    "Mode switched will stay in RTL ");
			}
        }
        catch(statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "AUTORTL");
        }

        VehicleStatusMsg.RcSignalLost = true;
        rc_signal_lost_timestamp = ManualControlSetpointMsg.Timestamp;
    }

}

void VM::RcModes()
{
    osalbool posctl =
            (ManualControlSetpointMsg.PosctlSwitch == PX4_SWITCH_POS_ON);
    osalbool altctl =
            (ManualControlSetpointMsg.AltctlSwitch == PX4_SWITCH_POS_ON);
    osalbool rtl = (ManualControlSetpointMsg.ReturnSwitch == PX4_SWITCH_POS_ON);
    osalbool loiter =
            (ManualControlSetpointMsg.LoiterSwitch == PX4_SWITCH_POS_ON);
    osalbool takeoff = (ManualControlSetpointMsg.TransitionSwitch
            == PX4_SWITCH_POS_ON);
    osalbool manual = (!posctl && !rtl && !loiter && !takeoff);
    osalbool mode_changed = !(posctl == previous_modes.inPosCtl
            && rtl == previous_modes.inRtl && loiter == previous_modes.inLoiter
            && manual == previous_modes.inManual
            && takeoff == previous_modes.intakeoff
            && altctl == previous_modes.inAltCtl);

    if (posctl && !altctl && !rtl && !loiter && !takeoff && mode_changed)
    {
        try
        {
            NavigationSM.FSM.trPositionControl();
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(VM_RC_POSCTL_INFO_EID, CFE_EVS_INFORMATION,
                    "Mode switched to position control by rc");
        }
        catch (statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "POSCTL");
        }

    }
    else if (rtl && mode_changed)
    {
        try
        {
            NavigationSM.FSM.trAutoReturnToLaunch();
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(VM_RC_RTL_INFO_EID, CFE_EVS_INFORMATION,
                    "Mode switched to auto rtl by rc ");
        }
        catch (statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "AUTORTL");
        }

    }
    else if (!posctl && !altctl && !rtl && loiter && !takeoff && mode_changed)
    {
        try
        {
            NavigationSM.FSM.trAutoLoiter();
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(VM_RC_LTR_INFO_EID, CFE_EVS_INFORMATION,
                    "Mode switched to auto loiter by rc");
        }
        catch (statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "AUTOLTR");
        }
    }
    else if (takeoff && mode_changed)
    {
        try
        {
            NavigationSM.FSM.trAutoTakeoff();
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(VM_RC_TAKE_OFF_INFO_EID,
            CFE_EVS_INFORMATION, "Mode switched to auto takeoff by rc");
        }
        catch (statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "AUTOTAKOF");
        }
    }
    else if (!posctl && altctl && !rtl && !loiter && !takeoff && mode_changed)
    {
        try
        {
            NavigationSM.FSM.trAltitudeControl();
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(VM_RC_TAKE_OFF_INFO_EID,
            CFE_EVS_INFORMATION, "Mode switched to altitude control by rc");
        }
        catch (statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "ALTCTL");
        }
    }
    else if (manual && mode_changed)
    {
        try
        {
            NavigationSM.FSM.trManual();
            HkTlm.usCmdCnt++;
            (void) CFE_EVS_SendEvent(VM_RC_MAN_INFO_EID, CFE_EVS_INFORMATION,
                    "Mode switched to Manual by rc");
        }
        catch (statemap::TransitionUndefinedException e)
        {
            HkTlm.usCmdErrCnt++;
            uint32 PrevState = NavigationSM.GetCurrentStateID();
            CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
            CFE_EVS_INFORMATION,
                    "Illegal Nav transition [%s -> %s].  Command rejected.",
                    GetNavStateAsString(PrevState), "MANUAL");
        }
    }

    previous_modes.inPosCtl = posctl;
    previous_modes.inAltCtl = altctl;
    previous_modes.inRtl = rtl;
    previous_modes.inLoiter = loiter;
    previous_modes.inManual = manual;
    previous_modes.intakeoff = takeoff;
}



void VM::FlightSessionInit()
{
    (void) CFE_EVS_SendEvent(VM_LND_INIT_INFO_EID, CFE_EVS_INFORMATION,
            "Flight states reset. [Navigation -> MANUAL | Arming -> STANDBY]");

    /* Push states to init */
    ArmingSM.FSM.Reset();
    NavigationSM.FSM.Reset();

    /* Transition from init to default state */
    ArmingSM.FSM.InitComplete();
    NavigationSM.FSM.trInitComplete();
}



const char* VM::GetNavStateAsString(uint32 id)
{
    const char * State_ptr;

    switch (id)
    {
		case 0:
		{
			State_ptr = "MANUAL";
			break;
		}

		case 1:
		{
			State_ptr = "ALTCTL";
			break;
		}

		case 2:
		{
			State_ptr = "POSCTL";
			break;
		}

		case 3:
		{
			State_ptr = "AUTORTL";
			break;
		}

		case 4:
		{
			State_ptr = "AUTOLTR";
			break;
		}

		case 5:
		{
			State_ptr = "ACRO";
			break;
		}

		case 6:
		{
			State_ptr = "STAB";
			break;
		}

		case 7:
		{
			State_ptr = "RATT";
			break;
		}

		case 8:
		{
			State_ptr = "AUTOTAKOF";
			break;
		}

		case 9:
		{
			State_ptr = "AUTOLND";
			break;
		}

		default:
		{
			State_ptr = "UNKNOWN";
			break;
		}
    }

    return State_ptr;
}



void VM::ReportConfiguration()
{
	CFE_PSP_MemCpy(&ConfigTlm.ConfigTbl, ConfigTblPtr, sizeof(ConfigTlm.ConfigTbl));

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*) &ConfigTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*) &ConfigTlm);
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize named parameters.                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 VM::InitParams(void)
{
    int32 iStatus = -1;

    PRMLIB_ParamRegistrations_t ParamRegistrations =
    {
    	VM_PARAM_PIPE_NAME,
		VM_PARAM_PIPE_DEPTH,
        PARAM_ID_COM_RC_IN_MODE,       &ConfigTblPtr->COM_RC_IN_MODE,       TYPE_UINT32,
    	PARAM_ID_COM_ARM_SWISBTN,      &ConfigTblPtr->COM_ARM_SWISBTN,      TYPE_UINT32,
    	PARAM_ID_COM_RC_ARM_HYST,      &ConfigTblPtr->COM_RC_ARM_HYST,      TYPE_UINT32,
    	PARAM_ID_MAV_SYS_ID,           &ConfigTblPtr->MAV_SYS_ID,           TYPE_UINT32,
        PARAM_ID_MAV_COMP_ID,          &ConfigTblPtr->MAV_COMP_ID,          TYPE_UINT32,
    	PARAM_ID_COM_RC_LOSS_T,        &ConfigTblPtr->COM_RC_LOSS_T,        TYPE_REAL32,
        PARAM_ID_COM_LOW_BAT_ACT,      &ConfigTblPtr->COM_LOW_BAT_ACT,      TYPE_UINT32,
        PARAM_ID_COM_HOME_H_T,         &ConfigTblPtr->COM_HOME_H_T,         TYPE_REAL32,
        PARAM_ID_COM_HOME_V_T,         &ConfigTblPtr->COM_HOME_V_T,         TYPE_REAL32,
        PARAM_ID_HOME_POS_ALT_PADDING, &ConfigTblPtr->HOME_POS_ALT_PADDING, TYPE_REAL32,
		""
    };

    iStatus = CPPApp::InitParams(ParamRegistrations);
    if(iStatus != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(VM_PARAM_INIT_ERR_EID, CFE_EVS_ERROR,
                "Failed to initialize named parameters (0x%04X)",
                (unsigned short)iStatus);
    }

    return iStatus;
}



void VM::onParamsChange(PRMLIB_ParamRegistration_t *ParamsData, uint32 ParamsCount)
{
	/* This is called when a named parameter has been modified. */
	CFE_TBL_Modified(ConfigTblHdl);
}



void VM::onReceivedUnexpectedMessageID(const char *ErrorText, CFE_SB_MsgId_t MsgId)
{
	(void) CFE_EVS_SendEvent(VM_MSGID_ERR_EID, CFE_EVS_ERROR, "%s", ErrorText);
}



void VM::onReceivedTelemetryWithIncorrectLength(const char *ErrorText, CFE_SB_MsgId_t MsgId, uint32 Length, uint32 ActualLength)
{
	(void) CFE_EVS_SendEvent(VM_MSGLEN_ERR_EID, CFE_EVS_ERROR, "%s", ErrorText);
}



void VM::onReceivedCommandWithIncorrectLength(const char *ErrorText, CFE_SB_MsgId_t MsgId, uint16 CmdCode, uint32 Length, uint32 ActualLength)
{
	(void) CFE_EVS_SendEvent(VM_MSGLEN_ERR_EID, CFE_EVS_ERROR, "%s", ErrorText);
}



void VM::onReceivedUnexpectedCommand(const char *ErrorText, CFE_SB_MsgId_t MsgId, uint16 CmdCode)
{
	(void) CFE_EVS_SendEvent(VM_CC_ERR_EID, CFE_EVS_ERROR, "%s", ErrorText);
}



void VM::onReceivedCommand(CFE_SB_MsgId_t MsgID, uint16 CmdCode, CFE_SB_MsgPtr_t MsgPtr)
{
	OS_printf("%s %u\n", __FUNCTION__, __LINE__);

    switch (CmdCode)
    {
		case VM_NOOP_CC:
		{
			HkTlm.usCmdCnt++;
			(void) CFE_EVS_SendEvent(VM_CMD_NOOP_EID, CFE_EVS_INFORMATION,
					"Recvd NOOP. Version %d.%d.%d.%d",
					VM_MAJOR_VERSION,
					VM_MINOR_VERSION,
					VM_REVISION,
					VM_MISSION_REV);
			break;
		}

		case VM_RESET_CC:
		{
			HkTlm.usCmdCnt = 0;
			HkTlm.usCmdErrCnt = 0;
			break;
		}

		case VM_VEHICLE_ARM_CC:
		{
			try {
				ArmingSM.FSM.Arm();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				CFE_EVS_SendEvent(VM_ARMING_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Arming transition. [%s] Command rejected.",
						"ARM");
			}
			break;
		}

		case VM_VEHICLE_DISARM_CC:
		{
			try {
				ArmingSM.FSM.Disarm();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				CFE_EVS_SendEvent(VM_ARMING_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Arming transition. [%s] Command rejected.",
						"DISARM");
			}
			break;
		}

		case VM_SET_NAV_MANUAL_CC:
		{
			try {
				NavigationSM.FSM.trManual();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "MANUAL");
			}
			break;
		}

		case VM_SET_NAV_ALTCTL_CC:
		{
			try {
				NavigationSM.FSM.trAltitudeControl();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "ALTCTL");
			}
			break;
		}

		case VM_SET_NAV_POSCTL_CC:
		{
			try {
				NavigationSM.FSM.trPositionControl();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "POSCTL");
			}
			break;
		}

		case VM_SET_NAV_AUTO_LOITER_CC:
		{
			try {
				NavigationSM.FSM.trAutoLoiter();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "AUTORTL");
			}
			break;
		}

		case VM_SET_NAV_AUTO_RTL_CC:
		{
			try {
				NavigationSM.FSM.trAutoReturnToLaunch();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "AUTOLTR");
			}
			break;
		}

		case VM_SET_NAV_ACRO_CC:
		{
			try {
				NavigationSM.FSM.trAcrobatic();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "ACRO");
			}
			break;
		}

		case VM_SET_NAV_STABILIZE_CC:
		{
			try {
				NavigationSM.FSM.trStabilize();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "STAB");
			}
			break;
		}

		case VM_SET_NAV_RATTITUDE_CC:
		{
			try {
				NavigationSM.FSM.trRattitude();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "RATT");
			}
			break;
		}

		case VM_SET_NAV_AUTO_TAKEOFF_CC:
		{
			try {
				NavigationSM.FSM.trAutoTakeoff();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "AUTOTAKOF");
			}
			break;
		}

		case VM_SET_NAV_AUTO_LAND_CC:
		{
			try {
				NavigationSM.FSM.trAutoLand();
				HkTlm.usCmdCnt++;
			} catch (statemap::TransitionUndefinedException e) {
				HkTlm.usCmdErrCnt++;
				uint32 PrevState = NavigationSM.GetCurrentStateID();
				CFE_EVS_SendEvent(VM_NAV_ILLEGAL_TRANSITION_ERR_EID,
				CFE_EVS_INFORMATION,
						"Illegal Nav transition [%s -> %s].  Command rejected.",
						GetNavStateAsString(PrevState), "AUTOLND");
			}
			break;
		}

		case VM_SEND_CONFIGURATION_CC:
		{
			HkTlm.usCmdCnt++;
			ReportConfiguration();
			break;
		}

		default:
		{
			HkTlm.usCmdErrCnt++;
			(void) CFE_EVS_SendEvent(VM_CC_ERR_EID, CFE_EVS_ERROR,
					"Recvd invalid command code (%u)",
					(unsigned int) CmdCode);
			break;
		}
    }
}



void VM::onReceivedTelemetry(CFE_SB_MsgId_t MsgID, CFE_SB_MsgPtr_t MsgPtr)
{
    switch (MsgID)
    {
		case PX4_SENSOR_MAG_MID:
		{
			CFE_PSP_MemCpy(&SensorMagMsg, MsgPtr, sizeof(SensorMagMsg));
			break;
		}

		case PX4_SENSOR_GYRO_MID:
		{
			CFE_PSP_MemCpy(&SensorGyroMsg, MsgPtr, sizeof(SensorGyroMsg));
			break;
		}

		case PX4_BATTERY_STATUS_MID:
		{
			CFE_PSP_MemCpy(&BatteryStatusMsg, MsgPtr, sizeof(BatteryStatusMsg));
			break;
		}

		case PX4_VEHICLE_GLOBAL_POSITION_MID:
		{
			CFE_PSP_MemCpy(&VehicleGlobalPositionMsg, MsgPtr,
					sizeof(VehicleGlobalPositionMsg));
			break;
		}

		case PX4_TELEMETRY_STATUS_MID:
		{
			CFE_PSP_MemCpy(&TelemetryStatusMsg, MsgPtr, sizeof(TelemetryStatusMsg));
			break;
		}

		case PX4_SUBSYSTEM_INFO_MID:
		{
			CFE_PSP_MemCpy(&SubsystemInfoMsg, MsgPtr, sizeof(SubsystemInfoMsg));
			break;
		}

		case PX4_VEHICLE_GPS_POSITION_MID:
		{
			CFE_PSP_MemCpy(&VehicleGpsPositionMsg, MsgPtr,
					sizeof(VehicleGpsPositionMsg));
			break;
		}

		case PX4_VEHICLE_ATTITUDE_MID:
		{
			CFE_PSP_MemCpy(&VehicleAttitudeMsg, MsgPtr, sizeof(VehicleAttitudeMsg));
			break;
		}

		case PX4_VEHICLE_LOCAL_POSITION_MID:
		{
			CFE_PSP_MemCpy(&VehicleLocalPositionMsg, MsgPtr,
					sizeof(VehicleLocalPositionMsg));
			break;
		}

		case PX4_VEHICLE_LAND_DETECTED_MID:
		{
			CFE_PSP_MemCpy(&VehicleLandDetectedMsg, MsgPtr,
					sizeof(VehicleLandDetectedMsg));
			break;
		}

		case PX4_MISSION_RESULT_MID:
		{
			CFE_PSP_MemCpy(&MissionResultMsg, MsgPtr, sizeof(MissionResultMsg));
			break;
		}

		case PX4_MANUAL_CONTROL_SETPOINT_MID:
		{
			CFE_PSP_MemCpy(&ManualControlSetpointMsg, MsgPtr,
					sizeof(ManualControlSetpointMsg));
			break;
		}

		case PX4_POSITION_SETPOINT_TRIPLET_MID:
		{
			CFE_PSP_MemCpy(&PositionSetpointTripletMsg, MsgPtr,
					sizeof(PositionSetpointTripletMsg));
			break;
		}

		case PX4_SENSOR_ACCEL_MID:
		{
			CFE_PSP_MemCpy(&SensorAccelMsg, MsgPtr, sizeof(SensorAccelMsg));
			break;
		}

		case PX4_SAFETY_MID:
		{
			CFE_PSP_MemCpy(&SafetyMsg, MsgPtr, sizeof(SafetyMsg));
			break;
		}

		case PX4_SENSOR_CORRECTION_MID:
		{
			CFE_PSP_MemCpy(&SensorCorrectionMsg, MsgPtr, sizeof(SensorCorrectionMsg));
			break;
		}

		case PX4_VEHICLE_STATUS_MID:
		{
			CFE_PSP_MemCpy(&VehicleStatusMsg, MsgPtr, sizeof(VehicleStatusMsg));
			break;
		}

		case PX4_VEHICLE_CONTROL_MODE_MID:
		{
			CFE_PSP_MemCpy(&VehicleControlModeMsg, MsgPtr,
					sizeof(VehicleControlModeMsg));
			break;
		}

		case PX4_SENSOR_COMBINED_MID:
		{
			CFE_PSP_MemCpy(&SensorCombinedMsg, MsgPtr, sizeof(SensorCombinedMsg));
			break;
		}

		default:
		{
			(void) CFE_EVS_SendEvent(VM_MSGID_ERR_EID, CFE_EVS_ERROR,
					"Recvd invalid SCH msgId (0x%04X)", MsgID);
			break;
		}
    }
}



void VM::onPendPipeTimeout(void)
{
	(void) CFE_EVS_SendEvent(VM_PEND_TIMEOUT_ERR_EID, CFE_EVS_ERROR, "SCH pipe timed out.");
}



/************************/
/*  End of File Comment */
/************************/
