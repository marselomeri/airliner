import pyliner
import time

global cmd_count
cmd_count = 0
log_mode = 0
max_pr = 0
log_size = 0
log_entries = 0

# Callback 1
def cb_1(data):
    #print data
    cmd_count = data['params']['CmdCounter']['value']
    print "Cmd counter: " + str(cmd_count)
    
# Callback 2
def cb_2(data):
    log_mode = data['params']['SysLogMode']['value']
    print "Log mode: " + str(log_mode)
    
# Callback 3
def cb_3(data):
    max_pr = data['params']['MaxProcessorResets']['value']
    print "Max processor resets: " + str(max_pr)

# Callback 4
def cb_4(data):
    log_size = data['params']['SysLogBytesUsed']['value']
    log_entries = data['params']['SysLogEntries']['value']
    print "Log size: " + str(log_size)
    print "Log entries: " + str(log_entries)



# Initialize pyliner object
airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json", "test_name": "demo_test"})

# Subscribe to desired telemetry for our callbacks
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]}, cb_1)                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogMode'}]}, cb_2)                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'MaxProcessorResets'}]}, cb_3)
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogBytesUsed'}, {'name':'SysLogEntries'}]}, cb_4)
print airliner.log_name
# Start sending commands
for i in range(10):
    print "AAAAAAAAAAAAAAAAAAA: " + str(cmd_count)
    airliner.assert_equals(1,1)
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
    time.sleep(1)

airliner.finish_test()

