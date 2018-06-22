from SocketServer import TCPServer, StreamRequestHandler
from threading import Thread

from pyliner.service import Service


class SocketServiceHandler(StreamRequestHandler):
    def handle(self):
        self.service.debug('Handling Request: {}'.format(self.rfile.read()))

    @property
    def service(self):
        return self.server.service


class SocketService(Service):
    """The Socket Service listens to a TCP port for vehicle commands.

    The Service parses the given commands into events that the system responds
    to.
    """

    def __init__(self, port, request_handler_class=SocketServiceHandler):
        super(SocketService, self).__init__()
        self.request_handler_class = request_handler_class
        self.port = port
        self.server = None
        """:type: TCPServer"""

    def start(self):
        super(SocketService, self).start()
        self.info('Starting SocketService')
        self.server = TCPServer(('', self.port), self.request_handler_class)
        self.server.service = self

        listen_thread = Thread(target=self.server.serve_forever)
        listen_thread.daemon = True
        listen_thread.start()

    def stop(self):
        super(SocketService, self).stop()
        self.info('Stopping SocketService')
        self.server.shutdown()
