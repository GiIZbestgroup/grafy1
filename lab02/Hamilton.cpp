#include "Hamilton.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<int> Hamilton::HamiltonCycle(vector<vector<int> > &myGraphToCheck)
{
    srand( time( NULL ) );
    vector<vector<int> > neighbours = findNeighbours(myGraphToCheck);
    vector<int>  FinalPath; // tworzy wektor, do ktorego przepisze juz gotowy cykl z ActualPath
    if (myGraphToCheck.size() > 0) // jezeli graf zawiera choc jeden wierzcholek
        {
            vector<int> ActualPath; // tworzy wektor, w ktorym bedzie umieszczal odwiedzone wierzcholki
            bool isVisited[int(ActualPath.size())]; // pomocnicza tablica, ktora informuje, czy mozna wejsc do nast. wierzcholka i dodac go do ActualPath
            int v = ( std::rand() % (myGraphToCheck.size()) ); // wierzcholek, od ktorego zaczynamy poszukiwanie
            bool isHamiltonGraph; // flaga okreslajaca, czy algorytm znalazl cykl i czy moze przepisac go z ActualPath do FinalPath

            for (int i = 0; i < myGraphToCheck.size() ; i++)
            {
                isVisited[i] = false; // zerowanie tablicy odwiedzin
            }
            HamiltonAlgorithm(neighbours, v, isVisited, ActualPath, FinalPath, isHamiltonGraph);
            //cout << "Moja koncowa sciezka ma: " << FinalPath.size() << " wierzcholkow :)" << endl;
        }
    return FinalPath;
}

void Hamilton::HamiltonAlgorithm(vector<vector<int> > &neighbours, int v, bool* isVisited, vector<int> &ActualPath, vector<int> &FinalPath, bool& isHamiltonGraph)
{
            ActualPath.push_back(v);  //dodaje do listy odwiedzonych wierzcholkow aktualny wierzcholek v, w ktorym sie znajduje

            if ( ActualPath.size() == neighbours.size() ) // sprawdzanie czy nie odwiedzono wszystkich wierzcholkow (jezeli tak to istnieje szansa na cykl!)
            {
                //cout << "Znalazlem sciezke hamiltona" << endl;
                int last_node_id = ActualPath[ActualPath.size() - 1 ]; //numer ostatniego wierzcholka
                for (unsigned int i = 0; i < neighbours[last_node_id].size(); ++i)  //sprawdzanie wszystkich sasiadow ostatniego wierzcholka
                {
                    if (neighbours[last_node_id][i] == ActualPath[0]) // sprawdzanie czy z ostatniego wierzcholka moge wrocic do poczatkowego. Jak tak, to cykl istnieje!
                    {
                        isHamiltonGraph = true;
                        break;
                    }
                }

                if (FinalPath.size() == 0 && isHamiltonGraph) // Jezeli isHamiltonGraph == true oraz jakis cykl nie zostal juz zapisany (bo moglo byc ich kilka) to zapisuje wlasnie znaleziony
                {
                    for (unsigned int i = 0; i < ActualPath.size(); ++i)
                    {
                        FinalPath.push_back(ActualPath[i]);
                    }
                }
                if (isHamiltonGraph && (FinalPath[0] != FinalPath[FinalPath.size() - 1]))
                {
                    FinalPath.push_back(ActualPath[0]); // dodaje na koniec cyklu element poczatkowy (1->2->3 + (->1))
                }
            }
            else // jednak nie odwiedzilismy jeszcze wszystkich wierzcholkow, bo dlugosc tablicy odwiedzin jest mniejsza od ilosci wierzcholkow w grafie
            {
                isVisited[v] = true;  // dodanie do tablicy odwiedzin, wierzcholka, w ktorym aktualnie sie jest
                for (unsigned int i = 0; i < neighbours[v].size(); ++i) // dla kazdego sasiada v, wykonuje:
                {
                    if (isVisited[neighbours[v][i]] == false) //jezeli sposrod sasiadow wierzcholka v, wierzcholek (isVisited[neighbours[v][i]]) nie byl odwiedzony:
                    {
                        HamiltonAlgorithm(neighbours, neighbours[v][i], isVisited, ActualPath, FinalPath, isHamiltonGraph); //wejscie do tego wierzcholka i wykonanie algorytmu od nowa
                    }
                }
                isVisited[v] = false; //okazalo sie, ze wejscie do v wprowadzilo w slepy zaulek (brak polaczen lub wszystkie sasiadujace wierzcholki byly juz odwiedzone)
            }

            if (ActualPath.size() > 0)
            {
                ActualPath.pop_back(); // wyrzucenie wierzcholka v, ktory jest slepym zaulkiem
            }
}


vector<vector<int> > Hamilton::findNeighbours(vector<vector<int> > connectionArray)
{
    vector<vector<int> > neighbours;

    for(unsigned int i = 0 ; i < connectionArray.size(); ++i)
    {
        vector<int> tmp; // wektor przechowujacy numery wierzcholkow, ktore sa sasiadami danego wiechrzolka
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
