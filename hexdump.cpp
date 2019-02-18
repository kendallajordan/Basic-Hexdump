/********************************************************************
 Name: Kendall Jordan
 Username: cssc0443
 Course: CS530 Spring 2019
 Project: Assignment #1: Basic Hexdump Program
 File: hexdump.cpp
 Last Date Modified: Feb 18, 2019
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>
#include "hexdump.h"

using namespace std;

/********************************************************************
Function: void createHeader(int mode)
Description: Creates a table header for the file contents.
Parameters: Input: int mode, Selects header mode (hex = 1, bin = 2)
			Output:
********************************************************************/
void createHeader(int mode){
	int addressWidth = 12;
	int hexValueWidth = 41;
	int binValueWidth = 55;
	char separator = ' ';
	char line = '-';

	cout << left << setw(addressWidth) << setfill(separator) << " Address";
	if(mode == 1)
		cout << left << setw(hexValueWidth) << setfill(separator) << "Data Values";
	else
		cout << left << setw(binValueWidth) << setfill(separator) << "Data Values";
	cout << "Printable";
	cout << setw(80) << setfill(line);
	cout << '\n';
}

/********************************************************************
Function: void toHex(fileName)
Description: Dumps the specified file in ASCII/hex format.
Parameters: Input: string fileName, The file name of the specified file.
			Output: 
********************************************************************/
void toHex(string fileName){
	ifstream inFile;
	int address = 0;
	int numBytes;
	char buffer[16];

	/* Open the file. If it cannot open, exit program */
	inFile.open(fileName, ios::in);
	if(!inFile){
		cout << "Error: Cannot open " << fileName << "\n";
		cout << "Exiting program...\n";
		return;
	}

	/* Create a header table for the file dump contents */
	cout << "\n Hexdump of " << fileName << ":\n\n";
	createHeader(1);

	/* Dump the file contents */
	cout << right << hex << setfill('0');

	while(!inFile.eof()){
		/* Read up to 16 bytes from file each loop and store in buffer */
		for(numBytes = 0; numBytes < 16 && inFile.get(buffer[numBytes]); numBytes++);
		if(numBytes == 0)
			break;

		/* Print address in hexadecimal */
		cout << ' ';
		cout << setw(8) << address;
		cout << ":  ";

		/* Print 16 data values as 8 two-byte pairs, in hexadecimal */
		for(int i = 0; i < 16; i++){
			if(i % 2 == 0 && i != 0)
					cout << ' ';
			if(i < numBytes)
				cout << setw(2) << (unsigned)buffer[i];
			/* Use spaces if final iteration has less than 16 bytes */
			else
				cout << setw(2) << setfill(' ') << ' ';
		}

		/* Print the printable characters, or a period if unprintable */
		cout << "  |";
		for(int i = 0; i < numBytes; i++){
			if(buffer[i] < 32 || buffer[i] > 126)
				cout << '.';
			else
				cout << buffer[i];
		}

		/* Update address location */
		cout << "|\n";
		address += 16;
	}

	/* Close the file */
	inFile.close();
	return;
}

/********************************************************************
Function: void toBin(fileName)
Description: Dumps the specified file in binary format.
Parameter:	Input: String fileName, The file name of the specified file.
			Output:
********************************************************************/
void toBin(string fileName){
	ifstream inFile;
	int address = 0;
	int numBytes;
	char buffer[6];

	/* Open the file. If it cannot open, exit program */
	inFile.open(fileName, ios::in);
	if(!inFile){
		cout << "Error: Cannot open " << fileName << "\n";
		cout << "Exiting program...\n";
		return;
	}

	/* Create a header table for the file dump contents */
	cout << "\n Binary dump of " << fileName << ":\n\n";
	createHeader(2);

	/* Dump the file contents */
	cout << right << hex << setfill('0');

	while(!inFile.eof()){
		/* Read up to 6 bytes from file each loop and store in buffer */
		for(numBytes = 0; numBytes < 6 && inFile.get(buffer[numBytes]); numBytes++);
		if(numBytes == 0)
			break;

		/* Print address in hexadecimal */
		cout << ' ';
		cout << setw(8) << address;
		cout << ":  ";

		/* Print 6 data values as 8-bit binary octets */
		for(int i = 0; i < 6; i++){
			if(i < numBytes){
				bitset<8> b(buffer[i]);
				cout << setw(8) << b;
				cout << ' ';
			}
			/* Use spaces if final iteration has less than 16 bytes */
			else
				cout << setw(9) << setfill(' ') << ' ';
		}

		/* Print the printable characters, or a period if unprintable */
		cout << " |";
		for(int i = 0; i < numBytes; i++){
			if(buffer[i] < 32 || buffer[i] > 126)
				cout << '.';
			else
				cout << buffer[i];
		}

		/* Update address location */
		cout << "|\n";
		address += 6;
	}

	/* Close the file */
	inFile.close();
	return;
}

/********************************************************************
Function: int main(int argc, char *argv[])
Description: Entry Point. Controls the flow of execution 
			in the program.
Parameters:	Input: int argc, The number of command line arguments.
				   char *argv[], The command line argument list.
********************************************************************/
int main(int argc, char *argv[]){
	/* If input file not specified, exit program */
	if (argc <= 1){
		cout << "Error: Filename is not specified!\n";
		cout << "Exiting program...\n";
	}

	/* Else, if default command, dump the file in ASCII/hex format */
	else if (argc == 2)
		toHex(argv[1]);

	/* Else, if -b flag in command, dump the file in binary format */
	else if (argc == 3){
		string flag = argv[1];
		if(flag.compare("-b") == 0)
			toBin(argv[2]);
		else{
			cout <<"Error: Unrecognized flag!\n";
			cout <<"Exiting program...\n";
		}
	}

	/* Else, exit program */
	else{
		cout << "Error: Too many arguments!\n";
		cout << "Exiting program...\n";
	}
	
	cout << "\n";
	return 0;
}
/************************[ EOF: hexdump.cpp ]***********************/