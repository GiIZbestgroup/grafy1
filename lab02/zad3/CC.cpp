//funkcja findCC - szukanie najwiekszej spojnej skladowej na grafie
//przyjmuje wektor wektorow - macierz sasiedztwa
//zwraca wektor, w ktorym zapisane sa wierzcholki nalezace do skladowej
//znajduje jedna najwieksza spojna skladowa (jesli jest ich wiecej, to przykro)
//wykorzystuje funkcje vector<vector<int> > findNeighbours(vector<vector<int> > &_matrix)
//dolaczam ponizej, jest ona rowniez wykorzystywana w Hamiltonach


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

vector<int> findCC(vector<vector<int> > &_matrix){

    vector<vector<int> > neighbours = findNeighbours(_matrix);
    print(neighbours);
    int largestNumberOfNeighbors = 0; //liczba sasiadow
    int first = 0;
    vector<int> CC;
    int visited[_matrix.size()];
    for (int i = 0; i<_matrix.size(); ++i)
    {
        visited[i] = 0;
    }

    for(unsigned int i = 0 ; i < neighbours.size(); ++i)
    {
        if (neighbours[i].size() > largestNumberOfNeighbors)
        {
            largestNumberOfNeighbors = neighbours[i].size();
            while (CC.size())
                CC.pop_back();
            first = i;
            CC.push_back(first);
            visited[first] = 1;
            for (unsigned int j = 0; j < neighbours[i].size(); ++j)
            {
                CC.push_back(neighbours[i][j]);
                visited[neighbours[i][j]] = 1;
            }
        }
    }

    for (unsigned int i = 1; i < neighbours.size(); ++i)
    {
        for (unsigned int j = 1; j < neighbours[i].size(); ++j) //pierwszego nie sprawdzamy
        {
            if ( visited[neighbours[i][j]] == 0)
            {
                CC.insert(CC.end(), neighbours[i][j]);
                visited[neighbours[i][j]] = 1;
                continue;
            }
        }
    }

    CC.push_back(first);
    return CC;
}
