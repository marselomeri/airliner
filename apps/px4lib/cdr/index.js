'use strict';

var path = require( 'path' );

const CdrPlugin = require( path.join( global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin' ) ).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor( urlBase ) {
    super( 'px4', path.join( __dirname, 'web', urlBase ) );
  }

  getContent() {
    var result = {
      shortDescription: 'PX4',
      longDescription: 'PX4 Message Displays',
      nodes: {
        Main: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Main',
          longDescription: 'PX4 Main Layout',
          filePath: '/main.lyt'
        },
        Dataplot: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Dataplot',
          longDescription: 'Generic Dataplot',
          filePath: '/data_plot.pug'
        },
        PX4_ActuatorArmedMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Actuator Armed',
          longDescription: 'PX4 Actuator Armed Message',
          filePath: '/PX4_ActuatorArmedMsg.pug'
        },
        PX4_ActuatorControlsMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Actuator Controls',
          longDescription: 'PX4 Actuator Controls Message',
          filePath: '/PX4_ActuatorControlsMsg.pug'
        },
        PX4_ActuatorOutputsMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Actuator Outputs',
          longDescription: 'PX4 Actuator Outputs Message',
          filePath: '/PX4_ActuatorOutputsMsg.pug'
        },
        PX4_AirspeedMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Air Speed',
          longDescription: 'PX4 Air Speed Message',
          filePath: '/PX4_AirspeedMsg.pug'
        },
        PX4_BatteryStatusMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Battery Status',
          longDescription: 'PX4 Battery Status Message',
          filePath: '/PX4_BatteryStatusMsg.pug'
        },
        PX4_CommanderStateMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Commander State',
          longDescription: 'PX4 Commander State Message',
          filePath: '/PX4_CommanderStateMsg.pug'
        },
        PX4_ControlStateMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Control State',
          longDescription: 'PX4 Control State Message',
          filePath: '/PX4_ControlStateMsg.pug'
        },
        PX4_DifferentialPressureMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Differential Pressure',
          longDescription: 'PX4 Differential Pressure Message',
          filePath: '/PX4_DifferentialPressureMsg.pug'
        },
        PX4_DistanceSensorMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Distance Sensor',
          longDescription: 'PX4 Distance Sensor Message',
          filePath: '/PX4_DistanceSensorMsg.pug'
        },
        PX4_EstimatorStatusMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Estimator Status',
          longDescription: 'PX4 Estimator Status Message',
          filePath: '/PX4_EstimatorStatusMsg.pug'
        },
        PX4_GpsInjectDataMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'GPS Inject Data',
          longDescription: 'PX4 GPS Inject Data Message',
          filePath: '/PX4_GpsInjectDataMsg.pug'
        },
        PX4_HomePositionMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Home Position',
          longDescription: 'PX4 Home Position Message',
          filePath: '/PX4_HomePositionMsg.pug'
        },
        PX4_InputRcMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Input RC',
          longDescription: 'PX4 Input RC Message',
          filePath: '/PX4_InputRcMsg.pug'
        },
        PX4_LedControlMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Led Control',
          longDescription: 'PX4 Led Control Message',
          filePath: '/PX4_LedControlMsg.pug'
        },
        PX4_ManualControlSetpointMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Manual Control Setpoint',
          longDescription: 'PX4 Manual Control Setpoint Message',
          filePath: '/PX4_ManualControlSetpointMsg.pug'
        },
        PX4_McAttCtrlStatusMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Multicoptor Attitude Control Status',
          longDescription: 'PX4 Multicoptor Attitude Control Status Message',
          filePath: '/PX4_McAttCtrlStatusMsg.pug'
        },
        PX4_MissionMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Mission',
          longDescription: 'PX4 Mission Message',
          filePath: '/PX4_MissionMsg.pug'
        },
        PX4_MissionResultMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Mission Result',
          longDescription: 'PX4 Mission Result Message',
          filePath: '/PX4_MissionResultMsg.pug'
        },
        PX4_MultirotorMotorLimitsMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Multirotor Motor Limits',
          longDescription: 'PX4 Multirotor Motor Limits Message',
          filePath: '/PX4_MultirotorMotorLimitsMsg.pug'
        },
        PX4_OpticalFlowMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Optical Flow',
          longDescription: 'PX4 Optical Flow Message',
          filePath: '/PX4_OpticalFlowMsg.pug'
        },
        PX4_PositionSetpointTripletCurrentMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Position Setpoint Triplet - Current',
          longDescription: 'PX4 Position Setpoint Triplet Current Message',
          filePath: '/PX4_PositionSetpointTripletCurrentMsg.pug'
        },
        PX4_PositionSetpointTripletNextMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Position Setpoint Triplet - Next',
          longDescription: 'PX4 Position Setpoint Triplet Next Message',
          filePath: '/PX4_PositionSetpointTripletNextMsg.pug'
        },
        PX4_PositionSetpointTripletPreviousMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Position Setpoint Triplet - Previous',
          longDescription: 'PX4 Position Setpoint Triplet Previous Message',
          filePath: '/PX4_PositionSetpointTripletPreviousMsg.pug'
        },
        PX4_RcChannelsMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'RC Channels',
          longDescription: 'PX4 RC Channels Message',
          filePath: '/PX4_RcChannelsMsg.pug'
        },
        PX4_SafetyMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Safety',
          longDescription: 'PX4 Safety Message',
          filePath: '/PX4_SafetyMsg.pug'
        },
        PX4_SatelliteInfoMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Satellite Info',
          longDescription: 'PX4 Satellite Info Message',
          filePath: '/PX4_SatelliteInfoMsg.pug'
        },
        PX4_SensorAccelMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Sensor Accel',
          longDescription: 'PX4 Sensor Accelerometer Message',
          filePath: '/PX4_SensorAccelMsg.pug'
        },
        PX4_SensorBaroMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Sensor Baro',
          longDescription: 'PX4 Sensor Barometer Message',
          filePath: '/PX4_SensorBaroMsg.pug'
        },
        PX4_SensorCombinedMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Sensor Combined',
          longDescription: 'PX4 Sensor Combined Message',
          filePath: '/PX4_SensorCombinedMsg.pug'
        },
        PX4_SensorCorrectionMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Sensor Correction',
          longDescription: 'PX4 Sensor Correction Message',
          filePath: '/PX4_SensorCorrectionMsg.pug'
        },
        PX4_SensorGyroMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Sensor Gyro',
          longDescription: 'PX4 Sensor Gyroscope Message',
          filePath: '/PX4_SensorGyroMsg.pug'
        },
        PX4_SensorMagMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Sensor Mag',
          longDescription: 'PX4 Sensor Magnetometer Message',
          filePath: '/PX4_SensorMagMsg.pug'
        },
        PX4_SubsystemInfoMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Subsystem Info',
          longDescription: 'PX4 Subsystem Info Message',
          filePath: '/PX4_SubsystemInfoMsg.pug'
        },
        PX4_TelemetryStatusMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Telemetry Status',
          longDescription: 'PX4 Telemetry Status Message',
          filePath: '/PX4_TelemetryStatusMsg.pug'
        },
        PX4_VehicleAttitudeMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Attitude',
          longDescription: 'PX4 Vehicle Attitude Message',
          filePath: '/PX4_VehicleAttitudeMsg.pug'
        },
        PX4_VehicleAttitudeSetpointMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Attitude Setpoint',
          longDescription: 'PX4 Vehicle Attitude Setpoint Message',
          filePath: '/PX4_VehicleAttitudeSetpointMsg.pug'
        },
        PX4_VehicleCommandMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Command',
          longDescription: 'PX4 Vehicle Command Message',
          filePath: '/PX4_VehicleCommandMsg.pug'
        },
        PX4_VehicleControlModeMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Control Mode',
          longDescription: 'PX4 Vehicle Control Mode Message',
          filePath: '/PX4_VehicleControlModeMsg.pug'
        },
        PX4_VehicleGlobalPositionMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Global Position',
          longDescription: 'PX4 Vehicle Global Position Message',
          filePath: '/PX4_VehicleGlobalPositionMsg.pug'
        },
        PX4_VehicleGlobalVelocitySetpointMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Global Velocity Setpoint',
          longDescription: 'PX4 Vehicle Global Velocity Setpoint Message',
          filePath: '/PX4_VehicleGlobalVelocitySetpointMsg.pug'
        },
        PX4_VehicleGpsPositionMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle GPS Position',
          longDescription: 'PX4 Vehicle GPS Position Message',
          filePath: '/PX4_VehicleGpsPositionMsg.pug'
        },
        PX4_VehicleLandDetectedMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Land Detected',
          longDescription: 'PX4 Vehicle Land Detected Message',
          filePath: '/PX4_VehicleLandDetectedMsg.pug'
        },
        PX4_VehicleLocalPositionMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Local Position',
          longDescription: 'PX4 Vehicle Local Position Message',
          filePath: '/PX4_VehicleLocalPositionMsg.pug'
        },
        PX4_VehicleLocalPositionSetpointMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Local Position Setpoint',
          longDescription: 'PX4 Vehicle Local Position Setpoint Message',
          filePath: '/PX4_VehicleLocalPositionSetpointMsg.pug'
        },
        PX4_VehicleRatesSetpointMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Rates Setpoint',
          longDescription: 'PX4 Vehicle Rates Setpoint Message',
          filePath: '/PX4_VehicleRatesSetpointMsg.pug'
        },
        PX4_VehicleStatusMsg: {
          type: CdrPlugin.ContentType.PANEL,
          shortDescription: 'Vehicle Status',
          longDescription: 'PX4 Vehicle Status Message',
          filePath: '/PX4_VehicleStatusMsg.pug'
        },
        PX4_ActuatorArmedMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Actuator Armed',
          longDescription: 'PX4 Actuator Armed Message',
          filePath: '/PX4_ActuatorArmedMsg.lyt'
        },
        PX4_ActuatorControlsMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Actuator Controls',
          longDescription: 'PX4 Actuator Controls Message',
          filePath: '/PX4_ActuatorControlsMsg.lyt'
        },
        PX4_ActuatorOutputsMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Actuator Outputs',
          longDescription: 'PX4 Actuator Outputs Message',
          filePath: '/PX4_ActuatorOutputsMsg.lyt'
        },
        PX4_AirspeedMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Air Speed',
          longDescription: 'PX4 Air Speed Message',
          filePath: '/PX4_AirspeedMsg.lyt'
        },
        PX4_BatteryStatusMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Battery Status',
          longDescription: 'PX4 Battery Status Message',
          filePath: '/PX4_BatteryStatusMsg.lyt'
        },
        PX4_CommanderStateMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Commander State',
          longDescription: 'PX4 Commander State Message',
          filePath: '/PX4_CommanderStateMsg.lyt'
        },
        PX4_ControlStateMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Control State',
          longDescription: 'PX4 Control State Message',
          filePath: '/PX4_ControlStateMsg.lyt'
        },
        PX4_DifferentialPressureMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Differential Pressure',
          longDescription: 'PX4 Differential Pressure Message',
          filePath: '/PX4_DifferentialPressureMsg.lyt'
        },
        PX4_DistanceSensorMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Distance Sensor',
          longDescription: 'PX4 Distance Sensor Message',
          filePath: '/PX4_DistanceSensorMsg.lyt'
        },
        PX4_EstimatorStatusMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Estimator Status',
          longDescription: 'PX4 Estimator Status Message',
          filePath: '/PX4_EstimatorStatusMsg.lyt'
        },
        PX4_GpsInjectDataMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'GPS Inject Data',
          longDescription: 'PX4 GPS Inject Data Message',
          filePath: '/PX4_GpsInjectDataMsg.lyt'
        },
        PX4_HomePositionMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Home Position',
          longDescription: 'PX4 Home Position Message',
          filePath: '/PX4_HomePositionMsg.lyt'
        },
        PX4_InputRcMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Input RC',
          longDescription: 'PX4 Input RC Message',
          filePath: '/PX4_InputRcMsg.lyt'
        },
        PX4_LedControlMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Led Control',
          longDescription: 'PX4 Led Control Message',
          filePath: '/PX4_LedControlMsg.lyt'
        },
        PX4_ManualControlSetpointMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Manual Control Setpoint',
          longDescription: 'PX4 Manual Control Setpoint Message',
          filePath: '/PX4_ManualControlSetpointMsg.lyt'
        },
        PX4_McAttCtrlStatusMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Multicoptor Attitude Control Status',
          longDescription: 'PX4 Multicoptor Attitude Control Status Message',
          filePath: '/PX4_McAttCtrlStatusMsg.lyt'
        },
        PX4_MissionMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Mission',
          longDescription: 'PX4 Mission Message',
          filePath: '/PX4_MissionMsg.lyt'
        },
        PX4_MissionResultMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Mission Result',
          longDescription: 'PX4 Mission Result Message',
          filePath: '/PX4_MissionResultMsg.lyt'
        },
        PX4_MultirotorMotorLimitsMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Multirotor Motor Limits',
          longDescription: 'PX4 Multirotor Motor Limits Message',
          filePath: '/PX4_MultirotorMotorLimitsMsg.lyt'
        },
        PX4_OpticalFlowMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Optical Flow',
          longDescription: 'PX4 Optical Flow Message',
          filePath: '/PX4_OpticalFlowMsg.lyt'
        },
        PX4_PositionSetpointTripletMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Position Setpoint Triplet',
          longDescription: 'PX4 Position Setpoint Triplet Message',
          filePath: '/PX4_PositionSetpointTripletMsg.lyt'
        },
        PX4_RcChannelsMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'RC Channels',
          longDescription: 'PX4 RC Channels Message',
          filePath: '/PX4_RcChannelsMsg.lyt'
        },
        PX4_SafetyMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Safety',
          longDescription: 'PX4 Safety Message',
          filePath: '/PX4_SafetyMsg.lyt'
        },
        PX4_SatelliteInfoMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Satellite Info',
          longDescription: 'PX4 Satellite Info Message',
          filePath: '/PX4_SatelliteInfoMsg.lyt'
        },
        PX4_SensorAccelMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Sensor Accel',
          longDescription: 'PX4 Sensor Accelerometer Message',
          filePath: '/PX4_SensorAccelMsg.lyt'
        },
        PX4_SensorBaroMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Sensor Baro',
          longDescription: 'PX4 Sensor Barometer Message',
          filePath: '/PX4_SensorBaroMsg.lyt'
        },
        PX4_SensorCombinedMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Sensor Combined',
          longDescription: 'PX4 Sensor Combined Message',
          filePath: '/PX4_SensorCombinedMsg.lyt'
        },
        PX4_SensorCorrectionMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Sensor Correction',
          longDescription: 'PX4 Sensor Correction Message',
          filePath: '/PX4_SensorCorrectionMsg.lyt'
        },
        PX4_SensorGyroMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Sensor Gyro',
          longDescription: 'PX4 Sensor Gyroscope Message',
          filePath: '/PX4_SensorGyroMsg.lyt'
        },
        PX4_SensorMagMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Sensor Mag',
          longDescription: 'PX4 Sensor Magnetometer Message',
          filePath: '/PX4_SensorMagMsg.lyt'
        },
        PX4_SubsystemInfoMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Subsystem Info',
          longDescription: 'PX4 Subsystem Info Message',
          filePath: '/PX4_SubsystemInfoMsg.lyt'
        },
        PX4_TelemetryStatusMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Telemetry Status',
          longDescription: 'PX4 Telemetry Status Message',
          filePath: '/PX4_TelemetryStatusMsg.lyt'
        },
        PX4_VehicleAttitudeMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Attitude',
          longDescription: 'PX4 Vehicle Attitude Message',
          filePath: '/PX4_VehicleAttitudeMsg.lyt'
        },
        PX4_VehicleAttitudeSetpointMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Attitude Setpoint',
          longDescription: 'PX4 Vehicle Attitude Setpoint Message',
          filePath: '/PX4_VehicleAttitudeSetpointMsg.lyt'
        },
        PX4_VehicleCommandMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Command',
          longDescription: 'PX4 Vehicle Command Message',
          filePath: '/PX4_VehicleCommandMsg.lyt'
        },
        PX4_VehicleControlModeMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Control Mode',
          longDescription: 'PX4 Vehicle Control Mode Message',
          filePath: '/PX4_VehicleControlModeMsg.lyt'
        },
        PX4_VehicleGlobalPositionMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Global Position',
          longDescription: 'PX4 Vehicle Global Position Message',
          filePath: '/PX4_VehicleGlobalPositionMsg.lyt'
        },
        PX4_VehicleGlobalVelocitySetpointMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Global Velocity Setpoint',
          longDescription: 'PX4 Vehicle Global Velocity Setpoint Message',
          filePath: '/PX4_VehicleGlobalVelocitySetpointMsg.lyt'
        },
        PX4_VehicleGpsPositionMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle GPS Position',
          longDescription: 'PX4 Vehicle GPS Position Message',
          filePath: '/PX4_VehicleGpsPositionMsg.lyt'
        },
        PX4_VehicleLandDetectedMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Land Detected',
          longDescription: 'PX4 Vehicle Land Detected Message',
          filePath: '/PX4_VehicleLandDetectedMsg.lyt'
        },
        PX4_VehicleLocalPositionMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Local Position',
          longDescription: 'PX4 Vehicle Local Position Message',
          filePath: '/PX4_VehicleLocalPositionMsg.lyt'
        },
        PX4_VehicleLocalPositionSetpointMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Local Position Setpoint',
          longDescription: 'PX4 Vehicle Local Position Setpoint Message',
          filePath: '/PX4_VehicleLocalPositionSetpointMsg.lyt'
        },
        PX4_VehicleRatesSetpointMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Rates Setpoint',
          longDescription: 'PX4 Vehicle Rates Setpoint Message',
          filePath: '/PX4_VehicleRatesSetpointMsg.lyt'
        },
        PX4_VehicleStatusMsgLyt: {
          type: CdrPlugin.ContentType.LAYOUT,
          shortDescription: 'Vehicle Status',
          longDescription: 'PX4 Vehicle Status Message',
          filePath: '/PX4_VehicleStatusMsg.lyt'
        }
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {