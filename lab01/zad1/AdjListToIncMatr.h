int** AdjListToIncMatr (std::vector<int> *adjList, int nodes, int edges)
{
	//alokujemy tablicę int IncMatr[nodes][edges] i ustawiamy każdą wartość na 0
	
	int counter = 0;
	
	for (int i = 0; i < nodes; i++)
	{
		for(vector<int>::iterator iter=adjList[i].begin(); iter != adjList[i].end(); ++iter)
		{
			int j = *iter;

			IncMatr[i][counter] = 1;
			IncMatr[j][counter] = 1;
			counter++;
				
			if (counter == edges)
				break;
		}
		
		if (counter == edges)
			break;
	}
	
	return IncMatr;
}