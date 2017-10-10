import socket
from struct import pack
from struct import unpack
from arte_ccsds import *
import msg_pb2
import time

def client(ip, port, header):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    try:
        #send message
        sock.sendall(header)
        
        #receive response
        command_header = CCSDS_CmdPkt_t()
        print("before receive response")
        response_header = sock.recv(command_header.get_packet_size())
        print("after receive response = ", response_header)
        command_header.set_decoded(response_header)
        message_length = command_header.get_user_data_length()
        print("message_length", message_length)
        response = sock.recv(message_length)
        pb_message = msg_pb2.next_step()
        pb_message.ParseFromString(response)
        print ("client received message: ", pb_message.microseconds)
        
        time.sleep(5)
        
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
        
if __name__ == "__main__":
    
    IP, PORT = "localhost", 9999

    # prepare the ccsds header
    header = CCSDS_TlmPkt_t()
    header.init_packet()
    header.set_current_time()
    header.set_user_data_length(0)

    print("client 1 is ready, notify server")
    client(IP, PORT, header.get_encoded())

