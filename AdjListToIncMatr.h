int** AdjListToIncMatr (std::list<int> *adjList, int nodes, int edges)
{
	//alokujemy tablicę bool condition[nodes][nodes] i ustawiamy każdą wartość na false
	//alokujemy tablicę int IncMatr[nodes][edges] i ustawiamy każdą wartość na 0
	int counter = 0;
	int i;
	int j = 0;
	
	for (i = 0; i < nodes; i++)
	{
		   for(list<int>::iterator iter=adjList.begin(); iter != adjList.end(); ++iter)
		   {
			   if(!condition[counter][i])
			   {
				   IncMatr[i][j] = 1;
				   
				   condition[counter][i] = true;
				   condition[i][counter] = true;
				   counter++;
				   j++;
			   }
		   }
	}
	
	//dealokujemy tablicę condition
	return IncMatr;
}