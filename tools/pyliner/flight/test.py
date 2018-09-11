

from pyliner import Vehicle
from pyliner.apps.communication import Communication
from pyliner.scripting_wrapper import ScriptingWrapper
from pyliner.util import read_json
from pyliner.telemetry import Telemetry
import time


cmd_count = 0

def cmd_count_callback1(data):
    print("1 %s = %d   " % (data.name, data.value))
    
    #global cmd_count
    #cmd_count = data['params']['CmdCounter']['value']
    #print "Cmd counter: " + str(cmd_count)
    #recv_frame = client.sequence
    #print "Cmd processed in %s frames" % (recv_frame - sent_frame)

def cmd_count_callback2(data):
    print("2 %s = %d   " % (data.name, data.value))

def cmd_err_callback1(data):
    print("3 %s = %d   " % (data.name, data.value))
    print("*2 %s = %d   " % (cmdCounter2.name, cmdCounter2.value))
    print(cmdCounter4.value)
    #print("*4 %s = %d   " % (cmdCounter4.name, cmdCounter4.value))
    
vehicle = Vehicle(
    vehicle_id='rocky',
    communication=Communication(
        airliner_map=read_json("airliner.json"),
        address="127.0.0.1",
        ci_port=5009,
        to_port=5012)
)

with ScriptingWrapper(vehicle) as v:
    #v.await_change('/Airliner/ES/HK/CmdCounter',
    #                   'Waiting for telemetry downlink...')
    
    cmdCounter4 = v.com.subscribe('/Airliner/CFE/ES_HK/CmdCounter', cmd_count_callback1)
    
    v.com.send_command({'name':'/Airliner/CFE/ES_Noop'})
    
    v.com.send_command(Telemetry('/Airliner/CFE/ES_Noop'))
    
    v.com.send_command({'name':'/Airliner/CFE/SetMaxPRCount', 'args':[
                             {'name':'MaxPRCount', 'value':2}]})
    
    time.sleep( 2 )
    
    cmdCounter2 = v.com.telemetry('/Airliner/CFE/ES_HK/CmdCounter')
    cmdCounter2.add_listener(cmd_count_callback2)
    
    cmdErr1 = v.com.telemetry('/Airliner/CFE/ES_HK/ErrCounter')
    cmdErr1.add_listener(cmd_err_callback1)
        
    time.sleep( 1000000000 )
    
