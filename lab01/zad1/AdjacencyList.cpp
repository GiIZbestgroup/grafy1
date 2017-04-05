#include "AdjacencyList.h"

using namespace std;

void AdjacencyList::SetAdjacencyList(std::list<int> * adjacencyList)
{
	this->adjacencyList = adjacencyList;
}

std::list<int> * AdjacencyList::GetAdjacencyList()
{
	return adjacencyList;
}

void AdjacencyList::AdjListFromInput()
{
	int answer;

	adjacencyList = new std::list<int>[edgesNumber];

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

void AdjacencyList::AdjListFromFile()
{

}

void AdjacencyList::ShowAdjList(int edgesNumber)
{
	for (int i = 0; i < edgesNumber; i++)
	{
		for (std::list<int>::iterator it = adjacencyList[i].begin(); it != adjacencyList[i].end(); it++)
		{
			cout << *it << " -> ";
		}
		cout << endl;
	}
}

void AdjacencyList::AdjMatrixToAdjList(Matrix adjacencyMatrix)
{
	adjacencyList = new std::list<int>[edgesNumber];

	for (int i = 0; i < edgesNumber; i++)
	{
		adjacencyList[i].push_back(i + 1);

		for (int j = 0; j < edgesNumber; j++)
		{
			if (adjacencyMatrix[i][j]) //POPRAWIC 
			{
				adjacencyList[i].push_back(j + 1);
			}
		}
	}
}