#include "IncidenceMatrix.h"
#include "AdjacencyList.h"

IncidenceMatrix::IncidenceMatrix()
{
	this->vertexNumber = 0;
	this->edgesNumber = 0;
}

IncidenceMatrix::IncidenceMatrix(int vertexNumber, int edgesNumber)
{
	this->vertexNumber = vertexNumber;
	this->edgesNumber = edgesNumber;

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
	this->vertexNumber = incidenceMatrix.GetRows();
	this->edgesNumber = incidenceMatrix.GetColumns();
}

void IncidenceMatrix::ToFile(const char * path) const
{
	incidenceMatrix.ToFile(path);
}

void IncidenceMatrix::Show() const
{
	incidenceMatrix.Show();
}

IncidenceMatrix* IncidenceMatrix::FromAdjList(AdjacencyList adjList) //????????????????????????????????????????????????????????????????????????????
{
	IncidenceMatrix* incMatrix = new IncidenceMatrix(adjList.GetVertexNumber(), adjList.GetEdgesNumber());

	incMatrix->incidenceMatrix.ZeroMatrix();

	bool** condition = new bool*[adjList.GetVertexNumber()];
	for(int i = 0; i < adjList.GetVertexNumber(); i++)
	{
		condition[i] = new bool[adjList.GetVertexNumber()];
	}

	for(int i = 0; i < adjList.GetVertexNumber(); i++)
	{
		for(int j = 0; j < adjList.GetVertexNumber(); j++)
		{
			condition[i][j] = false;
		}
	}

	int counter = 0;

	for (int i = 0; i < adjList.GetVertexNumber(); i++)
	{
		for (std::vector<int>::iterator iter = adjList.Get()[i].begin(); iter != adjList.Get()[i].end(); ++iter)
		{
			int j = *iter - 1;

			if (!condition[j][i])
			{
				incMatrix->incidenceMatrix.SetField(i, counter, 1);
				incMatrix->incidenceMatrix.SetField(j, counter, 1);

				condition[j][i] = true;
				condition[i][j] = true;

				counter++;
			}

			if (counter == adjList.GetEdgesNumber())
				break;
		}

		if (counter == adjList.GetEdgesNumber())
			break;
	}

	return incMatrix;
}


