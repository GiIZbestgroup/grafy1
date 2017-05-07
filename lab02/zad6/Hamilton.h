#pragma once
#include <vector>

//WYSTARCZY ZROBIC TAK:
    //vector<int> ReadyCycle = Hamilton::HamiltonCycle(connectionArray);
        //connectionArray to macierz sasiedztwa zapisana w wektorze wektorow

class Hamilton
{
public:
        //glowna metoda znajdujaca cykl Hamiltona,
        //pobiera macierz sasiedztwa bedaca wektorem wektorow, zwraca wektor, w ktorym zapisane sa numery kolejnych wierzcholkow.
        //UWAGA!
        //1) gdy zwroci pusty wektor == cykl nie istnieje
        //2) gdy cykl istnieje to nr ostatniego wierzcholka w wektorze == pierwszy wierzcholek, od ktorego zaczynamy (np. 0 -> 1 -> 2 -> 0)

    static std::vector<int> HamiltonCycle(std::vector<std::vector<int> > &connectionArray);

        //wewnetrzna metoda uzywana przez metode HamiltonCycle
    static void HamiltonAlgorithm(std::vector<std::vector<int> > &neighbours, int v, bool* isVisited, std::vector<int> &ActualPath, std::vector<int> &FinalPath, bool& isHamiltonGraph);

        //metoda pobierajaca macierz sasiedztwa
        //zwraca wektor wektorow, w ktorym zapisane sa numery wierzcholkow bedace sasiadami
    static std::vector<std::vector<int> > findNeighbours(std::vector<std::vector<int> > connectionArray);
};
