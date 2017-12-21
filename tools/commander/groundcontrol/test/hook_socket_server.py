
from websocket_server import WebsocketServer
skip =200
thres = 1000

count = 0
count2 = 0
name = 'channel_8_10000'
open(name+'.txt','w').close()
f = open(name+'.txt','w')

def printer(client, server,message):
    global count,count2,thres,f,skip

    if count2>skip:
        if count<=thres and message != 'connected':
            print message , count
            f.write(message)
            f.write("\n")
        elif message == 'connected':
            print 'connected'
        else:
            print '---end---'
            f.close()
        count += 1
    count2 +=1
    print 'just' + message

def new_client(client, server):
	server.send_message_to_all("Hey all, a new client has joined us")

server = WebsocketServer(7000, host='localhost')
server.set_fn_new_client(new_client)
server.set_fn_message_received(printer)
server.run_forever()
