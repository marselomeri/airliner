import socket
from struct import pack
from struct import unpack
from arte_ccsds import *
import msg_pb2

def client(ip, port, header, message):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    try:
        #send message
        sock.sendall(header)
        sock.sendall(message)

        #receive response
        response_header = sock.recv(8)
        command_header = CCSDS_CmdPkt_t()
        command_header.set_decoded(response_header)
        message_length = command_header.get_user_data_length()
        
        response = sock.recv(message_length)
        pb_message = msg_pb2.next_step()
        pb_message.ParseFromString(response)
        print ("client received message: ", pb_message.seconds, pb_message.subseconds)
        
    finally:
        sock.close()
        
if __name__ == "__main__":
    
    IP, PORT = "localhost", 9999
    
    test_message = msg_pb2.test_msg()
    test_message.content = "Test client is ready!"
    encoded = test_message.SerializeToString()
    
    # prepare the ccsds header
    header = CCSDS_TlmPkt_t()
    header.init_packet()
    header.set_current_time()
    header.set_user_data_length(len(encoded))

    print("client 2 is ready, notify server")
    client(IP, PORT, header.get_encoded(), encoded)
    

