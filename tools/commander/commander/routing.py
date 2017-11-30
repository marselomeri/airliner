from channels.routing import route,include,route_class
from groundcontrol.consumers import *


mc = MyCache()
mc.initialize()

ins = Instance()
dir = Directory()

evt = Event()
vid = Video()

tlm = Telemetry()
cmd = Command()
cmds = Command()







#-----------------------------------------------------------

#ins = Instance()

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
#-----------------------------------------------------------
#dir = Directory()

directory = [
    route('websocket.connect',dir.connect),
    route('websocket.disconnect',dir.disconnect),
    route('websocket.receive',dir.directoryListing)
]
#-----------------------------------------------------------
#tlm = Telemetry()

telemetry_subscribe = [
    route('websocket.connect',tlm.connect),
    route('websocket.disconnect',tlm.disconnect),
    route('websocket.receive',tlm.getTelemetry),

]




#-----------------------------------------------------------
#cmd = Command()

command_info = [
    route('websocket.connect',cmd.connect),
    route('websocket.disconnect',cmd.disconnect),
    route('websocket.receive',cmd.getCommandInfo)
]

#cmds = Command()

command_send = [
    route('websocket.connect',cmds.connect),
    route('websocket.disconnect',cmds.disconnect),
    route('websocket.receive',cmds.postCommand)
]
#-----------------------------------------------------------
#event=Event()

event_channels = [
    route('websocket.connect',evt.connect),
    route('websocket.disconnect',evt.disconnect),
    route('websocket.receive',evt.getEvents)
]

#-----------------------------------------------------------
#vid = Video()
video = [
    route('websocket.connect',vid.connect),
    route('websocket.disconnect',vid.disconnect),
    route('websocket.receive',vid.getVideo)
]

#-----------------------------------------------------------




#-----------------------------------------------------------


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

