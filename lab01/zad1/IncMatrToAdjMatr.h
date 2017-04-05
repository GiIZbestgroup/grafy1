int** IncMatrixToAdjMatrix (int** IncMatr)
{
	int hold[2] = {0, 0};
	int counter = 0;
	int w, k;	//w - liczba wierzcholkow, k - liczba krawedzi
	//alokujemy tablice AdjMatr[w][w] i ustawiamy jej wszystko na zero, nie chce mi sie tego zapisywac xD
	for(int i = 0; i < k; i++)
	{
		for(int j = 0; j < w; j++)
		{
			if(IncMatr[i][j] == 1)
			{
				hold[counter] = w;		//albo w+1, jeśli wierzchołki na grafie numerujemy od 1, nie ma znaczenia
				++counter;
			}
		}
		
		AdjMatr[hold[0]] = hold[1];
		AdjMatr[hold[1]] = hold[0];
	}
	
	return AdjMatr;
}