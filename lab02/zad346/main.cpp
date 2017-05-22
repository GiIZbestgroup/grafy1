#include <iostream>
#include "Hamilton.h"

using namespace std;

#include<iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <iomanip>

using namespace std;

//sprawdzanie czy graf jest eulerowski
    //zwraca 0 gdy graf nie jest
    //zwraca 1 gdy jest eulerowski

    //wywolanie:
    //int isEulerian(vector<vector<int> > _graph, int numberofNodes, int numberofEdges)

//procz funkcji bezp. z tym zwiazanych dolaczone:
    //vector <vector<int> > fromfile(int& numberofNodes,int& numberofEdges) - wczytywanie z pliku
    //vector<vector<int> > findNeighbours(vector<vector<int> > connectionArray) - szukanie "sasiadow"

    /////////////////////UNIWERSALNE////////////////////////
    ///////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////

void print(vector<vector<int> > &_matrix)
{
	for(int i = 0 ; i < _matrix.size() ; ++i)
    {
		for(int j = 0 ; j < _matrix[i].size() ; ++j)
			cout << _matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void print(vector<int> connectionArray)
{
    for(unsigned int i = 0 ; i < connectionArray.size() ; ++i)
        cout << connectionArray[i] << " ";
    cout << endl;
}

vector <vector<int> > fromfile(int& numberofNodes,int& numberofEdges)
{
        ifstream file("adjMat.txt");
        int x_size,y_size;
        file >> x_size;
        file >> y_size;
        x_size = static_cast<int>(x_size);

        int tmp;

        if(x_size != 0)
        {
            vector<vector<int> > connectionArray1(x_size,vector<int> (x_size));
            cout<<"Macierz "<<x_size<<" na "<<x_size<<endl;
            for(int i=0; i<x_size; i++)
            {
                for(int j=0; j<x_size; j++)
                {
                    file >> tmp;
                    if (tmp)
                        numberofEdges++;
                    cout<<tmp;
                    connectionArray1[i][j] = tmp;
                }
                cout<<endl;
            }
            numberofNodes = x_size;
            return connectionArray1;
        }
        else
        {
            vector <vector<int> > k;
            cout<<"Niestety nie"<<endl;
            return k;
        }
}

vector<vector<int> > findNeighbours(vector<vector<int> > connectionArray)
{
    vector<vector<int> > neighbours;

    for(unsigned int i = 0 ; i < connectionArray.size(); ++i)
    {
        vector<int> tmp; // wektor przechowujacy numery wierzcholkow, ktore sa sasiadami danego wiechrzolka`
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
 ////////////////////////////////EULER////////////////////////////////
 /////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////

class Graph
{
    int V; //liczba wierzcholkow
    list<int> *adj; //lista sasiedztwa
public:
    Graph(int V)   {this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete [] adj; }

    void addEdge(int v, int w); //funkcja dodajaca krawedz do grafu
    void rmvEdge(int u, int v); //funkcja usuwajaca krawedz z grafu

    int isEulerian(); //sprawdzanie, czy eulerowski (0 lub 1)

    bool isConnected(); //sprawdzanie, czy wszystkie (o st > 0) wierzcholki sa polaczone

    void DFSUtil(int v, bool visited[]); //funkcja do DFS, uzywana w isConnected()

    void printEulerUtil(int start); //wyswietlanie sciezki eulera z zadanego wierzcholka

    int DFSCount(int v, bool visited[]); //zwraca liczbe wierzcholkow, ktore mozna odwiedzic z v

    bool isValidNextEdge(int u, int v); // sprawdzanie czy krawedz u-v mozna dolaczyc jako nastepna do sciezki/cyklu
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true; //obecnie odwiedzany wierzcholek - odwiedzony

    list<int>::iterator i; //dla wszystkich wierzcholkow polaczonych z obecnym wywolujemy - rekurencja
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i]) //oczywiscie jesli juz nie zostal odwiedzony
            DFSUtil(*i, visited); //rekurencja
}

bool Graph::isConnected()
{
    bool visited[V]; //tablica odwiedzin wierzcholkow, V - l. wierzcholkow
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false; //wszystkie wierzcholki sa nieodwiedzone

    for (i = 0; i < V; i++) //szukanie wierzcholka o st != 0
        if (adj[i].size() != 0)
            break;

    if (i == V) //gdy liczba wierzcholkow (st=0) = liczba wszystkich wierzcholkow -> nie ma krawedzi
        return true; //to jest eulerowski - bo wszystkie krawedzie przeszlismy (bo przejscie przez wierzcholki niewazne)

    DFSUtil(i, visited); //dla wierzch. o niezerowym st. sprawdzanie, czy wszystkie sa polaczone

    for (i = 0; i < V; i++)
       if (visited[i] == false && adj[i].size() > 0) //jesli jest nieodwiedzony i ma st > 0
            return false;

    return true;
}

int Graph::isEulerian()
{
    if (isConnected() == false) //czy wszystkie wierzcholki polaczone
        return 0;

    int odd = 0; //liczba wierzcholkow o stopniu nieparzystym
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1) //(i & 1) = 1,3,5,7,9
            odd++;

    if (odd > 2) //jesli wiecej niz dwa o st nieparzystym, to odpada
        return 0;

    return (odd)? 0 : 1;
}

void test(Graph &g)
{
    int result = g.isEulerian();
    if (result == 0)
        cout << "graf nie jest eulerowski\n";
    else
        cout << "graf ma cykl Eulera (jest eulerowski)\n";
}

//wypisz sciezke/cykl zaczynajac od u
void Graph::printEulerUtil(int u)
{
  //wybierz wszystkie polaczone z tym wierzcholkiem wierzcholki
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
      int v = *i;

      //jesli krawedz nie jest usunieta (wart -1) i jest to poprawna sciezka
      if (v != -1 && isValidNextEdge(u, v))
      {
          cout << u << "-" << v << "  ";
          rmvEdge(u, v); //usuwamy
          printEulerUtil(v); //rekurencyjne wywolanie dla v
      }
  }
}

//sprawdzanie czy krawedz mozna uznac jako nastepny krok
bool Graph::isValidNextEdge(int u, int v)
{
  //jest to spelnione, gdy:

  // 1) v to jedyny sasiad u
  int count = 0;  // liczba przylaczonych wierzcholkow
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
     if (*i != -1)
        count++;
  if (count == 1)
    return true;


  // 2) Jesli kilka mozliwych, to taka, ze u-v nie jest mostem
  // sprawdzanie czy u-v jest mostem:

  // 2.a) liczenie wierzcholkow, do ktorych mozna dojsc z u
  bool visited[V];
  memset(visited, false, V);
  int count1 = DFSCount(u, visited);

  // 2.b) Usuniecie krawedzi (u, v), a nastepnie zliczenie wierzcholkow, do ktorych mozna dojsc z u
  rmvEdge(u, v);
  memset(visited, false, V);
  int count2 = DFSCount(u, visited);

  // 2.c) dodanie krawedzi znowu do grafu
  addEdge(u, v);

  // 2.d) jesli count1 jest wieksze, to krawedz (u, v) jest mostem
  return (count1 > count2)? false: true;
}

// usuwanie krawedzi z grafu, zastepuje wart -1
void Graph::rmvEdge(int u, int v)
{
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
  *iv = -1;
  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
  *iu = -1;
}

//funkcja oparta na DFS do zliczania wierzcholkow, do ktorych mozna dojsc z v
int Graph::DFSCount(int v, bool visited[])
{
  visited[v] = true; //obecnie odwiedzany wierzcholek - odwiedzony
  int count = 1; //mozna dojsc do tego wlasnie wierzcholka

  //dla wszystkich wierzcholkow polaczonych z obecnym wywolujemy - rekurencja
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
      if (*i != -1 && !visited[*i])
          count += DFSCount(*i, visited);

  return count;
}

int isE(vector<vector<int> > _graph, int numberofNodes, int numberofEdges)
{
    vector<vector<int> > neighbours = findNeighbours(_graph);
    Graph g(numberofNodes);

    for(int i = 0; i < _graph.size(); i++)
    {
        for(int j = 0; j < neighbours[i].size(); j++)
        {
            if (i < neighbours[i][j])
                g.addEdge(i, neighbours[i][j]);
        }
    }
    test(g);
    return g.isEulerian();
}

void findEC(vector<vector<int> > _graph, int numberofNodes, int numberofEdges)
{
    vector<vector<int> > neighbours = findNeighbours(_graph);
    Graph g(numberofNodes);

    for(int i = 0; i < _graph.size(); i++)
    {
        for(int j = 0; j < neighbours[i].size(); j++)
        {
            if (i < neighbours[i][j])
                g.addEdge(i, neighbours[i][j]);
        }
    }

    int value = isE(_graph, numberofNodes, numberofEdges);
    if (value == 0)
        return;
    else
        g.printEulerUtil(0);
}

void findEC(vector<vector<int> > _graph, int numberofNodes, int numberofEdges, int start)
{
    vector<vector<int> > neighbours = findNeighbours(_graph);
    Graph g(numberofNodes);

    for(int i = 0; i < _graph.size(); i++)
    {
        for(int j = 0; j < neighbours[i].size(); j++)
        {
            if (i < neighbours[i][j])
                g.addEdge(i, neighbours[i][j]);
        }
    }

    int value = isE(_graph, numberofNodes, numberofEdges);
    if (value == 0)
        return;
    else
        g.printEulerUtil(start);
}

//funkcja findCC - szukanie najwiekszej spojnej skladowej na grafie
//przyjmuje wektor wektorow - macierz sasiedztwa, liczbe wierzcholkow i liczbe krawedzi
//zwraca wektor, w ktorym zapisane sa wierzcholki nalezace do skladowej
//znajduje jedna najwieksza spojna skladowa (jesli jest ich wiecej, to przykro)
//wykorzystuje funkcje vector<vector<int> > findNeighbours(vector<vector<int> > &_matrix)
//dolaczam ponizej, jest ona rowniez wykorzystywana w Hamiltonach

//////////////////////////////////////SKLADOWA/////////////////////////////////////
 ///////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////

struct TNode
{
  TNode *up;                      // Rodzic wêz³a
  int rank;                       // Ranga
  int data;                       // Zawartoœæ wêz³a
};

// Tworzy drzewo jednowêz³owe
//---------------------------
void MakeSet(TNode * x)
{
  x->up = x;                      // x staje siê korzeniem drzewa
  x->rank = 0;                    // Rangê zerujemy
}

// Zwraca korzeñ drzewa i ustawia pola up
// wszystkich wêz³ów nadrzêdnych a¿ do korzenia
//---------------------------------------------
TNode * FindSet(TNode * x)
{
  if(x->up != x) x->up = FindSet(x->up);
  return x->up;
}

// £¹czy ze sob¹ drzewa z x i z y
//-------------------------------
void UnionSets(TNode *x, TNode *y)
{
  TNode *rx,*ry;

  rx = FindSet(x);                // Wyznaczamy korzeñ drzewa z wêz³em x
  ry = FindSet(y);                // Wyznaczamy korzeñ drzewa z wêz³em y
  if(rx != ry)                    // Korzenie musz¹ byæ ró¿ne
  {
    if(rx->rank > ry->rank)       // Porównujemy rangi drzew
       ry->up = rx;               // rx wiêksze, do³¹czamy ry
    else
    {
      rx->up = ry;                // równe lub ry wiêksze, do³¹czamy rx
      if(rx->rank == ry->rank) ry->rank++;
    }
  }
}

vector<int> findCC(vector<vector<int> > &_graph,int n, int m)
{
  //int numberofNodes, numberofEdges; // Liczba wierzcho³ków i krawêdzi
  TNode * T;
  int i,j,v,u;
  vector<int> CC;
  vector<vector<int> > neighbours = findNeighbours(_graph);
  int connected[n][n];
  for (int i = 0; i<n; ++i)
    {
        for (int j = 0; j < n; j++)
            connected[i][j] = 0;
    }


  T = new TNode [n];              // tworzenie tablicê zbiorów roz³¹cznych

  // Tablicê T inicjujemy

  for(i = 0; i < n; i++)
  {
    T[i].data = i;                // numer wêz³a
    MakeSet(&T[i]);               // tworzenie zbioru jednoelementowego
  }

  // kolejne krawedzie grafu

  for(i = 0; i < _graph.size(); i++)
  {
    //v , u - wierzcho³ki tworz¹ce krawêdŸ
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

  cout << endl;

  for(i = 0; i < n; i++)
    if(i == FindSet(&T[i])->data)
    {
      vector<int> tmp;
      cout << "SCC"<< " :";
      for(j = 0; j < n; j++)
        if(i == FindSet(&T[j])->data)
        {
            cout << j << " ";
            tmp.push_back(j);
        }
        if (tmp.size() > CC.size())
            CC = tmp;
      cout << endl;
    }

  // usuwanie tablicy zbiorow rozlacznych

  delete [] T;

  //zwrocenie najwiekszej spojnej skladowej
  return CC;
}

   /////////////////////MAIN////////////////////////
    ///////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////

int main()
{
    cout << "Ladowanie grafu z pliku. Zaladowano:" <<endl;
    int numberofNodes, numberofEdges;
    vector<vector<int> > _graph;
    _graph = fromfile(numberofNodes, numberofEdges);
    cout << endl << endl;
    int opcja = 0;
    while (1)
    {
        cout << "Co chcesz zrobic?" << endl << endl;
        cout << "1 - znajdowanie najwiekszej spojnej skladowej (zad 3)" << endl;
        cout << "2 - sprawdz czy graf jest eulerowski i jesli jest - wypisz cykl Eulera (zad 4)" << endl;
        cout << "3 - sprawdz czy graf jest eulerowski i jesli jest - wypisz cykl Eulera zaczynajac od podanego wierzcholka" << endl;
        cout << "4 - sprawdz, czy graf jest hamiltonowski (zad 6)" << endl << endl;
        cin >> opcja;
        if (opcja == 1 || opcja == 2 || opcja == 3 || opcja == 4)
            break;
    }

    if (opcja == 1)
    {
        cout << "Znajdowanie najwiekszej spojnej skladowej" << endl;
        vector<int> CC;
        CC = findCC(_graph,numberofNodes, numberofEdges);
        cout << endl;
        cout << "najwieksza spojna skladowa ma " << CC.size() << " wierzolkow: ";
        print(CC);
    }

    else if (opcja == 2)
    {
        cout << "Sprawdzanie, czy graf jest eulerowski" << endl;
        findEC(_graph, numberofNodes, numberofEdges);
    }

    else if (opcja == 3)
    {
        cout << "Sprawdzanie, czy graf jest eulerowski" << endl << endl;
        cout << "Podaj numer wierzcholka, od ktorego zacznie sie wypisywanie sciezki Eulera, gdy graf jest eulerowski" << endl;
        cout << "(liczba z przedzialu [0, " << numberofNodes-1 << "])" << endl;
        int start;
        do
            cin >> start;
        while (start < 0 || start > numberofNodes-1);
        findEC(_graph, numberofNodes, numberofEdges, start);
    }

    else
    {
        cout << "Sprawdzanie, czy graf jest hamiltonowski" << endl;
        vector<int> HC = Hamilton::HamiltonCycle(_graph);
        cout << endl;
        if (!HC.size())
            cout << "Graf nie jest hamiltonowski" << endl;
        else
        {
            cout << "Graf nie jest hamiltonowski" << endl;
            cout << "dlugosc sciezki Hamiltona wynosi " << HC.size() << " wierzolkow: ";
            print(HC);
        }
    }

    return 0;
}
