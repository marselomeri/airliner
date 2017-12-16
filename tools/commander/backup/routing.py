from channels.routing import route,include,route_class
from groundcontrol.consumers import *

session = ServerSession()


video_socket=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.videoEcho)
                  ]

data_socket=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.simpleEcho)
                  ]

directory_socket = [route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.directoryEcho)
                  ]

hps_socket = [route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.hpsEcho)
                  ]




telemetry_commands =[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.handlerTlmCommand)]

instance=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.getHandler)]
"""
events_alarms=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.handlerEventAlarms)]

directory=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.handlerDirectory)]

misc=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.handlerMisc)]

video=[route('websocket.connect',session.connect),
                   route('websocket.disconnect',session.disconnect),
                   route('websocket.receive',session.handlerVideo)]
"""


channel_routing = [route('websocket.receive',session.setDefaultInstance,path='^/setdefinst/'),
                   include(telemetry_commands,path='^/tlm_cmd/'),
                   include(data_socket,path='^/inst/'),
                   include(directory_socket,path='^/ena/'),
                   include(directory_socket,path='^/dir/'),
                   include(directory_socket,path='^/misc/'),
                   include(directory_socket,path='^/vid/'),
                   include(video_socket,path='^/groundcontrol_video_socket/'),
                   include(data_socket,path='^/data/'),
                   #include(directory_socket,path='^/dir/'),
                   include(hps_socket, path='^/hps/')
]
