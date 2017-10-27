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
from arte_ccsds import *

try:
    import socketserver
except Exception:
    print ("python3 socketserver not found. Must be python2.")

class MyTCPHandler(socketserver.BaseRequestHandler):
    """
    The request handler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """
    def initial_setup(self):
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
        self.command_packet.PriHdr.StreamId.bits.app_id = 1

    def recv_message(self):
        packet = self.request.recv(self.telemetry_packet_size)
        if len(packet) == self.telemetry_packet_size:
            self.telemetry_packet.set_decoded(packet)
            print ("received message timestamp :", self.telemetry_packet.get_time())

    def send_response(self):
        print("sequence count = ", self.command_packet.PriHdr.Sequence.bits.count)
        # increment the sequence count
        if self.command_packet.PriHdr.Sequence.bits.count == 16383:
            self.command_packet.PriHdr.Sequence.bits.count = 0
        else:
            self.command_packet.PriHdr.Sequence.bits.count += 1
        # increment the minor frame count
        if self.command_packet.PriHdr.StreamId.bits.app_id == 200:
            self.command_packet.PriHdr.StreamId.bits.app_id  = 0
            pass
        else:
            self.command_packet.PriHdr.StreamId.bits.app_id += 1
        # Send the packet
        self.request.sendall(self.command_packet.get_encoded())
        print("server sent response")

    def handle(self):
        self.initial_setup()
        while(1):
            self.recv_message()
            #input("Press Enter to continue...")
            for x in range(0, 199):
                self.send_response()
                self.recv_message()
                x += 1
            self.send_response()

class ArteRepl(object):
    def __init__(self):
        print("Server object created")
        HOST, PORT = "localhost", 9999
        # Create the server, binding to localhost on port 9999
        socketserver.TCPServer.allow_reuse_address = True
        self.server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)
        
    def run(self):
        print("waiting for connection...")
        self.server.handle_request()


def init_repl():
    r = ArteRepl
    r.__init__(r)
    r.run(r)

    

