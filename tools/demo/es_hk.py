"""
Sprint 4 demo
"""

import socket
import os
import sys
import time
import errno
import es_hk_pb2

soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
soc.connect(("127.0.0.1", 5012))

es_hk = es_hk_pb2.es_hk_pb()

while True:
	print "Waiting for msg"
	time.sleep(1)
	tlm = soc.recv(64)
	es_hk.ParseFromString(tlm)
	


# Overwrite cmd
es_payload_o = es_log_pb2.es_log_pb()
es_payload_o.Mode = 1
# Discard cmd
es_payload_d = es_log_pb2.es_log_pb()
es_payload_d.Mode = 0

