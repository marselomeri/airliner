import pyliner
import time

# Callback 1
def cb_1(data):
    print "Cmd counter: " + str(data['params']['CmdCounter']['value'])
    
# Callback 2
def cb_2(data):
    print "Log mode: " + str(data['params']['SysLogMode']['value'])
    
# Callback 3
def cb_3(data):
    print "Max processor resets: " + str(data['params']['MaxProcessorResets']['value'])

# Callback 4
def cb_4(data):
    print "Log size: " + str(data['params']['SysLogBytesUsed']['value'])
    print "Log entries: " + str(data['params']['SysLogEntries']['value'])



# Initialize pyliner object
airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json"})

# Subscribe to desired telemetry for our callbacks
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]}, cb_1)                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogMode'}]}, cb_2)                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'MaxProcessorResets'}]}, cb_3)
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogBytesUsed'}, {'name':'SysLogEntries'}]}, cb_4)

# Start sending commands
for i in range(250):
    # Noop
    airliner.send_command({'name':'/Airliner/ES/Noop'})
    
    # Set max cpu resets equal to loop iteration
    airliner.send_command({'name':'/Airliner/ES/SetMaxPRCount', 'args':[
                                 {'name':'MaxProcResets', 'value':i}]})
    # At 15 iterations clear logs
    if i == 15:
        airliner.send_command({'name':'/Airliner/ES/ClearSysLog'})
        airliner.send_command({'name':'/Airliner/ES/ClearERLog'})
    
    # Switch log mode on even/odd iterations
    if i % 2 == 0:
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':1}]})
    else:
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':0}]})
    print ""
    time.sleep(1)

