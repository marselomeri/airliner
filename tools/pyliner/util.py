import json
import socket
import sys
import threading
import time
from datetime import datetime

import socketserver
from flufl.enum import Enum


class LogLevel(Enum):
    Debug = 1
    Info = 2
    Warn = 3
    Error = 4


class PeriodicExecutor(threading.Thread):
    """Executes a callback function every x-seconds."""
    def __init__(self, callback, every=1):
        super(PeriodicExecutor, self).__init__()
        self.callback = callback
        self.every = every
        self.daemon = True

    def run(self):
        while True:
            self.callback()
            time.sleep(self.every)


class ThreadedUDPRequestHandler(socketserver.BaseRequestHandler):
    def __init__(self, callback, *args, **keys):
        self.callback = callback
        socketserver.BaseRequestHandler.__init__(self, *args, **keys)

    def handle(self):
        self.callback(self.request)


def get_time():
    return int((datetime.utcnow() - datetime(1970, 1, 1)).total_seconds() * 10000)


def handler_factory(callback):
    """ Creates server object and sets the callback """
    return lambda *args, **kwargs: ThreadedUDPRequestHandler(callback, *args, **kwargs)


def indent(level, iterable):
    for string in iterable:
        yield ' '*level + str(string)


def init_socket():
    """ Creates a UDP socket object and returns it """
    return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


def query_yes_no(question, default=None):
    """Ask a yes/no question via raw_input() and return their answer.

    "question" is a string that is presented to the user.
    "default" is the presumed answer if the user just hits <Enter>.

    The "answer" return value is one of "yes" or "no".
    Adapted from: http://code.activestate.com/recipes/577058/
    """
    valid = {True: {'y', 'ye', 'yes'},
             False: {'n', 'no'}}
    if default is None:
        prompt = " [y/n] "
    elif default:
        prompt = " [Y/n] "
    else:
        prompt = " [y/N] "

    while True:
        sys.stdout.write(question + prompt)
        choice = raw_input().lower()
        if default is not None and choice == '':
            return default
        for answer, options in valid.items():
            if choice in options:
                return answer
        else:
            sys.stdout.write("Please respond with 'yes' or 'no' "
                             "(or 'y' or 'n').\n")


def read_json(file_path):
    """Parses the required JSON input file containing Airliner mappings.

    Returns:
        dict
    """
    try:
        with open(file_path, 'r') as airliner_map:
            return json.load(airliner_map)
    except IOError:
        print("Specified input file (%s) does not exist" % file_path)
    except Exception as e:
        print(e)


def serialize(header, payload):
    """
    Receive a CCSDS message and payload then returns the
    serialized concatenation of them.
    """
    ser = header.get_encoded()
    if payload:
        ser += payload.SerializeToString()
    return ser
