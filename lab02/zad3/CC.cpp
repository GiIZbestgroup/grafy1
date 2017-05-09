//funkcja findCC - szukanie najwiekszej spojnej skladowej na grafie
//przyjmuje wektor wektorow - macierz sasiedztwa, liczbe wierzcholkow i liczbe krawedzi
//zwraca wektor, w ktorym zapisane sa wierzcholki nalezace do skladowej
//znajduje jedna najwieksza spojna skladowa (jesli jest ich wiecej, to przykro)
//wykorzystuje funkcje vector<vector<int> > findNeighbours(vector<vector<int> > &_matrix)
//dolaczam ponizej, jest ona rowniez wykorzystywana w Hamiltonach


#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

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

struct TNode
{
  TNode *up;                      
  int rank;                     
  int data;                       
};


void MakeSet(TNode * x)
{
  x->up = x;                      
  x->rank = 0;                    
}

TNode * FindSet(TNode * x)
{
  if(x->up != x) x->up = FindSet(x->up);
  return x->up;
}


//-------------------------------
void UnionSets(TNode *x, TNode *y)
{
  TNode *rx,*ry;

  rx = FindSet(x);                
  ry = FindSet(y);                
  if(rx != ry)                    
  {
    if(rx->rank > ry->rank)       
       ry->up = rx;              
    else
    {
      rx->up = ry;                
      if(rx->rank == ry->rank) ry->rank++;
    }
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

// **********************
// *** FUNKCJA GLOWNA ***
// **********************

vector<int> findCC(vector<vector<int> > &_graph,int n, int m)
{
  //int numberofNodes, numberofEdges; // liczba wierzcholkow i krawedzi
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


  T = new TNode [n];              // tworzenie tablicy zbiorow rozlacznych

  // Tablicê T inicjujemy

  for(i = 0; i < n; i++)
  {
    T[i].data = i;                // numer wezla
    MakeSet(&T[i]);               // tworzenie zbioru jednoelementowego
  }

  // kolejne krawedzie grafu

  for(i = 0; i < _graph.size(); i++)
  {
    //v , u - wierzcholki tworzace krawedz
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

/*  /////////////PRZYKLADOWE UZYCIE////////////////////
int main()
{
    int numberofNodes, numberofEdges;
    vector<vector<int> > _graph;
    vector<int> CC;
    _graph = fromfile(numberofNodes, numberofEdges);
    CC = findCC(_graph,numberofNodes, numberofEdges);
    cout << endl;
    cout << "najwieksza spojna skladowa ma " << CC.size() << " wierzolkow: ";
    print(CC);
    return 0;
}
*/
