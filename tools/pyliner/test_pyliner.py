import pyliner
import time

cmd_count = 0
log_mode = 0
max_pr = 0
log_size = 0
log_entries = 0

# Callback 1
def cb_1(data):
    global cmd_count
    cmd_count = data['params']['CmdCounter']['value']
    
# Callback 2
def cb_2(data):
    global log_mode
    log_mode = data['params']['SysLogMode']['value']
    
# Callback 3
def cb_3(data):
    global max_pr
    max_pr = data['params']['MaxProcessorResets']['value']

# Callback 4
def cb_4(data):
    global log_size
    global log_entries
    log_size = data['params']['SysLogBytesUsed']['value']
    log_entries = data['params']['SysLogEntries']['value']


# Initialize pyliner object
airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json", "test_name": "demo_test"})

# Subscribe to desired telemetry for our callbacks
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]}, cb_1)                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogMode'}]}, cb_2)                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'MaxProcessorResets'}]}, cb_3)
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogBytesUsed'}, {'name':'SysLogEntries'}]}, cb_4)

# Reset everything
airliner.send_command({'name':'/Airliner/ES/SetMaxPRCount', 'args':[
                                 {'name':'MaxProcResets', 'value':0}]})
airliner.send_command({'name':'/Airliner/ES/Reset'})

# Send Noop
airliner.send_command({'name':'/Airliner/ES/Noop'})
time.sleep(1)
airliner.assert_equals(cmd_count, 1)

# Start sending commands
for i in range(1, 11):
    airliner.assert_equals(max_pr, i-1)

    # Set max cpu resets equal to loop iteration
    airliner.send_command({'name':'/Airliner/ES/SetMaxPRCount', 'args':[
                                 {'name':'MaxProcResets', 'value':i}]})

    # Switch log mode on even/odd iterations
    if i % 2 == 0:
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':1}]})
    else:
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':0}]})
    
    time.sleep(1)
    
# End test
airliner.finish_test()
