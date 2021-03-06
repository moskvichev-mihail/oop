// multmatrix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX_SIZE_MATRIX = 3;

bool ReadMatrix(ifstream & inputFile, vector<vector<double>> & matrix)
{
	for (size_t i = 0; i < MAX_SIZE_MATRIX; ++i)
	{
		vector<double> row;
		for (size_t j = 0; j < MAX_SIZE_MATRIX; ++j)
		{
			if (!inputFile.eof())
			{
				double element;
				inputFile >> element;
				row.push_back(element);
			}
			else
			{
				return false;
			}
		}
		matrix.push_back(row);
	}
	return true;
}

void MultmultiplicationMatrix(vector<vector<double>> & matrix1, vector<vector<double>> & matrix2, 
	vector<vector<double>> & resultMatrix)
{
	for (size_t row = 0; row < MAX_SIZE_MATRIX; row++)
	{
		for (size_t col = 0; col < MAX_SIZE_MATRIX; col++)
		{
			for (size_t inner = 0; inner < MAX_SIZE_MATRIX; inner++)
			{
				resultMatrix[row][col] += matrix1[row][inner] * matrix2[inner][col];
			}
		}
	}
}

void PrintMatrix(const vector<vector<double>> & matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			cout << fixed << setprecision(3) << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Error: invalid arguments count.\n";
		cout << "Usage: multmatrix.exe <matrix file1> <matrix file1>\n";
		return 1;
	}

	ifstream inputFile1(argv[1]);
	if (!inputFile1.is_open())
	{
		cout << "Error: failed to open " << argv[1] << "for reading.\n";
		return 1;
	}

	ifstream inputFile2(argv[2]);
	if (!inputFile2.is_open())
	{
		cout << "Error: failed to open " << argv[2] << "for reading.\n";
		return 1;
	}

	vector<vector<double>> matrix1;
	if (!ReadMatrix(inputFile1, matrix1))
	{
		cout << "Error. The matrix is not read.\n";
		return 1;
	}

	vector<vector<double>> matrix2;
	if (!ReadMatrix(inputFile2, matrix2))
	{
		cout << "Error. The matrix is not read.\n";
		return 1;
	}
	vector<vector<double>> resultMatrix(MAX_SIZE_MATRIX, vector<double>(MAX_SIZE_MATRIX));
	MultmultiplicationMatrix(matrix1, matrix2, resultMatrix);
	PrintMatrix(resultMatrix);
	return 0;
}