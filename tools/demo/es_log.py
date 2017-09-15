"""
Sprint 4 demo
"""

import socket
import os
import sys
import time
import errno
import es_log_pb2

cfs = ('', 5010)
soc = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
flag = True


es_payload_o = es_log_pb2.es_log_pb()
es_payload_o.Mode = 1
es_payload_d = es_log_pb2.es_log_pb()
es_payload_d.Mode = 0

#header 18 06 c0 0a 00 05 00 12
#es_overwrite = bytearray([0x18, 0x06, 0xc0, 0x03, 0x00, 0x05, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00 ])
#es_discard = bytearray([0x18, 0x06, 0xc0, 0x04, 0x00, 0x05, 0x00, 0x12, 0x01, 0x00, 0x00, 0x00])
es_cmd_hdr = bytearray([0x18, 0x06, 0xc0, 0x00, 0x00, 0x05, 0x00, 0x12])
es_overwrite = str(es_cmd_hdr) + es_payload_o.SerializeToString()
es_discard = str(es_cmd_hdr) + es_payload_d.SerializeToString()

print len(es_cmd_hdr)
print len(es_overwrite)
print len(es_discard)

while True:
	time.sleep(3)
	try:
		if flag:
			soc.sendto(es_cmd_hdr, cfs)
			flag = False
		else:
			soc.sendto(es_cmd_hdr, cfs)
			flag = True
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

