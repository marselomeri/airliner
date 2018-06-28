from SocketServer import TCPServer
from abc import abstractmethod
from threading import Thread

from pyliner.app import App


class SocketApp(App):
    """The Socket Service listens to a TCP port for vehicle commands.

    The Service parses the given commands into events that the system responds
    to.
    """

    def __init__(self, port):
        super(SocketApp, self).__init__()
        self.port = port
        self.server = None
        """:type: TCPServer"""

    def __repr__(self):
        return '{}({})'.format(self.__class__.__name__, self.port)

    @abstractmethod
    def handle(self, request, client_address):
        pass

    def attach(self, vehicle_wrapper):
        super(SocketApp, self).attach(vehicle_wrapper)
        self.info('Starting SocketService on port {}'.format(self.port))
        self.server = TCPServer(
            ('', self.port),
            lambda request, client_address, _self:
                self.handle(request, client_address))
        self.server.service = self

        listen_thread = Thread(target=self.server.serve_forever)
        listen_thread.daemon = True
        listen_thread.start()

    def detach(self):
        self.info('Stopping SocketService on port {}'.format(self.port))
        self.server.shutdown()
        super(SocketApp, self).detach()
