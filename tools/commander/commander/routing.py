from channels.routing import route,include
from groundcontrol.consumers import *

# Load variables into cache
mc = MyCache()
mc.initialize()

ins = Instance()
dir = Directory()

evt = Event()
vid = Video()

tlm = Telemetry()
cmd = Command()
cmds = Command()






instance = [
    route('websocket.connect',ins.connect),
    route('websocket.disconnect',ins.disconnect),
    route('websocket.receive',ins.getInstanceList)
]

default_instance = [
    route('websocket.connect',ins.connect),
    route('websocket.disconnect',ins.disconnect),
    route('websocket.receive',ins.setDefaultInstance)
]


directory = [
    route('websocket.connect',dir.connect),
    route('websocket.disconnect',dir.disconnect),
    route('websocket.receive',dir.directoryListing)
]


telemetry_subscribe = [
    route('websocket.connect',tlm.connect),
    route('websocket.disconnect',tlm.disconnect),
    route('websocket.receive',tlm.getTelemetry),

]



command_info = [
    route('websocket.connect',cmd.connect),
    route('websocket.disconnect',cmd.disconnect),
    route('websocket.receive',cmd.getCommandInfo)
]



command_send = [
    route('websocket.connect',cmds.connect),
    route('websocket.disconnect',cmds.disconnect),
    route('websocket.receive',cmds.postCommand)
]


event_channels = [
    route('websocket.connect',evt.connect),
    route('websocket.disconnect',evt.disconnect),
    route('websocket.receive',evt.getEvents)
]

video = [
    route('websocket.connect',vid.connect),
    route('websocket.disconnect',vid.disconnect),
    route('websocket.receive',vid.getVideo)
]


channel_routing = [

                   include(instance,path='^/inst/'),
                   include(directory,path='^/dir/'),
                   include(default_instance,path='^/defaultInst/'),
                   include(telemetry_subscribe,path='^/tlm_s/'),
                   include(command_info,path='^/cmd_i/'),
                   include(command_send,path='^/cmd_s/'),
                   include(event_channels,path='^/event/'),
                   include(video, path='^/video/'),

]

