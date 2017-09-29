"""
Sprint 4 demo
"""

import socket
import os
import sys
import time
import errno

from arte_ccsds import *

cfs = ('', 5010)

#ea_noop = "28 41 192 34 0 1 0 0"
#ea_noop = "2841192320100"
#ea_noop = ''.join(chr(x) for x in [0x1c, 0x29, 0xc0, 0x23, 0x00, 0x01, 0x00, 0x00])
command_packet = CCSDS_CmdPkt_t()
ea_noop = bytes.fromhex("1c29c02300010000")
command_packet.set_decoded(ea_noop)
print (ea_noop)

soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 

while True:
    time.sleep(1)

    soc.sendto(command_packet.get_encoded(), cfs)

