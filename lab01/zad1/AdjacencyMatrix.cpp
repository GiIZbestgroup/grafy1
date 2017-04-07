#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int vertexNumber)
{
	this->vertexNumber = vertexNumber;
	adjacencyMatrix.Init(vertexNumber, vertexNumber);
}

int** AdjacencyMatrix::Get() const
{
	return adjacencyMatrix.GetMatrix();
}

void AdjacencyMatrix::Input() const
{
	adjacencyMatrix.Input();
}

void AdjacencyMatrix::FromFile(const char* path)
{
	adjacencyMatrix.FromFile(path);
}

void AdjacencyMatrix::ToFile(const char * path) const
{
	adjacencyMatrix.ToFile(path);
}

void AdjacencyMatrix::Show() const
{
	adjacencyMatrix.Show();
}

AdjacencyMatrix* AdjacencyMatrix::FromIncMatrix(IncidenceMatrix incMatrix)
{
	int tmp[2] = { 0, 0 };
	int counter = 0;
	
	AdjacencyMatrix* adjMatrix = new AdjacencyMatrix(incMatrix.GetVertexNumber());
	adjMatrix->adjacencyMatrix.ZeroMatrix();

	for(int i = 0; i < incMatrix.GetEdgesNumber(); i++)
	{
		for(int j = 0; j < incMatrix.GetVertexNumber(); j++)
		{
			if(incMatrix.Get()[i][j] == 1)
			{
				tmp[counter] = incMatrix.GetVertexNumber();
				++counter;
			}
		}

		adjMatrix[tmp[0]] = tmp[1];
		adjMatrix[tmp[1]] = tmp[0];
	}

	return adjMatrix;
}


