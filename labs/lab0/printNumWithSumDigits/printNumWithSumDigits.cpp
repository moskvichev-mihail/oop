// printNumWithSumDigits.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

int SumDigits(int i)
{
	int sum = 0;

	// цикл продолжается до тех пор, пока число не станет равным 0
	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}


int main(int argc, char* argv[])
{
	for (int i = 1; i <= 1000; i++)
	{
		if (i % SumDigits(i) == 0)
		{
			cout << i << endl;
		}
	}
	return 0;
}
