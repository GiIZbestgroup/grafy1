#pragma once

#include "GraphRepresentation.h"
#include "Matrix.h"
#include "IncidenceMatrix.h"

class IncidenceMatrix;

class AdjacencyMatrix : public GraphRepresentation
{
	//Macierz sasiedztwa
	Matrix adjacencyMatrix;

public:

	//Konstruktor
	AdjacencyMatrix();
	AdjacencyMatrix(int vertexNumber, int edgesNumber);

	//Getter
	int** Get() const;

	//Z klawiatury
	void Input() const;

	//Z pliku
	//Metoda wymaga uzycia obiektu zainicjalizowanego konstruktorem domyslnym (wskaznik tablicowy powinien wskazywac na nullptr)
	//W przeciwnym wypadku stracimy wczeœniej zarezerwowana pamiec
	void FromFile(const char* path);

	//Do pliku
	void ToFile(const char* path) const;

	//Wyswietlanie
	void Show() const;

	//Konwersja z macierzy incydencji
	//Metoda statyczna, zwraca adres do nowego obiektu
	static AdjacencyMatrix* FromIncMatrix(IncidenceMatrix incMatrix);
};
