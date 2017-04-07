#include "IncidenceMatrix.h"
#include "AdjacencyList.h"

IncidenceMatrix::IncidenceMatrix(int vertexNumber, int edgesNumber)
{
	this->edgesNumber = edgesNumber;
	this->vertexNumber = vertexNumber;
	incidenceMatrix.Init(vertexNumber, edgesNumber);
}

int** IncidenceMatrix::Get() const
{
	return incidenceMatrix.GetMatrix();
}

void IncidenceMatrix::Input() const
{
	incidenceMatrix.Input();
}

void IncidenceMatrix::FromFile(const char* path)
{
	incidenceMatrix.FromFile(path);
}

void IncidenceMatrix::ToFile(const char * path) const
{
	incidenceMatrix.ToFile(path);
}

void IncidenceMatrix::Show() const
{
	incidenceMatrix.Show();
}

IncidenceMatrix* IncidenceMatrix::FromAdjList(AdjacencyList adjList)
{
	IncidenceMatrix* incMatrix = new IncidenceMatrix(1, 1);

	bool** condition = new bool*[adjList.GetVertexNumber()];
	for(int i = 0; i < adjList.GetVertexNumber(); i++)
	{
		condition[i] = new bool[adjList.GetVertexNumber()];
	}

	int counter = 0;
	int j = 0;

	for (int i = 0; i < adjList.GetVertexNumber(); i++)
	{
		for (std::list<int>::iterator iter = adjList.Get()->begin(); iter != adjList.Get()->end(); ++iter)
		{
			if (!condition[counter][i])
			{
				incMatrix->incidenceMatrix.SetField(i, j, 1);

				condition[counter][i] = true;
				condition[i][counter] = true;
				counter++;
				j++;
			}
		}
	}

	return incMatrix;
}


