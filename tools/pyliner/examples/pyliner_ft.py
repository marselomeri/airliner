from os import path, sys
sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
from pyliner import Pyliner
import time

# Initialize pyliner object
airliner = Pyliner(**{"airliner_map": "cookiecutter_fc.json", 
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
                             {'name':'Lat', 'value':},
                             {'name':'Lon', 'value':1},
                             {'name':'X', 'value':1},
                             {'name':'Y', 'value':1},
                             {'name':'Z', 'value':1},
                             {'name':'VX', 'value':1},
                             {'name':'VY', 'value':1},
                             {'name':'VZ', 'value':1},
                             {'name':'Alt', 'value':1},
                             {'name':'Yaw', 'value':1},
                             {'name':'Yawspeed', 'value':1},
                             {'name':'LoiterRadius', 'value':1},
                             {'name':'PitchMin', 'value':1},
                             {'name':'A_X', 'value':1},
                             {'name':'A_Y', 'value':1},
                             {'name':'A_Z', 'value':1},
                             {'name':'AcceptanceRadius', 'value':1},
                             {'name':'CruisingSpeed', 'value':1},
                             {'name':'CruisingThrottle', 'value':1},
                             {'name':'Valid', 'value':1},
                             {'name':'Type', 'value':1},
                             {'name':'PositionValid', 'value':1},
                             {'name':'VelocityValid', 'value':1},
                             {'name':'YawValid', 'value':1},
                             {'name':'DisableMcYawControl', 'value':1},
                             {'name':'YawspeedValid', 'value':1},
                             {'name':'LoiterDirection', 'value':1},
                             {'name':'AccelerationValid', 'value':1},
                             {'name':'AccelerationIsForce', 'value':1}]})
                             
    # Sleep for duration of a major frame
    time.sleep(1)
