#pragma once

#include <iostream>
#include <string>
#include <list>

class GraphRepresentation
{
protected:
	//ZMIENNE//////////////////////////////////////////////////////////////////////////////////////////////////

	//Liczba wierzcholkow
	int vertexNumber;

	//Liczba krawedzi
	int edgesNumber;

public:
	//METODY////////////////////////////////////////////////////////////////////////////////////////////////////

	//Konstruktory
	GraphRepresentation();

	//Destruktory
	~GraphRepresentation();

	//Settery
	void SetEdgesNumber(int edgesNumber) { this->edgesNumber = edgesNumber; }
	void SetVertexNumber(int vertexNumber) { this->vertexNumber = vertexNumber; }

	//Gettery
	int GetEdgesNumber() const { return edgesNumber; }
	int GetVertexNumber() const { return vertexNumber; }

};