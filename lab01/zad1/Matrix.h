#pragma once

class Matrix
{
	int ** matrix;
	int rows, columns;

public:

	//Konstruktory i destruktor
	Matrix();
	Matrix(const int rows, const int columns);
	~Matrix();

	//Gettery
	int** GetMatrix() const;
	int GetRows() const;
	int GetColumns() const;

	//Settery
	void SetField(int row, int column, int value) const;

	//Tworzenie i inicjalizacja macierzy
	void Init(const int rows, const int columns);

	//Zerowanie macierzy
	void ZeroMatrix() const;

	//Macierz jednostkowa
	void IdentityMatrix() const;

	//Wpisywanie do macierzy
	void Input() const;

	//Wyswietlanie macierzy
	void Show() const; 

	//Zapisywanie do pliku
	void ToFile(const char* path) const;

	//Wczytywanie z pliku
	void FromFile(const char* path);

	//Operacje na macierzach
	Matrix operator+(Matrix matrixB) const;
	Matrix operator-(Matrix matrixB) const;
	Matrix operator*(Matrix matrixB) const;
};