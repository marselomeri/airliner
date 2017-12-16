from channels import Group
import toolkit as tk
import socket
import time
import datetime
import base64
import urllib,json,os
from websocket import create_connection
from channels.generic import BaseConsumer

from threading import Thread

# any user who will be using commander will be added to users

class IO:

    def __init__(self,instance,socket_name,address,port):
        self.socket_name = socket_name
        self.instance = instance
        self.address = address
        self.port = port
        self.isConnActive = True
        self.counter = 0


    def connect(self,message):
        self.isConnActive = True
        message.reply_channel.send({'accept': True})
        tk.log(self.socket_name,'CONNETED TO IO','INFO')



    def disconnect(self,message):
        self.isConnActive = False
        message.reply_channel.send({'close': True})
        tk.log(self.socket_name, 'DISCONNECTED FROM IO', 'INFO')

    def get(self):
        pass
    def post(self):
        pass


    def subscribe(self,message):

        message_text = message.content['text']


        if message_text == 'START_COMM_HS':
            tk.log(self.socket_name, 'GOT HS SIGNAL FROM CLIENT', 'INFO')
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            tk.log(self.socket_name, 'GOT CLOSE SIGNAL FROM CLIENT', 'INFO')
            self.unsubscribe()
        else:
            received = ''
            to_send = ''

            if self.socket_name == 'PARAMETER':
                temp = tk.byteify(message_text)
                temp = json.loads(temp)
                temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'


            elif self.socket_name == 'EVENT':
                temp = '{"events": "subscribe"}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'

            elif self.socket_name == 'EVENT':
                temp = '{"alarms": "subscribe"}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'
            #while True:
            ws = create_connection('ws://' + self.address + ':' + self.port + '/' + self.instance + '/_websocket')
            ws.send(to_send)
            ## LAUNCING THREADS
            t = Thread(target=self.special_looping_over, args=[ws, message,self.counter])
            t.start()
            #while True:#self.isConnActive:
            #    result = ws.recv()
            #    print result
            #    if result != '[1,2,'+str(self.counter)+']':
            #        result = tk.preProcess(result)
            #        message.reply_channel.send({'text': result})
            #        tk.log(self.socket_name, 'BOUND', 'INFO')




    def unsubscribe(self):
        self.disconnect()

    def sokcetPost(self):
        pass

    def directoryListing(self,message):
        name = message.content['text']
        print '[' + tk.getDate() + ']' + name
        if name == 'START_COMM_HS':
            # Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            print '[' + tk.getDate() + ']' + ' Server disconnecting...'
        else:
            response = tk.get_directory(name)
            data = json.dumps(response)
            # Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': data})
            print '[' + tk.getDate() + ']' + ' Packet ' + name + ' sent.'

    def special_looping_over(self,websocket_obj,message_obj,counter):
        while self.isConnActive:
            result = websocket_obj.recv()
            print result
            if result != '[1,2,' + str(counter) + ']':
                result = tk.preProcess(result)
                message_obj.reply_channel.send({'text': result})
                tk.log(self.socket_name, 'BOUND', 'INFO')











class ServerSession:

    def __init__(self):
        #SESSION VARIABLES
        self.activeInstances = []
        self.subscribers = []
        self.defaultInstance = None
        self.cmdSeqNum = 0
        self.tlmSeqNum = 0

        #WEBSOCKET VARIABLES
        self.port = 8090
        self.address = '127.0.0.1'

        #UNKNOWN VARIABLES
        self.ClientProxy = None
        self.tlmBypass = None

        #DATA VARIABLES
        self.video_port = 3001
        self.video_frame_counter = 0
        self.video_socket = None
        self.data1 = None
        self.SLUG_DICTIONARY = {
            'getInstances': '/api/instances',
            'getCommands': '/api/mdb/softsim/commands',
        }



    def connect(self,message):
        message.reply_channel.send({'accept': True})
        tk.log('','CONNETED TO IO','INFO')

    def disconnect(self,message):
        message.reply_channel.send({'close': True})
        tk.log('', 'DISCONNECTED FROM IO', 'INFO')


    def setDefaultInstance(self,message):
        name = message.content['text']
        if name == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        else:
            self.defaultInstance = name

    def VideoThroughUDP(self):
        UDP_IP = self.address
        UDP_PORT = self.video_port
        self.video_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  # UDP
        self.video_socket.bind(("", UDP_PORT))
        while True:
            data, addr = self.video_socket.recvfrom(65527)  # buffer size is 1024 bytes
            b64_img = base64.b64encode(data)
            self.video_frame_counter = self.video_frame_counter + 1
            print 'Frame# : ['+self.video_frame_counter+'] sent.'
            yield b64_img

    def videoEcho(self,message):
        b = self.VideoThroughUDP().next()
        #Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': b})

    def simpleEcho(self,message):
        name = message.content['text']
        if name == 'START_COMM_HS':
            #Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            print '[' + tk.getDate() + ']' + ' Server disconnecting...'
        else:
            response = urllib.urlopen('http://localhost:8090' + self.SLUG_DICTIONARY[name])
            data = json.loads(json.dumps(response.read()))
            #Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': data})
            print '[' + tk.getDate() + ']' + ' Packet ' + name + ' sent.'

    def directoryEcho(self,message):
        name = message.content['text']
        print '[' + tk.getDate() + ']' + name
        if name == 'START_COMM_HS':
            #Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            print '[' + tk.getDate() + ']' + ' Server disconnecting...'
        else:
            response = tk.get_directory(name)
            data = json.dumps(response)
            #Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': data})
            print '[' + tk.getDate() + ']' + ' Packet ' + name + ' sent.'

    def hpsEcho(self,message):
        io = IO('softsim','PARAMETER','127.0.0.1','8090')
        io.subscribe(message)
        self.subscribers.push(io)

    def getHandler(self,message):
        name = message.content['text']
        if name == 'START_COMM_HS':
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            self.disconnect()
            tk.log(name, 'DISCONNECING FROM IO', 'INFO')
        else:
            response = urllib.urlopen('http://' + str(self.address) + ':' + str(self.port) +''+ str(self.SLUG_DICTIONARY[name]))
            data = json.loads(json.dumps(response.read()))
            message.reply_channel.send({'text': data})
            tk.log(name, 'PACKET SENT', 'INFO')


    def handlerTlmCommand(self,message):
        message_text = message.content['text']

        if message_text == 'START_COMM_HS':
            tk.log('', 'GOT HS SIGNAL FROM CLIENT', 'INFO')
            message.reply_channel.send({'text': 'START_COMM_ACK'})

        elif message_text == 'CLOSE_COMM_NOFBCK':
            tk.log('', 'GOT CLOSE SIGNAL FROM CLIENT', 'INFO')
            self.disconnect()
        else:
            received = ''
            to_send = ''

            #if self.socket_name == 'PARAMETER':
            temp = tk.byteify(message_text)
            temp = json.loads(temp)
            temp = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(temp['tlm'])) + '}}'
            temp = temp.replace("\'", "\"")
            to_send = '[1,1,' + str(self.tlmSeqNum) + ',' + str(temp) + ']'
            """

            elif self.socket_name == 'EVENT':
                temp = '{"events": "subscribe"}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'

            elif self.socket_name == 'ALARM':
                temp = '{"alarms": "subscribe"}'
                temp = temp.replace("\'", "\"")
                to_send = '[1,1,' + str(self.counter) + ',' + str(temp) + ']'
            """
            # while True:
            ws = create_connection('ws://' + self.address + ':' + str(self.port) + '/' + 'softsim' + '/_websocket')
            ws.send(to_send)
            ## LAUNCING THREADS
            t = Thread(target=self.special_looping_over, args=[ws, message, self.tlmSeqNum])
            t.start()

    def special_looping_over(self, websocket_obj, message_obj, counter):
        while True:
            result = websocket_obj.recv()
            print result
            if result != '[1,2,' + str(counter) + ']':
                result = tk.preProcess(result)
                message_obj.reply_channel.send({'text': result})
                tk.log('', 'BOUND', 'INFO')




