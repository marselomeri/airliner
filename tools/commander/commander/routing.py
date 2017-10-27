from channels.routing import route,include
from groundcontrol.consumers import *

video_socket=[route('websocket.connect',v_ws_connect),
                   route('websocket.disconnect',v_ws_disconnect),
                   route('websocket.receive',v_ws_echo)
                  ]

data_socket=[route('websocket.connect',connect),
                   route('websocket.disconnect',disconnect),
                   route('websocket.receive',echo)
                  ]

directory_socket = [route('websocket.connect',connect),
                   route('websocket.disconnect',disconnect),
                   route('websocket.receive',getDirListing)
                  ]

hps_socket = [route('websocket.connect',connect),
                   route('websocket.disconnect',disconnect),
                   route('websocket.receive',hps)
                  ]



channel_routing = [
                   include(video_socket,path='^/groundcontrol_video_socket/'),
                   include(data_socket,path='^/data/'),
                   include(directory_socket,path='^/dir/'),
include(hps_socket, path='^/hps/')
]
