// dec2bin.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

void DecToBin(int n)
{
	string binNumber;
	while (n > 0)
	{
		if (n % 2)
			binNumber += '1';
		else
			binNumber += '0';
		n /= 2;
	}
	reverse(binNumber.begin(), binNumber.end());
	cout << binNumber << endl;
}

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

	if ((number < 0) || (number > (pow(2, 32) - 1)))
	{
		cout << "Error. Input number cannot be more or less, than the value in the range.\n";
		return 1;
	}
	else
	{
		DecToBin(number);
		return 0;
	}
}