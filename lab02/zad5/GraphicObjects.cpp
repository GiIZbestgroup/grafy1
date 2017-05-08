#define WINDOWSIZE_X 720
#define WINDOWSIZE_Y 480

#include "GraphicObjects.h"

#include <cmath>
#include <iostream>
#include <sstream>

void GraphicObjects::createPoints(int numberofNodes, int nodesperLattice, float latticesProportion, std::vector<Point> &points)
{

	int nodesinthisLattice;

	std::cout << "NODES:" << std::endl;

	for (int i = 0; i<numberofNodes; i++)
	{
		if (numberofNodes - (i / nodesperLattice)*nodesperLattice >= nodesperLattice)
		{
			nodesinthisLattice = nodesperLattice;
		}
		else
		{
			nodesinthisLattice = numberofNodes - (i / (nodesperLattice - 1))*nodesperLattice;
		}

		//IMPORTANT UNMAINTAINABLE CODE
		points.push_back(Point(pow(latticesProportion, i / nodesperLattice)*200.0 / 720.0*WINDOWSIZE_X*cos(static_cast<float>(i%nodesinthisLattice) * 2 * M_PI / static_cast<float>(nodesinthisLattice) + i / nodesinthisLattice*360.0 / static_cast<float>(nodesperLattice)), pow(latticesProportion, i / nodesperLattice)*200.0 / 480.0*WINDOWSIZE_Y*sin(static_cast<float>(i%nodesinthisLattice) * 2 * M_PI / static_cast<float>(nodesinthisLattice) + i / nodesinthisLattice*360.0 / static_cast<float>(nodesperLattice))));

		std::cout << points[i].x_cord << "," << points[i].y_cord << std::endl;
	}

}

void GraphicObjects::createNames(int numberofNodes, int nodesperLattice, float latticesProportion, std::vector<Point> &points, std::vector<sf::Text> &names, sf::Font &font)
{

	for (int i = 0; i<numberofNodes; i++)
	{
		names.push_back(sf::Text());
		std::ostringstream ss;
		ss << (i + 1);
		names[i].setString(ss.str());
		names[i].setFont(font);
		names[i].setCharacterSize(14);
		names[i].setOrigin(6, 6);
		names[i].setPosition(points[i].x_cord + 13 * cos(static_cast<float>(i) * 2 * M_PI / static_cast<float>(numberofNodes)), points[i].y_cord + 13 * sin(static_cast<float>(i) * 2 * M_PI / static_cast<float>(numberofNodes)));
		names[i].setColor(sf::Color::Black);
	}
}

void GraphicObjects::createLines(int numberofNodes, std::vector<Point> &points, std::vector<std::vector<int>> &connectionArray, std::vector<sf::VertexArray> &lines)
{

	int counter = 0;

	for (int i = 0; i<numberofNodes; i++)
	{
		for (int j = 0; j<i; j++)
		{
			if (connectionArray[i][j])
			{
				lines.push_back(sf::VertexArray(sf::LineStrip, 2));
				lines[counter][0].position = sf::Vector2f(points[i].x_cord, points[i].y_cord);
				lines[counter][1].position = sf::Vector2f(points[j].x_cord, points[j].y_cord);
				lines[counter][0].color = sf::Color(100, 100, 200);
				lines[counter][1].color = sf::Color(100, 100, 200);
				counter++;
			}
		}
	}
}