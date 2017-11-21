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


#ws = create_connection('ws://127.0.0.1:8090/softsim/_websocket')
"""
def f1():
    print 'waiting f1'
    time.sleep(5)
    ws.send('[1,1,0, {"parameter":"subscribe", "data":{"list":[{"name": "/CFS/DS/AppEnableState"}]}}]')

#time.sleep(5)
def f2():
    print 'waiting f2'
    time.sleep(2)
    ws.send('[1,1,0, {"parameter":"subscribe", "data":{"list":[{"name": "/CFS/DS/DestTblLoadCounter"}]}}]')

def f3():
    print 'waiting f3'
    time.sleep(25)
    ws.send('[1,1,0, {"parameter":"unsubscribe", "data":{"list":[{"name": "/CFS/DS/DestTblLoadCounter"}]}}]')

f1()
f2()
f3()

while True:
    res = ws.recv()
    if res.find('[1,2')==-1:
        x = (json.loads(res)[3]['data']['parameter'])
        for each in x:
            print each['id']['name']
        #pprint
        #break
"""