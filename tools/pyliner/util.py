import SocketServer
import json
import socket
from datetime import datetime


def get_time():
    return int((datetime.utcnow() - datetime(1970, 1, 1)).total_seconds() * 10000)


def init_socket():
    """ Creates a UDP socket object and returns it """
    return socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


def server_factory(callback):
    """ Creates server object and sets the callback """
    def create_handler(*args, **kwargs):
        return ThreadedUDPRequestHandler(callback, *args, **kwargs)
    return create_handler


def read_json(file_path):
    """ Parses the required JSON input file containing Airliner mappings """
    try:
        with open(file_path, 'r') as airliner_map:
            return json.load(airliner_map)
    except IOError:
        print "Specified input file (%s) does not exist" % file_path
    except Exception as e:
        print e


class ThreadedUDPRequestHandler(SocketServer.BaseRequestHandler):
    def __init__(self, callback, *args, **keys):
        self.callback = callback
        SocketServer.BaseRequestHandler.__init__(self, *args, **keys)

    def handle(self):
        self.callback(self.request)
