#pragma once

#include <vector>


class Generator
{
public:
	static std::vector<std::vector<int>> random(double probability_of_connection, int numberofNodes, int& numberofEdges);
	static std::vector<std::vector<int>> fullyRandom(double probability_of_connection, int& numberofNodes, int& numberofEdges, int &nodesperLattice);
	static std::vector<std::vector<int>> fullGraph(int numberofNodes, int& numberofEdges);
	static std::vector<std::vector<int>> randomSpecifiedEdges(double probability_of_connection, int numberofNodes, int& numberofEdges, int desiredNumberofEdges);
	static std::vector<std::vector<int>> randomRegular(int numberofNodes, int& numberofEdges, int degree);
	static std::vector<std::vector<int>> fullyRandomRegular(int maxNodeNumber, int& numberofEdges, int degree);
	static int countOnes(std::vector<int> list);
};