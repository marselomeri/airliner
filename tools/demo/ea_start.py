"""
Sprint 4 demo
"""

import socket
import os
import sys
import time
import errno
import ea_start_pb2

cfs = ('', 5010)
soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

ea_payload = ea_start_pb2.ea_start_pb()
ea_payload.interpreter = "/usr/bin/python"
ea_payload.script = "/home/vagrant/Desktop/fibbig.py"

ea_header = bytearray([0x1c, 0x29, 0xc0, 0x27, 0x00, 0x81, 0x00, 0x02])
ea_start = str(ea_header) + ea_payload.SerializeToString()

soc.sendto(ea_start, cfs)
