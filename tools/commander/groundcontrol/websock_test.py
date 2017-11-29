from websocket import create_connection
#"""
"""
d = '[1,1,0, {"parameter":"subscribe", "data":{"list":[{"name": "/CFS/DS/CmdAcceptedCounter"}]}}]'
ws = create_connection('ws://127.0.0.1:8090/softsim/_websocket')
d2 = '[1,1,0, {"parameter":"unsubscribe", "data":{"list":[{"name": "/CFS/DS/CmdAcceptedCounter"}]}}]'

ws.send(str(d))
i=0
while True:

    try:
        print ws.next()
    except:
        break

    if i ==5:
        ws.send(str(d2))
        ws.abort()
        #ws.send_close(500, 'hello')

    i = i + 1
"""
#"""