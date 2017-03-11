#include <SFML/Graphics.hpp>
#include <vector> 
#include <iostream>
#include <cmath>
#include <cstdlib>

#define WINDOWSIZE_X 720
#define WINDOWSIZE_Y 480

#include "Point.h"
#include "Generator.h"
#include "GraphicObjects.h"

int main()
{
    //Ładowanie pliku czcionki (musi być tutaj jeżeli nie chcę robić wskaźnika, a nie chcę.)
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
        std::cout<<"Nie można załadować pliku czcionki: font.ttf";
    //Stworzenie okna
    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "GraphMaker"); 
    //stworzenie na razie pustych tablic na punkty, podpisy i linie(musi być tutaj jeżeli nie chcę robić wskaźników, a nie chcę.)
    std::vector<sf::Text> names;
    std::vector<Point> points;
    std::vector<sf::VertexArray> lines;
    //Początkowa liczba, nie zmieniać, sama się zmieni, określa ile utworzono krawędzi
    int numberofEdges = 0;


    //PARAMETRY:

    //Liczba wierzchołków
    int numberofNodes = 14;
    //Prawdopodobieństwo (łączenie węzłów, ponowne złączanie w przypadku funkcji strogatz()) dane w procentach
    int probability_of_connection = 10;
    //Liczba węzłów na obręcz
    int nodesperLattice = 2;
    //Stosunek rozmiaru mniejszej obręczy do większej
    float latticesProportion = 0.75;


    //Wygenerowanie macierzy sąsiedztwa dla danej liczby wierzchołków według różnych algorytmów klasy Generator:
    //Graf losowy o zadanej liczbie węzłów i prawdopodobieństwie połaczenia (liczba krawędzi to referencja aby zmieniało tą liczbę w mainie)
    //std::vector<std::vector<int>> connectionArray=Generator::random(probability_of_connection,numberofNodes,numberofEdges);
    //Graf pełny o zadanej liczbie węzłów (znów liczba krawędzi jest referencja z maina i określa obecną ich liczbę)
    std::vector<std::vector<int>> connectionArray=Generator::fullGraph(numberofNodes,numberofEdges);
    //Graf losowy o zadanym niczym!
    //std::vector<std::vector<int>> connectionArray=Generator::fullyRandom(probability_of_connection,numberofNodes,numberofEdges,nodesperLattice);



    //Stworzenie punktów i podpisów (obiektów graficznych) wedle parametrów danych wyżej
    GraphicObjects::createPoints(numberofNodes, nodesperLattice, latticesProportion, points);
    GraphicObjects::createNames(numberofNodes, nodesperLattice, latticesProportion, points, names, font);

    //Wygenerowanie obiektów graficznych dla krawędzi łaczących węzły na podstawie wcześniej wygenerowanej
    //macierzy sąsiedztwa
    GraphicObjects::createLines(numberofNodes, points, connectionArray, lines);


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