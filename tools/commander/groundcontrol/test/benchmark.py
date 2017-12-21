# -*- coding: utf-8 -*-
from __future__ import unicode_literals
#from ..toolkit import *
import unittest
import websocket
import urllib
import time
from socketIO_client import SocketIO, LoggingNamespace
import matplotlib.pyplot as plt
import numpy as np
import signal
import json
import sqlite3


class channel_plugin:
    def __init__(self,url):
        self.ws = websocket.WebSocket()
        self.ws.connect(url,timeout=3)

    def getSock(self):
        return self.ws

    def send(self,msg):
        self.ws.send(msg)
        return self.ws

    def closeSock(self):
        self.ws.close()

class socket_io:
    def __init__(self,slug):
        self.slug = slug
        self.sio = SocketIO('localhost',3000,LoggingNamespace)
        self.result = None

    def cb(self,a):
        print a
        self.result = a

    def response(self):
        return self.result

    def emit(self):
            self.sio.emit(self.slug, self.cb)
            self.sio.wait(seconds=0.0001)

    def emit_wa(self,args):
        self.sio.emit(self.slug,args, self.cb)
        self.sio.wait(seconds=0.0001)

    def emit_this(self,sl,arg):
        self.sio.emit(sl,arg, self.cb)
        self.sio.wait(seconds=0.0001)

def plots(x,y,z,slug):

    _mean = [np.mean(x[slug]['data']),np.mean(y[slug]['data']),np.mean(z[slug]['data'])]
    _max = [max(x[slug]['data']), max(y[slug]['data']), max(z[slug]['data'])]
    _min = [min(x[slug]['data']), min(y[slug]['data']), min(z[slug]['data'])]

    if  _mean[0]!= 0:
        s = " MIN: "+str(round(_min[0]*1000,2))+" ms   , MAX: "+str(round(_max[0]*1000,2))+" ms   , AVG: "+str(round(_mean[0]*1000,2))+" ms"

        plt.plot([_max[0]] * len(x[slug]['data']), 'b-',alpha = 0.2)
        #plt.text((len(x[slug]['data']) ), _max[0], str(_max[0]))

        plt.plot([_min[0]] * len(x[slug]['data']), 'b-',alpha = 0.2)
        #plt.text((len(x[slug]['data']) ), _min[0], str(_min[0]))

        plt.plot([_mean[0]]*len(x[slug]['data']), 'b--')
        #plt.text((len(x[slug]['data'])),_mean[0], str(_mean[0]))

        plt.plot(x[slug]['data'],'b-',label =x[slug]['label'] + s)

    #######################
    if _mean[1] != 0:
        s1 = " MIN: " + str(round(_min[1] * 1000, 2)) + " ms   , MAX: " + str(
            round(_max[1] * 1000, 2)) + " ms   , AVG: " + str(round(_mean[1] * 1000, 2)) + " ms"
        plt.plot([_max[1]] * len(y[slug]['data']), 'r-',alpha = 0.2)
        #plt.text((len(y[slug]['data']) ), _max[1], str(_max[1]))

        plt.plot([_min[1]] * len(y[slug]['data']), 'r-',alpha = 0.2)
        #plt.text((len(y[slug]['data'])), _min[1], str(_min[1]))



        plt.plot([_mean[1]] * len(y[slug]['data']), 'r--')
        #plt.text((len(y[slug]['data'])), _mean[1], str(_mean[1]))
        plt.plot(y[slug]['data'], 'r-', label=y[slug]['label']+s1)

    #######################
    if _mean[2] != 0:
        s2 = " MIN: " + str(round(_min[2] * 1000, 2)) + " ms   , MAX: " + str(
            round(_max[2] * 1000, 2)) + " ms   , AVG: " + str(round(_mean[2] * 1000, 2)) + " ms"
        plt.plot([_max[2]] * len(z[slug]['data']), 'g-',alpha = 0.2)
        #plt.text((len(z[slug]['data'])), _max[2], str(_max[2]))

        plt.plot([_min[2]] * len(z[slug]['data']), 'g-',alpha = 0.2)
        #plt.text((len(z[slug]['data'])), _min[2], str(_min[2]))

        plt.plot([_mean[2]] * len(z[slug]['data']), 'g--')
        #plt.text((len(z[slug]['data'])), _mean[2], str(_mean[2]))
        plt.plot(z[slug]['data'], 'g-', label=z[slug]['label']+s2)

    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,ncol=1, mode="expand", borderaxespad=0.)
    plt.show()


def plots2(x,y,z,slug1,slug2,slug3):

    _mean = [np.mean(x),np.mean(y),np.mean(z)]
    _max = [max(x), max(y), max(z)]
    _min = [min(x), min(y), min(z)]

    if  _mean[0]!= 0:
        s = " MIN: "+str(round(_min[0]*1,2))+" ms   , MAX: "+str(round(_max[0]*1,2))+" ms   , AVG: "+str(round(_mean[0]*1,2))+" ms"

        plt.plot([_max[0]] * len(x), 'b-',alpha = 0.2)
        #plt.text((len(x) ), _max[0], str(_max[0]))

        plt.plot([_min[0]] * len(x), 'b-',alpha = 0.2)
        #plt.text((len(x) ), _min[0], str(_min[0]))

        plt.plot([_mean[0]]*len(x), 'b--')
        #plt.text((len(x)),_mean[0], str(_mean[0]))

        plt.plot(x,'b-',label =slug1 + s)

    #######################
    if _mean[1] != 0:
        s1 = " MIN: " + str(round(_min[1] *1, 2)) + " ms   , MAX: " + str(
            round(_max[1] *1, 2)) + " ms   , AVG: " + str(round(_mean[1] *1, 2)) + " ms"
        plt.plot([_max[1]] * len(y), 'r-',alpha = 0.2)
        #plt.text((len(y) ), _max[1], str(_max[1]))

        plt.plot([_min[1]] * len(y), 'r-',alpha = 0.2)
        #plt.text((len(y)), _min[1], str(_min[1]))



        plt.plot([_mean[1]] * len(y), 'r--')
        #plt.text((len(y)), _mean[1], str(_mean[1]))
        plt.plot(y, 'r-', label=slug2+s1)

    #######################
    if _mean[2] != 0:
        s2 = " MIN: " + str(round(_min[2] *1, 2)) + " ms   , MAX: " + str(
            round(_max[2] *1, 2)) + " ms   , AVG: " + str(round(_mean[2] *1, 2)) + " ms"
        plt.plot([_max[2]] * len(z), 'g-',alpha = 0.2)
        #plt.text((len(z)), _max[2], str(_max[2]))

        plt.plot([_min[2]] * len(z), 'g-',alpha = 0.2)
        #plt.text((len(z)), _min[2], str(_min[2]))

        plt.plot([_mean[2]] * len(z), 'g--')
        #plt.text((len(z)), _mean[2], str(_mean[2]))
        plt.plot(z, 'g-', label=slug3+s2)

    plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,ncol=1, mode="expand", borderaxespad=0.)
    plt.show()

## LATENCY TESTS #######################
"""
c = channel_plugin('ws://127.0.0.1:8000/inst/')
sio = socket_io('getAllInstances')


def get_instance_django():
    s = time.time()
    ws = c.send('INVOKE')
    op = ws.recv()
    te = time.time() - s
    print 'DJANGO',te
    return te

def get_instance_traditional():
    s = time.time()
    op = urllib.urlopen('http://localhost:8090/api/instances').read()
    te = time.time()-s
    print '\t\t\t\t\t\t\tTRADITIONAL',te
    return te

def get_instance_Node():
    s = time.time()
    sio.emit()
    op = sio.response()
    #print op
    te = time.time()-s
    print '\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tNODE',te
    return te




## BIDIRICTION TEST
##get data from sql

"""







if __name__ =='__main__':

    x={'data1':{'data':[],'label':'django'},'data2':{'data':[],'label':'django'},'data3':{'data':[],'label':'django'},'data4':{'data':[],'label':'django'}}
    y={'data1':{'data':[],'label':'traditional'},'data2':{'data':[],'label':'traditional'},'data3':{'data':[],'label':'traditional'},'data4':{'data':[],'label':'traditional'}}
    z={'data1':{'data':[],'label':'node'},'data2':{'data':[],'label':'node'},'data3':{'data':[],'label':'node'},'data4':{'data':[],'label':'node'}}
    ITER = 1000
    """
    def execute_this():
        for e in range(ITER):
            print e
            x['data1']['data'].append(get_instance_django())


        for e in range(ITER):
            print e
            #y['data1']['data'].append(get_instance_traditional())

            y['data1']['data'].append(0)
        for e in range(ITER):
            print e
            #z['data1']['data'].append(get_instance_Node())

            z['data1']['data'].append(0)


        plots(x,y,z,'data1')
        
    """
    file_a = 'socketio_1000'
    file_b = 'channel_10_1000'
    file_c = 'channel_8_10000'


    ##LOADING##############
    sockio = []
    with open(file_a+'.txt', 'r') as f:
        for each in f.readlines():
            sockio.append(  (each.replace("\"", "")).split(',')  )

    channels10 = []
    with open(file_b+'.txt', 'r') as f:
        for each in f.readlines():
            channels10.append(  (each.replace("\"", "")).split(',') )


    channels30 = []
    with open(file_c+'.txt', 'r') as f:
        for each in f.readlines():
            channels30.append(  (each.replace("\"", "")).split(',') )
    #############################
    ####VALIDATE#########
    print sockio
    print channels10
    print channels30

    ###############
    num = 2  #COLUMN NUMBER
    type = 0
    noise = 500



    x = []
    y = []
    z = []
    st = float(sockio[0][num])
    st1 = float(channels10[0][num])
    st2 = float(channels30[0][num])

    for e in sockio:
        try:
            if type == 1:
                x.append(float(e[num])-st)
            else:
                x.append(float(e[num]))
        except:
            print e
            #x.append(float(noise))
            pass
    for e in channels10:
        try:
            if type == 1:
                y.append(float(e[num]) - st1)
            else:
                y.append(float(e[num]))
        except:
            print e
            #y.append(float(noise))
            pass
    for e in channels30:
        try:
            if type == 1:
                z.append(float(e[num]) - st2)
            else:
                z.append(float(e[num]))
        except:
            print e
            #z.append(float(noise))
            pass
    #x = [0]*len(x)
    #y = [0] * len(y)
    #z = [0] * len(z)
    #print len(x),x
    #print len(y), y
    #print len(z), z
    plots2(x,y,z,'SocketIO','Channels_10','Channels_8')
   



