#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
	matrix = NULL;
	rows = 0;
	columns = 0;
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Matrix::MatrixInit(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}
}

void Matrix::MatrixInput()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "M[" << i << "," << j << "] = ";
			cin >> matrix[i][j];
		}
	}
}

void Matrix::ShowMatrix()
{
	for (int i = 0; i < rows; i++)
	{
		cout << "| ";
		for (int j = 0; j < columns; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << "|" << endl;
	}
}