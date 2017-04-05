#pragma once

#include <vector>


class Generator
{
public:
static std::vector<std::vector<int>> random(double probability_of_connection,int numberofNodes,int& numberofEdges);
static std::vector<std::vector<int>> fullyRandom(double probability_of_connection,int& numberofNodes,int& numberofEdges,int &nodesperLattice);
static std::vector<std::vector<int>> fullGraph(int numberofNodes,int& numberofEdges);
static std::vector<std::vector<int>> randomSpecifiedEdges(double probability_of_connection,int numberofNodes,int& numberofEdges,int desiredNumberofEdges);
};