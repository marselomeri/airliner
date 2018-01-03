from flask import Flask
from flask_sockets import Sockets
from multiprocessing import Process
import time,psutil




app = Flask(__name__)
sockets = Sockets(app)

server = None
pid = None
hist_messages = []

data = '[1,4,9,{"dt":"PARAMETER","data":{"parameter":[{"id":{"name":"/CFS/DS/CmdAcceptedCounter"},"rawValue":{"type":"UINT32","uint32Value":0},"engValue":{"type":"UINT32","uint32Value":0},"acquisitionTime":1514407805707,"generationTime":316968547101,"acquisitionStatus":"ACQUIRED","processingStatus":true,"acquisitionTimeUTC":"2017-12-27T20:49:28.707","generationTimeUTC":"1980-01-17T14:48:48.101","expirationTime":1514407807207,"expirationTimeUTC":"2017-12-27T20:49:30.207"}]}}]'


@sockets.route('/softsim/_websocket')
def echo_socket(ws):
        global server,current_message
        message = ws.receive()
        hist_messages.append(message)
        #print message
        ws.send(data)
        #server.close()



@app.route('/')
def hello():
    return 'Hello World!'

def start():
    global server,pid
    from gevent import pywsgi
    from geventwebsocket.handler import WebSocketHandler
    server = pywsgi.WSGIServer(('localhost', 8090), app, handler_class=WebSocketHandler)

    #print 'YAMCS MOCK SERVER STARTED!', server
    process = Process(target=server.serve_forever)
    process.start()
    pid = process.pid


def kill():
    global server,pid
    server.close()

    to_kill = psutil.Process(pid)
    to_kill.kill()
    #print 'YAMCS MOCK SERVER CLOSED!', server

def getMessage():
    global hist_messages
    return hist_messages

