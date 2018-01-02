from channels.routing import route,include
from groundcontrol.consumers import *

# Load variables into cache
mc = MyCache()
mc.initialize()




channel_routing = [

                    route(u'websocket.connect', tlm_connect, path='/tlm'),
                    route(u'websocket.receive', getTelemetry, path='/tlm'),
                    route(u'websocket.disconnect', tlm_disconnect, path='/tlm'),

                    route(u'websocket.connect', cmd1_connect, path='/cmd1'),
                    route(u'websocket.receive', getCommandInfo, path='/cmd1'),
                    route(u'websocket.disconnect', cmd1_disconnect, path='/cmd1'),

                    route(u'websocket.connect', cmd2_connect, path='/cmd2'),
                    route(u'websocket.receive', postCommand, path='/cmd2'),
                    route(u'websocket.disconnect', cmd2_disconnect, path='/cmd2'),

                    route(u'websocket.connect', inst_connect, path='/inst'),
                    route(u'websocket.receive', getInstanceList, path='/inst'),
                    route(u'websocket.disconnect', inst_disconnect, path='/inst'),

                    route(u'websocket.connect', tid_connect, path='/tid'),
                    route(u'websocket.receive', setDefaultInstance, path='/tid'),
                    route(u'websocket.disconnect', tid_disconnect, path='/tid'),

                    route(u'websocket.connect', dir_connect, path='/dir'),
                    route(u'websocket.receive', directoryListing, path='/dir'),
                    route(u'websocket.disconnect', dir_disconnect, path='/dir'),

                    route(u'websocket.connect', eve_connect, path='/event'),
                    route(u'websocket.receive', getEvents, path='/event'),
                    route(u'websocket.disconnect', eve_disconnect, path='/event'),

                    route(u'websocket.connect', vid_connect, path='/video'),
                    route(u'websocket.receive', getTelemetry, path='/video'),
                    route(u'websocket.disconnect', vid_disconnect, path='/video'),

                    route(u'websocket.connect', tlm_connect, path='/tlm'),
                    route(u'websocket.receive', getTelemetry, path='/tlm'),
                    route(u'websocket.disconnect', tlm_disconnect, path='/tlm'),
]

