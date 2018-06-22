from SocketServer import TCPServer, BaseRequestHandler, StreamRequestHandler
from threading import Thread

from pyliner.service import Service


class SocketParser(StreamRequestHandler):
    def handle(self):
        service = self.server.service
        """:type: SocketService"""
        service.info('Handling Request: {}'.format(self.rfile.readline()))


class SocketService(Service):
    """The Socket Service listens to a TCP port for vehicle commands.

    The Service parses the given commands into events that the system responds
    to.
    """

    def __init__(self, port, request_handler_class=SocketParser):
        super(SocketService, self).__init__()
        self.request_handler_class = request_handler_class
        self.port = port
        self.server = None
        """:type: TCPServer"""

    def start(self):
        self.info('Starting SocketService')
        self.server = TCPServer(('', self.port), self.request_handler_class)
        self.server.service = self

        listen_thread = Thread(target=self.server.serve_forever)
        listen_thread.daemon = True
        listen_thread.start()

    def stop(self):
        self.info('Stopping SocketService')
        self.server.shutdown()

