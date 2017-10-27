from channels import Group
import toolkit as tk
import socket
import time
import datetime
import base64
import urllib,json,os
from websocket import create_connection


# any user who will be using commander will be added to users


class ServerSession:

    def __init__(self):
        #SESSION VARIABLES
        self.activeInstances = [];
        self.subscribers = [];
        self.defaultInstance = None;
        self.cmdSeqNum = 0;
        self.tlmSeqNum = 0;

        #WEBSOCKET VARIABLES
        self.port = 0;
        self.address = '127.0.0.1';

        #UNKNOWN VARIABLES
        self.ClientProxy = None;
        self.tlmBypass = None;

        #DATA VARIABLES
        self.video_port = 3001
        self.video_frame_counter = 0
        self.video_socket = None
        self.data1 = None

    def connect(self,message):
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'accept': True})
        print '[' + tk.getDate() + ']' + ' Server connected to client.'

    def disconnect(self,message):
        Group('users').add(message.reply_channel)
        message.reply_channel.send({"close": True})
        Group('users').discard(message.reply_channel)
        print '[' + tk.getDate() + ']' + ' Server disconnected from client.'

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
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': b})

    def Simpleecho(message):
        name = message.content['text']
        if name == 'START_COMM_HS':
            Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': 'START_COMM_ACK'})
        elif name == 'CLOSE_COMM_NOFBCK':
            print '[' + tk.getDate() + ']' + ' Server disconnecting...'
        else:
            response = urllib.urlopen('http://localhost:8090' + SLUG_DICTIONARY[name])
            data = json.loads(json.dumps(response.read()))
            Group('users').add(message.reply_channel)
            message.reply_channel.send({'text': data})
            print '[' + tk.getDate() + ']' + ' Packet ' + name + ' sent.'

        def getDirListing(message):
            name = message.content['text']
            print '[' + getDate() + ']' + name
            if name == 'START_COMM_HS':
                Group('users').add(message.reply_channel)
                message.reply_channel.send({'text': 'START_COMM_ACK'})
            elif name == 'CLOSE_COMM_NOFBCK':
                print '[' + getDate() + ']' + ' Server disconnecting...'
            else:
                response = tk.get_directory(name)
                data = json.dumps(response)
                Group('users').add(message.reply_channel)
                message.reply_channel.send({'text': data})
                print '[' + getDate() + ']' + ' Packet ' + name + ' sent.'

        def hps(message):

            name = message.content['text']
            if name == 'START_COMM_HS':
                Group('users').add(message.reply_channel)
                message.reply_channel.send({'text': 'START_COMM_ACK'})
            elif name == 'CLOSE_COMM_NOFBCK':
                print '[' + getDate() + ']' + ' Server disconnecting...'
            else:
                result = 'NA'
                data = tk.byteify(name)
                data = json.loads(data)
                op_message = ' {"parameter":"subscribe", "data":{"list":' + str(tk.byteify(data['tlm'])) + '}}'
                op_message_1 = op_message.replace("\'", "\"");
                op_message_2 = '[1,1,' + '1' + ',' + op_message_1 + ']'
                ws = create_connection("ws://localhost:8090/softsim/_websocket")
                ws.send(op_message_2)
                result = ws.recv()
                if result == '[1,2,1]':
                    ws.send(op_message_2)
                    result = ws.recv()
                Group('users').add(message.reply_channel)
                message.reply_channel.send({'text': result})
                print '[' + getDate() + ']' + ' HPS websocket Packet sent.'
                print result


#Global Lookup Dictionary
SLUG_DICTIONARY={
    'getInstances' : '/api/instances',
    'getCommands': '/api/mdb/softsim/commands',
}






def connect(message):
    Group('users').add(message.reply_channel)
    message.reply_channel.send({'accept': True})
    print '['+getDate()+']'+' Server connected to client.'


def disconnect(message):
    Group('users').add(message.reply_channel)
    message.reply_channel.send({"close": True})
    Group('users').discard(message.reply_channel)
    print '[' + getDate() + ']' + ' Server disconnected from client.'

def echo(message):

    name = message.content['text']
    if name == 'START_COMM_HS' :
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': 'START_COMM_ACK'})
    elif name == 'CLOSE_COMM_NOFBCK':
        print '[' + getDate() + ']' + ' Server disconnecting...'
    else:
        response = urllib.urlopen('http://localhost:8090'+SLUG_DICTIONARY[name])
        data = json.loads(json.dumps(response.read()))
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': data})
        print '[' + getDate() + ']' + ' Packet '+name+' sent.'


def getDirListing(message):
    name = message.content['text']
    print '[' + getDate() + ']' +name
    if name == 'START_COMM_HS':
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': 'START_COMM_ACK'})
    elif name == 'CLOSE_COMM_NOFBCK':
        print '[' + getDate() + ']' + ' Server disconnecting...'
    else:
        response = tk.get_directory(name)
        data = json.dumps(response)
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': data})
        print '[' + getDate() + ']' + ' Packet ' + name + ' sent.'




def hps(message):

    name = message.content['text']
    if name == 'START_COMM_HS' :
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': 'START_COMM_ACK'})
    elif name == 'CLOSE_COMM_NOFBCK':
        print '[' + getDate() + ']' + ' Server disconnecting...'
    else:
        result='NA'
        data=tk.byteify(name)
        data = json.loads(data)
        op_message =' {"parameter":"subscribe", "data":{"list":'+str(tk.byteify(data['tlm']))+'}}'
        op_message_1 = op_message.replace("\'","\"");
        op_message_2 = '[1,1,' + '1' + ',' + op_message_1 + ']'
        ws = create_connection("ws://localhost:8090/softsim/_websocket")
        ws.send(op_message_2)
        result = ws.recv()
        if result =='[1,2,1]':
            ws.send(op_message_2)
            result = ws.recv()
        Group('users').add(message.reply_channel)
        message.reply_channel.send({'text': result})
        print '[' + getDate() + ']' + ' HPS websocket Packet sent.'
        print result


