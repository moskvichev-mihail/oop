// rle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <string>

using namespace std;

void Pack(string str, char * out, int size)
{
	int counter = 0;
	int recurringCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (str[i] != str[i + 1])
		{
			recurringCount++;
			out[counter++] = str[i];
			out[counter++] = recurringCount + '0';
			recurringCount = 0;
		}
		else
		{
			recurringCount++;
		}
	}
}

void Unpack(string str, char * out, int size)
{
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (i & 1)
		{
			int num = str[i] - '0';
			for (int j = 0; j < num; j++) {
				out[counter++] = str[i - 1];
			}
		}
	}
}


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Error: invalid arguments count.\n";
		cout << "Usage: rle.exe pack <input file> <output file> or rle.exe unpack <input file> <output file>.\n";
		return 1;
	}
	if (argv[1] == "pack" || argv[1] == "unpack")
	{
		ifstream inputFile(argv[2]);
		if (!inputFile.is_open())
		{
			cout << "Error: failed to open " << argv[2] << "for reading.\n";
			return 1;
		}
		ofstream outputFile(argv[3]);
		if (!outputFile.is_open())
		{
			cout << "Failed to open " << argv[3] << " for writing\n";
			return 1;
		}
		string str;
		inputFile >> str;
		int size = str.length();
		if (size == 0)
		{
			cout << "Error: zero length input file.\n";
			return 1;
		}
		if (argv[1] == "pack")
		{
			char * pack = new char[size + 1]();
			pack[size] = '\0';
			Pack(str, pack, size);
			outputFile << pack;
			delete[] pack;
		}
		else if (argv[1] == "unpack")
		{
			char * unpack = new char[size + 1]();
			unpack[size] = '\0';
			Unpack(str, unpack, size);
			outputFile << unpack;
			delete[] unpack;
		}
	}
	else
	{
		cout << "Error: invalid parametr.\n";
		cout << "Usage: pack or unpack.\n";
		return 1;
	}
	return 0;
}