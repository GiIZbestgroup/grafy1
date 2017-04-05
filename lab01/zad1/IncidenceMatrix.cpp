#include "IncidenceMatrix.h"

using namespace std;

IncidenceMatrix::IncidenceMatrix()
{
	incidenceMatrix.MatrixInit(edgesNumber, verticlesNumber);
}

void IncidenceMatrix::SetIncidenceMatrix(Matrix incidenceMatrix)
{
	this->incidenceMatrix = incidenceMatrix;
}

Matrix IncidenceMatrix::GetIncidenceMatrix()
{
	return incidenceMatrix;
}

void IncidenceMatrix::IncMatrixFromInput()
{
	incidenceMatrix.MatrixInput();
}

void IncidenceMatrix::IncMatrixFromFile()
{

}

void IncidenceMatrix::ShowIncMatrix()
{
	incidenceMatrix.ShowMatrix();
}

void IncidenceMatrix::AdjListToIncMatrix()
{

}
