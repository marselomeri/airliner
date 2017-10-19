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
import time
from struct import unpack
from struct import pack
from arte_ccsds import *
from arte_time import *

try:
    import socketserver
except Exception:
    print ("python3 socketserver not found. Must be python2.")


class EventDrivenTCPServer(socketserver.TCPServer):
    """Base class for various socket-based server classes extended
       to add an event_handler argument. The request handler will be
       called with an event_handler object.
    """
    def __init__(self, server_address, RequestHandlerClass, event_handler, client_count, timeout, bind_and_activate=True):
        self.event_handler = event_handler
        self.client_count = client_count
        self.timeout = timeout
        socketserver.TCPServer.__init__(self, server_address, RequestHandlerClass, bind_and_activate=True)
        
    def finish_request(self, request, client_address):
        """Finish one request by instantiating RequestHandlerClass.
           Now extended with an event_handler argument.
        """
        self.RequestHandlerClass(request, client_address, self, self.event_handler, self.client_count, self.timeout)


class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):
    client_count = 0
    client_ready_count = 0
    client_ready_condition = threading.Condition()
    shutdown_flag = True

    def __init__(self, request, client_address, server, event_handler, client_count, timeout):
        self.event_handler = event_handler
        ThreadedTCPRequestHandler.client_count = client_count
        ThreadedTCPRequestHandler.client_ready_count = client_count
        # Set up telemetry packet
        self.telemetry_packet = CCSDS_TlmPkt_t()
        self.telemetry_packet.clear_packet()
        self.telemetry_packet.init_packet()
        self.telemetry_packet.set_user_data_length(0)
        self.telemetry_packet_size = self.telemetry_packet.get_packet_size()
        # Set up command  packet
        self.command_packet = CCSDS_CmdPkt_t()
        self.command_packet.clear_packet()
        self.command_packet.init_packet()
        self.command_packet.set_user_data_length(0)
        self.command_packet.PriHdr.Sequence.bits.count = 1
        # call the parent constructor
        socketserver.BaseRequestHandler.__init__(self, request, client_address, server)
        self.request.settimeout(timeout)

    def recv_message(self, cur_thread):
        # TODO edge cases for receive. timeouts, interrupts, errors etc
        # request.recv is a socket object
        packet = bytes(0)
        while len(packet) != self.telemetry_packet_size:
            packet = self.request.recv(self.telemetry_packet_size)
            if len(packet) == self.telemetry_packet_size:
                self.telemetry_packet.set_decoded(packet)
                print ("received message timestamp :", self.telemetry_packet.get_time(), cur_thread)
                self.decode_message(cur_thread)
        
    def decode_message(self, cur_thread):
        # if app_id > 0 we've received a shutdown requests
        if self.telemetry_packet.PriHdr.StreamId.bits.app_id > 0:
            # if app_id == 1 the client test(s) succeeded
            if self.telemetry_packet.PriHdr.StreamId.bits.app_id == 1:
                print("received shutdown message and success", cur_thread)
            # if app_id == 2 the client test(s) failed
            elif self.telemetry_packet.PriHdr.StreamId.bits.app_id == 2:
                print("received shutdown message and failure", cur_thread)
                self.event_handler.returnCode = 1
            # if we've received an unknown test outcome code
            else:
                print("received shutdown message and unknown status", cur_thread)
                self.event_handler.returnCode = 2
            # notify the event handler
            self.event_handler.shutdown_notification.set()
    
    def send_response(self, cur_thread):
        self.request.sendall(self.command_packet.get_encoded())
        print("server sent response", cur_thread)
        # increment the sequence count
        self.command_packet.PriHdr.Sequence.bits.count += 1

    def handle(self):
        # TODO

        cur_thread = threading.current_thread()
        
        while ThreadedTCPRequestHandler.shutdown_flag:
            try:
                self.recv_message(cur_thread)
            except socket.timeout:
                print("ARTE Server socket receive timed out", cur_thread)

            with ThreadedTCPRequestHandler.client_ready_condition:
                # decrement the client count
                ThreadedTCPRequestHandler.client_ready_count -= 1
                if ThreadedTCPRequestHandler.client_ready_count == 0 and ThreadedTCPRequestHandler.shutdown_flag:
                    print("all clients ready")
                    # if all clients have connected release any threads that
                    # are waiting
                    ThreadedTCPRequestHandler.client_ready_condition.notify_all()
                    self.send_response(cur_thread)
                    # reset the client connect count
                    ThreadedTCPRequestHandler.client_ready_count = ThreadedTCPRequestHandler.client_count
                elif ThreadedTCPRequestHandler.shutdown_flag:
                    # wait for all clients to connect
                    print("client ready, waiting for all clients...", cur_thread)
                    ThreadedTCPRequestHandler.client_ready_condition.wait()
                    if ThreadedTCPRequestHandler.shutdown_flag:
                        # send "next step" to all clients
                        self.send_response(cur_thread)
                    else:
                        break
                else:
                    break
        # we're outside the while loop so the shutdown flag has been 
        # raised
        print("thread done = ", cur_thread.name)


class ThreadedTCPServer(socketserver.ThreadingMixIn, EventDrivenTCPServer):
    pass


class ArteServer(object):
    """

    Args:
        host (str): IP address.
        port (int): Port number.
        client_count (int): Number of clients that will connect. 

    """
    def __init__(self, host, port, client_count, event_handler, timeout):
        self.host = host
        self.port = port
        self.client_count = client_count
        self.timeout = timeout
        # register server_startup and shutdown with the event handler
        self.event_handler = event_handler
        self.event_handler.startup += self.server_startup
        self.event_handler.shutdown += self.server_shutdown
    
    def server_startup(self, sender):
        # prevent error 98 Address already in use when relaunching 
        socketserver.TCPServer.allow_reuse_address = True
        self.server = ThreadedTCPServer((self.host, self.port), ThreadedTCPRequestHandler, self.event_handler, self.client_count, self.timeout)
        # start a thread with the server -- that thread will then start one
        # more thread for each request
        self.server_thread = threading.Thread(target=self.server.serve_forever)
        # exit the server thread when the main thread terminates
        self.server_thread.daemon = True
        self.server_thread.start()
        print ("ARTE server loop running in thread: ", self.server_thread.name)

    def server_shutdown(self, sender):
        print("reached server_shutdown()")
        ThreadedTCPRequestHandler.shutdown_flag = False
        # Go ahead and notify any waiting threads
        with ThreadedTCPRequestHandler.client_ready_condition:
            ThreadedTCPRequestHandler.client_ready_condition.notify_all()
        time.sleep(1)
        print("threading.enumerate() ", threading.enumerate())
        self.server.shutdown()
        print("threading.enumerate() ", threading.enumerate())
        #self.server_thread.join(1)
