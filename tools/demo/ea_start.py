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
flag = True

ea_payload = ea_start_pb2.ea_start_pb()
ea_payload.interpreter = "/usr/bin/python"
ea_payload.script = "/home/vagrant/Desktop/fibbig.py"

ea_header = bytearray([0x1c, 0x29, 0xc0, 0x27, 0x00, 0x81, 0x00, 0x02])
ea_start = str(ea_header) + ea_payload.SerializeToString()

soc.sendto(ea_start, cfs)

while True:
	time.sleep(3)
	try:
		print "Sending cmd"
		#soc.sendto(ea_start, cfs)
	except socket.error, e:
		if isinstance(e.args, tuple):
			print "errno %d" % e[0]
			if e[0] == errno.EPIPE:
				print "Detected remote disconnect"
			else:
				pass
		else:
			print "socket error ", e
			remote.close()
			break

