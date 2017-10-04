"""

   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
 3. Neither the name Windhover Labs nor the names of its 
    contributors may be used to endorse or promote products derived 
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

"""
import socket
import sys
import threading
import msg_pb2
from struct import unpack
from struct import pack
from arte_ccsds import *
from arte_time import *

try:
    import socketserver
except Exception:
    print ("python3 socketserver not found. Must be python2.")

def message_handler(message, threadname):
    print(message + " " + threadname)


class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):

    def handle(self):
        time_source = ArteTimeSource(0, .25)
        time_source.set_start_time()
        cur_thread = threading.current_thread()
        telemetry_packet = CCSDS_TlmPkt_t()
        # receive message
        header = self.request.recv(telemetry_packet.get_packet_size())
        telemetry_packet.set_decoded(header)
        message_length = telemetry_packet.get_user_data_length() 
        print ("received message timestamp :", telemetry_packet.get_time())
        
        message = self.request.recv(message_length)
        pb_message = msg_pb2.test_msg()
        pb_message.ParseFromString(message)
        message_handler(pb_message.content, cur_thread.name)
        
        # decrement the client count
        ArteServerGlobals.client_count -= 1
        
        if ArteServerGlobals.client_count == 0:
            # if all clients have connected release any threads that
            # are waiting
            with ArteServerGlobals.condition:
                print("all clients connected")
                ArteServerGlobals.condition.notify_all()
            # wait for all clients to connect
            ''' Note on acquire/release for condition
            All of the objects provided by a module that has acquire() 
            and release() methods can be used as context managers for a with 
            statement. The acquire() method will be called when the block 
            is entered, and release() will be called when the block is exited 
            (see https://docs.python.org/3/library/threading.html#with-locks)
            '''
        else:
            with ArteServerGlobals.condition:
                print("client connected, waiting for all clients to connect")
                ArteServerGlobals.condition.wait()

        # send response
        test_response = msg_pb2.next_step()
        test_response.seconds, test_response.subseconds = time_source.get_time()
        encoded = test_response.SerializeToString(test_response)
        # prepare header
        command_header = CCSDS_CmdPkt_t()
        command_header.init_packet()
        command_header.set_user_data_length(len(encoded))
        # send encoded header
        self.request.sendall(command_header.get_encoded())
        # send payload
        self.request.sendall(encoded)
        print("server sent response")


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass


class ArteServer(object):
    """

    Args:
        host (str): IP address.
        port (int): Port number.
        client_count (int): Number of clients that will connect. 

    """
    def __init__(self, host, port, client_count):
        self.host = host
        self.port = port
        self.client_count = client_count
        # set the shared client count
        ArteServerGlobals.client_count = self.client_count
        # prevent error 98 Address already in use when relaunching 
        socketserver.TCPServer.allow_reuse_address = True
        self.server = ThreadedTCPServer((self.host, self.port), ThreadedTCPRequestHandler)
        # start a thread with the server -- that thread will then start one
        # more thread for each request
        self.server_thread = threading.Thread(target=self.server.serve_forever)
        # exit the server thread when the main thread terminates
        self.server_thread.daemon = True
        self.server_thread.start()
        print ("ARTE server loop running in thread: ", self.server_thread.name)


class ArteServerGlobals:
    """Shared data between server and client threads."""
    client_count = 0
    condition = threading.Condition()
