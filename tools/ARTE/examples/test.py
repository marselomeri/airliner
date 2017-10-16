import socket
import sys
from arte_ccsds import *

HOST, PORT = "localhost", 9999

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
telemetry_packet = CCSDS_TlmPkt_t()
telemetry_packet.clear_packet()
telemetry_packet.init_packet()
telemetry_packet.set_user_data_length(0)
try:
    # Connect to server and send data
    sock.connect((HOST, PORT))
    sock.sendall(telemetry_packet.get_encoded())

    # Receive data from the server and shut down
    received = sock.recv(1024)
finally:
    sock.close()
