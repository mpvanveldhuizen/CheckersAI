#!/usr/bin/env python
import socket
import os
import sys
import re
from msg import checkersMessage
PORT = 42069
HOST = ''


if __name__=='__main__':
	

	msg=checkersMessage()
	msg.printBoard()

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	s.bind((HOST, PORT))
	s.listen(1)

	conn1, addr1 = s.accept()

	startFlag=0

	print 'Connected by', addr1
	data=conn1.recv(1024)
	if data=="Ready to Play":
		startFlag+=1

	conn2, addr2 = s.accept()
	print 'Connected by', addr2
	data=conn2.recv(1024)
	
	if data=="Ready to Play":
		startFlag+=1	

	while True:
		conn1.sendall(msg.toString())
		data=conn1.recv(1024)
		print("Red move")
		msg.fromString(data)
		msg.printBoard()
		sts=msg.getStatus()

		if sts==3:
			conn2.sendall("Game over")

			print("red has won")
			s.close()
			break
		elif sts!=0:
			conn2.sendall("Stopping game due to illegal move")
			print("illegal move black")
			s.close()
			break
		conn2.sendall(msg.toString())
		
		data=conn2.recv(1024)
		print("Black move")
		msg.fromString(data)
		msg.printBoard()
		if sts==3:
			conn1.sendall("Game over")
			print("black has won")
			s.close()
			break
		elif sts!=0:
			conn1.sendall("Stopping game due to illegal move")
			print("red has made an illegal move")
			s.close()
			break		
