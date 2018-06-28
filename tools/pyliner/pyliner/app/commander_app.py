import json

from pyliner.app.socket_app import SocketApp


class CommanderApp(SocketApp):
    @property
    def qualified_name(self):
        return 'com.windhover.pyliner.app.commander'

    def handle(self, request, client_address):
        j = json.loads(request)
        self.info('JSON from {}: {}'.format(client_address, j))
