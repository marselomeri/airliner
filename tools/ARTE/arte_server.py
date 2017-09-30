import socket
import sys
import threading
import msg_pb2
from struct import unpack
from struct import pack
from arte_ccsds import *


# Note global for quick testing. Needs to move to extended classes below.
condition = threading.Condition()

# Note global for quick testing.
client_count = 2

try:
    import socketserver
except Exception:
    print ("python3 socketserver not found. Must be python2.")

def message_handler(message, threadname):
    print(message + " " + threadname)


class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):

    def handle(self):
        cur_thread = threading.current_thread()
        # receive message
        header = self.request.recv(12)
        telemetry_packet = CCSDS_TlmPkt_t()
        telemetry_packet.set_decoded(header)
        message_length = telemetry_packet.get_length() 
        print ("received message timestamp :", telemetry_packet.get_time())
        
        message = self.request.recv(message_length)
        pb_message = msg_pb2.test_msg()
        pb_message.ParseFromString(message)
        message_handler(pb_message.content, cur_thread.name)
        
        # decrement the client count
        global client_count
        client_count -= 1
        
        if client_count == 0:
            # if all clients have connected release any threads that
            # are waiting
            with condition:
                print("all clients connected")
                condition.notify_all()
            # wait for all clients to connect
            ''' Note on acquire/release for condition
            All of the objects provided by a module that has acquire() 
            and release() methods can be used as context managers for a with 
            statement. The acquire() method will be called when the block 
            is entered, and release() will be called when the block is exited 
            (see https://docs.python.org/3/library/threading.html#with-locks)
            '''
        else:
            with condition:
                print("client connected, waiting for all clients to connect")
                condition.wait()

        # send response
        test_response = msg_pb2.test_msg()
        test_response.content = "Server says step"
        encoded = test_response.SerializeToString(test_response)
        # prepare header
        command_header = CCSDS_CmdPkt_t()
        command_header.init_packet()
        command_header.set_length(len(encoded))
        # send encoded header
        self.request.sendall(command_header.get_encoded())
        # send payload
        self.request.sendall(encoded)
        print("server sent response")


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass


class arte_server(object):
    def __init__(self, host, port):
        self.host = host
        self.port = port
        # Prevent error 98 Address already in use when relaunching 
        socketserver.TCPServer.allow_reuse_address = True
        self.server = ThreadedTCPServer((self.host, self.port), ThreadedTCPRequestHandler)
        # Start a thread with the server -- that thread will then start one
        # more thread for each request
        self.server_thread = threading.Thread(target=self.server.serve_forever)
        # Exit the server thread when the main thread terminates
        self.server_thread.daemon = True
        self.server_thread.start()
        print ("ARTE server loop running in thread: ", self.server_thread.name)
