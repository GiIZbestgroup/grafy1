#pragma once

#include "GraphRepresentation.h"
#include "Matrix.h"
#include "AdjacencyList.h"

class IncidenceMatrix : public GraphRepresentation
{
	//Macierz incydencji (tablica dwuwymiarowa)
	Matrix incidenceMatrix;

public:

	//Konstruktor
	IncidenceMatrix(int vertexNumber, int edgesNumber);

	//Getter
	int** Get() const;

	//Z klawiatury
	void Input() const;

	//Z pliku
	void FromFile(const char* path);

	//Do pliku
	void ToFile(const char* path) const;

	//Wyswietlanie
	void Show() const;

	//Konwersja z listy sasiedztwa
	static IncidenceMatrix* IncidenceMatrix::FromAdjList(AdjacencyList adjList);

};