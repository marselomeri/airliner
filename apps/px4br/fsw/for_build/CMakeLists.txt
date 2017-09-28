 #############################################################################
 #
 #   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
 #
 # Redistribution and use in source and binary forms, with or without
 # modification, are permitted provided that the following conditions
 # are met:
 #
 # 1. Redistributions of source code must retain the above copyright
 #    notice, this list of conditions and the following disclaimer.
 # 2. Redistributions in binary form must reproduce the above copyright
 #    notice, this list of conditions and the following disclaimer in
 #    the documentation and/or other materials provided with the
 #    distribution.
 # 3. Neither the name PX4 nor the names of its contributors may be
 #    used to endorse or promote products derived from this software
 #    without specific prior written permission.
 #
 # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 # "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 # LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 # FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 # COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 # INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 # BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 # OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 # AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 # LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 # ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 # POSSIBILITY OF SUCH DAMAGE.
 #
 #############################################################################
 
 
set(PX4BR_PROTOBUF_MSGS_DIR ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf)
set(PX4_MSGS_DIR ${CMAKE_CURRENT_BINARY_DIR}/../src)

add_airliner_app_def(px4br
    FILE PX4BR
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_cmd_codes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_routes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_routes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_serialization.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_serialization.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4br_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/px4_msgs.h
        
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_armed.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_armed.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_controls.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_controls.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_direct.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_direct.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_outputs.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/actuator_outputs.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/adc_report.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/adc_report.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/airspeed.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/airspeed.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/att_pos_mocap.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/att_pos_mocap.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/battery_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/battery_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/camera_trigger.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/camera_trigger.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/commander_state.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/commander_state.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/control_state.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/control_state.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/cpuload.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/cpuload.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/debug_key_value.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/debug_key_value.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/differential_pressure.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/differential_pressure.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/distance_sensor.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/distance_sensor.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/ekf2_innovations.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/ekf2_innovations.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/ekf2_replay.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/ekf2_replay.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/esc_report.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/esc_report.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/esc_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/esc_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/estimator_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/estimator_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/fence.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/fence.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/fence_vertex.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/fence_vertex.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/filtered_bottom_flow.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/filtered_bottom_flow.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/follow_target.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/follow_target.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/fw_pos_ctrl_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/fw_pos_ctrl_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/fw_virtual_attitude_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/fw_virtual_attitude_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/fw_virtual_rates_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/fw_virtual_rates_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/geofence_result.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/geofence_result.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/gps_dump.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/gps_dump.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/gps_inject_data.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/gps_inject_data.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/hil_sensor.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/hil_sensor.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/home_position.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/home_position.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/input_rc.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/input_rc.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/log_message.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/log_message.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/manual_control_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/manual_control_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/mavlink_log.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/mavlink_log.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/mc_att_ctrl_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/mc_att_ctrl_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/mc_virtual_attitude_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/mc_virtual_attitude_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/mc_virtual_rates_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/mc_virtual_rates_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/mission.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/mission.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/mission_result.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/mission_result.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/multirotor_motor_limits.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/multirotor_motor_limits.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/offboard_control_mode.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/offboard_control_mode.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/optical_flow.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/optical_flow.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/output_pwm.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/output_pwm.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/parameter_update.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/parameter_update.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/position_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/position_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/position_setpoint_triplet.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/position_setpoint_triplet.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/pwm_input.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/pwm_input.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/qshell_req.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/qshell_req.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/rc_channels.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/rc_channels.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/rc_parameter_map.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/rc_parameter_map.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/safety.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/safety.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/satellite_info.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/satellite_info.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_accel.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_accel.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_baro.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_baro.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_combined.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_combined.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_gyro.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_gyro.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_mag.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/sensor_mag.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/servorail_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/servorail_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/subsystem_info.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/subsystem_info.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/system_power.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/system_power.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/tecs_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/tecs_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/telemetry_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/telemetry_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/test_motor.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/test_motor.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/time_offset.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/time_offset.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/transponder_report.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/transponder_report.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/uavcan_parameter_request.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/uavcan_parameter_request.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/uavcan_parameter_value.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/uavcan_parameter_value.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_attitude.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_attitude.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_attitude_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_attitude_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_command_ack.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_command_ack.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_command.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_command.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_control_mode.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_control_mode.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_force_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_force_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_global_position.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_global_position.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_global_velocity_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_global_velocity_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_gps_position.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_gps_position.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_land_detected.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_land_detected.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_local_position.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_local_position.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_local_position_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_local_position_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_rates_setpoint.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_rates_setpoint.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vehicle_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/vtol_vehicle_status.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/vtol_vehicle_status.pb.h
        ${PX4BR_PROTOBUF_MSGS_DIR}/wind_estimate.pb.c
        ${PX4BR_PROTOBUF_MSGS_DIR}/wind_estimate.pb.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${PX4BR_PROTOBUF_MSGS_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/px4_msgs/

    PROTOBUF_DEFS
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/actuator_armed.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/actuator_controls.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/actuator_direct.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/actuator_outputs.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/adc_report.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/airspeed.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/att_pos_mocap.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/battery_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/camera_trigger.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/commander_state.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/control_state.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/cpuload.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/debug_key_value.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/differential_pressure.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/distance_sensor.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/ekf2_innovations.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/ekf2_replay.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/esc_report.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/esc_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/estimator_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/fence_vertex.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/fence.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/filtered_bottom_flow.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/follow_target.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/fw_pos_ctrl_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/fw_virtual_attitude_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/fw_virtual_rates_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/geofence_result.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/gps_dump.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/gps_inject_data.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/hil_sensor.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/home_position.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/input_rc.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/log_message.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/manual_control_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/mavlink_log.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/mc_att_ctrl_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/mc_virtual_attitude_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/mc_virtual_rates_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/mission_result.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/mission.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/multirotor_motor_limits.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/offboard_control_mode.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/optical_flow.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/output_pwm.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/parameter_update.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/position_setpoint_triplet.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/position_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/pwm_input.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/qshell_req.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/rc_channels.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/rc_parameter_map.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/safety.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/satellite_info.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/sensor_accel.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/sensor_baro.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/sensor_combined.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/sensor_gyro.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/sensor_mag.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/servorail_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/subsystem_info.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/system_power.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/tecs_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/telemetry_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/test_motor.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/time_offset.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/transponder_report.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/uavcan_parameter_request.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/uavcan_parameter_value.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_attitude_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_attitude.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_command_ack.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_command.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_control_mode.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_force_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_global_position.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_global_velocity_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_gps_position.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_land_detected.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_local_position.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_local_position_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_rates_setpoint.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vehicle_position_estimate.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/vtol_vehicle_status.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/protobuf/wind_estimate.proto

    PROTOBUF_MSGS_DIR        
        ${PX4BR_PROTOBUF_MSGS_DIR}
        
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)

set(PX4_MSGS_DIR ${PX4_MSGS_DIR} PARENT_SCOPE)
