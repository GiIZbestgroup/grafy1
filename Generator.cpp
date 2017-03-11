#include "Generator.h"

#include <cstdlib>
#include <iostream>


std::vector<std::vector<int>> Generator::random(float probability_of_connection,int numberofNodes,int& numberofEdges)
{
	srand(time(0));
	std::vector<std::vector<int>> connectionArray(numberofNodes,std::vector<int> (numberofNodes));

	for(int i=0;i<numberofNodes;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if((rand()%100<probability_of_connection)&&i!=j)
            connectionArray[i][j]=1;
            else
            connectionArray[i][j]=0;
            if(connectionArray[i][j])
            {
                numberofEdges++;
            }
            std::cout<<connectionArray[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return connectionArray;
}

std::vector<std::vector<int>> Generator::fullyRandom(float probability_of_connection,int& numberofNodes,int& numberofEdges,int &nodesperLattice)
{
	srand(time(0));
	numberofNodes=rand()%100;
	nodesperLattice=rand()%numberofNodes;
	probability_of_connection=rand()%30;

	std::vector<std::vector<int>> connectionArray(numberofNodes,std::vector<int> (numberofNodes));

	for(int i=0;i<numberofNodes;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if((rand()%100<probability_of_connection)&&i!=j)
            connectionArray[i][j]=1;
            else
            connectionArray[i][j]=0;
            if(connectionArray[i][j])
            {
                numberofEdges++;
            }
            std::cout<<connectionArray[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return connectionArray;
}

std::vector<std::vector<int>> Generator::fullGraph(int numberofNodes,int& numberofEdges)
{
	srand(time(0));
	std::vector<std::vector<int>> connectionArray(numberofNodes,std::vector<int> (numberofNodes));

	for(int i=0;i<numberofNodes;i++)
    {
        for(int j=0;j<=i;j++)
        {
        	if(i!=j)
            	connectionArray[i][j]=1;
        	else
        		connectionArray[i][j]=0;
            if(connectionArray[i][j])
            {
                numberofEdges++;
            }
            std::cout<<connectionArray[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return connectionArray;
}


std::vector<std::vector<int>> Generator::randomSpecifiedEdges(float probability_of_connection,int numberofNodes,int& numberofEdges,int desiredNumberofEdges)
{
    srand(time(0));
    bool indicator = true;
    std::vector<std::vector<int>> connectionArray(numberofNodes,std::vector<int> (numberofNodes));
    while(indicator)
    {
        
        for(int i=0;i<numberofNodes;i++)
        {
            for(int j=0;j<=i;j++)
            {
               if((rand()%100<probability_of_connection)&&i!=j)
                connectionArray[i][j]=1;
                else
                connectionArray[i][j]=0;
                if(connectionArray[i][j])
                {
                    numberofEdges++;
                }
                std::cout<<connectionArray[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        if(numberofEdges==desiredNumberofEdges)
        {
            indicator=false;
        }
        else
        {
            for(int i=0;i<numberofNodes;i++)
            {
                for(int j=0;j<=i;j++)
                {
                    connectionArray[i][j]=0;
                }
            }
            numberofEdges=0;
        }

    }
    return connectionArray;
}
