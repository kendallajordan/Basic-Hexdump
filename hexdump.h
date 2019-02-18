/********************************************************************
 Name: Kendall Jordan
 Username: cssc0443
 Course: CS530 Spring 2019
 Project: Assignment #1: Basic Hexdump Program
 File: hexdump.h
 Last Date Modified: Feb 18, 2019
********************************************************************/
#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <string>

/********************************************************************
Function: void createHeader(int mode)
Description: Creates a table header for the file contents.
Parameters: Input: int mode, Selects header mode (hex = 1, bin = 2)
			Output:
********************************************************************/
void createHeader(int mode);

/********************************************************************
Function: void toHex(fileName)
Description: Dumps the specified file in ASCII/hex format.
Parameters: Input: string fileName, The file name of the specified file.
			Output: 
********************************************************************/
void toHex(std::string fileName);

/********************************************************************
Function: void toBin(fileName)
Description: Dumps the specified file in binary format.
Parameter:	Input: String fileName, The file name of the specified file.
			Output:
********************************************************************/
void toBin(std::string fileName);

#endif
/*************************[ EOF: hexdump.h ]************************/