from websocket import create_connection
import  toolkit as tk
import time
import socket
import base64

def VideoThroughUDP():
    UDP_IP = '127.0.0.1'
    UDP_PORT = 3001
    video_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP
    video_socket.bind(("", UDP_PORT))

    print 'plug1'
    while True:
        print video_socket.recvfrom(65527)
        data, addr = video_socket.recvfrom(65527)  # buffer size is 1024 bytes

        print data, addr
        b64_img = base64.b64encode(data)
        video_frame_counter = video_frame_counter + 1
        print 'Frame# : [' + str(video_frame_counter) + '] sent.'

        yield b64_img


buff = VideoThroughUDP().next()