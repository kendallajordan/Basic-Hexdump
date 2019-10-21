################################################################
#	Name: Kendall Jordan
#       Project: Basic Hexdump Program
#	File: Makefile
#	Last Date Modified: Feb 18, 2019
################################################################

# Variables
EXEC = xbd			# Executable file
CC = g++			# Compiler
CFLAGS = -c -Wall	# Compiler flags
					# -c is for compilation, 
					# -Wall is for most compiler warnings

# Command list
# Substitute variables into action section using $(VARIABLE_HERE) format
all: $(EXEC)

$(EXEC): hexdump.o
	$(CC) hexdump.o -o $(EXEC)

hexdump.o: hexdump.cpp
	$(CC) $(CFLAGS) hexdump.cpp

clean:
	rm -rf *.o $(EXEC)

####################### [EOF: Makefile ] #######################
