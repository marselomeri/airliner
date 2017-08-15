#ifndef _EFT1_MIDS_H_
#define _EFT1_MIDS_H_

#include "cfe_msgids.h"

/* Commands */

/* TO 										*/
/* Range: 0x900 - 0x90f 					*/
#define TO_CMD_MID 						0x1900
#define TO_SEND_HK_MID 					0x1901
#define TO_HK_TLM_MID 					0x0902
#define TO_SEND_TLM_MID					0x1903
#define TO_DATA_TYPE_MID		        0x0904

/* CI 										*/
/* Range: 0x900 - 0x90f 					*/
#define CI_CMD_MID 						0x1905
#define CI_SEND_HK_MID 					0x1906
#define CI_HK_TLM_MID 					0x0907
#define CI_WAKEUP_MID					0x1908
#define CI_OUT_DATA_MID		            0x1909

/* CF										*/
/* Range: 0x910 - 0x92f						*/
#define CF_CMD_MID                      0x1910
#define CF_INCOMING_PDU_MID             0x0FFD
#define CF_SEND_HK_MID                  0x1912
#define CF_SPARE1_CMD_MID               0x1913
#define CF_SPARE2_CMD_MID               0x1914
#define CF_SPARE3_CMD_MID               0x1915
#define CF_SPARE4_CMD_MID               0x1916
#define CF_SPARE5_CMD_MID               0x1917
#define CF_WAKE_UP_REQ_CMD_MID          0x1918
#define CF_CONFIG_TLM_MID               0x0919
#define CF_HK_TLM_MID                   0x091a
#define CF_SPARE0_TLM_MID               0x091b
#define CF_SPARE1_TLM_MID               0x091c
#define CF_SPARE2_TLM_MID               0x091d
#define CF_SPARE3_TLM_MID               0x091e
#define CF_SPARE4_TLM_MID               0x091f
#define CF_TRANS_TLM_MID                0x0920
/*
** NOTE: the definition below is NOT used by the code. The code uses the MsgId
** defined in the CF table. For the purpose of keeping all CF related message
** IDs defined in this file, the CF table should reference this macro
** definition.
*/
#define CF_SPACE_TO_GND_PDU_MID         0x1FFE


/* CS										*/
/* Range: 0x930 - 0x93f						*/
#define CS_CMD_MID						0x1930
#define CS_BACKGROUND_CYCLE_MID			0x1931
#define CS_SEND_HK_MID					0x1932
#define CS_HK_TLM_MID					0x0933


/* DS										*/
/* Range: 0x940 - 0x94f						*/
#define DS_CMD_MID						0x1940
#define DS_SEND_HK_MID					0x1941
#define DS_HK_TLM_MID					0x0942
#define DS_DIAG_TLM_MID					0x0943


/* EIM										*/
/* Range: 0x950 - 0x97f						*/
#define EIM_CMD_MID						0x1950
#define EIM_SEND_HK_MID					0x1951
#define EIM_HK_TLM_MID					0x0952
#define EIM_IMU_MID						0x0953
#define EIM_NAVDATA_DEMO_MID			0x0954
#define EIM_NAVDATA_TIME_MID			0x0955
#define EIM_NAVDATA_RAW_MEASURES_MID	0x0956
#define EIM_NAVDATA_PRESSURE_RAW_MID	0x0957
#define EIM_NAVDATA_MAGNETO_MID			0x0958
#define EIM_NAVDATA_WIND_SPEED_MID		0x0959
#define EIM_NAVDATA_KALMAN_PRESSURE_MID	0x095a
#define EIM_NAVDATA_ZIMMU_3000_MID		0x095b
#define EIM_NAVDATA_PHYS_MEASURES_MID	0x095c
#define EIM_NAVDATA_GYRO_OFFSETS_MID	0x095d
#define EIM_NAVDATA_EULER_ANGLES_MID	0x095e
#define EIM_NAVDATA_REFERENCES_MID		0x095f
#define EIM_NAVDATA_TRIMS_MID			0x0960
#define EIM_NAVDATA_RC_REFERENCES_MID	0x0961
#define EIM_NAVDATA_PWM_MID				0x0962
#define EIM_NAVDATA_ALTITUDE_MID		0x0963
#define EIM_NAVDATA_VISION_RAW_MID		0x0964
#define EIM_NAVDATA_VISION_MID			0x0965
#define EIM_NAVDATA_VISION_PERF_MID		0x0966
#define EIM_NAVDATA_TRACKERS_SEND_MID	0x0967
#define EIM_NAVDATA_DETECT_MID			0x0968
#define EIM_NAVDATA_VISION_OF_MID		0x0969
#define EIM_NAVDATA_WATCHDOG_MID		0x096a
#define EIM_NAVDATA_ADC_DATA_FRAME_MID	0x096b
#define EIM_NAVDATA_VIDEO_STREAM_MID	0x096c
#define EIM_NAVDATA_HDVIDEO_MID			0x096d
#define EIM_NAVDATA_GAMES_MID			0x096e
#define EIM_NAVDATA_WIFI_MID			0x096f


/* FM										*/
/* Range: 0x980 - 0x98f						*/
#define FM_CMD_MID  					0x1980
#define FM_SEND_HK_MID					0x1981
#define FM_HK_TLM_MID       			0x0982
#define FM_OPEN_FILES_TLM_MID			0x0983
#define FM_FREE_SPACE_TLM_MID			0x0984
#define FM_FILE_INFO_TLM_MID			0x0985
#define FM_DIR_LIST_TLM_MID				0x0986


/* HK										*/
/* Range: 0x990 - 0x99f						*/
#define HK_CMD_MID  					0x1990
#define HK_SEND_HK_MID					0x1991
#define HK_SEND_COMBINED_PKT_MID    	0x1992
#define HK_HK_TLM_MID       			0x0993
#define HK_COMBINED_PKT1_MID			0x0994
#define HK_COMBINED_PKT2_MID			0x0995
#define HK_COMBINED_PKT3_MID			0x0996
#define HK_COMBINED_PKT4_MID			0x0997
#define HK_COMBINED_PKT5_MID			0x0998
#define HK_COMBINED_PKT6_MID			0x0999
#define HK_COMBINED_PKT7_MID			0x099a
#define HK_COMBINED_PKT8_MID			0x099b
#define HK_COMBINED_PKT9_MID			0x099c
#define HK_COMBINED_PKT10_MID			0x099d


/* HS										*/
/* Range: 0x9a0 - 0x9af						*/
#define HS_CMD_MID     					0x19a0
#define HS_SEND_HK_MID      			0x19a1
#define HS_WAKEUP_MID       			0x19a2
#define HS_HK_TLM_MID       			0x09a3
#define HS_CUSTOM_HK_TLM_MID			0x09a4


/* LC										*/
/* Range: 0x9b0 - 0x9bf						*/
#define LC_HK_TLM_MID					0x09b0
#define LC_SEND_HK_MID					0x19b1
#define LC_CMD_MID						0x19b2
#define LC_SAMPLE_AP_MID				0x09b3


/* MM										*/
/* Range: 0x9c0 - 0x9c2						*/
#define MM_CMD_MID        				0x19c0
#define MM_SEND_HK_MID    				0x19c1
#define MM_HK_TLM_MID     				0x09c2


/* MD										*/
/* Range: 0x9c3 - 0x9cf						*/
#define MD_CMD_MID						0x19c3
#define MD_WAKEUP_MID					0x19c4
#define MD_SEND_HK_MID					0x19c5
#define MD_HK_TLM_MID					0x09c6
#define MD_DWELL_PKT_MID_BASE			0x09c7


/* NAV										*/
/* Range: 0x9d0 - 0x9df						*/
#define NAV_CMD_MID						0x19d0
#define NAV_SEND_HK_MID					0x19d1
#define NAV_FUNC2_MID					0x19d2
#define NAV_FUNC3_MID					0x19d3
#define NAV_FUNC4_MID					0x19d4
#define NAV_FUNC5_MID					0x19d5
#define NAV_FUNC6_MID					0x19d6
#define NAV_FUNC7_MID					0x19d7
#define NAV_FUNC8_MID					0x19d8
#define NAV_FUNC9_MID					0x19d9
#define NAV_FUNC10_MID					0x19da
#define NAV_HK_TLM_MID					0x09db
#define NAV_HIGH_RATE_NAV_MID			0x09dc


/* SC										*/
/* Range: 0x9e0 - 0x9e3						*/
#define SC_CMD_MID                      0x19e0
#define SC_SEND_HK_MID                  0x19e1
#define SC_1HZ_WAKEUP_MID               0x19e2
#define SC_HK_TLM_MID                   0x09e3


/* SCH										*/
/* Range: 0x9e4 - 0x9ef						*/
#define SCH_CMD_MID         			0x19e4
#define SCH_SEND_HK_MID     			0x19e5
#define SCH_UNUSED_MID      			0
#define SCH_DIAG_TLM_MID				0x09e7
#define SCH_HK_TLM_MID					0x09e8
#define SCH_ACTIVITY_DONE_MID			0x09e9


/* GOPRO									*/
/* Range: 0x9f0 - 0x9ff						*/
#define GOPRO_CMD_MID						0x19f0
#define GOPRO_SEND_HK_MID					0x19f1
#define GOPRO_HK_TLM_MID					0x09f2


/* PX4												*/
/* Range: 0x9f0 - 0x9ff								*/
#define PX4_ACTUATOR_ARMED_MID						0x0a05
#define PX4_ACTUATOR_CONTROLS_MID					0x0a06
#define PX4_ACTUATOR_DIRECT_MID						0x0a07
#define PX4_ACTUATOR_OUTPUTS_MID					0x0a08
#define PX4_ADC_REPORT_MID							0x0a09
#define PX4_AIRSPEED_MID							0x0a0a
#define PX4_ATT_POS_MOCAP_MID						0x0a0b
#define PX4_BATTERY_STATUS_MID						0x0a0c
#define PX4_CAMERA_TRIGGER_MID						0x0a0d
#define PX4_COMMANDER_STATE_MID						0x0a0e
#define PX4_CONTROL_STATE_MID						0x0a0f
#define PX4_CPULOAD_MID								0x0a10
#define PX4_DEBUG_KEY_VALUE_MID						0x0a11
#define PX4_DIFFERENTIAL_PRESSURE_MID				0x0a12
#define PX4_DISTANCE_SENSOR_MID						0x0a13
#define PX4_FW_POS_CTRL_STATUS_MID					0x0a14
#define PX4_FW_VIRTUAL_ATTITUDE_SETPOINT_MID		0x0a15
#define PX4_FW_VIRTUAL_RATES_SETPOINT_MID			0x0a16
#define PX4_EKF2_INNOVATIONS_MID					0x0a17
#define PX4_EKF2_REPLAY_MID							0x0a18
#define PX4_ESC_REPORT_MID							0x0a19
#define PX4_ESC_STATUS_MID							0x0a1a
#define PX4_ESTIMATOR_STATUS_MID					0x0a1b
#define PX4_FENCE_MID								0x0a1c
#define PX4_FENCE_VERTEX_MID						0x0a1d
#define PX4_FILTERED_BOTTOM_FLOW_MID				0x0a1e
#define PX4_FOLLOW_TARGET_MID						0x0a1f
#define PX4_GEOFENCE_RESULT_MID						0x0a20
#define PX4_GPS_DUMP_MID							0x0a21
#define PX4_GPS_INJECT_DATA_MID						0x0a22
#define PX4_HIL_SENSOR_MID							0x0a23
#define PX4_HOME_POSITION_MID						0x0a24
#define PX4_INPUT_RC_MID							0x0a25
#define PX4_LOG_MESSAGE_MID							0x0a26
#define PX4_MANUAL_CONTROL_SETPOINT_MID				0x0a27
#define PX4_MAVLINK_LOG_MID							0x0a28
#define PX4_MC_ATT_CTRL_STATUS_MID					0x0a29
#define PX4_MC_VIRTUAL_ATTITUDE_SETPOINT_MID		0x0a2a
#define PX4_MC_VIRTUAL_RATES_SETPOINT_MID			0x0a2b
#define PX4_MISSION_MID								0x0a2c
#define PX4_MISSION_RESULT_MID						0x0a2d
#define PX4_MULTIROTOR_MOTOR_LIMITS_MID				0x0a2e
#define PX4_OFFBOARD_CONTROL_MODE_MID				0x0a2f
#define PX4_OPTICAL_FLOW_MID						0x0a30
#define PX4_OUTPUT_PWM_MID							0x0a31
#define PX4_PARAMETER_UPDATE_MID					0x0a32
#define PX4_POSITION_SETPOINT_MID					0x0a33
#define PX4_POSITION_SETPOINT_TRIPLET_MID			0x0a34
#define PX4_PWM_INPUT_MID							0x0a35
#define PX4_QSHELL_REQ_MID							0x0a36
#define PX4_RC_CHANNELS_MID							0x0a37
#define PX4_RC_PARAMETER_MAP_MID					0x0a38
#define PX4_SAFETY_MID								0x0a39
#define PX4_SATELLITE_INFO_MID						0x0a3a
#define PX4_SENSOR_ACCEL_MID						0x0a3b
#define PX4_SENSOR_BARO_MID							0x0a3c
#define PX4_SENSOR_COMBINED_MID						0x0a3d
#define PX4_SENSOR_GYRO_MID							0x0a3e
#define PX4_SENSOR_MAG_MID							0x0a3f
#define PX4_SERVORAIL_STATUS_MID					0x0a40
#define PX4_SUBSYSTEM_INFO_MID						0x0a41
#define PX4_SYSTEM_POWER_MID						0x0a42
#define PX4_TECS_STATUS_MID							0x0a43
#define PX4_TELEMETRY_STATUS_MID					0x0a44
#define PX4_TEST_MOTOR_MID							0x0a45
#define PX4_TIME_OFFSET_MID							0x0a46
#define PX4_TRANSPONDER_REPORT_MID					0x0a47
#define PX4_UAVCAN_PARAMETER_REQUEST_MID			0x0a48
#define PX4_UAVCAN_PARAMETER_VALUE_MID				0x0a49
#define PX4_VEHICLE_ATTITUDE_MID					0x0a4a
#define PX4_VEHICLE_ATTITUDE_SETPOINT_MID			0x0a4b
#define PX4_VEHICLE_COMMAND_ACK_MID					0x0a4c
#define PX4_VEHICLE_COMMAND_MID						0x0a4d
#define PX4_VEHICLE_CONTROL_MODE_MID				0x0a4e
#define PX4_VEHICLE_FORCE_SETPOINT_MID				0x0a4f
#define PX4_VEHICLE_GLOBAL_POSITION_MID				0x0a50
#define PX4_VEHICLE_GLOBAL_VELOCITY_SETPOINT_MID	0x0a51
#define PX4_VEHICLE_GPS_POSITION_MID				0x0a52
#define PX4_VEHICLE_LAND_DETECTED_MID				0x0a53
#define PX4_VEHICLE_LOCAL_POSITION_MID				0x0a54
#define PX4_VEHICLE_LOCAL_POSITION_SETPOINT_MID		0x0a55
#define PX4_VEHICLE_RATES_SETPOINT_MID				0x0a56
#define PX4_VEHICLE_STATUS_MID						0x0a57
#define PX4_VISION_POSITION_ESTIMATE_MID			0x0a58
#define PX4_VTOL_VEHICLE_STATUS_MID					0x0a59
#define PX4_WIND_ESTIMATE_MID						0x0a5a

/* VID													*/
/* Range: 0xb20 - 0xb2f									*/
#define VID_CMD_MID									0x1b40
#define VID_SEND_HK_MID								0x1b41
#define VID_HK_TLM_MID								0x0b42
#define VID_GRAB_FRAME_MID							0x1b43
#define VID_FWD_CAM_FRAME_MID			    		0x0b44

#define MPU9250_SEND_HK_MID							0x1b50
#define MPU9250_HK_TLM_MID							0x0b51
#define MPU9250_DIAG_TLM_MID						0x0b52
#define MPU9250_CMD_MID								0x1b53
#define MPU9250_MEASURE_MID							0x1b54
#define MPU9250_RAW_MEAS_MID						0x0b55
#define MPU9250_CAL_MEAS_MID						0x0b56

#define MS5611_SEND_HK_MID							0x1b60
#define MS5611_HK_TLM_MID							0x0b61
#define MS5611_DIAG_TLM_MID							0x0b62
#define MS5611_CMD_MID								0x1b63
#define MS5611_MEASURE_MID							0x1b64
#define MS5611_RAW_MEAS_MID							0x0b65
#define MS5611_CAL_MEAS_MID							0x0b66

#define NEOM8N_SEND_HK_MID							0x1b70
#define NEOM8N_HK_TLM_MID							0x0b71
#define NEOM8N_DIAG_TLM_MID							0x0b72
#define NEOM8N_CMD_MID								0x1b73
#define NEOM8N_MEASURE_MID							0x1b74
#define NEOM8N_PROC_CMDS_MID						0x1b75
#define NEOM8N_CAL_MEAS_MID							0x0b76
#define NEOM8N_NAV_POSECEF_MID						0x0b77
#define NEOM8N_NAV_POSLLH_MID						0x0b78
#define NEOM8N_NAV_STATUS_MID						0x0b79
#define NEOM8N_NAV_DOP_MID							0x0b7a
#define NEOM8N_NAV_ATT_MID							0x0b7b
#define NEOM8N_NAV_SOL_MID							0x0b7c
#define NEOM8N_NAV_NAVPVT_MID						0x0b7d
#define NEOM8N_NAV_ODO_MID							0x0b7e
#define NEOM8N_NAV_RESETODO_MID						0x0b7f
#define NEOM8N_NAV_VELECEF_MID						0x0b80
#define NEOM8N_NAV_VELNED_MID						0x0b81
#define NEOM8N_NAV_TIMEGPS_MID						0x0b82
#define NEOM8N_NAV_TIMEUTC_MID						0x0b83
#define NEOM8N_NAV_CLOCK_MID						0x0b84
#define NEOM8N_NAV_TIMEGLO_MID						0x0b85
#define NEOM8N_NAV_TIMEBDS_MID						0x0b86
#define NEOM8N_NAV_TIMEGAL_MID						0x0b87
#define NEOM8N_NAV_TIMELS_MID						0x0b88
#define NEOM8N_NAV_SVINFO_MID						0x0b89
#define NEOM8N_NAV_DGPS_MID							0x0b8a
#define NEOM8N_NAV_SBAS_MID							0x0b8b
#define NEOM8N_NAV_ORB_MID							0x0b8c
#define NEOM8N_NAV_NAVSAT_MID						0x0b8d
#define NEOM8N_NAV_GEOFENCE_MID						0x0b8e
#define NEOM8N_NAV_AOPSTATUS_MID					0x0b8f
#define NEOM8N_NAV_EOE_MID							0x0b90
#define NEOM8N_MON_IO_MID							0x0b91
#define NEOM8N_MON_VER_MID							0x0b92
#define NEOM8N_MON_MSGPP_MID						0x0b93
#define NEOM8N_MON_RXBUF_MID						0x0b94
#define NEOM8N_MON_TXBUF_MID						0x0b95
#define NEOM8N_MON_HW_MID							0x0b96
#define NEOM8N_MON_HW2_MID							0x0b97
#define NEOM8N_MON_RXR_MID							0x0b98
#define NEOM8N_MON_PATCH_MID						0x0b99
#define NEOM8N_MON_GNSS_MID							0x0b9a
#define NEOM8N_MON_SMGR_MID							0x0b9b

#define SBN_WAKEUP_MID								0x0ba0

/* ROS 										*/
/* Range: 0x900 - 0x90f 					*/
#define ROS_CMD_MID	 								0x1bb0
#define ROS_SEND_HK_MID 							0x1bb1
#define ROS_HK_TLM_MID 								0x0bb3
#define ROS_SEND_TLM_MID							0x0bb4

/* ETA 												*/
/* Range: 0x900 - 0x90f 							*/
#define ETA_CMD_MID 								0x1bc0
#define ETA_SEND_HK_MID 							0x1bc1
#define ETA_DATA_TYPES_MID				    		0x0bc2
#define ETA_HK_TLM_MID 					    		0x0bc3
#define ETA_SEND_TLM_MID							0x0bc4


/* PX4BR												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4BR_CMD_MID 								0x1bd0
#define PX4BR_SEND_HK_MID 							0x1bd1
#define PX4BR_HK_TLM_MID 							0x0bd2
#define PX4BR_PROC_CMD_MID							0x1bd3


/* PX4UORB												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4UORB_CMD_MID 							0x1bd4
#define PX4UORB_SEND_HK_MID 						0x1bd5
#define PX4UORB_HK_TLM_MID 							0x0bd6
#define PX4UORB_READ_CMD_MID						0x1bd7


/* PX4AEQ												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4AEQ_CMD_MID 								0x1bd8
#define PX4AEQ_SEND_HK_MID 							0x1bd9
#define PX4AEQ_HK_TLM_MID 							0x0bda
#define PX4AEQ_READ_CMD_MID							0x1bdb


/* PX4SEN												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4SEN_CMD_MID 								0x1bdc
#define PX4SEN_SEND_HK_MID 							0x1bdd
#define PX4SEN_HK_TLM_MID 							0x0bde
#define PX4SEN_READ_CMD_MID							0x1bdf


/* PX4SIM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4SIM_CMD_MID 								0x1be0
#define PX4SIM_SEND_HK_MID 							0x1be1
#define PX4SIM_HK_TLM_MID 							0x0be2
#define PX4SIM_READ_CMD_MID							0x1be3


/* PX4ASIM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4ASIM_CMD_MID 							0x1be4
#define PX4ASIM_SEND_HK_MID 						0x1be5
#define PX4ASIM_HK_TLM_MID 							0x0be6
#define PX4ASIM_READ_CMD_MID						0x1be7


/* PX4ADSM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4ADSM_CMD_MID 							0x1be8
#define PX4ADSM_SEND_HK_MID 						0x1be9
#define PX4ADSM_HK_TLM_MID 							0x0bea
#define PX4ADSM_READ_CMD_MID						0x1beb


/* PX4BASM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4BASM_CMD_MID 							0x1bf0
#define PX4BASM_SEND_HK_MID 						0x1bf1
#define PX4BASM_HK_TLM_MID 							0x0bf2
#define PX4BASM_READ_CMD_MID						0x1bf3


/* PX4DMAN												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4DMAN_CMD_MID 							0x1bf8
#define PX4DMAN_SEND_HK_MID 						0x1bf9
#define PX4DMAN_HK_TLM_MID 							0x0bfa
#define PX4DMAN_READ_CMD_MID						0x1bfb


/* PX4GPSM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4GPSM_CMD_MID 							0x1bfc
#define PX4GPSM_SEND_HK_MID 						0x1bfd
#define PX4GPSM_HK_TLM_MID 							0x0bfe
#define PX4GPSM_READ_CMD_MID						0x1bff

/* PX4GSIM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4GSIM_CMD_MID 							0x1c04
#define PX4GSIM_SEND_HK_MID 						0x1c05
#define PX4GSIM_HK_TLM_MID 							0x0c06
#define PX4GSIM_READ_CMD_MID						0x1c07


/* PX4LPEQ												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4LPEQ_CMD_MID 							0x1c08
#define PX4LPEQ_SEND_HK_MID 						0x1c09
#define PX4LPEQ_HK_TLM_MID 							0x0c0a
#define PX4LPEQ_READ_CMD_MID						0x1c0b


/* PX4MAC												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4MAC_CMD_MID 								0x1c0c
#define PX4MAC_SEND_HK_MID 							0x1c0d
#define PX4MAC_HK_TLM_MID 							0x0c0e
#define PX4MAC_READ_CMD_MID							0x1c0f


/* PX4MPC												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4MPC_CMD_MID 								0x1c10
#define PX4MPC_SEND_HK_MID 							0x1c11
#define PX4MPC_HK_TLM_MID 							0x0c12
#define PX4MPC_READ_CMD_MID							0x1c13


/* PX4NAV												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4NAV_CMD_MID 								0x1c14
#define PX4NAV_SEND_HK_MID 							0x1c15
#define PX4NAV_HK_TLM_MID 							0x0c16
#define PX4NAV_READ_CMD_MID							0x1c17


/* PX4POS												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4POS_CMD_MID 								0x1c18
#define PX4POS_SEND_HK_MID 							0x1c19
#define PX4POS_HK_TLM_MID 							0x0c1a
#define PX4POS_READ_CMD_MID							0x1c1b


/* PX4RSIM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4RSIM_CMD_MID 							0x1c1c
#define PX4RSIM_SEND_HK_MID 						0x1c1d
#define PX4RSIM_HK_TLM_MID 							0x0c1e
#define PX4RSIM_READ_CMD_MID						0x1c1f


/* PX4TARM												*/
/* Range: 0x900 - 0x90f 								*/
#define PX4TARM_CMD_MID 							0x1c20
#define PX4TARM_SEND_HK_MID 						0x1c21
#define PX4TARM_HK_TLM_MID 							0x0c22
#define PX4TARM_READ_CMD_MID						0x1c23


/* PX4LDSM											    */
/* Range: 0x900 - 0x90f 								*/
#define PX4LDSM_CMD_MID 							0x1c24
#define PX4LDSM_SEND_HK_MID 						0x1c25
#define PX4LDSM_HK_TLM_MID 							0x0c26
#define PX4LDSM_READ_CMD_MID						0x1c27

#define SBNPX4_WAKEUP_MID							0x0c28

/* EA                                                   */
#define EA_CMD_MID                                  0x1c29
#define EA_SEND_HK_MID                              0x1c2a
#define EA_HK_TLM_MID                               0x0c2b
#define EA_WAKEUP_MID                               0x1c2c
#define EA_OUT_DATA_MID            					0x0c2d
#define EA_PERFMON_MID            					0x1c2e

/* VC                                                   */
#define VC_HK_TLM_MID                               0x0c39
#define VC_SEND_HK_MID                              0x1c3a
#define VC_CMD_MID                                  0x1c3b
#define VC_WAKEUP_MID                               0x1c3c

#endif
