#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
	matrix = nullptr;
	rows = 0;
	columns = 0;
}

Matrix::Matrix(int rows, int columns)
{
	Init(rows, columns);
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
//		delete[] this->matrix[i];
	}
//	delete[] this->matrix;
}

void Matrix::Init(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}
}

void Matrix::ZeroMatrix() const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void Matrix::IdentityMatrix() const
{
	ZeroMatrix();

	for (int i = 0; i < rows; i++)
	{
		matrix[i][i] = 1;
	}
}

void Matrix::Input() const
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

void Matrix::Show() const
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

void Matrix::ToFile(const char* path) const
{
	FILE** newFile = new FILE*;
	fopen_s(newFile, path, "w");

	if (rows == columns)
	{
		fprintf(*newFile, "%d %d\n", rows, 0);
	}
	else
	{
		fprintf(*newFile, "%d %d\n", rows, columns);
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			fprintf(*newFile, "%d ", matrix[i][j]);
		}
		fprintf(*newFile, "\n");
	}

	fclose(*newFile);
}

void Matrix::FromFile(const char * path)
{
	FILE** newFile = new FILE*;
	fopen_s(newFile, path, "r");

	fscanf_s(*newFile, "%d %d", &rows, &columns);
	fscanf_s(*newFile, "\n");
	if (!columns)
	{
		columns = rows;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			fscanf_s(*newFile, "%d", &matrix[i][j]);
		}
		fscanf_s(*newFile, "\n");
	}

	fclose(*newFile);
}

Matrix Matrix::operator+(Matrix matrixB) const
{
	Matrix resultMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			resultMatrix.matrix[i][j] = this->matrix[i][j] + matrixB.matrix[i][j];
		}
	}

	return resultMatrix;
}

Matrix Matrix::operator-(Matrix matrixB) const
{
	Matrix resultMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			resultMatrix.matrix[i][j] = this->matrix[i][j] - matrixB.matrix[i][j];
		}
	}

	return resultMatrix;
}

Matrix Matrix::operator*(Matrix matrixB) const
{
	Matrix resultMatrix(rows, columns);
	resultMatrix.ZeroMatrix();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < rows; k++)
			{
				resultMatrix.matrix[i][j] += this->matrix[i][k] * matrixB.matrix[k][j];
			}
		}
	}

	return resultMatrix;
}
