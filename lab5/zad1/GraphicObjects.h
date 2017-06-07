#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Point.h"

class GraphicObjects
{
public:
	static void createPoints(std::vector<int> layers,int numberofNodes,int nodesperLattice, float latticesProportion,std::vector<Point> &points);
	static void createNames(bool numerateEdges,std::vector<std::vector<int>> &connectionArray,int numberofNodes,int nodesperLattice, float latticesProportion,std::vector<Point> &points,std::vector<sf::Text> &names,sf::Font &font);
	static void createLines(int numberofNodes,std::vector<Point> &points,std::vector<std::vector<int>> &connectionArray,std::vector<sf::VertexArray> &lines,std::vector<sf::CircleShape> &arrows,int choice);

};