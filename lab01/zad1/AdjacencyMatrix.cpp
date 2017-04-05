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

bool AdjacencyMatrix::IsSymmetricalMatrix()
{
	bool answer = true;
	if(adjacencyMatrix.rows==adjacencyMatrix.columns)
	{
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<columns;j++)
			{
				if(adjacencyMatrix.matrix[i][j]!=adjacencyMatrix.matrix[j][i])
					answer = false;
			}
		}
	}
	else
	{
		answer = false;
	}
	return answer;
}
