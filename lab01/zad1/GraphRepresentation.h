#pragma once

#include <iostream>
#include <string>
#include <list>

class GraphRepresentation
{
protected:
	//ZMIENNE//////////////////////////////////////////////////////////////////////////////////////////////////

	//Liczba wierzcholkow
	int edgesNumber;
	//Liczba krawedzi
	int verticlesNumber;

public:
	//METODY////////////////////////////////////////////////////////////////////////////////////////////////////

	//Konstruktory
	GraphRepresentation();

	//Destruktory
	~GraphRepresentation();

	//Settery
	void SetEdgesNumber(int edgesNumber);
	void SetVerticlesNumber(int verticlesNumber);

	//Gettery
	int GetEdgesNumber();
	int GetVerticlesNumber();

};