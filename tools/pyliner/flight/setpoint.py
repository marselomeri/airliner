import time
from os.path import join, dirname, abspath

import util
from pyliner import Pyliner

# Initialize pyliner object
rocky = Pyliner(**{
    "airliner_map": join(dirname(dirname(abspath(__file__))), "airliner.json"),
    "ci_port": 5009,
    "to_port": 5012,
    "script_name": "FT6_GCS",
    "log_dir": join(dirname(abspath(__file__)), "logs")})

# Subscribe to desired telemetry
rocky.com.subscribe({'tlm': ['/Airliner/CNTL/VehicleGlobalPosition/Lat',
                             '/Airliner/CNTL/VehicleGlobalPosition/Lon',
                             '/Airliner/CNTL/VehicleGlobalPosition/Alt',
                             '/Airliner/CNTL/VehicleGlobalPosition/Yaw',
                             '/Airliner/CNTL/VehicleGlobalPosition/VelN',
                             '/Airliner/CNTL/VehicleGlobalPosition/VelE',
                             '/Airliner/CNTL/VehicleGlobalPosition/VelD',
                             '/Airliner/CNTL/SetpointTriplet/Timestamp',
                             '/Airliner/CNTL/SetpointTriplet/Cur_Lat',
                             '/Airliner/CNTL/SetpointTriplet/Prev_Lat']})

# Wait for pyliner data dictionary to populate with initial values
while rocky.tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt') == 'NULL':
    print "Waiting for telemetry downlink..."
    time.sleep(1)

rocky.com.send_telemetry(
    {'name': '/Airliner/CNTL/SetpointTriplet', 'args': [
        {'name': 'Timestamp', 'value': util.get_time()},
        {'name': 'Prev_Lat', 'value': 0.0},
        {'name': 'Prev_Lon', 'value': 0.0},
        {'name': 'Prev_X', 'value': 0.0},
        {'name': 'Prev_Y', 'value': 0.0},
        {'name': 'Prev_Z', 'value': 0.0},
        {'name': 'Prev_VX', 'value': 0.0},
        {'name': 'Prev_VY', 'value': 0.0},
        {'name': 'Prev_VZ', 'value': 0.0},
        {'name': 'Prev_Alt', 'value': 0.0},
        {'name': 'Prev_Yaw', 'value': 0.0},
        {'name': 'Prev_Yawspeed', 'value': 0.0},
        {'name': 'Prev_LoiterRadius', 'value': 0.0},
        {'name': 'Prev_PitchMin', 'value': 0.0},
        {'name': 'Prev_AX', 'value': 0.0},
        {'name': 'Prev_AY', 'value': 0.0},
        {'name': 'Prev_AZ', 'value': 0.0},
        {'name': 'Prev_AcceptanceRadius', 'value': 0.0},
        {'name': 'Prev_CruisingSpeed', 'value': 0.0},
        {'name': 'Prev_CruisingThrottle', 'value': 0.0},
        {'name': 'Prev_Valid', 'value': 0},
        {'name': 'Prev_Type', 'value': 0},
        {'name': 'Prev_PositionValid', 'value': 0},
        {'name': 'Prev_VelocityValid', 'value': 0},
        {'name': 'Prev_YawValid', 'value': 0},
        {'name': 'Prev_DisableMcYawControl', 'value': 0},
        {'name': 'Prev_YawspeedValid', 'value': 0},
        {'name': 'Prev_LoiterDirection', 'value': 0},
        {'name': 'Prev_AccelerationValid', 'value': 0},
        {'name': 'Prev_AccelerationIsForce', 'value': 0},
        {'name': 'Cur_Lat', 'value': 45.0},
        {'name': 'Cur_Lon', 'value': 45.0},
        {'name': 'Cur_X', 'value': 0.0},
        {'name': 'Cur_Y', 'value': 0.0},
        {'name': 'Cur_Z', 'value': 0.0},
        {'name': 'Cur_VX', 'value': 0.0},
        {'name': 'Cur_VY', 'value': 0.0},
        {'name': 'Cur_VZ', 'value': 0.0},
        {'name': 'Cur_Alt', 'value': 0.0},
        {'name': 'Cur_Yaw', 'value': 0.0},
        {'name': 'Cur_Yawspeed', 'value': 0.0},
        {'name': 'Cur_LoiterRadius', 'value': 0.0},
        {'name': 'Cur_PitchMin', 'value': 0.0},
        {'name': 'Cur_AX', 'value': 0.0},
        {'name': 'Cur_AY', 'value': 0.0},
        {'name': 'Cur_AZ', 'value': 0.0},
        {'name': 'Cur_AcceptanceRadius', 'value': 0.0},
        {'name': 'Cur_CruisingSpeed', 'value': 0.0},
        {'name': 'Cur_CruisingThrottle', 'value': 0.0},
        {'name': 'Cur_Valid', 'value': 1},
        {'name': 'Cur_Type', 'value': 0},
        {'name': 'Cur_PositionValid', 'value': 0},
        {'name': 'Cur_VelocityValid', 'value': 0},
        {'name': 'Cur_YawValid', 'value': 0},
        {'name': 'Cur_DisableMcYawControl', 'value': 0},
        {'name': 'Cur_YawspeedValid', 'value': 0},
        {'name': 'Cur_LoiterDirection', 'value': 0},
        {'name': 'Cur_AccelerationValid', 'value': 0},
        {'name': 'Cur_AccelerationIsForce', 'value': 0},
        {'name': 'Next_Lat', 'value': 0.0},
        {'name': 'Next_Lon', 'value': 0.0},
        {'name': 'Next_X', 'value': 0.0},
        {'name': 'Next_Y', 'value': 0.0},
        {'name': 'Next_Z', 'value': 0.0},
        {'name': 'Next_VX', 'value': 0.0},
        {'name': 'Next_VY', 'value': 0.0},
        {'name': 'Next_VZ', 'value': 0.0},
        {'name': 'Next_Alt', 'value': 0.0},
        {'name': 'Next_Yaw', 'value': 0.0},
        {'name': 'Next_Yawspeed', 'value': 0.0},
        {'name': 'Next_LoiterRadius', 'value': 0.0},
        {'name': 'Next_PitchMin', 'value': 0.0},
        {'name': 'Next_AX', 'value': 0.0},
        {'name': 'Next_AY', 'value': 0.0},
        {'name': 'Next_AZ', 'value': 0.0},
        {'name': 'Next_AcceptanceRadius', 'value': 0.0},
        {'name': 'Next_CruisingSpeed', 'value': 0.0},
        {'name': 'Next_CruisingThrottle', 'value': 0.0},
        {'name': 'Next_Valid', 'value': 0},
        {'name': 'Next_Type', 'value': 0},
        {'name': 'Next_PositionValid', 'value': 0},
        {'name': 'Next_VelocityValid', 'value': 0},
        {'name': 'Next_YawValid', 'value': 0},
        {'name': 'Next_DisableMcYawControl', 'value': 0},
        {'name': 'Next_YawspeedValid', 'value': 0},
        {'name': 'Next_LoiterDirection', 'value': 0},
        {'name': 'Next_AccelerationValid', 'value': 0},
        {'name': 'Next_AccelerationIsForce', 'value': 0}]})


print rocky.tlm_value("/Airliner/CNTL/SetpointTriplet/Cur_Lat")


def wait():
    print('Waiting')


rocky.await_change("/Airliner/CNTL/SetpointTriplet/Cur_Lat", out=wait)
print rocky.tlm_value("/Airliner/CNTL/SetpointTriplet/Cur_Lat")
