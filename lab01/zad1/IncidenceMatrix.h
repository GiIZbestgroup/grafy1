#pragma once

#include "GraphRepresentation.h"
#include "Matrix.h"
#include "AdjacencyList.h"

class AdjacencyList;

class IncidenceMatrix : public GraphRepresentation
{
	//Macierz incydencji
	Matrix incidenceMatrix;

public:

	//Konstruktor
	IncidenceMatrix();
	IncidenceMatrix(int vertexNumber, int edgesNumber);

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

	//Konwersja z listy sasiedztwa
	//Metoda statyczna, zwraca adres do nowego obiektu
	static IncidenceMatrix* FromAdjList(AdjacencyList adjList);

};