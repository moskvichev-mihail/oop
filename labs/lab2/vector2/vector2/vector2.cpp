// vector2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void ReadVector(vector<double>& inputVector)
{
	double value;
	while (cin >> value)
	{
		inputVector.push_back(value);
	}
}

double FindMinValueInVector(vector<double>& inputVector, double minValue)
{
	for (int t = 1; t < inputVector.size(); ++t)
	{
		if (inputVector[t] < minValue)
		{
			minValue = inputVector[t];
		}
	}
	return minValue;
}

vector<double> DivideElements(vector<double>& inputVector, double minValue)
{
	for (int i = 0; i < inputVector.size(); ++i)
	{
		inputVector[i] /= minValue;
	}
	return inputVector;
}

void PrintElements(vector<double>& inputVector)
{
	for (int i = 0; i < inputVector.size(); ++i)
	{
		cout << inputVector[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<double> inputVector;
	ReadVector(inputVector);
	double minValue = inputVector[0];
	FindMinValueInVector(inputVector, minValue);
	DivideElements(inputVector, minValue);
	sort(inputVector.begin(), inputVector.end());
	PrintElements(inputVector);
    return 0;
}