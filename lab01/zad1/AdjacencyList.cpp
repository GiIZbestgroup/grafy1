#include "AdjacencyList.h"

using namespace std;

AdjacencyList::AdjacencyList(int vertexNumber)
{
	this->vertexNumber = vertexNumber;

	adjacencyList = new std::list<int>[vertexNumber];
}

std::list<int> * AdjacencyList::Get() const
{
	return adjacencyList;
}

void AdjacencyList::FromInput() const
{
	int answer;

	for (int i = 0; i < edgesNumber; i++)
	{
		cout << "Wierzcholek nr " << i + 1;
		adjacencyList[i].push_back(i + 1);

		do
		{
			cout << "Czy istnieje kolejny sasiad? Podaj go. Jesli nie wpisz 0." << endl;
			cin >> answer;
		} while (answer > edgesNumber || answer < 0);

		while (answer)
		{
			adjacencyList[i].push_back(answer);

			do
			{
				cout << "Czy istnieje kolejny sasiad? Podaj go. Jesli nie wpisz 0." << endl;
				cin >> answer;
			} while (answer > edgesNumber || answer < 0);
		}
	}
}

void AdjacencyList::FromFile()
{

}

void AdjacencyList::ToFile(const char * path)
{

}

void AdjacencyList::Show() const
{
	for (int i = 0; i < vertexNumber; i++)
	{
		for (std::list<int>::iterator it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it)
		{
			cout << *it << " -> ";
		}
		cout << endl;
	}
}

void AdjacencyList::FromAdjMatrix(Matrix adjacencyMatrix)
{
	adjacencyList = new std::list<int>[edgesNumber];

	for (int i = 0; i < edgesNumber; i++)
	{
		adjacencyList[i].push_back(i + 1);

		for (int j = 0; j < edgesNumber; j++)
		{
			//if (adjacencyMatrix[i][j]) //POPRAWIC 
			//{
			//	adjacencyList[i].push_back(j + 1);
			//}
		}
	}
}