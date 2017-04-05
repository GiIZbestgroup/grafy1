#pragma once

#include <iostream>
#include "GraphRepresentation.h"
#include "Matrix.h"

class AdjacencyList : public GraphRepresentation
{
	//Lista sasiedztwa (tablica list)
	std::list<int> * adjacencyList;

public:

	void SetAdjacencyList(std::list<int> * adjacencyList);
	std::list<int> * GetAdjacencyList();
	void AdjListFromInput();
	void AdjListFromFile();
	void ShowAdjList(int edgesNumber);
	void AdjMatrixToAdjList(Matrix adjacencyMatrix);
};