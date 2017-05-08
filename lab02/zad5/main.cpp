#include <SFML/Graphics.hpp>
#include <vector> 
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>

#define WINDOWSIZE_X 720
#define WINDOWSIZE_Y 480

#include "Point.h"
#include "Generator.h"
#include "GraphicObjects.h"

std::vector <std::vector<int>> fromfile(int& numberofNodes, int& numberofEdges)
{
	std::ifstream file("adjMat.txt");
	int x_size, y_size;
	file >> x_size;
	file >> y_size;
	x_size = static_cast<int>(x_size);

	int tmp;

	if (x_size != 0)
	{
		std::vector<std::vector<int>> connectionArray1(x_size, std::vector<int>(x_size));
		std::cout << "Macierz " << x_size << " na " << x_size << std::endl;
		for (int i = 0; i<x_size; i++)
		{
			for (int j = 0; j<x_size; j++)
			{
				file >> tmp;
				if (tmp)
					numberofEdges++;
				std::cout << tmp;
				connectionArray1[i][j] = tmp;
			}
			std::cout << std::endl;
		}
		numberofNodes = x_size;
		return connectionArray1;
	}
	else
	{
		std::vector <std::vector<int>> k;
		std::cout << "Niestety nie" << std::endl;
		return k;
	}
}

void tofile(int numberofNodes, std::vector <std::vector<int>> matrix)
{
	std::ofstream file("adjMat.txt");
	file << numberofNodes << " ";
	file << numberofNodes << "\n";

	for (int i = 0; i<numberofNodes; i++)
	{
		for (int j = 0; j<numberofNodes; j++)
		{
			file << matrix[i][j] << " ";
		}
		file << "\n";
	}

}

int main()
{
	//�adowanie pliku czcionki (musi by� tutaj je�eli nie chc� robi� wska�nika, a nie chc�.)
	sf::Font font;
	if (!font.loadFromFile("font.ttf"))
		std::cout << "Nie mo�na za�adowa� pliku czcionki: font.ttf";
	//Stworzenie okna

	//stworzenie na razie pustych tablic na punkty, podpisy i linie(musi by� tutaj je�eli nie chc� robi� wska�nik�w, a nie chc�.)
	std::vector<sf::Text> names;
	std::vector<Point> points;
	std::vector<sf::VertexArray> lines;
	//Pocz�tkowa liczba, nie zmienia�, sama si� zmieni, okre�la ile utworzono kraw�dzi
	int numberofEdges = 0;


	//PARAMETRY:

	//Liczba wierzcho�k�w
	int numberofNodes;
	//Prawdopodobie�stwo (��czenie w�z��w, ponowne z��czanie w przypadku funkcji strogatz()) dane w procentach
	double probability_of_connection;
	//Liczba w�z��w na obr�cz
	int nodesperLattice;
	//Stosunek rozmiaru mniejszej obr�czy do wi�kszej
	float latticesProportion;
	//Upragniona liczba kraw�dzi przy generowaniu losowego z okre�lon� ich liczb�
	int desiredNumberofEdges;
	//Stopie� dla grafu regularnego
	int degree;

	//Tu mamy obs�ug� wej�cia:

	std::cout << std::endl << "FUNKCJE PROGRAMU\n" << "1 - wczytaj graf z pliku incMat.txt\n";
	std::cout << "2 - generuj graf losowy o zadanej liczbie w�z��w i prawdopodobie�stwie\n";
	std::cout << "3 - generuj graf losowy o zadanej liczbie w�z��w i kraw�dzi\n";
	std::cout << "4 - generuj graf losowy bez parametr�w\n";
	std::cout << "5 - generuj graf pe�ny o zadanej liczbie wierzcho�k�w\n";
	std::cout << "6 - generuj graf k-regularny o zadanym stopniu i liczbie wierzcholkow\n";
	std::cout << "7 - generuj graf k-regularny o zadanym stopniu i losowej liczbie wierzcholkow\n";
	int choice;
	std::cin >> choice;
	std::cout << std::endl;
	std::vector<std::vector<int>> connectionArray;

	switch (choice)
	{
	case 1:

		connectionArray = fromfile(numberofNodes, numberofEdges);
		std::cout << "\nPodaj liczb� w�z��w na jedn� obr�cz:" << std::endl;
		std::cin >> nodesperLattice;
		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;

		break;

	case 2:

		std::cout << "Podaj liczb� w�z��w:" << std::endl;
		std::cin >> numberofNodes;
		std::cout << "Podaj Prawdopodobie�stwo po��czenia w�z��w:" << std::endl;
		std::cin >> probability_of_connection;
		std::cout << "Podaj liczb� w�z��w na jedn� obr�cz:" << std::endl;
		std::cin >> nodesperLattice;
		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;
		connectionArray = Generator::random(probability_of_connection, numberofNodes, numberofEdges);

		break;

	case 3:

		std::cout << "Podaj liczb� w�z��w:" << std::endl;
		std::cin >> numberofNodes;
		std::cout << "Podaj upragnion� liczb� kraw�dzi:" << std::endl;
		std::cin >> desiredNumberofEdges;
		probability_of_connection = static_cast<double>((100.0*static_cast<double>(desiredNumberofEdges)) / (static_cast<double>(numberofNodes)*(static_cast<double>(numberofNodes) - 1.0) / 2.0));
		std::cout << "Podaj liczb� w�z��w na jedn� obr�cz:" << std::endl;
		std::cin >> nodesperLattice;
		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;
		connectionArray = Generator::randomSpecifiedEdges(probability_of_connection, numberofNodes, numberofEdges, desiredNumberofEdges);

		break;

	case 4:

		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;
		connectionArray = Generator::fullyRandom(probability_of_connection, numberofNodes, numberofEdges, nodesperLattice);

		break;

	case 5:

		std::cout << "Podaj liczb� w�z��w:" << std::endl;
		std::cin >> numberofNodes;
		std::cout << "Podaj liczb� w�z��w na jedn� obr�cz:" << std::endl;
		std::cin >> nodesperLattice;
		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;
		connectionArray = Generator::fullGraph(numberofNodes, numberofEdges);

		break;

	case 6:

		std::cout << "Podaj liczb� w�z��w: " << std::endl;
		std::cin >> numberofNodes;
		std::cout << "Podaj liczb� w�z��w na jedn� obr�cz:" << std::endl;
		std::cin >> nodesperLattice;
		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;
		std::cout << "Podaj stopie�: " << std::endl;
		std::cin >> degree;
		connectionArray = Generator::randomRegular(numberofNodes, numberofEdges, degree);

		break;

	case 7:

		std::cout << "Podaj maksymaln� liczb� w�z��w: " << std::endl;
		std::cin >> numberofNodes;
		std::cout << "Podaj liczb� w�z��w na jedn� obr�cz:" << std::endl;
		std::cin >> nodesperLattice;
		std::cout << "Podaj proporcj� wielko�ci obr�czy:" << std::endl;
		std::cin >> latticesProportion;
		std::cout << "Podaj stopie�: " << std::endl;
		std::cin >> degree;
		connectionArray = Generator::randomRegular(numberofNodes, numberofEdges, degree);

		break;

	}


	tofile(numberofNodes, connectionArray);


	//Stworzenie okna
	sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "GraphMaker - Master the Space-Time Continuum");

	//Stworzenie punkt�w i podpis�w (obiekt�w graficznych) wedle parametr�w danych wy�ej
	GraphicObjects::createPoints(numberofNodes, nodesperLattice, latticesProportion, points);
	GraphicObjects::createNames(numberofNodes, nodesperLattice, latticesProportion, points, names, font);

	//Wygenerowanie obiekt�w graficznych dla kraw�dzi �acz�cych w�z�y na podstawie wcze�niej wygenerowanej
	//macierzy s�siedztwa
	GraphicObjects::createLines(numberofNodes, points, connectionArray, lines);


	while (window.isOpen())
	{
		//Tworzy obiekt typu zdarzenie (statyczny)
		sf::Event event;

		//Daje oknu status "zamkni�te" gdy wy��czymy okno przez co p�tla i program ko�cz� si� z zamkni�ciem okna graficznego
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Czy�ci okno na dany kolor
		window.clear(sf::Color::White);

		//Rysuje linie na podstawie tablicy obiekt�w graficznych lines
		for (int i = 0; i<numberofEdges; i++)
		{
			window.draw(lines[i]);
		}

		//Rysuje punkty i ich podpisy na podstawie tablic obiekt�w graficznych points i names
		for (int i = 0; i<numberofNodes; i++)
		{
			window.draw(points[i].point_graphic);
			window.draw(names[i]);
		}

		//Wy�wietla wyrysowane w buforze obiekty graficzne na ekran
		window.display();
	}

	return 0;
}