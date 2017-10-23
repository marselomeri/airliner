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
import logging
import errno
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
    """The request handler for ARTE server.
    
    Args:
        event_handler (:obj: ArteEventHandler): An instance of an 
        ArteEventHandler object.
        client_count (int): Number of clients that will connect.
        timeout (unsigned int): The timeout value used for anything
        that pends forever.
    
    Class Attributes:
        client_count (unsigned int): The total client count.
        client_ready_count (unsigned int): The client counter used for
        counting "ready" clients each frame step.
        client_ready_condition (:obj: threading.Condition()): A 
        conditional variable object for thread synchronization.
        shutdown_flag (boolean): A while loop flag for threads.
        
    Attributes:
        
    

    """
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
        self.timeout = timeout
        # call the parent constructor
        socketserver.BaseRequestHandler.__init__(self, request, client_address, server)
        self.request.settimeout(self.timeout)

    def recv_message(self, cur_thread):
        """Receive an ARTE client message over TCP socket.
        
        Args:
            cur_thread ("obj" threading.thread): The current thread.
        
        Returns:
            True for success, and False for failure.
        """
        returnBool = False
        # TODO edge cases for receive. timeouts, interrupts, errors etc
        # request.recv is a socket object
        logging.debug('About to receive message %s', cur_thread)
        try:
            packet = self.request.recv(self.telemetry_packet_size)
            logging.debug('packet len received %d', len(packet))
            if len(packet) == self.telemetry_packet_size:
                self.telemetry_packet.set_decoded(packet)
                logging.debug('received message timestamp %s:%s', self.telemetry_packet.get_time(), cur_thread)
                self.decode_message(cur_thread)
                returnBool = True
            elif len(packet) == 0:
                logging.error('client closed connection %s', cur_thread)
        except socket.timeout:
            logging.error('ARTE Server socket receive timed out %s', cur_thread)
        return returnBool
        
    def initiate_shutdown(self, returnCode):
        """Shutdown for use when ARTE cannot continue.
        
        Args:
            returnCode (unsigned int): The return code that ARTE should
            use when it exits. 
        """
        # set the return code
        self.event_handler.returnCode = returnCode
        # notify the event handler
        self.event_handler.shutdown_notification.set()
        # set the shutdown flag
        ThreadedTCPRequestHandler.shutdown_flag = False
        
    def decode_message(self, cur_thread):
        """Decode a message from ARTE clients."""
        returnCode = 0
        # if app_id > 0 we've received a shutdown requests
        if self.telemetry_packet.PriHdr.StreamId.bits.app_id > 0:
            # if app_id == 1 the client test(s) succeeded
            if self.telemetry_packet.PriHdr.StreamId.bits.app_id == 1:
                logging.info('received shutdown message and success %s', cur_thread)
            # if app_id == 2 the client test(s) failed
            elif self.telemetry_packet.PriHdr.StreamId.bits.app_id == 2:
                logging.info('received shutdown message and failure %s', cur_thread)
                returnCode = 1
            # if we've received an unknown test outcome code
            else:
                logging.error('received shutdown message and unknown status %s', cur_thread)
                returnCode = 3
            # For now break out of the thread that received the 
            # shutdown request
            self.initiate_shutdown(returnCode)
            
    def send_response(self, cur_thread):
        """Send a response to an ARTE client.
        
        Args:
            cur_thread ("obj" threading.thread): The current thread.
        
        Returns:
            True for success, and False for failure.
        """
        returnBool = False
        try:
            self.request.sendall(self.command_packet.get_encoded())
            logging.debug('server sent response %s', cur_thread)
            # increment the sequence count
            if self.command_packet.PriHdr.Sequence.bits.count == 16383:
                self.command_packet.PriHdr.Sequence.bits.count = 1
            else:
                self.command_packet.PriHdr.Sequence.bits.count += 1
            returnBool = True
        except socket.error as e:
            if e.errno == errno.EPIPE:
                logging.error('broken pipe error %s', cur_thread)
            else:
                logging.error('socket send error %s', cur_thread)
        return returnBool

    def handle(self):
        """The overriden BaseRequestHandler class handle method.
    
        Note:
            This method will process incoming requests.
        """
        cur_thread = threading.current_thread()

        while ThreadedTCPRequestHandler.shutdown_flag:

            if self.recv_message(cur_thread):
                with ThreadedTCPRequestHandler.client_ready_condition:
                    # decrement the client count
                    ThreadedTCPRequestHandler.client_ready_count -= 1
                    if ThreadedTCPRequestHandler.client_ready_count == 0 and ThreadedTCPRequestHandler.shutdown_flag:
                        logging.debug('all clients ready')
                        # if all clients have connected release any threads that
                        # are waiting
                        ThreadedTCPRequestHandler.client_ready_condition.notify_all()
                        self.send_response(cur_thread)
                        # reset the client connect count
                        ThreadedTCPRequestHandler.client_ready_count = ThreadedTCPRequestHandler.client_count
                    elif ThreadedTCPRequestHandler.shutdown_flag:
                        # wait for all clients to connect
                        logging.debug('client ready, waiting for all clients... %s', cur_thread)
                        ThreadedTCPRequestHandler.client_ready_condition.wait()
                        if ThreadedTCPRequestHandler.shutdown_flag:
                                # send "next step" to all clients
                                if self.send_response(cur_thread):
                                    pass
                                else:
                                    logging.error('thread encountered a send error %s', cur_thread)
                                    self.initiate_shutdown(4)
                                    break
                        else:
                            logging.info('shutdown flag encountered on wakeup %s', cur_thread)
                            # shutdown flag has been set...
                            break
                    else:
                        logging.info('shutdown flag encountered %s', cur_thread)
                        # shutdown flag has been set...
                        break
            else:
                # Recieve error or client close connection
                logging.error('thread encountered a receive error %s', cur_thread)
                self.initiate_shutdown(4)
                break
        # we're outside the while loop so the shutdown flag has been 
        # raised
        logging.debug('thread done %s', cur_thread.name)


class ThreadedTCPServer(socketserver.ThreadingMixIn, EventDrivenTCPServer):
    pass


class ArteServer(object):
    """ArteServer used for inter-process TCP synchronization.

    Args:
        host (str): IP address.
        port (int): Port number.
        client_count (int): Number of clients that will connect.
        event_handler (:obj: ArteEventHandler): An instance of an 
        ArteEventHandler object.
        timeouts (unsigned int): The timeouts value used for anything
        that pends forever.

    Attributes:
        host (str): IP address.
        port (int): Port number.
        client_count (unsigned int): The number of clients in the 
        configuration file.
        event_handler (:obj: ArteEventHandler): An instance of an 
        ArteEventHandler object. Callbacks are assigned to the 
        server_startup and server_shutdown EventHandler objects.
        timeouts (unsigned int): The timeouts value used for anything
        that pends forever.
        server (:obj: ThreadedTCPServer) An extended instance of
        socketserver ThreadingMixIn and TCPServer.
        server_thread (:obj: threading.Thread) The main server thread
        which will spawn other threads for each new connection.

    """
    def __init__(self, host, port, client_count, event_handler, timeouts):
        self.host = host
        self.port = port
        self.client_count = client_count
        self.timeouts = timeouts
        # register server_startup and shutdown with the event handler
        self.event_handler = event_handler
        self.event_handler.startup += self.server_startup
        self.event_handler.shutdown += self.server_shutdown

    def server_startup(self, sender):
        # prevent error 98 Address already in use when relaunching 
        socketserver.TCPServer.allow_reuse_address = True
        self.server = ThreadedTCPServer((self.host, self.port), ThreadedTCPRequestHandler, self.event_handler, self.client_count, self.timeouts)
        # start a thread with the server -- that thread will then start one
        # more thread for each request
        self.server_thread = threading.Thread(target=self.server.serve_forever)
        # exit the server thread when the main thread terminates
        self.server_thread.daemon = True
        self.server_thread.start()
        logging.info('ARTE server loop running in thread %s', self.server_thread.name)

    def server_shutdown(self, sender):
        logging.info('reached server_shutdown()')
        ThreadedTCPRequestHandler.shutdown_flag = False
        # Go ahead and notify any waiting threads
        with ThreadedTCPRequestHandler.client_ready_condition:
            ThreadedTCPRequestHandler.client_ready_condition.notify_all()
        time.sleep(1)
        logging.debug('threading.enumerate() %s', threading.enumerate())
        self.server.shutdown()
        logging.debug('threading.enumerate() %s', threading.enumerate())
        #self.server_thread.join(1)
