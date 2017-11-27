# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.shortcuts import render
from django.http import HttpResponse






def index(r,a=None):
    #cons.ws_disconnect()
    if a==None:
        print '[REQUEST] Index page requested. [index.pug] '
        #return render(r, 'layout.pug')
        return render(r,'index2.pug')
    elif a.find('.js')!=-1:
        print '[REQUEST] Javascript document requested. [/', a, ']'
        return render(r, str(a))
    elif a.find('groundcontrol_video_socket')!=-1:
        print '[SOCKET_REQUEST] Websocket requested. [/', a, ']'
        return HttpResponse('Connected to websockets.')
    else:
        print '[REQUEST] Document requested. [/',a,'.pug]'
        return render(r, str(a+'.pug'))




def router(r,a,b,c=None,d=None):
    if c==None and d==None:
        print '[REQUEST] Document requested. [/', a,'/',b, '.pug]'
        return render(r, str(a+'/'+b+'.pug'))
    elif d==None:
        print '[REQUEST] Document requested. [/', a,'/',b,'/',c, '.pug]'
        return render(r, str(a+'/'+b+'/'+c+'.pug'))
    else:
        print '[REQUEST] Document requested. [/', a,'/', b,'/',c,'/',d,  '.pug]'
        return render(r, str(a +'/'+b+'/'+c+'/'+d+ '.pug'))

def pug_router(r,a,b,c=None,d=None):
    if c==None and d==None:
        print '[REQUEST] Document requested. [/', a,'/',b,']'
        return render(r, str(a+'/'+b))
    elif d==None:
        print '[REQUEST] Document requested. [/', a,'/',b,'/',c, ']'
        return render(r, str(a+'/'+b+'/'+c))
    else:
        print '[REQUEST] Document requested. [/', a,'/', b,'/',c,'/',d,  ']'
        return render(r, str(a +'/'+b+'/'+c+'/'+d))
