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


//FUNKCJE DARII
//funkcja findCC - szukanie najwiekszej spojnej skladowej na grafie
//przyjmuje wektor wektorow - macierz sasiedztwa
//zwraca wektor, w ktorym zapisane sa wierzcholki nalezace do skladowej
//znajduje jedna najwieksza spojna skladowa (jesli jest ich wiecej, to przykro)
//wykorzystuje funkcje std::vector<std::vector<int> > findNeighbours(std::vector<std::vector<int> > &_matrix)
//dolaczam ponizej, jest ona rowniez wykorzystywana w Hamiltonach

struct TNode
{
  TNode *up;                      // Rodzic węzła
  int rank;                       // Ranga
  int data;                       // Zawartoć węzła
};

// Tworzy drzewo jednowęzłowe
//---------------------------
void MakeSet(TNode * x)
{
  x->up = x;                      // x staje się korzeniem drzewa
  x->rank = 0;                    // Rangę zerujemy
}

// Zwraca korzeń drzewa i ustawia pola up
// wszystkich węzłów nadrzędnych aż do korzenia
//---------------------------------------------
TNode * FindSet(TNode * x)
{
  if(x->up != x) x->up = FindSet(x->up);
  return x->up;
}

// Łšczy ze sobš drzewa z x i z y
//-------------------------------
void UnionSets(TNode *x, TNode *y)
{
  TNode *rx,*ry;

  rx = FindSet(x);                // Wyznaczamy korzeń drzewa z węzłem x
  ry = FindSet(y);                // Wyznaczamy korzeń drzewa z węzłem y
  if(rx != ry)                    // Korzenie muszš być różne
  {
    if(rx->rank > ry->rank)       // Porównujemy rangi drzew
       ry->up = rx;               // rx większe, dołšczamy ry
    else
    {
      rx->up = ry;                // równe lub ry większe, dołšczamy rx
      if(rx->rank == ry->rank) ry->rank++;
    }
  }
}

std::vector<std::vector<int> > findNeighbours(std::vector<std::vector<int> > connectionArray)
{
    std::vector<std::vector<int> > neighbours;

    for(unsigned int i = 0 ; i < connectionArray.size(); ++i)
    {
        std::vector<int> tmp; // wektor przechowujacy numery wierzcholkow, ktore sa sasiadami danego wiechrzolka`
        for(unsigned int j = 0 ; j < connectionArray[i].size() ; ++j)
        {
            if(i!=j) // wierzcholek nie sasiaduje z samym soba
            {
                if (connectionArray[i][j]!=0) // gdy wartosc != 0 to polaczenie istnieje (nie == 1, bo potem moga to byc wagi przejscia sciezek)
                    tmp.push_back(j); // zapisanie numeru wierzcholka do wektora
            }
        }
        neighbours.push_back(tmp);
        tmp.clear();
    }

    return neighbours;
}
void print(std::vector<std::vector<int> > &_matrix)
{
    for(int i = 0 ; i < _matrix.size() ; ++i)
    {
        for(int j = 0 ; j < _matrix[i].size() ; ++j)
            std::cout << _matrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print(std::vector<int> connectionArray)
{
    for(unsigned int i = 0 ; i < connectionArray.size() ; ++i)
        std::cout << connectionArray[i] << " ";
    std::cout << std::endl;
}

// **********************
// *** FUNKCJA GLOWNA ***
// **********************

std::vector<int> findCC(std::vector<std::vector<int> > &_graph,int n, int m)
{
  //int numberofNodes, numberofEdges; // Liczba wierzchołków i krawędzi
  TNode * T;
  int i,j,v,u;
  std::vector<int> CC;
  std::vector<std::vector<int> > neighbours = findNeighbours(_graph);
  int connected[n][n];
  for (int i = 0; i<n; ++i)
    {
        for (int j = 0; j < n; j++)
            connected[i][j] = 0;
    }


  T = new TNode [n];              // tworzenie tablicę zbiorów rozłšcznych

  // Tablicę T inicjujemy

  for(i = 0; i < n; i++)
  {
    T[i].data = i;                // numer węzła
    MakeSet(&T[i]);               // tworzenie zbioru jednoelementowego
  }

  // kolejne krawedzie grafu

  for(i = 0; i < _graph.size(); i++)
  {
    //v , u - wierzchołki tworzšce krawęd
    for(j = 0; j < neighbours[i].size(); j++)
    {
        v = i;
        u = neighbours[i][j];
        if (connected[i][j] != 1)
            UnionSets(&T[v],&T[u]);       // laczenie zbiorow z u i v
        connected[i][j] = connected[j][i] = 1;
    }
  }

  // wypisanie wszystkich spojnych skladowych na grafie

  std::cout << std::endl;

  for(i = 0; i < n; i++)
    if(i == FindSet(&T[i])->data)
    {
      std::vector<int> tmp;
      std::cout << "SCC"<< " :";
      for(j = 0; j < n; j++)
        if(i == FindSet(&T[j])->data)
        {
            std::cout << j << " ";
            tmp.push_back(j);
        }
        if (tmp.size() > CC.size())
            CC = tmp;
      std::cout << std::endl;
    }

  // usuwanie tablicy zbiorow rozlacznych

  delete [] T;

  //zwrocenie najwiekszej spojnej skladowej
  return CC;
}
//KONIEC FUNKCJI DARII

















std::vector <std::vector<int>> fromfile(int& numberofNodes,int& numberofEdges)
{
        std::ifstream file("adjMat.txt");
        int x_size,y_size;
        file >> x_size;
        file >> y_size;
        x_size = static_cast<int>(x_size);

        int tmp;

        if(x_size != 0)
        {
            std::vector<std::vector<int>> connectionArray1(x_size,std::vector<int> (x_size));
            std::cout<<"Macierz "<<x_size<<" na "<<x_size<<std::endl;
            for(int i=0; i<x_size; i++)
            {
                for(int j=0; j<x_size; j++)
                {
                    file >> tmp;
                    if (tmp && j<i)
                        numberofEdges++;
                    std::cout<<tmp;
                    connectionArray1[i][j] = tmp;
                    connectionArray1[j][i] = tmp;
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
        std::ofstream file("adjMat.txt");
        file << numberofNodes <<" ";
        file << numberofNodes <<"\n";

            for(int i=0; i<numberofNodes; i++)
            {
                for(int j=0; j<numberofNodes; j++)
                {
                    file <<matrix[i][j]<<" ";
                }
                file<<"\n";
            }

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

    std::cout<<std::endl<<"Wczytano graf z pliku incMat.txt\n";
    

    std::vector <std::vector<int>> connectionArray = fromfile(numberofNodes,numberofEdges);
    std::cout<<"\nPodaj liczbę węzłów na jedną obręcz:"<<std::endl;
    std::cin>>nodesperLattice;
    std::cout<<"Podaj proporcję wielkości obręczy:"<<std::endl;
    std::cin>>latticesProportion;
        
     

     for(int i=0;i<numberofNodes;i++)
        for(int j=0;j<i;j++)
            connectionArray[j][i] = connectionArray[i][j];

     tofile(numberofNodes,connectionArray);

    //Szukanie spójnej składowej
    std::vector<int> CCpoints = findCC(connectionArray,numberofNodes,numberofEdges);

    std::cout<<"Największa spójna składowa:\n";
    for(int i=0;i<CCpoints.size();i++)
    {
        std::cout<<CCpoints[i]+1<<" ";
    }
    std::cout<<std::endl;

     //Stworzenie okna
     sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_X, WINDOWSIZE_Y), "GraphMaker - Master the Space-Time Continuum"); 

    //Stworzenie punktów i podpisów (obiektów graficznych) wedle parametrów danych wyżej
    GraphicObjects::createPoints(numberofNodes, nodesperLattice, latticesProportion, points);
    GraphicObjects::createNames(numberofNodes, nodesperLattice, latticesProportion, points, names, font);

    //Wygenerowanie obiektów graficznych dla krawędzi łaczących węzły na podstawie wcześniej wygenerowanej
    //macierzy sąsiedztwa
    GraphicObjects::createLines(numberofNodes, points, connectionArray, lines, CCpoints);








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