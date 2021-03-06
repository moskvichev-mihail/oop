// crypt.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char Change(char ch) 
{
	ch = ch & 160 | ch;
	ch = ch & 66 | ch;
	ch = ch & 33 | ch;
	ch = ch & 144 | ch;
	ch = ch & 72 | ch;
	ch = ch & 20 | ch;
	ch = ch & 10 | ch;
	ch = ch & 5 | ch;
	return ch;
}

string Decrypt(string cryptLine, int key)
{
	for (unsigned int i = 0; i < cryptLine.size(); ++i)
	{
		cryptLine[i] = Change(cryptLine[i]);
		cryptLine[i] = cryptLine[i] ^ key;
	}
	return cryptLine;
}

string Crypt(string cryptLine, int key)
{
	for (unsigned int i = 0; i < cryptLine.size(); ++i)
	{
		cryptLine[i] = cryptLine[i] ^ key;
		cryptLine[i] = Change(cryptLine[i]);
	}
	return cryptLine;
}

int StringToInt(const char* str, bool & err)
{
	char* pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count.\n"
			 << "Usage for crypt: crypt.exe crypt <input file> <output file> <key>\n"
		     << "Usage for decrypt: crypt.exe decrypt <input file> <output file> <key>\n";
		return 1;
	}
	string action = argv[1];
	if (action == "crypt" || action == "decrypt")
	{
		ifstream inputFile(argv[2]);
		ofstream outputFile(argv[3]);
		if (!inputFile.is_open())
		{
			cout << "Could not open file " << argv[2] << endl;
			return 1;
		}
		if (!outputFile.is_open())
		{
			cout << "Could not open file " << argv[3] << endl;
			return 1;
		}
		bool err;
		int key = StringToInt(argv[4], err);
		if (err)
		{
			cout << "Argument <key> is not a number!\n";
			return 1;
		}
		if ((key < 0) || (key > 255))
		{
			cout << "Argument <key> is out of range 0 to 255!\n";
			return 1;
		}
		string line;
		while (getline(inputFile, line))
		{
			if (action == "crypt")
			{
				outputFile << Crypt(line, key) << endl;
			}	
			else
			{
				outputFile << Decrypt(line, key) << endl;
			}
		}
	}
	else
	{
		cout << "Error. Program know only two operations: crypt or decrypt.\n";
		return 1;
	}
    return 0;
}