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

#include "vm_Arming.h"
#include "vm_events.h"
#include "vm_app.h"
#include <math.h>

#include "px4lib.h"
#include "px4lib_msgids.h"

VM_Arming::VM_Arming(VM &inApp) :
        FSM(*this), App(inApp) {

}

VM_Arming::~VM_Arming() {

}

uint32 VM_Arming::GetCurrentStateID() {
return FSM.getState().getId();
}

void VM_Arming::Init(void) {
App.ActuatorArmedMsg.Timestamp = 0;
App.ActuatorArmedMsg.Armed = false;
App.ActuatorArmedMsg.Prearmed = false;
App.ActuatorArmedMsg.ReadyToArm = false;
App.ActuatorArmedMsg.Lockdown = false;
App.ActuatorArmedMsg.ManualLockdown = false;
App.ActuatorArmedMsg.ForceFailsafe = false;
App.ActuatorArmedMsg.InEscCalibrationMode = false;
App.VehicleStatusMsg.ArmingState = PX4_ARMING_STATE_INIT;

}

void VM_Arming::EnteredStandby() {
App.ActuatorArmedMsg.Armed = false;
App.ActuatorArmedMsg.Prearmed = true;
App.ActuatorArmedMsg.ReadyToArm = true;
App.VehicleStatusMsg.ArmingState = PX4_ARMING_STATE_STANDBY;

CFE_EVS_SendEvent(VM_ARMING_ENTERED_STANDBY_STATE_INFO_EID, CFE_EVS_INFORMATION,
        "Arming::Standby");
}

void VM_Arming::EnteredArmed() {
App.ActuatorArmedMsg.Prearmed = false;
App.ActuatorArmedMsg.ReadyToArm = false;
App.VehicleStatusMsg.ArmingState = PX4_ARMING_STATE_ARMED;
App.ActuatorArmedMsg.Armed = true;
App.VehicleControlModeMsg.Armed = true;
App.SendActuatorArmedMsg();
App.SetHomePosition();
App.SendVehicleStatusMsg();

CFE_EVS_SendEvent(VM_ARMING_ENTERED_ARMED_STATE_INFO_EID, CFE_EVS_INFORMATION,
        "Arming::Armed");
}

void VM_Arming::ExitedArmed() {
App.ActuatorArmedMsg.Armed = false;
App.VehicleControlModeMsg.Armed = false;
App.SendActuatorArmedMsg();
}

void VM_Arming::EnteredStandbyError() {
App.VehicleStatusMsg.ArmingState = PX4_ARMING_STATE_STANDBY_ERROR;
App.SendActuatorArmedMsg();

CFE_EVS_SendEvent(VM_ARMING_ENTERED_STANDBY_ERROR_STATE_INFO_EID,
CFE_EVS_INFORMATION, "Arming::StandbyError");
}

void VM_Arming::EnteredArmedError() {
App.VehicleStatusMsg.ArmingState = PX4_ARMING_STATE_ARMED_ERROR;
App.SendActuatorArmedMsg();

CFE_EVS_SendEvent(VM_ARMING_ENTERED_ARMED_ERROR_STATE_INFO_EID,
CFE_EVS_INFORMATION, "Arming::ArmedError");
}

void VM_Arming::DoAction() {
if (strcmp(FSM.getState().getName(),"VM_ArmingMap::Init") == 0) {
    /* Keep sending this message */
    App.SendActuatorArmedMsg();
} else if (strcmp(FSM.getState().getName(),"VM_ArmingMap::Standby") == 0) {
    /* Keep sending this message */
    App.SendActuatorArmedMsg();

} else if (strcmp(FSM.getState().getName(),"VM_ArmingMap::Armed") == 0) {
    /* TODO */

} else if (strcmp(FSM.getState().getName(),"VM_ArmingMap::StandbyError") == 0) {
    /* TODO */
} else {
CFE_EVS_SendEvent(VM_IN_UNKNOWN_STATE_ERR_EID, CFE_EVS_ERROR,
        "VM_ArmingMap is in unknown state (%u, '%s')", FSM.getState().getId(), FSM.getState().getName());
}

}

osalbool VM_Arming::PreFlightCheckCleared() {
osalbool battery_ok = true;
osalbool safety_off = true;
osalbool sensors_ok = true;


/* Warn about global position */
if (App.VehicleGlobalPositionMsg.Timestamp == 0) {
    (void) CFE_EVS_SendEvent(VM_NOPE_ERR_EID, CFE_EVS_ERROR,
                            "WARN! - Position estimator not initialized");
}


/* Battery warning check */
if (App.BatteryStatusMsg.Warning
    >= PX4_BatteryWarningSeverity_t::PX4_BATTERY_WARNING_LOW) {
CFE_EVS_SendEvent(VM_PRE_ARM_BAT_CHECK_INFO_EID, CFE_EVS_ERROR,
        "Low battery, cannot arm");
battery_ok = false;
}

/* Safety check */
if (App.SafetyMsg.SafetySwitchAvailable && !App.SafetyMsg.SafetyOff) {
CFE_EVS_SendEvent(VM_PRE_ARM_SAFETY_CHECK_INFO_EID, CFE_EVS_ERROR,
        "Safety is ON, cannot arm");
safety_off = false;
}

/* Sensors check */
if (!App.status_flags.condition_system_sensors_initialized) {
CFE_EVS_SendEvent(VM_PRE_ARM_SENSORS_CHECK_INFO_EID, CFE_EVS_ERROR,
        "Sensors not setup correctly");
sensors_ok = false;
}

osalbool flight_ok = (battery_ok && safety_off && sensors_ok);

return flight_ok;
}

