import pyliner
import time

airliner = pyliner.Pyliner(**{"airliner_map": "cookiecutter.json"})

#airliner.send_command({'name':'Airliner/Steve/Noop'})

flag = True
while True:
    time.sleep(1)
    if flag:
        flag = True
        airliner.send_command({'name':'Airliner/Steve/OverwriteSysLog', 'args':[
                             {'name':'Payload.Mode', 'value':'1'}]})
    else:
        flag = False
        airliner.send_command({'name':'Airliner/Steve/OverwriteSysLog', 'args':[
                             {'name':'Payload.Mode', 'value':'0'}]})

