import json

from pyliner.action import ACTION_GOTO
from pyliner.app.navigation.waypoint import Waypoint
from pyliner.app.socket_app import SocketApp
from pyliner.intent import Intent


class CommanderApp(SocketApp):
    def handle(self, request, client_address):
        data = request.recv(1024)
        j = json.loads(data)
        self.info('JSON from {}: {}'.format(client_address, j))
        if j['command'] == 'goto':
            waypoints = [Waypoint(
                latitude=w['lat'], longitude=w['lon'], altitude=w['alt'],
                heading=None) for w in j['waypoints']]
            goto = {'waypoints': waypoints, 'tolerance': j['tolerance']}
            self.vehicle.broadcast(Intent(action=ACTION_GOTO, data=goto))
        else:
            print('CommanderApp unable to route JSON.')

    @property
    def qualified_name(self):
        return 'com.windhover.pyliner.app.commander'
