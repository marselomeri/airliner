import pyliner
import time

airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json"})

max_pr = 0
flag = True

while True:
    airliner.send_command({'name':'/Airliner/ES/Noop'})
    airliner.send_command({'name':'/Airliner/ES/SetMaxPRCount', 'args':[
                                 {'name':'Payload.MaxPRCount', 'value':max_pr}]})
    if max_pr == 15:                
        airliner.send_command({'name':'/Airliner/ES/ClearSysLog'})
        airliner.send_command({'name':'/Airliner/ES/ClearERLog'})
                                 
    if flag:
        flag = False
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'Payload.Mode', 'value':1}]})
    else:
        flag = True
        airliner.send_command({'name':'/Airliner/ES/OverwriteSysLog', 'args':[
                             {'name':'Payload.Mode', 'value':0}]})
                             
    max_pr += 1
    time.sleep(2)

