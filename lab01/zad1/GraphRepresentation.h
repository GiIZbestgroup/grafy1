#pragma once

#include <iostream>
#include <string>
#include <list>

class GraphRepresentation
{
protected:

	//Liczba wierzcholkow
	int vertexNumber;

	//Liczba krawedzi
	int edgesNumber;

public:

	//Konstruktory
	GraphRepresentation(){}
	GraphRepresentation(int vertexNumber, int edgesNumber){ this->vertexNumber = vertexNumber; this->edgesNumber = edgesNumber; }

	//Destruktory
	~GraphRepresentation(){}

	//Settery
	void SetEdgesNumber(int edgesNumber) { this->edgesNumber = edgesNumber; }
	void SetVertexNumber(int vertexNumber) { this->vertexNumber = vertexNumber; }

	//Gettery
	int GetEdgesNumber() const { return edgesNumber; }
	int GetVertexNumber() const { return vertexNumber; }

};