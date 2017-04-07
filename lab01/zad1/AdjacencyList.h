#pragma once

#include <iostream>
#include <list>
#include "GraphRepresentation.h"
#include "Matrix.h"

class AdjacencyList : public GraphRepresentation
{
	//Lista sasiedztwa (tablica list)
	std::list<int> * adjacencyList;

	//Liczba wierzcholkow
	int vertexNumber;

public:

	//Konstruktor
	AdjacencyList(int vertexNumber);

	//Getter
	std::list<int> * Get() const;

	//Z klawiatury
	void FromInput() const;

	//Z pliku
	void FromFile();

	//Do pliku
	void ToFile(const char* path);

	//Wyswietlanie
	void Show() const;

	//Konwersja z macierzy sasiedztwa
	void FromAdjMatrix(Matrix adjacencyMatrix);
};