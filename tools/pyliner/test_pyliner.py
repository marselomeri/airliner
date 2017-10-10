import pyliner
import time

def cb(data):
    #print data
    print "CmdCounter: " + str(data['params']['CmdCounter']['value'])
    print "SysLogMode: " + str(data['params']['SysLogMode']['value'])
    print "MaxProcessorResets: " + str(data['params']['MaxProcessorResets']['value'])
    print ""

airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json"})

max_pr = 0
flag = True

airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[
                         {'name':'CmdCounter'}, {'name':'SysLogMode'}, {'name':'MaxProcessorResets'}]}, cb)

while True:
    airliner.send_command({'name':'/Airliner/ES/Noop'})
    airliner.send_command({'name':'/Airliner/ES/SetMaxPRCount', 'args':[
                                 {'name':'MaxProcResets', 'value':max_pr}]})
    if max_pr == 15:                
        airliner.send_command({'name':'/Airliner/ES/ClearSysLog'})
        airliner.send_command({'name':'/Airliner/ES/ClearERLog'})
                                 
    if flag:
        flag = False
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':1}]})
    else:
        flag = True
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'OverwriteMode', 'value':0}]})
                             
    max_pr += 1
    time.sleep(1)

