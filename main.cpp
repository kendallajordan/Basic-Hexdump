/********************************************************************
 Name: Kendall Jordan
 Username: cssc0443
 Course: CS530 Spring 2019
 Project: Assignment #1: Basic Hexdump Program
 File: main.cpp
 Last Date Modified: Feb 18, 2019
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

void createHeader(void);
void toHex(string fileName);
void toBin(string fileName);

/********************************************************************
Function: void createHeader(void)
Description: Creates a table header for the file contents.
Parameters: Input:
			Output:
********************************************************************/
void createHeader(void){
	int addressWidth = 9;
	int valueWidth = 54;
	int printableWidth = 16;
	char separator = ' ';
	char line = '-';

	cout << left << setw(addressWidth) << setfill(separator) << "Address";
	cout << left << setw(valueWidth) << setfill(separator) << "Data Values";
	cout << left << setw(printableWidth) << setfill(separator) << "Printable";
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
	int nread;
	char buffer[16];

	/* Open the file. If it cannot open, exit program */
	inFile.open(fileName, ios::in);
	if(!inFile){
		cout << "\nError: Cannot open " << fileName << "\n";
		cout << "Exiting program...\n";
		return;
	}

	/* Create a header table for the file dump contents */
	cout << "\nHexdump of " << fileName;
	createHeader();

	/* Dump the file contents */
	cout << hex << setfill('0');

	while(!inFile.eof()){
		/* Read up to 16 bytes from file each loop and store in buffer */
		for(nread = 0; nread < 16 && inFile.get(buffer[nread]); nread++);
		if(nread == 0)
			break;

		/* Print address in hexadecimal */
		cout << setw(8) << address;
		cout << ":";

		/* Print 16 data values as 8 two-byte pairs, in hexadecimal */
		for(int i = 0; i < 16; i++){
			if(i % 2 == 0)
				cout << ' ';
			if(i < nread)
				cout << setw(2) << (unsigned)buffer[i];
			/* Use spaces if final iteration has less than 16 bytes */
			else
				cout << ' ';
		}

		/* Print the printable characters, or a period if unprintable */
		cout << "  ";
		for(int i = 0; i < nread; i++){
			if(buffer[i] < 32 || buffer[i] > 126)
				cout << '.';
			else
				cout << buffer[i];
		}

		cout << "\n";
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
	int nread;
	char buffer[6];

	/* Open the file. If it cannot open, exit program */
	inFile.open(fileName, ios::in);
	if(!inFile){
		cout << "\nError: Cannot open " << fileName << "\n";
		cout << "Exiting program...\n";
		return;
	}

	/* Create a header table for the file dump contents */
	cout << "\nBinary dump of " << fileName;
	createHeader();

	/* Dump the file contents */
	cout << hex << setfill('0');

	while(!inFile.eof()){
		/* Read up to 6 bytes from file each loop and store in buffer */
		for(nread = 0; nread < 6 && inFile.get(buffer[nread]); nread++);
		if(nread == 0)
			break;

		/* Print address in hexadecimal */
		cout << setw(8) << address;
		cout << ": ";

		/* Print 6 data values as 8-bit binary octets */
		for(int i = 0; i < 6; i++){
			if(i < nread)
				bitset<8> b(buffer[i]);
				cout << setw(8) << b;
				cout << ' ';
			/* Use spaces if final iteration has less than 16 bytes */
			else
				cout << "         ";
		}

		/* Print the printable characters, or a period if unprintable */
		cout << "  ";
		for(int i = 0; i < nread; i++){
			if(buffer[i] < 32 || buffer[i] > 126)
				cout << '.';
			else
				cout << buffer[i];
		}

		cout << "\n";
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
		cout << "\nError: Filename is not specified!\n";
		cout << "Exiting program...\n";
	}

	/* Else, if default command, dump the file in ASCII/hex format */
	else if (argc == 2){
		toHex(argv[1]);

	/* Else, if -b flag in command, dump the file in binary format */
	else if (argc == 3){
		if(argv[1] == "-b")
			toBin(argv[2]);
		else{
			cout <<"\nError: Unrecognized flag!\n";
			cout <<"Exiting program...\n";
		}

	/* Else, exit program */
	else{
		cout << "\nError: Too many arguments!\n";
		cout << "Exiting program...\n";
	}
	return 0;
}
/*************************[ EOF: main.cpp ]*************************/