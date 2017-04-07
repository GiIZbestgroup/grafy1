#pragma once

#include "GraphRepresentation.h"
#include "Matrix.h"
#include "IncidenceMatrix.h"

class AdjacencyMatrix : public GraphRepresentation
{
	//ZMIENNE//////////////////////////////////////////////////////////////////////////////////////////////////

	//Macierz sasiedztwa (tablica dwuwymiarowa)
	Matrix adjacencyMatrix;

	//Lista pomocniczych macierzy do usuniecia w destruktorze
	//static std::list<int **> toDelete;

public:
	//METODY////////////////////////////////////////////////////////////////////////////////////////////////////

	//Konstruktor
	AdjacencyMatrix(int vertexNumber);

	//Setter i getter
	int** Get() const;

	//Z klawiatury
	void Input() const;

	//Z pliku
	void FromFile(const char* path);

	//Do pliku
	void ToFile(const char* path) const;

	//Wyswietlanie
	void Show() const;

	//Konwersja z macierzy incydencji
	static AdjacencyMatrix* AdjacencyMatrix::FromIncMatrix(IncidenceMatrix incMatrix);
};
