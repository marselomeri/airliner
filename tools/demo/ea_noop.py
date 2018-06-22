"""
Sprint 4 demo
"""

import socket
import os
import sys
import time
import errno

cfs = ('', 5010)

#ea_noop = "28 41 192 34 0 1 0 0"
#ea_noop = "2841192320100"
ea_noop = ''.join(chr(x) for x in [0x1c, 0x29, 0xc0, 0x23, 0x00, 0x01, 0x00, 0x00])
print ea_noop

soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 

while True:
	time.sleep(1)
	try:
		soc.sendto(ea_noop, cfs)
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

