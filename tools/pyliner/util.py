import socketserver
import json
import socket
import threading
from datetime import datetime

import time
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


def init_socket():
    """ Creates a UDP socket object and returns it """
    return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


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
