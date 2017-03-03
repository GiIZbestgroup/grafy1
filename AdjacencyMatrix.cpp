#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix()
{
	adjacencyMatrix.MatrixInit(edgesNumber, edgesNumber);
}

void AdjacencyMatrix::SetAdjacencyMatrix(Matrix adjacencyMatrix)
{
	this->adjacencyMatrix = adjacencyMatrix;
}

Matrix AdjacencyMatrix::GetAdjacencyMatrix()
{
	return adjacencyMatrix;
}

void AdjacencyMatrix::AdjMatrixFromInput()
{
	adjacencyMatrix.MatrixInput();
}

void AdjacencyMatrix::AdjMatrixFromFile()
{

}

void AdjacencyMatrix::ShowAdjMatrix()
{
	adjacencyMatrix.ShowMatrix();
}

void AdjacencyMatrix::IncMatrixToAdjMatrix()
{

}