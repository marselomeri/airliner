"""
Sprint 4 demo
"""

import socket
import os
import sys
import time

#app_mids = {'ea': }

ea_noop = 2841192300100

soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

num = raw_input("Enter number: ")

soc.connect(('127.0.0.1', 5010))

while True:
	time.sleep(1)
	soc.send(ea_noop)








#if __name__ == "__main__":
	#print "Starting demo"
