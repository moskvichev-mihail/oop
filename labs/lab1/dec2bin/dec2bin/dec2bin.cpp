// dec2bin.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count.\n"
			<< "Usage: dec2bin.exe <number in the decimal system>\n";
		return 1;
	}
	char * pLastChar = NULL;
	const char * pArg = argv[1];
	int number = strtol(pArg, &pLastChar, 10);
	if ((*pArg == '\0') || (*pLastChar != '\0'))
	{
		cout << "Argument is not a number in the decimal system.\n";
		return 1;
	}
	string binNumber = "";
	if ((number < 0) || (number > (pow(2, 32) - 1)))
	{
		cout << "Error. Input number cannot be more or less, than the value in the range.\n";
	}
	else
	{
		while (number > 0)
		{
			if (number % 2)
				binNumber += '1';
			else
				binNumber += '0';
			number /= 2;
		}
		reverse(binNumber.begin(), binNumber.end());
		cout << binNumber << "\n";
		return 0;
	}
}