from os import path, sys
sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
from pyliner import Pyliner
import time

# Initialize pyliner object
airliner = Pyliner(**{"airliner_map": "cookiecutter.json", 
                      "ci_port": 5009,
                      "to_port": 5012,
                      "script_name": "demo_test",
                      "log_dir": "./logs/"})

# Subscribe to desired telemetry
#airliner.subscribe({'tlm': []})

# Perform 15 batches of sending commands and receiving telemetry
for i in range(15):
    # Print all data for CmdCounter
    #print "Telemetry: %s   Value: %s   Timestamp: %s" % (cmd_count_data['name'], cmd_count_data['value'], cmd_count_data['time'])
    
    # Get just the value of other subscribed items
    #log_mode = airliner.get_tlm_value('/Airliner/ES/HK/SysLogMode')
    

    # Print the fresh telemetry values
    #print "Log mode: " + str(log_mode)

    # Send NoOp command

    airliner.send_command({'name':'/Airliner/CNTL/SetpointTriplet', 'args':[
                             {'name':'Prev_Lat', 'value':1.0},
                             {'name':'Prev_Lon', 'value':1.0},
                             {'name':'Prev_X', 'value':1.0},
                             {'name':'Prev_Y', 'value':1.0},
                             {'name':'Prev_Z', 'value':1.0},
                             {'name':'Prev_VX', 'value':1.0},
                             {'name':'Prev_VY', 'value':1.0},
                             {'name':'Prev_VZ', 'value':1.0},
                             {'name':'Prev_Alt', 'value':1.0},
                             {'name':'Prev_Yaw', 'value':1.0},
                             {'name':'Prev_Yawspeed', 'value':1.0},
                             {'name':'Prev_LoiterRadius', 'value':1.0},
                             {'name':'Prev_PitchMin', 'value':1.0},
                             {'name':'Prev_AX', 'value':1.0},
                             {'name':'Prev_AY', 'value':1.0},
                             {'name':'Prev_AZ', 'value':1.0},
                             {'name':'Prev_AcceptanceRadius', 'value':1.0},
                             {'name':'Prev_CruisingSpeed', 'value':1.0},
                             {'name':'Prev_CruisingThrottle', 'value':1.0},
                             {'name':'Prev_Valid', 'value':True},
                             {'name':'Prev_Type', 'value':1},
                             {'name':'Prev_PositionValid', 'value':True},
                             {'name':'Prev_VelocityValid', 'value':True},
                             {'name':'Prev_YawValid', 'value':True},
                             {'name':'Prev_DisableMcYawControl', 'value':True},
                             {'name':'Prev_YawspeedValid', 'value':True},
                             {'name':'Prev_LoiterDirection', 'value':1},
                             {'name':'Prev_AccelerationValid', 'value':True},
                             {'name':'Prev_AccelerationIsForce', 'value':True},
                             {'name':'Cur_Lat', 'value':1.0},
                             {'name':'Cur_Lon', 'value':1.0},
                             {'name':'Cur_X', 'value':1.0},
                             {'name':'Cur_Y', 'value':1.0},
                             {'name':'Cur_Z', 'value':1.0},
                             {'name':'Cur_VX', 'value':1.0},
                             {'name':'Cur_VY', 'value':1.0},
                             {'name':'Cur_VZ', 'value':1.0},
                             {'name':'Cur_Alt', 'value':1.0},
                             {'name':'Cur_Yaw', 'value':1.0},
                             {'name':'Cur_Yawspeed', 'value':1.0},
                             {'name':'Cur_LoiterRadius', 'value':1.0},
                             {'name':'Cur_PitchMin', 'value':1.0},
                             {'name':'Cur_AX', 'value':1.0},
                             {'name':'Cur_AY', 'value':1.0},
                             {'name':'Cur_AZ', 'value':1.0},
                             {'name':'Cur_AcceptanceRadius', 'value':1.0},
                             {'name':'Cur_CruisingSpeed', 'value':1.0},
                             {'name':'Cur_CruisingThrottle', 'value':1.0},
                             {'name':'Cur_Valid', 'value':True},
                             {'name':'Cur_Type', 'value':1},
                             {'name':'Cur_PositionValid', 'value':True},
                             {'name':'Cur_VelocityValid', 'value':True},
                             {'name':'Cur_YawValid', 'value':True},
                             {'name':'Cur_DisableMcYawControl', 'value':True},
                             {'name':'Cur_YawspeedValid', 'value':True},
                             {'name':'Cur_LoiterDirection', 'value':1},
                             {'name':'Cur_AccelerationValid', 'value':True},
                             {'name':'Cur_AccelerationIsForce', 'value':True},
                             {'name':'Next_Lat', 'value':1.0},
                             {'name':'Next_Lon', 'value':1.0},
                             {'name':'Next_X', 'value':1.0},
                             {'name':'Next_Y', 'value':1.0},
                             {'name':'Next_Z', 'value':1.0},
                             {'name':'Next_VX', 'value':1.0},
                             {'name':'Next_VY', 'value':1.0},
                             {'name':'Next_VZ', 'value':1.0},
                             {'name':'Next_Alt', 'value':1.0},
                             {'name':'Next_Yaw', 'value':1.0},
                             {'name':'Next_Yawspeed', 'value':1.0},
                             {'name':'Next_LoiterRadius', 'value':1.0},
                             {'name':'Next_PitchMin', 'value':1.0},
                             {'name':'Next_AX', 'value':1.0},
                             {'name':'Next_AY', 'value':1.0},
                             {'name':'Next_AZ', 'value':1.0},
                             {'name':'Next_AcceptanceRadius', 'value':1.0},
                             {'name':'Next_CruisingSpeed', 'value':1.0},
                             {'name':'Next_CruisingThrottle', 'value':1.0},
                             {'name':'Next_Valid', 'value':True},
                             {'name':'Next_Type', 'value':1},
                             {'name':'Next_PositionValid', 'value':True},
                             {'name':'Next_VelocityValid', 'value':True},
                             {'name':'Next_YawValid', 'value':True},
                             {'name':'Next_DisableMcYawControl', 'value':True},
                             {'name':'Next_YawspeedValid', 'value':True},
                             {'name':'Next_LoiterDirection', 'value':1},
                             {'name':'Next_AccelerationValid', 'value':True},
                             {'name':'Next_AccelerationIsForce', 'value':True},
                             {'name':'Timestamp', 'value':0}




]})
                             
    # Sleep for duration of a major frame
    time.sleep(1)
