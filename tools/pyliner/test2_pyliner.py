import pyliner
import time
max_pr = 0
def cb_1(data):
    print "CmdCounter: " + str(data['params']['CmdCounter']['value'])
    print ""
    
def cb_2(data):
    print "SysLogMode: " + str(data['params']['SysLogMode']['value'])
    print ""
    
def cb_3(data):
    max_pr = data['params']['MaxProcessorResets']['value'] + 1
    print "MaxProcessorResets: " + str(data['params']['MaxProcessorResets']['value'])
    print ""

airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json"})

#max_pr = 0
flag = True

airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'CmdCounter'}]}, cb_1)
                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'SysLogMode'}]}, cb_2)
                         
airliner.subscribe({'name': '/Airliner/ES/HK', 'args':[{'name':'MaxProcessorResets'}]}, cb_3)

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

