#pragma once

#include <iostream>
#include <vector>
#include "GraphRepresentation.h"
#include "AdjacencyMatrix.h"

class AdjacencyMatrix;

class AdjacencyList : public GraphRepresentation
{
	//Lista sasiedztwa (tablica list)
	std::vector<int> * adjacencyList;

public:

	//Konstruktory
	AdjacencyList();
	AdjacencyList(int vertexNumber);

	//Getter
	std::vector<int> * Get() const;

	//Z klawiatury
	void FromInput() const;

	//Z pliku
	//Metoda wymaga uzycia obiektu zainicjalizowanego konstruktorem domyslnym (wskaznik tablicowy powinien wskazywac na nullptr)
	//W przeciwnym wypadku stracimy wczeœniej zarezerwowana pamiec
	void FromFile(const char * path);

	//Do pliku
	void ToFile(const char* path) const;

	//Wyswietlanie
	void Show() const;

	//Konwersja z macierzy sasiedztwa
	//Metoda statyczna, zwraca adres do nowego obiektu
	static AdjacencyList* FromAdjMatrix(AdjacencyMatrix adjacencyMatrix);
};