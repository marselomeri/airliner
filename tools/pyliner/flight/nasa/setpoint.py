from os import sys
from os.path import join, dirname, abspath
sys.path.append(dirname(dirname(dirname(abspath(__file__)))))
from pyliner import Pyliner
from flight_control_lib import *
import math
import time



def vehicle_spiral_ccw():
    rocky.send_telemetry(
        {'name':'/Airliner/CNTL/ManualSetpoint', 'args':[
        {'name':'Timestamp', 'value':rocky.get_time()},
        {'name':'X', 'value':0.0},
        {'name':'Y', 'value':0.65},
        {'name':'Z', 'value':0.65},
        {'name':'R', 'value':-0.35},
        {'name':'Flaps', 'value':0.0},
        {'name':'Aux1', 'value':0.0},
        {'name':'Aux2', 'value':0.0},
        {'name':'Aux3', 'value':0.0},
        {'name':'Aux4', 'value':0.0},
        {'name':'Aux5', 'value':0.0},
        {'name':'ModeSwitch', 'value':0},
        {'name':'ReturnSwitch', 'value':0},
        {'name':'RattitudeSwitch', 'value':0},
        {'name':'PosctlSwitch', 'value':1},
        {'name':'LoiterSwitch', 'value':0},
        {'name':'AcroSwitch', 'value':0},
        {'name':'OffboardSwitch', 'value':0},
        {'name':'KillSwitch', 'value':0},
        {'name':'TransitionSwitch', 'value':0},
        {'name':'GearSwitch', 'value':0},
        {'name':'ArmSwitch', 'value':1},
        {'name':'StabSwitch', 'value':0},
        {'name':'ManSwitch', 'value':0},
        {'name':'ModeSlot', 'value':0},
        {'name':'DataSource', 'value':0}]})
        
def  vehicle_fly_spiral_ccw(deltaZ):
    print "Fly spiral CCW and up " + str(deltaZ) +" meters"
    initial_altitude = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
    print "Initial altitude: " + str(initial_altitude)
    current_altitude = initial_altitude
    while(current_altitude < (initial_altitude + deltaZ)):
        vehicle_spiral_ccw()
        time.sleep(1.0)
        current_altitude = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
        print "Current altitude: " + str(current_altitude)
    vehicle_stable_hover(rocky)
    time.sleep(1)


# Initialize pyliner object
rocky = Pyliner(**{"airliner_map": join(dirname(abspath(__file__)), "cookiecutter.json"), 
                   "ci_port": 5009,
                   "to_port": 5012,
                   "script_name": "FT6_GCS",
                   "log_dir": join(dirname(abspath(__file__)), "logs")})

# Subscribe to desired telemetry
rocky.subscribe({'tlm': ['/Airliner/CNTL/VehicleGlobalPosition/Lat',
                         '/Airliner/CNTL/VehicleGlobalPosition/Lon',
                         '/Airliner/CNTL/VehicleGlobalPosition/Alt',
                         '/Airliner/CNTL/VehicleGlobalPosition/Yaw',
                         '/Airliner/CNTL/VehicleGlobalPosition/VelN',
                         '/Airliner/CNTL/VehicleGlobalPosition/VelE',
                         '/Airliner/CNTL/VehicleGlobalPosition/VelD',
                         '/Airliner/CNTL/SetpointTriplet/Timestamp']})

# Wait for pyliner data dictionary to populate with initial values
while rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt') == 'NULL':
    print "Waiting for telemetry downlink..."
    time.sleep(1)
    
alt = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
print "Alt: " + str(alt)

atp(rocky, "Arm")
vehicle_arm(rocky)

atp(rocky, "Takeoff")
vehicle_takeoff(rocky)
vehicle_flight_mode(rocky, FlightMode.PosCtl)

alt = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
print "Alt: " + str(alt)

atp(rocky, "Move up")
vehicle_move(rocky, Direction.Up, speed = .85, time = 1, stop = True, stop_wait = 3)

alt = rocky.get_tlm_value('/Airliner/CNTL/VehicleGlobalPosition/Alt')
print "Alt: " + str(alt)

rocky.send_telemetry(
    {'name':'/Airliner/CNTL/SetpointTriplet', 'args':[
    {'name':'Timestamp', 'value':rocky.get_time()},
    {'name':'Prev_Lat', 'value':0.0},
    {'name':'Prev_Lon', 'value':0.0},
    {'name':'Prev_X', 'value':0.0},
    {'name':'Prev_Y', 'value':0.0},
    {'name':'Prev_Z', 'value':0.0},
    {'name':'Prev_VX', 'value':0.0},
    {'name':'Prev_VY', 'value':0.0},
    {'name':'Prev_VZ', 'value':0.0},
    {'name':'Prev_Alt', 'value':0.0},
    {'name':'Prev_Yaw', 'value':0.0},
    {'name':'Prev_Yawspeed', 'value':0.0},
    {'name':'Prev_LoiterRadius', 'value':0.0},
    {'name':'Prev_PitchMin', 'value':0.0},
    {'name':'Prev_AX', 'value':0.0},
    {'name':'Prev_AY', 'value':0.0},
    {'name':'Prev_AZ', 'value':0.0},
    {'name':'Prev_AcceptanceRadius', 'value':0.0},
    {'name':'Prev_CruisingSpeed', 'value':0.0},
    {'name':'Prev_CruisingThrottle', 'value':0.0},
    {'name':'Prev_Valid', 'value':0},
    {'name':'Prev_Type', 'value':0},
    {'name':'Prev_PositionValid', 'value':0},
    {'name':'Prev_VelocityValid', 'value':0},
    {'name':'Prev_YawValid', 'value':0},
    {'name':'Prev_DisableMcYawControl', 'value':0},
    {'name':'Prev_YawspeedValid', 'value':0},
    {'name':'Prev_LoiterDirection', 'value':0},
    {'name':'Prev_AccelerationValid', 'value':0},
    {'name':'Prev_AccelerationIsForce', 'value':0},
    {'name':'Cur_Lat', 'value':45.0},
    {'name':'Cur_Lon', 'value':45.0},
    {'name':'Cur_X', 'value':0.0},
    {'name':'Cur_Y', 'value':0.0},
    {'name':'Cur_Z', 'value':0.0},
    {'name':'Cur_VX', 'value':0.0},
    {'name':'Cur_VY', 'value':0.0},
    {'name':'Cur_VZ', 'value':0.0},
    {'name':'Cur_Alt', 'value':0.0},
    {'name':'Cur_Yaw', 'value':0.0},
    {'name':'Cur_Yawspeed', 'value':0.0},
    {'name':'Cur_LoiterRadius', 'value':0.0},
    {'name':'Cur_PitchMin', 'value':0.0},
    {'name':'Cur_AX', 'value':0.0},
    {'name':'Cur_AY', 'value':0.0},
    {'name':'Cur_AZ', 'value':0.0},
    {'name':'Cur_AcceptanceRadius', 'value':0.0},
    {'name':'Cur_CruisingSpeed', 'value':0.0},
    {'name':'Cur_CruisingThrottle', 'value':0.0},
    {'name':'Cur_Valid', 'value':1},
    {'name':'Cur_Type', 'value':0},
    {'name':'Cur_PositionValid', 'value':0},
    {'name':'Cur_VelocityValid', 'value':0},
    {'name':'Cur_YawValid', 'value':0},
    {'name':'Cur_DisableMcYawControl', 'value':0},
    {'name':'Cur_YawspeedValid', 'value':0},
    {'name':'Cur_LoiterDirection', 'value':0},
    {'name':'Cur_AccelerationValid', 'value':0},
    {'name':'Cur_AccelerationIsForce', 'value':0},
    {'name':'Next_Lat', 'value':0.0},
    {'name':'Next_Lon', 'value':0.0},
    {'name':'Next_X', 'value':0.0},
    {'name':'Next_Y', 'value':0.0},
    {'name':'Next_Z', 'value':0.0},
    {'name':'Next_VX', 'value':0.0},
    {'name':'Next_VY', 'value':0.0},
    {'name':'Next_VZ', 'value':0.0},
    {'name':'Next_Alt', 'value':0.0},
    {'name':'Next_Yaw', 'value':0.0},
    {'name':'Next_Yawspeed', 'value':0.0},
    {'name':'Next_LoiterRadius', 'value':0.0},
    {'name':'Next_PitchMin', 'value':0.0},
    {'name':'Next_AX', 'value':0.0},
    {'name':'Next_AY', 'value':0.0},
    {'name':'Next_AZ', 'value':0.0},
    {'name':'Next_AcceptanceRadius', 'value':0.0},
    {'name':'Next_CruisingSpeed', 'value':0.0},
    {'name':'Next_CruisingThrottle', 'value':0.0},
    {'name':'Next_Valid', 'value':0},
    {'name':'Next_Type', 'value':0},
    {'name':'Next_PositionValid', 'value':0},
    {'name':'Next_VelocityValid', 'value':0},
    {'name':'Next_YawValid', 'value':0},
    {'name':'Next_DisableMcYawControl', 'value':0},
    {'name':'Next_YawspeedValid', 'value':0},
    {'name':'Next_LoiterDirection', 'value':0},
    {'name':'Next_AccelerationValid', 'value':0},
    {'name':'Next_AccelerationIsForce', 'value':0}]})


#atp(rocky, "Fly spiral")
#vehicle_fly_spiral_ccw(10)

#atp(rocky, "Move forward")
#vehicle_move(rocky, Direction.Forward, speed = .75, time = 2, stop = True, stop_wait = 3)
#atp(rocky, "Move left")
#vehicle_move(rocky, Direction.Left, speed = .75, time = 2, stop = True, stop_wait = 3)
#atp(rocky, "Move backward")
#vehicle_move(rocky, Direction.Backward, speed = .75, time = 2, stop = True, stop_wait = 3)
#atp(rocky, "Move right")
#vehicle_move(rocky, Direction.Right, speed = .75, time = 2, stop = True, stop_wait = 3)

atp(rocky, "RTL")
vehicle_rtl(rocky)
