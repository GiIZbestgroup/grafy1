#include <iostream>
#include <cstdlib>
#include "Matrix.h"
#include "AdjacencyMatrix.h"

void clrScr() { system("cls"); } //Na linuksie moze trzeba bedzie inaczej czyscic ekran!

int main(int argc, char* argv[])
{
	std::cout << "********************" << std::endl;
	std::cout << "*  Program: Lab01  *" << std::endl;
	std::cout << "********************" << std::endl;
	std::cout << "Autorzy:" << std::endl;
	std::cout << "Pawel Talaga" << std::endl;
	std::cout << "Daria Siemieniuk" << std::endl;
	std::cout << "Milosz Swierad" << std::endl;
	std::cout << "Kamil Turek" << std::endl;
	std::cout << "\nAGH WFiIS IS 2017\n" << std::endl;
	std::cout << "Wcisnij Enter aby kontynuowac...";

	std::cin.get();

	clrScr();

	int choice;
	char path[50];

	std::cout << "Podaj rodzaj reprezentacji grafu: " << std::endl;
	std::cout << "	1: Macierz sasiedztwa" << std::endl;
	std::cout << "	2: Macierz incydencji" << std::endl;
	std::cout << "	3: Lista sasiedztwa" << std::endl;
	std::cout << "	0: Wyjdz" << std::endl;

	std::cin >> choice;

	while (choice > 3 || choice < 0)
	{
		clrScr();

		std::cout << "Zly wybor!" << std::endl;
		std::cout << "	1: Macierz sasiedztwa" << std::endl;
		std::cout << "	2: Macierz incydencji" << std::endl;
		std::cout << "	3: Lista sasiedztwa" << std::endl;
		std::cout << "	0: Wyjdz" << std::endl;

		std::cin >> choice;
	}

	if (choice)
	{
		clrScr();
		std::cout << "Podaj sciezke do pliku (domyslnie \"graph.txt\"):" << std::endl;
		std::cin >> path;
	}

	AdjacencyMatrix* adjMat = new AdjacencyMatrix();
	IncidenceMatrix* incMat = new IncidenceMatrix();
	AdjacencyList* adjList = new AdjacencyList();

	switch(choice)
	{
	case 1:
		adjMat->FromFile(path);
		adjList = AdjacencyList::FromAdjMatrix(*adjMat);
		incMat = IncidenceMatrix::FromAdjList(*adjList);

		clrScr();

		std::cout << "Liczba wierzcholkow: " << adjMat->GetVertexNumber() << std::endl;
		std::cout << "Liczba krawedzi: " << adjMat->GetEdgesNumber() << std::endl;

		std::cout << "\nMacierz sasiedztwa: " << std::endl;
		adjMat->Show();
		std::cout << "\nMacierz incydencji: " << std::endl;
		incMat->Show();
		std::cout << "\nLista sasiedztwa: " << std::endl;
		adjList->Show();

		adjMat->ToFile("adjMat.txt");
		incMat->ToFile("incMat.txt");
		adjList->ToFile("adjList.txt");
		std::cout << "\nZapisano do plikow: \"adjMat.txt\", \"incMat.txt\", \"adjList.txt\"" << std::endl;
		break;

	case 2:
		incMat->FromFile(path);
		adjMat = AdjacencyMatrix::FromIncMatrix(*incMat);
		adjList = AdjacencyList::FromAdjMatrix(*adjMat);

		clrScr();

		std::cout << "Liczba wierzcholkow: " << adjMat->GetVertexNumber() << std::endl;
		std::cout << "Liczba krawedzi: " << adjMat->GetEdgesNumber() << std::endl;

		std::cout << "\nMacierz sasiedztwa: " << std::endl;
		adjMat->Show();
		std::cout << "\nMacierz incydencji: " << std::endl;
		incMat->Show();
		std::cout << "\nLista sasiedztwa: " << std::endl;
		adjList->Show();

		adjMat->ToFile("adjMat.txt");
		incMat->ToFile("incMat.txt");
		adjList->ToFile("adjList.txt");
		std::cout << "\nZapisano do plikow: \"adjMat.txt\", \"incMat.txt\", \"adjList.txt\"" << std::endl;
		break;

	case 3:
		adjList->FromFile(path);
		incMat = IncidenceMatrix::FromAdjList(*adjList);
		adjMat = AdjacencyMatrix::FromIncMatrix(*incMat);

		clrScr();

		std::cout << "Liczba wierzcholkow: " << adjMat->GetVertexNumber() << std::endl;
		std::cout << "Liczba krawedzi: " << adjMat->GetEdgesNumber() << std::endl;

		std::cout << "\nMacierz sasiedztwa: " << std::endl;
		adjMat->Show();
		std::cout << "\nMacierz incydencji: " << std::endl;
		incMat->Show();
		std::cout << "\nLista sasiedztwa: " << std::endl;
		adjList->Show();

		adjMat->ToFile("adjMat.txt");
		incMat->ToFile("incMat.txt");
		adjList->ToFile("adjList.txt");
		std::cout << "\nZapisano do plikow: \"adjMat.txt\", \"incMat.txt\", \"adjList.txt\"" << std::endl;
		break;

	default:
		clrScr();

		std::cout << "Zakonczono program." << std::endl;

		break;
	}

	delete adjMat;
	delete incMat;
	delete adjList;

	//Wywalic na linuksie!!!!!
	system("PAUSE");
}

