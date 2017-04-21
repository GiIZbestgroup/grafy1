int** AdjListToIncMatr (std::vector<int> *adjList, int nodes, int edges)
{
	//alokujemy tablicę bool condition[nodes][nodes] i ustawiamy każdą wartość na false
	//alokujemy tablicę int IncMatr[nodes][edges] i ustawiamy każdą wartość na 0
	
	int counter = 0;
	
	for (int i = 0; i < nodes; i++)
	{
		   for(vector<int>::iterator iter=adjList[i].begin(); iter != adjList[i].end(); ++iter)
		   {
				int j = *iter;

				if(!condition[j][i])
				{
				   IncMatr[i][counter] = 1;
				   
				   condition[j][i] = true;
				   condition[i][j] = true;
				   
				   counter++;
				}
		   }
	}
	
	//dealokujemy tablicę condition
	return IncMatr;
}