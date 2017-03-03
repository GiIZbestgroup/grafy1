#pragma once

#include "GraphRepresentation.h"
#include "Matrix.h"

class IncidenceMatrix : public GraphRepresentation
{
	//Macierz incydencji (tablica dwuwymiarowa)
	Matrix incidenceMatrix;

public:

	IncidenceMatrix();

	void SetIncidenceMatrix(Matrix incidenceMatrix);
	Matrix GetIncidenceMatrix();

	void IncMatrixFromInput();

	void IncMatrixFromFile();

	void ShowIncMatrix();

	void AdjListToIncMatrix();

};