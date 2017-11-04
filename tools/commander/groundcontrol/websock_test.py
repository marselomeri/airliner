from channels import Group,channel
import toolkit as tk
import socket
import time
import datetime
import base64
import urllib,json,os
from websocket import create_connection
from channels.generic import BaseConsumer
from threading import Thread
from pprint import pprint
from multiprocessing import Process
import psutil


class tester:
    def __init__(self,name = 'NONAME'):
        self.name=name
        self.proc = None
        self.connections =[]
        self.currentConnection = {}

    def pushProcess(self,m,data):
        while True:
                time.sleep(5)
                m.reply_channel.send({'text':data})

    def connect(self,message):
        self.currentConnection['CONNECT'] = message
        print 'NAME : ', self.name

    def disconnect(self,message):
        self.currentConnection['DISCONNECT'] = message



    def receive(self,message):
        #self.currentConnection['RECEIVED'] = message
        #self.connections.append(self.currentConnection);
        #print message.content['text']
        #print'+++++++++++++++++++++++++++++'
        #print self.connections
        if message.content['text'].find('START_COMM_HS')!=-1: #Handshake
            try:
                msg = message.content['text']
                msg = msg.split('/')[1]
                self.name = msg
                message.reply_channel.send({'text': 'START_COMM_ACK'})
            except:
                message.reply_channel.send({'text':'START_COMM_ERR'})
        elif message.content['text'].find('CLOSE_COMM')!=-1:
            print 'a'
        else:
            self.currentConnection['MESSAGE_CHANNEL'] = message
            data = message.content['text']
            self.proc = Process(target=self.push, args=(message, data))
            self.currentConnection['PROCESS_ID'] =self.proc.pid
            self.connections.append(self.currentConnection);
            print'+++++++++++++++++++++++++++++'
            print self.connections
            print'+++++++++++++++++++++++++++++'
            self.proc.start()



class nontester(BaseConsumer):

    test = tester()



    method_mapping = {
        "websocket.connect": "connect",
        "websocket.disconnect": "disconnect",
        "websocket.receive": "receive",
    }



    connect= test.connect

    disconnect=test.disconnect
    receive=test.receive


"""
        if self.th != None:
            print 'TH1 : ', self.th

            if self.th.is_alive() :
                print 'TH1.1 : ', self.th
                to_kill = psutil.Process(self.th.pid)
                to_kill.kill()
                self.th = Process(target=self.push, args=(message, data))
                self.th.start()
        else:
"""