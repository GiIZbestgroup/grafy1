#pragma once

#include "GraphRepresentation.h"
#include "Matrix.h"

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
	AdjacencyMatrix();

	//Setter i getter
	void SetAdjacencyMatrix(Matrix adjacencyMatrix);
	Matrix GetAdjacencyMatrix();

	//Z klawiatury
	void AdjMatrixFromInput();

	//Z pliku
	void AdjMatrixFromFile();
	
	//Sprawdzanie poprawnosci macierzy (gdy graf jest nieskierowany ma byc symetryczna)
	bool IsSymmetricalMatrix();

	//Wyswietlanie
	void ShowAdjMatrix();

	//Konwersja z macierzy incydencji
	void IncMatrixToAdjMatrix();
};
