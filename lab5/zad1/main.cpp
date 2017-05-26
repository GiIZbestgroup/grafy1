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

std::vector <std::vector<int>> fromfile(int& numberofNodes,int& numberofEdges,std::vector<int> &layers)
{
        std::ifstream file("adjMat.txt");
        int x_size,y_size,layers_number;
        file >> x_size;
        file >> y_size;
        file >> layers_number;
        x_size = static_cast<int>(x_size);
        layers_number = static_cast<int>(layers_number);

        int tmp;

        for(int i = 0; i < layers_number; i++)
        {
            file >> tmp;
            if(tmp)
            layers.push_back(tmp);
        }


        if(x_size != 0)
        {
            std::vector<std::vector<int>> connectionArray1(x_size,std::vector<int> (x_size));
            std::cout<<"Macierz "<<x_size<<" na "<<x_size<<std::endl;
            for(int i=0; i<x_size; i++)
            {
                for(int j=0; j<x_size; j++)
                {
                    file >> tmp;
                    if (tmp)
                        numberofEdges++;
                    std::cout<<tmp;
                    connectionArray1[i][j] = tmp;
                }
                std::cout<<std::endl;
            }
            numberofNodes = x_size;
            return connectionArray1;
        }
        else
        {
            std::vector <std::vector<int>> k;
            std::cout<<"Niestety nie"<<std::endl;
            return k;
        }
}


void tofile(int numberofNodes, std::vector <std::vector<int>> matrix)
{
      /*  std::ofstream file("adjMat.txt");
        file << numberofNodes <<" ";
        file << numberofNodes <<"\n";

            for(int i=0; i<numberofNodes; i++)
            {
                for(int j=0; j<numberofNodes; j++)
                {
                    file <<matrix[i][j]<<" ";
                }
                file<<"\n";
            }*/

}

int main()
{
    //Ładowanie pliku czcionki (musi być tutaj jeżeli nie chcę robić wskaźnika, a nie chcę.)
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
        std::cout<<"Nie można załadować pliku czcionki: font.ttf";
    //Stworzenie okna
    
    //stworzenie na razie pustych tablic na punkty, podpisy i linie(musi być tutaj jeżeli nie chcę robić wskaźników, a nie chcę.)
    std::vector<sf::Text> names;
    std::vector<Point> points;
    std::vector<sf::VertexArray> lines;
    std::vector<sf::CircleShape> arrows;
    //Początkowa liczba, nie zmieniać, sama się zmieni, określa ile utworzono krawędzi
    int numberofEdges = 0;


    //PARAMETRY:

    //Liczba wierzchołków
    int numberofNodes;
    //Prawdopodobieństwo (łączenie węzłów, ponowne złączanie w przypadku funkcji strogatz()) dane w procentach
    double probability_of_connection;
    //Liczba węzłów na obręcz
    int nodesperLattice;
    //Stosunek rozmiaru mniejszej obręczy do większej
    float latticesProportion;
    //Upragniona liczba krawędzi przy generowaniu losowego z określoną ich liczbą
    int desiredNumberofEdges;

    //Tu mamy obsługę wejścia:

     std::cout<<std::endl<<"FUNKCJE PROGRAMU\n"<<"1 - wczytaj graf z pliku adjMat.txt / bez kolorowania wag\n";
     std::cout<<"2 - wczytaj graf z pliku adjMat.txt / kolorowanie wag\n";
     int choice;
     std::cin>>choice;
     std::cout<<std::endl;
     std::vector<std::vector<int>> connectionArray;
     std::vector<int> layers;

     switch(choice)
     {
        case 1:

        connectionArray = fromfile(numberofNodes,numberofEdges,layers);
        //std::cout<<"\nPodaj liczbę węzłów na jedną obręcz:"<<std::endl;
        //std::cin>>nodesperLattice;
        //std::cout<<"Podaj proporcję wielkości obręczy:"<<std::endl;
        //std::cin>>latticesProportion;
        
        break;
        
        case 2:

        connectionArray = fromfile(numberofNodes,numberofEdges,layers);
        //std::cout<<"\nPodaj liczbę węzłów na jedną obręcz:"<<std::endl;
        //std::cin>>nodesperLattice;
        //std::cout<<"Podaj proporcję wielkości obręczy:"<<std::endl;
        //std::cin>>latticesProportion;
        
        break;

     }


     //Stworzenie okna
     sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "GraphMaker - Master the Space-Time Continuum"); 

    //Stworzenie punktów i podpisów (obiektów graficznych) wedle parametrów danych wyżej
    GraphicObjects::createPoints(layers, numberofNodes, nodesperLattice, latticesProportion, points);
    GraphicObjects::createNames(numberofNodes, nodesperLattice, latticesProportion, points, names, font);

    //Wygenerowanie obiektów graficznych dla łuków łaczących węzły na podstawie wcześniej wygenerowanej
    //macierzy sąsiedztwa
    GraphicObjects::createLines(numberofNodes, points, connectionArray, lines, arrows, choice);

    tofile(numberofNodes,connectionArray);

    int ctr = 0;
    int ctr2 = 0;

    while (window.isOpen())
    {
        //Tworzy obiekt typu zdarzenie (statyczny)
        sf::Event event;
        
        //Daje oknu status "zamknięte" gdy wyłączymy okno przez co pętla i program kończą się z zamknięciem okna graficznego
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Czyści okno na dany kolor
        window.clear(sf::Color::White);

        //Rysuje linie na podstawie tablicy obiektów graficznych lines
        for(int i=0;i<numberofEdges;i++)
        {
            window.draw(lines[i]);
            window.draw(arrows[i]);
        }

        //Rysuje punkty i ich podpisy na podstawie tablic obiektów graficznych points i names
        for(int i=0;i<numberofNodes;i++)
        {
            window.draw(points[i].point_graphic);
            window.draw(names[i]);
        }

        //Wyświetla wyrysowane w buforze obiekty graficzne na ekran
        window.display();
    }

    return 0;
}