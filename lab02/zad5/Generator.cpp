#include "Generator.h"

#include <cstdlib>
#include <iostream>
#include <ctime>


std::vector<std::vector<int>> Generator::random(double probability_of_connection, int numberofNodes, int& numberofEdges)
{
	srand(time(0));
	std::vector<std::vector<int>> connectionArray(numberofNodes, std::vector<int>(numberofNodes));

	for (int i = 0; i<numberofNodes; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if ((rand() % 100 + static_cast<double>(rand() % 100) / 100.0<probability_of_connection) && i != j)
				connectionArray[i][j] = 1;
			else
				connectionArray[i][j] = 0;
			if (connectionArray[i][j])
			{
				numberofEdges++;
			}
			std::cout << connectionArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return connectionArray;
}

std::vector<std::vector<int>> Generator::fullyRandom(double probability_of_connection, int& numberofNodes, int& numberofEdges, int &nodesperLattice)
{
	srand(time(0));
	numberofNodes = rand() % 100;
	nodesperLattice = rand() % numberofNodes;
	probability_of_connection = rand() % 30;

	std::vector<std::vector<int>> connectionArray(numberofNodes, std::vector<int>(numberofNodes));

	for (int i = 0; i<numberofNodes; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if ((rand() % 100 + static_cast<double>(rand() % 100) / 100.0<probability_of_connection) && i != j)
				connectionArray[i][j] = 1;
			else
				connectionArray[i][j] = 0;
			if (connectionArray[i][j])
			{
				numberofEdges++;
			}
			std::cout << connectionArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return connectionArray;
}

std::vector<std::vector<int>> Generator::fullGraph(int numberofNodes, int& numberofEdges)
{
	srand(time(0));
	std::vector<std::vector<int>> connectionArray(numberofNodes, std::vector<int>(numberofNodes));

	for (int i = 0; i<numberofNodes; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i != j)
				connectionArray[i][j] = 1;
			else
				connectionArray[i][j] = 0;
			if (connectionArray[i][j])
			{
				numberofEdges++;
			}
			std::cout << connectionArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return connectionArray;
}


std::vector<std::vector<int>> Generator::randomSpecifiedEdges(double probability_of_connection, int numberofNodes, int& numberofEdges, int desiredNumberofEdges)
{
	srand(time(0));
	bool indicator = true;
	std::vector<std::vector<int>> connectionArray(numberofNodes, std::vector<int>(numberofNodes));
	while (indicator)
	{

		for (int i = 0; i<numberofNodes; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if ((rand() % 100 + static_cast<double>(rand() % 100) / 100.0<probability_of_connection) && i != j)
					connectionArray[i][j] = 1;
				else
					connectionArray[i][j] = 0;
				if (connectionArray[i][j])
				{
					numberofEdges++;
				}
				std::cout << connectionArray[i][j] << " ";
			}
			std::cout << std::endl;
		}
		if (numberofEdges == desiredNumberofEdges)
		{
			indicator = false;
		}
		else
		{
			for (int i = 0; i<numberofNodes; i++)
			{
				for (int j = 0; j <= i; j++)
				{
					connectionArray[i][j] = 0;
				}
			}

			std::cout << "prob" << probability_of_connection << "," << numberofEdges << std::endl;
			numberofEdges = 0;
		}

	}
	return connectionArray;
}

int Generator::countOnes(std::vector<int> list)
{
	int counter = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == 1)
			counter++;
	}
	return counter;
}

std::vector<std::vector<int>> Generator::randomRegular(int numberofNodes, int& numberofEdges, int degree)
{
	srand(time(0));
	std::vector<std::vector<int>> connectionArray(numberofNodes, std::vector<int>(numberofNodes));

	for (int i = 0; i < numberofNodes; i++)
	{
		while (countOnes(connectionArray[i]) != degree)
		{
			int tmp = rand() % numberofNodes;

			if (tmp != i)
			{
				connectionArray[i][tmp] = 1;
				connectionArray[tmp][i] = 1;
				numberofEdges++;
			}
			else
			{
				connectionArray[i][tmp] = 0;
				connectionArray[tmp][i] = 0;
			}

//			std::cout << connectionArray[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < numberofNodes; i++)
	{
		for (int j = i + 1; j < numberofNodes; j++)
		{
			connectionArray[i][j] = 0;
		}
	}

	return connectionArray;
}

std::vector<std::vector<int>> Generator::fullyRandomRegular(int maxNodeNumber, int& numberofEdges, int degree)
{
	srand(time(0));
	int numberofNodes = degree + 1 + rand() % (maxNodeNumber - degree - 1);
	std::vector<std::vector<int>> connectionArray(numberofNodes, std::vector<int>(numberofNodes));

	for (int i = 0; i < numberofNodes; i++)
	{
		while (countOnes(connectionArray[i]) != degree)
		{
			int tmp = rand() % numberofNodes;

			if (tmp != i)
			{
				connectionArray[i][tmp] = 1;
				connectionArray[tmp][i] = 1;
				numberofEdges++;
			}
			else
			{
				connectionArray[i][tmp] = 0;
				connectionArray[tmp][i] = 0;
			}

			//			std::cout << connectionArray[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < numberofNodes; i++)
	{
		for (int j = i + 1; j < numberofNodes; j++)
		{
			connectionArray[i][j] = 0;
		}
	}

	return connectionArray;
}