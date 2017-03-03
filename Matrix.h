#pragma once

class Matrix
{
	int ** matrix;
	int rows, columns;

public:

	//Konstruktor i destruktor
	Matrix();
	~Matrix();

	//Tworzenie i inicjalizacja macierzy
	void MatrixInit(int rows, int columns);

	//Wpisywanie do macierzy
	void MatrixInput();

	//Wyswietlanie macierzy
	void ShowMatrix(); 

};