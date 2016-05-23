#!/usr/bin/env python
#Matt Van Veldhuizen and Ben Bettisworth
#Client for the Checkers Game

import socket
import check 
import sys
import getopt
from Tkinter import *

def rotate(boardState,n):
    return boardState[n:] + boardState[:n]

def pb(board, color):
	out = "";
	if color == "red":
		out = "Red Players Move\n"
	if color == "black":
		out = "Black Players Move\n"
	
	for i in range(1,65):
		if board[i] == "1":
			out += "[r] "
		if board[i] == "3":
			out += "[b] "
		if board[i] == "0":
			out += "[ ] "
		if board[i] == "8":
			out += "[_] "
		if board[i] == "5":
			out += "[R] "
		if board[i] == "7":
			out += "[B] "
		if i%8 == 0:
			out += "\n"
	return out

if __name__ == "__main__":
	if len(sys.argv) == 1:
		print "no ip addr or input file exiting"
		sys.exit()
	if sys.argv[1] == "-f":
		if len(sys.argv) == 2:
			print "no file given exiting"
			sys.exit()
		else:
			infile = sys.argv[2]
	if len(sys.argv) == 3:
		TCP_IP = '127.0.0.1'
	else:
		if sys.argv[3] == "-ip":
			if len(sys.argv) == 4:
				print "no ip given exiting"
				sys.exit()
			else:
				TCP_IP = sys.argv[4]
	if sys.argv[1] == "-h":
		print "usage:"
		print "client.py -f <inputfile> -ip <ipaddr>"
		print "client.py -f <inputfile>"
		sys.exit()

	TCP_PORT = 42069
	BUFFER_SIZE = 1024
	INITIALBOARD = "01818181881818181181818188080808008080808838383833838383883838383"
	newBoard = INITIALBOARD
	boardState = []
	master = Tk()
	text = Text(master)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((TCP_IP, TCP_PORT))
	s.send("Ready to Play")

	data = s.recv(BUFFER_SIZE)
	if data == INITIALBOARD:
		master.wm_title("Red Player")
		while True:
			newBoard = check.redBoard(data, newBoard, infile)
			s.send(newBoard)
			text.delete(1.0, END)
			text.insert(INSERT, pb(newBoard,"red"))
			text.pack()
			data = s.recv(BUFFER_SIZE)
			if(len(boardState) == 5):
				boardState = rotate(boardState, 1)
				boardState[4] = data
				if(boardState[0] == boardState[2] and boardState[1] == boardState[3]):
					tmp = list(data)
					tmp[0] = "7"
					d = "".join(tmp)
					s.send(d)
					print "cycle detected"
					s.close()
					sys.exit()
			else:
				boardState.append(data)
			text.insert(END, pb(data,"black"))
			text.pack()
			text.update()
	else:
		master.wm_title("Black Player")
		while True:
			newBoard = check.blackBoard(data, newBoard, infile)
			s.send(newBoard)
			text.delete(1.0, END)
			text.insert(INSERT, pb(newBoard,"black"))
			text.pack()
			data = s.recv(BUFFER_SIZE)
			if(len(boardState) == 5):
				boardState = rotate(boardState, 1)
				boardState[4] = data
				if(boardState[0] == boardState[2] and boardState[1] == boardState[3]):
					tmp = list(data)
					tmp[0] = "7"
					d = "".join(tmp)
					s.send(d)
					print "cycle detected"
					s.close()
					sys.exit()
			else:
				boardState.append(data)
			text.insert(END, pb(data,"red"))
			text.pack()
			text.update()
