/*==============================================================================
Copyright (c) 2015, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of TlmOut nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _TO_CONFIG_
#define _TO_CONFIG_

#ifdef	__cplusplus
extern "C" {
#endif


/*
** Pragmas
*/

/*
** Include Files
*/
#include "app.h"
#include "tbl.h"
#include "cfe_tbl_filedef.h"
#include "to_platform_cfg.h"
#include "to_mission_cfg.h"
#include "msg_ids.h"

/*
** Local Defines
*/


/*
** Local Structure Declarations
*/

CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "to_ConfigTable", "TO.to_config", "TO config table",
    "to_config.tbl", sizeof(TO_Table_t)
};

/*
** Default TO iLoad table data
*/

#define TO_QUEUE_PILOT			0
#define TO_QUEUE_HIGH			1
#define TO_QUEUE_PX4			2
#define TO_QUEUE_LOW			3
#define TO_QUEUE_EVENTS			4
#define TO_QUEUE_FWD_VIDEO		5
#define TO_QUEUE_CFDP			6

#define TO_QUEUE_PX4_SENSOR_ACCEL						7
#define TO_QUEUE_PX4_SENSOR_GYRO						8
#define TO_QUEUE_PX4_MC_ATT_CTRL_STATUS					9
#define TO_QUEUE_PX4_COMMANDER_STATE					10
#define TO_QUEUE_PX4_BATTERY_STATUS						11
#define TO_QUEUE_PX4_VEHICLE_LOCAL_POSITION				12
#define TO_QUEUE_PX4_ESTIMATOR_STATUS					13
#define TO_QUEUE_PX4_VEHICLE_GLOBAL_POSITION			14
#define TO_QUEUE_PX4_VEHICLE_GLOBAL_VELOCITY_SETPOINT	15
#define TO_QUEUE_PX4_SENSOR_MAG							16
#define TO_QUEUE_PX4_SENSOR_BARO						17
#define TO_QUEUE_PX4_ACTUATOR_ARMED						18
#define TO_QUEUE_PX4_VEHICLE_CONTROL_MODE				19
#define TO_QUEUE_PX4_VEHICLE_GPS_POSITION				20
#define TO_QUEUE_PX4_VEHICLE_STATUS						21
#define TO_QUEUE_PX4_WIND_ESTIMATE						22
#define TO_QUEUE_PX4_VEHICLE_ATTITUDE					23

#define TO_CHANNEL_PILOT		0
#define TO_CHANNEL_TLM			1
#define TO_CHANNEL_CFDP			2
#define TO_CHANNEL_PX4			3

TO_Table_t to_ConfigTable =
{
	TO_MAX_TLM_SUBSCRIPTIONS,
	0x1ffd,
	1000,
    {
    	/* 0 - 9 */
    	{CF_CONFIG_TLM_MID, 									1, TO_QUEUE_HIGH},
		{CF_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
		{CF_SPACE_TO_GND_PDU_MID, 								32, TO_QUEUE_CFDP},
		{CF_TRANS_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{CFE_ES_APP_TLM_MID,    								1, TO_QUEUE_HIGH},
    	{CFE_ES_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{CFE_ES_MEMSTATS_TLM_MID,								1, TO_QUEUE_HIGH},
    	{CFE_ES_SHELL_TLM_MID,  								32,	TO_QUEUE_LOW},
    	{CFE_EVS_EVENT_MSG_MID, 								32, TO_QUEUE_EVENTS},
    	{CFE_EVS_HK_TLM_MID,    								1, TO_QUEUE_HIGH},

    	/* 10 - 19 */
    	{CFE_SB_ALLSUBS_TLM_MID,								32, TO_QUEUE_LOW},
    	{CFE_SB_HK_TLM_MID,     								1, TO_QUEUE_HIGH},
    	{CFE_SB_ONESUB_TLM_MID, 								32, TO_QUEUE_LOW},
    	{CFE_SB_STATS_TLM_MID,  								1, TO_QUEUE_HIGH},
    	{CFE_TBL_HK_TLM_MID,    								1, TO_QUEUE_HIGH},
    	{CFE_TBL_REG_TLM_MID,   								1, TO_QUEUE_HIGH},
    	{CFE_TIME_DIAG_TLM_MID, 								1, TO_QUEUE_HIGH},
    	{CFE_TIME_HK_TLM_MID,   								1, TO_QUEUE_HIGH},
        {TO_HK_TLM_MID,     									1, TO_QUEUE_HIGH},
    	{HS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},

    	/* 20 - 29 */
    	{SCH_DIAG_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{SCH_HK_TLM_MID,         								1, TO_QUEUE_HIGH},
    	{EIM_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{FM_HK_TLM_MID,  										1, TO_QUEUE_HIGH},
    	{FM_OPEN_FILES_TLM_MID, 								1, TO_QUEUE_HIGH},
    	{FM_FREE_SPACE_TLM_MID, 								1, TO_QUEUE_HIGH},
    	{FM_FILE_INFO_TLM_MID, 									1, TO_QUEUE_HIGH},
    	{FM_DIR_LIST_TLM_MID, 									1, TO_QUEUE_HIGH},
    	{CS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{DS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},

    	/* 30 - 49 */
    	{DS_DIAG_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{HK_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT1_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT2_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT3_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT4_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT5_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT6_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT7_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT8_MID, 									1, TO_QUEUE_HIGH},

    	/* 40 - 49 */
    	{HK_COMBINED_PKT9_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT10_MID,									1, TO_QUEUE_HIGH},
    	{LC_HK_TLM_MID,											1, TO_QUEUE_HIGH},
    	{LC_SAMPLE_AP_MID,										1, TO_QUEUE_HIGH},
    	{MD_HK_TLM_MID,											1, TO_QUEUE_HIGH},
    	{MD_DWELL_PKT_MID_BASE,									1, TO_QUEUE_HIGH},
    	{SCH_DIAG_TLM_MID,										1, TO_QUEUE_HIGH},
    	{SCH_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{DS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{DS_DIAG_TLM_MID,										1, TO_QUEUE_HIGH},

    	/* 50 - 59 */
    	{MM_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{SC_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{NAV_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{HS_CUSTOM_HK_TLM_MID,									1, TO_QUEUE_HIGH},
    	{MPU9250_RAW_MEAS_MID, 									1, TO_QUEUE_HIGH},
    	{MPU9250_CAL_MEAS_MID,									1, TO_QUEUE_HIGH},
    	{MPU9250_HK_TLM_MID,									1, TO_QUEUE_HIGH},
    	{MS5611_RAW_MEAS_MID, 									1, TO_QUEUE_HIGH},

    	/* 60 - 69 */
    	{MS5611_CAL_MEAS_MID,									1, TO_QUEUE_HIGH},
    	{MS5611_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{NEOM8N_HK_TLM_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_DIAG_TLM_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_DOP_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_POSECEF_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_POSLLH_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_STATUS_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_ATT_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_SOL_MID, 									1, TO_QUEUE_HIGH},

    	/* 70 - 79 */
    	{NEOM8N_NAV_NAVPVT_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_ODO_MID, 									1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_RESETODO_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_VELECEF_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_VELNED_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_TIMEGPS_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_TIMEUTC_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_CLOCK_MID, 									1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_TIMEGLO_MID, 								1, TO_QUEUE_HIGH},
		{NEOM8N_NAV_TIMEBDS_MID, 								1, TO_QUEUE_HIGH},

    	/* 80 - 89 */
    	{NEOM8N_NAV_TIMEGAL_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_TIMELS_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_SVINFO_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_DGPS_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_SBAS_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_ORB_MID, 									1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_NAVSAT_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_GEOFENCE_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_AOPSTATUS_MID, 								1, TO_QUEUE_HIGH},
    	{NEOM8N_NAV_EOE_MID, 									1, TO_QUEUE_HIGH},

    	/* 90 - 99 */
    	{ETA_HK_TLM_MID, 									    1, TO_QUEUE_HIGH},
		{CI_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
		{PX4_ACTUATOR_ARMED_MID, 								1, TO_QUEUE_PX4_ACTUATOR_ARMED},
		{PX4_ACTUATOR_CONTROLS_MID, 							1, TO_QUEUE_PX4},
		{PX4_ACTUATOR_DIRECT_MID, 								1, TO_QUEUE_PX4},
		{PX4_ACTUATOR_OUTPUTS_MID, 								1, TO_QUEUE_PX4},
		{PX4_ADC_REPORT_MID, 									1, TO_QUEUE_PX4},
		{PX4_AIRSPEED_MID, 										1, TO_QUEUE_PX4},
		{PX4_ATT_POS_MOCAP_MID, 								1, TO_QUEUE_PX4},
		{PX4_BATTERY_STATUS_MID, 								1, TO_QUEUE_PX4_BATTERY_STATUS},

    	/* 100 - 109 */
		{PX4_CAMERA_TRIGGER_MID, 								1, TO_QUEUE_PX4},
		{PX4_COMMANDER_STATE_MID, 								1, TO_QUEUE_PX4_COMMANDER_STATE},
		{PX4_CONTROL_STATE_MID, 								1, TO_QUEUE_PX4},
		{PX4_CPULOAD_MID, 										1, TO_QUEUE_PX4},
		{PX4_DEBUG_KEY_VALUE_MID, 								1, TO_QUEUE_PX4},
		{PX4_DIFFERENTIAL_PRESSURE_MID, 						1, TO_QUEUE_PX4},
		{PX4_DISTANCE_SENSOR_MID, 								1, TO_QUEUE_PX4},
		{PX4_FW_POS_CTRL_STATUS_MID, 							1, TO_QUEUE_PX4},
		{PX4_FW_VIRTUAL_ATTITUDE_SETPOINT_MID, 					1, TO_QUEUE_PX4},
		{PX4_FW_VIRTUAL_RATES_SETPOINT_MID, 					1, TO_QUEUE_PX4},

    	/* 110 - 119 */
		{PX4_EKF2_INNOVATIONS_MID, 								1, TO_QUEUE_PX4},
		{PX4_EKF2_REPLAY_MID, 									1, TO_QUEUE_PX4},
		{PX4_ESC_REPORT_MID, 									1, TO_QUEUE_PX4},
		{PX4_ESC_STATUS_MID, 									1, TO_QUEUE_PX4},
		{PX4_ESTIMATOR_STATUS_MID, 								1, TO_QUEUE_PX4_ESTIMATOR_STATUS},
		{PX4_FENCE_MID, 										1, TO_QUEUE_PX4},
		{PX4_FENCE_VERTEX_MID, 									1, TO_QUEUE_PX4},
		{PX4_FILTERED_BOTTOM_FLOW_MID, 							1, TO_QUEUE_PX4},
		{PX4_FOLLOW_TARGET_MID, 								1, TO_QUEUE_PX4},
		{PX4_GEOFENCE_RESULT_MID, 								1, TO_QUEUE_PX4},

    	/* 120 - 129 */
		{PX4_GPS_DUMP_MID, 										1, TO_QUEUE_PX4},
		{PX4_GPS_INJECT_DATA_MID, 								1, TO_QUEUE_PX4},
		{PX4_HIL_SENSOR_MID, 									1, TO_QUEUE_PX4},
		{PX4_HOME_POSITION_MID, 								1, TO_QUEUE_PX4},
		{PX4_INPUT_RC_MID, 										1, TO_QUEUE_PX4},
		{PX4_LOG_MESSAGE_MID, 									1, TO_QUEUE_PX4},
		{PX4_MANUAL_CONTROL_SETPOINT_MID, 						1, TO_QUEUE_PX4},
		{PX4_MAVLINK_LOG_MID, 									1, TO_QUEUE_PX4},
		{PX4_MC_ATT_CTRL_STATUS_MID, 							1, TO_QUEUE_PX4_MC_ATT_CTRL_STATUS},
		{PX4_MC_VIRTUAL_ATTITUDE_SETPOINT_MID, 					1, TO_QUEUE_PX4},

    	/* 130 - 139 */
		{PX4_MC_VIRTUAL_RATES_SETPOINT_MID, 					1, TO_QUEUE_PX4},
		{PX4_MISSION_MID, 										1, TO_QUEUE_PX4},
		{PX4_MISSION_RESULT_MID, 								1, TO_QUEUE_PX4},
		{PX4_MULTIROTOR_MOTOR_LIMITS_MID, 						1, TO_QUEUE_PX4},
		{PX4_OFFBOARD_CONTROL_MODE_MID, 						1, TO_QUEUE_PX4},
		{PX4_OPTICAL_FLOW_MID, 									1, TO_QUEUE_PX4},
		{PX4_OUTPUT_PWM_MID, 									1, TO_QUEUE_PX4},
		{PX4_PARAMETER_UPDATE_MID, 								1, TO_QUEUE_PX4},
		{PX4_POSITION_SETPOINT_MID, 							1, TO_QUEUE_PX4},
		{PX4_POSITION_SETPOINT_TRIPLET_MID, 					1, TO_QUEUE_PX4},

    	/* 140 - 149 */
		{PX4_PWM_INPUT_MID, 									1, TO_QUEUE_PX4},
		{PX4_QSHELL_REQ_MID, 									1, TO_QUEUE_PX4},
		{PX4_RC_CHANNELS_MID, 									1, TO_QUEUE_PX4},
		{PX4_RC_PARAMETER_MAP_MID, 								1, TO_QUEUE_PX4},
		{PX4_SAFETY_MID, 										1, TO_QUEUE_PX4},
		{PX4_SATELLITE_INFO_MID, 								1, TO_QUEUE_PX4},
		{PX4_SENSOR_ACCEL_MID, 									1, TO_QUEUE_PX4_SENSOR_ACCEL},
		{PX4_SENSOR_BARO_MID, 									1, TO_QUEUE_PX4_SENSOR_BARO},
		{PX4_SENSOR_COMBINED_MID, 								1, TO_QUEUE_PX4},
		{PX4_SENSOR_GYRO_MID, 									1, TO_QUEUE_PX4_SENSOR_GYRO},

    	/* 150 - 159 */
		{PX4_SENSOR_MAG_MID, 									1, TO_QUEUE_PX4_SENSOR_MAG},
		{PX4_SERVORAIL_STATUS_MID, 								1, TO_QUEUE_PX4},
		{PX4_SUBSYSTEM_INFO_MID, 								1, TO_QUEUE_PX4},
		{PX4_SYSTEM_POWER_MID, 									1, TO_QUEUE_PX4},
		{PX4_TECS_STATUS_MID, 									1, TO_QUEUE_PX4},
		{PX4_TELEMETRY_STATUS_MID, 								1, TO_QUEUE_PX4},
		{PX4_TEST_MOTOR_MID, 									1, TO_QUEUE_PX4},
		{PX4_TIME_OFFSET_MID, 									1, TO_QUEUE_PX4},
		{PX4_TRANSPONDER_REPORT_MID, 							1, TO_QUEUE_PX4},
		{PX4_UAVCAN_PARAMETER_REQUEST_MID, 						1, TO_QUEUE_PX4},

    	/* 160 - 169 */
		{PX4_UAVCAN_PARAMETER_VALUE_MID, 						1, TO_QUEUE_PX4},
		{PX4_VEHICLE_ATTITUDE_MID, 								1, TO_QUEUE_PX4_VEHICLE_ATTITUDE},
		{PX4_VEHICLE_ATTITUDE_SETPOINT_MID, 					1, TO_QUEUE_PX4},
		{PX4_VEHICLE_COMMAND_ACK_MID, 							1, TO_QUEUE_PX4},
		{PX4_VEHICLE_COMMAND_MID, 								1, TO_QUEUE_PX4},
		{PX4_VEHICLE_CONTROL_MODE_MID, 							1, TO_QUEUE_PX4_VEHICLE_CONTROL_MODE},
		{PX4_VEHICLE_FORCE_SETPOINT_MID, 						1, TO_QUEUE_PX4},
		{PX4_VEHICLE_GLOBAL_POSITION_MID, 						1, TO_QUEUE_PX4_VEHICLE_GLOBAL_POSITION},
		{PX4_VEHICLE_GLOBAL_VELOCITY_SETPOINT_MID, 				1, TO_QUEUE_PX4_VEHICLE_GLOBAL_VELOCITY_SETPOINT},
		{PX4_VEHICLE_GPS_POSITION_MID, 							1, TO_QUEUE_PX4_VEHICLE_GPS_POSITION},

    	/* 170 - 179 */
		{PX4_VEHICLE_LAND_DETECTED_MID, 						1, TO_QUEUE_PX4},
		{PX4_VEHICLE_LOCAL_POSITION_MID, 						1, TO_QUEUE_PX4_VEHICLE_LOCAL_POSITION},
		{PX4_VEHICLE_LOCAL_POSITION_SETPOINT_MID, 				1, TO_QUEUE_PX4},
		{PX4_VEHICLE_RATES_SETPOINT_MID, 						1, TO_QUEUE_PX4},
		{PX4_VEHICLE_STATUS_MID, 								1, TO_QUEUE_PX4_VEHICLE_STATUS},
		{PX4_VISION_POSITION_ESTIMATE_MID, 						1, TO_QUEUE_PX4},
		{PX4_VTOL_VEHICLE_STATUS_MID, 							1, TO_QUEUE_PX4},
		{PX4_WIND_ESTIMATE_MID, 								1, TO_QUEUE_PX4_WIND_ESTIMATE},
    	{EA_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{EA_WAKEUP_MID, 										1, TO_QUEUE_HIGH},

    	/* 180 - 189 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 190 - 199 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 200 - 209 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 210 - 219 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 220 - 229 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

		/* 230 - 239 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{HS_CUSTOM_HK_TLM_MID,									1, TO_QUEUE_HIGH},

		/* 240 - 249 */
    	{MPU9250_RAW_MEAS_MID, 									1, TO_QUEUE_HIGH},
    	{MPU9250_CAL_MEAS_MID,									1, TO_QUEUE_HIGH},
    	{MPU9250_HK_TLM_MID,									1, TO_QUEUE_HIGH},
    	{MS5611_RAW_MEAS_MID, 									1, TO_QUEUE_HIGH},
    	{MS5611_CAL_MEAS_MID,									1, TO_QUEUE_HIGH},
    	{MS5611_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH}
    },
	{
		{ TO_QUEUE_ENABLED,  50,  10000,     TO_CHANNEL_PILOT, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,  50,    500000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,  200,    250000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20000,       TO_CHANNEL_CFDP, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},

		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},

		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},

		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0}
	},
	{
		{TO_CHANNEL_ENABLED, "127.0.0.1", 14550, 0 },
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 0 },
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 0 },
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 0 }
	}
};



/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#ifdef	__cplusplus
}
#endif

#endif /* _TO_CONFIG_ */
