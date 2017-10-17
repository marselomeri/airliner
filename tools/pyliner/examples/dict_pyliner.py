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
airliner.subscribe({'tlm': ['/Airliner/ES/HK/CmdCounter',
                            '/Airliner/ES/HK/SysLogMode', 
                            '/Airliner/ES/HK/MaxProcessorResets', 
                            '/Airliner/ES/HK/SysLogBytesUsed', 
                            '/Airliner/ES/HK/SysLogEntries']})

# Start sending commands
for i in range(15):
    cmd_count = airliner.telemetry['/Airliner/ES/HK/CmdCounter']['value']
    log_mode = airliner.telemetry['/Airliner/ES/HK/SysLogMode']['value']
    max_pr = airliner.telemetry['/Airliner/ES/HK/MaxProcessorResets']['value']
    log_size = airliner.telemetry['/Airliner/ES/HK/SysLogBytesUsed']['value']
    log_entries = airliner.telemetry['/Airliner/ES/HK/SysLogEntries']['value']

    print "Cmd counter: " + str(cmd_count)
    print "Log mode: " + str(log_mode)
    print "Max processor resets: " + str(max_pr)
    print "Log size: " + str(log_size)
    print "Log entries: " + str(log_entries)

    # Noop
    airliner.send_command({'name':'/Airliner/ES/Noop'})
    
    # Set max cpu resets equal to loop iteration
    airliner.send_command({'name':'/Airliner/ES/SetMaxPRCount', 'args':[
                                 {'name':'MaxProcResets', 'value':i}]})
    # At 10 iterations clear logs
    if i == 10:
        airliner.send_command({'name':'/Airliner/ES/ClearSysLog'})
        airliner.send_command({'name':'/Airliner/ES/ClearERLog'})
    
    # Switch log mode on even/odd iterations
    if i % 2 == 0:
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':1}]})
    else:
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':0}]})
                             
    time.sleep(1)
