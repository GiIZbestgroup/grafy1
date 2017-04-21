#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

AdjacencyMatrix::AdjacencyMatrix()
{
	this->vertexNumber = 0;
	this->edgesNumber = 0;
}

AdjacencyMatrix::AdjacencyMatrix(int vertexNumber, int edgesNumber)
{
	this->vertexNumber = vertexNumber;
	this->edgesNumber = edgesNumber;

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
	this->vertexNumber = adjacencyMatrix.GetRows();

	int edgesCounter = 0;

	for(int i = 0; i < adjacencyMatrix.GetRows() - 1; i++)
	{
		for(int j = i + 1; j < adjacencyMatrix.GetColumns(); j++)
		{
			if(adjacencyMatrix.GetMatrix()[i][j])
			{
				edgesCounter++;
			}
		}
	}

	this->edgesNumber = edgesCounter;
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
	AdjacencyMatrix* adjMatrix = new AdjacencyMatrix(incMatrix.GetVertexNumber(), incMatrix.GetEdgesNumber());
	adjMatrix->adjacencyMatrix.ZeroMatrix();

	int tmp[2] = { 0, 0 };
	int counter = 0;

	for(int i = 0; i < incMatrix.GetEdgesNumber(); i++)
	{
		for(int j = 0; j < incMatrix.GetVertexNumber(); j++)
		{
			if(incMatrix.Get()[j][i])
			{
				tmp[counter] = j;
				++counter;
			}
		}

		adjMatrix->adjacencyMatrix.SetField(tmp[0], tmp[1], 1);
		adjMatrix->adjacencyMatrix.SetField(tmp[1], tmp[0], 1);

		counter = 0;
	}

	return adjMatrix;
}


