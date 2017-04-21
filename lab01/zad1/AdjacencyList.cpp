#include "AdjacencyList.h"

using namespace std;

AdjacencyList::AdjacencyList()
{
	this->vertexNumber = 0;

	adjacencyList = nullptr;
}

AdjacencyList::AdjacencyList(int vertexNumber)
{
	this->vertexNumber = vertexNumber;

	adjacencyList = new vector<int>[vertexNumber];
}

vector<int>* AdjacencyList::Get() const
{
	return adjacencyList;
}

void AdjacencyList::FromInput() const
{
	int answer;

	for (int i = 0; i < vertexNumber; i++)
	{
		cout << "Wierzcholek nr " << i + 1 << ":" << endl;

		do
		{
			cout << "Czy istnieje kolejny sasiad? Podaj go. Jesli nie wpisz 0." << endl;
			cin >> answer;
		} while (answer > vertexNumber || answer < 0);

		while (answer)
		{
			adjacencyList[i].push_back(answer);

			do
			{
				cout << "Czy istnieje kolejny sasiad? Podaj go. Jesli nie wpisz 0." << endl;
				cin >> answer;
			} while (answer > vertexNumber || answer < 0);
		}
	}
}

void AdjacencyList::FromFile(const char * path)
{
	FILE** newFile = new FILE*;
	fopen_s(newFile, path, "r");

	fscanf_s(*newFile, "%d", &vertexNumber);
	fscanf_s(*newFile, "\n");

	adjacencyList = new vector<int>[vertexNumber];

	for (int i = 0; i < vertexNumber; i++)
	{
		fscanf_s(*newFile, "%d");

		while(!feof(*newFile)) // WARUNEK konca linii//////////////////////////////////////////////////////////
		{
			int value;
			fscanf_s(*newFile, "%d", &value);
			adjacencyList[i].push_back(value);
		}

		fscanf_s(*newFile, "\n");
	}

	fclose(*newFile);
}

void AdjacencyList::ToFile(const char * path) const
{
	FILE** newFile = new FILE*;
	fopen_s(newFile, path, "w");

	fprintf(*newFile, "%d\n", vertexNumber);

	for (int i = 0; i < vertexNumber; i++)
	{
		fprintf(*newFile, "%d ", i + 1);
		for (int j = 0; j < adjacencyList[i].size(); j++)
		{
			fprintf(*newFile, "%d ", adjacencyList[i][j]);
		}
		fprintf(*newFile, "\n");
	}

	fclose(*newFile);
}

void AdjacencyList::Show() const
{
	for (int i = 0; i < vertexNumber; i++)
	{
		cout << i + 1 << ": ";
		for (int j = 0; j < adjacencyList[i].size(); j++)
		{
			cout << adjacencyList[i][j] << ", ";
		}
		cout << endl;
	}
}

AdjacencyList* AdjacencyList::FromAdjMatrix(AdjacencyMatrix adjacencyMatrix)
{
	AdjacencyList* adjList = new AdjacencyList(adjacencyMatrix.GetVertexNumber());

	for (int i = 0; i < adjacencyMatrix.GetVertexNumber(); i++)
	{
		for (int j = 0; j < adjacencyMatrix.GetVertexNumber(); j++)
		{
			if (adjacencyMatrix.Get()[i][j])
			{
				adjList->adjacencyList[i].push_back(j + 1);
			}
		}
	}

	return adjList;
}