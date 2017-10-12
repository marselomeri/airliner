import socket
from struct import pack
from struct import unpack
from arte_ccsds import *
import time

class ArteClient(object):
    def __init__(self, ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((ip, port))
        self.sequence = 0
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

    def send_ready(self):
        #TODO add try catch
        print("sending ready to ARTE server")
        self.telemetry_packet.set_current_time()
        self.sock.sendall(self.telemetry_packet.get_encoded())
        
    def send_shutdown(self):
        #TODO add try catch
        print("sending shutdown to ARTE server")
        self.telemetry_packet.PriHdr.StreamId.bits.app_id = 1
        self.telemetry_packet.set_current_time()
        self.sock.sendall(self.telemetry_packet.get_encoded())
        self.telemetry_packet.PriHdr.StreamId.bits.app_id = 0
    
    def receive_response(self):
        print("waiting for response from ARTE server")
        response = self.sock.recv(self.command_packet.get_packet_size())
        self.command_packet.set_decoded(response)
        self.decode_sequence()
    
    def decode_sequence(self):
        self.sequence = self.command_packet.PriHdr.Sequence.bits.count
        print("sequence count from ARTE server = ", self.sequence)
        
    def close_conn(self):
        self.sock.close()

#Delete me -->
def client(ip, port, header):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    try:
        #send message
        sock.sendall(header)
        
        #receive response
        command_header = CCSDS_CmdPkt_t()
        response_header = sock.recv(command_header.get_packet_size())
        print("after receive response = ", response_header)
        command_header.set_decoded(response_header)

        time.sleep(3)
        
        #send message
        sock.sendall(header)
        
        #receive response
        command_header = CCSDS_CmdPkt_t()
        response_header = sock.recv(command_header.get_packet_size())
        print("after receive response = ", response_header)
        command_header.set_decoded(response_header)
        
        time.sleep(3)
        
        # send shutdown message
        shutdown_msg = CCSDS_TlmPkt_t()
        shutdown_msg.init_packet()
        shutdown_msg.set_current_time()
        shutdown_msg.set_user_data_length(0)
        shutdown_msg.PriHdr.StreamId.bits.app_id = 1
        sock.sendall(shutdown_msg.get_encoded())
        
        # receive last message
        response_header = sock.recv(command_header.get_packet_size())
        
    finally:
        sock.close()
#<-- Delete me

if __name__ == "__main__":
    
    IP, PORT = "localhost", 9999

    client = ArteClient(IP, PORT)
    for x in range(0, 10):
        client.send_ready()
        time.sleep(1)
        client.receive_response()
    client.send_shutdown()
    client.close_conn()


