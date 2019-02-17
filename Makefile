################################################################
#	Name: Kendall Jordan
#	Username: cssc0443
#	Course: CS530 Spring 2019
#   Project: Assignment #1: Basic Hexdump Program
#	File: Makefile
#	Last Date Modified: Feb 18, 2019
################################################################

xbd: main.o message.o
	g++ main.o message.o -o xbd

main.o: main.cpp
	g++ -c main.cpp

message.o: message.cpp message.h
	g++ -c message.cpp

clean:
	rm *.o xbd

####################### [EOF: Makefile ] #######################