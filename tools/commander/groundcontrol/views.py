"""Views.py
the url.py file filters and routes a url to one of the functions in this module. These functions determine the reqested page
and sends a page in response.

Since we are dealing with jade/pug template files these files are compiled and generate HTML which are sent over the network.

Todo:
    * Only identify and serve files compatible inside django framework.
"""
# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.shortcuts import render
from django.template import loader
from django import template
from django.http import HttpResponse
from toolkit import log,readJsonFromCloseCirlce


register = template.Library()

@register.filter()
def range(min=5):
    return range(min)


def index(r,a=None):
    """!
    Serves various files like pug and js.
    @param r: param 1
    @param a: param 2
    @return: Rendered Response
    """
    if a==None:
        log('index.pug','[REQUEST] Index page requested.','INFO')
        return render(r,'index.pug')
    elif a.find('.js')!=-1:
        log('/'+a, '[REQUEST] Javascript document requested.', 'INFO')
        return render(r, str(a))
    elif a.find('groundcontrol_video_socket')!=-1:
        log('/'+a, '[REQUEST]  Websocket requested.', 'INFO')
        return HttpResponse('Connected to websockets.')
    else:
        log('/'+a+'.pug', '[REQUEST] Document requested.', 'INFO')
        return render(r, str(a+'.pug'))

def router(r,a,b,c=None,d=None):
    """!
    Serves various files like pug and js.
    @param r: param 1
    @param a: param 2
    @param b: param 3
    @param c: param 4
    @param d: param 5
    @return: Rendered Response
    """
    if c==None and d==None:
        log(str(a+'/'+b+'.pug'), '[REQUEST] Document requested.', 'INFO')
        try:
            json = readJsonFromCloseCirlce(str(a))
        except:
            json = 'NULL'
        return render(r, str(a+'/'+b+'.pug'),{'obj':json})

    elif d==None:
        log(str(a+'/'+b+'/'+c+'.pug'), '[REQUEST] Document requested.', 'INFO')
        try:
            json = readJsonFromCloseCirlce(str(a+'/'+b+'/'))
        except:
            json = 'NULL'
        return render(r, str(a+'/'+b+'/'+c+'.pug'),{'obj':json})

    else:
        log(str(a +'/'+b+'/'+c+'/'+d+ '.pug'), '[REQUEST] Document requested.', 'INFO')
        try:
            json = readJsonFromCloseCirlce(str(a+'/'+b+'/'+c+'/'))
        except:
            json = 'NULL'
        return render(r, str(a +'/'+b+'/'+c+'/'+d+ '.pug'),{'obj':json})

def pug_router(r,a,b,c=None,d=None):
    """
     Serves various files like pug and js.
    @param r: param 1
    @param a: param 2
    @param b: param 3
    @param c: param 4
    @param d: param 5
    @return: Rendered Response
    """
    if c==None and d==None:
        log(str(a+'/'+b), '[REQUEST] Document requested.', 'INFO')
        return render(r, str(a+'/'+b))
    elif d==None:
        log(str(a+'/'+b+'/'+c), '[REQUEST] Document requested.', 'INFO')
        return render(r, str(a+'/'+b+'/'+c))
    else:
        log(str(a +'/'+b+'/'+c+'/'+d), '[REQUEST] Document requested.', 'INFO')
        return render(r, str(a +'/'+b+'/'+c+'/'+d))
