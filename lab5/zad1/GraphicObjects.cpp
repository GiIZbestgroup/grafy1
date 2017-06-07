#define WINDOWSIZE_X 720
#define WINDOWSIZE_Y 480

#include "GraphicObjects.h"

#include <cmath>
#include <iostream>
#include <sstream>

void GraphicObjects::createPoints(std::vector<int> layers,int numberofNodes,int nodesperLattice, float latticesProportion,std::vector<Point> &points)
{

	int nodesinthisLattice;

    std::cout<<"NODES:"<<std::endl;

    int stepx = static_cast<int>(WINDOWSIZE_X/(layers.size()+3));
    int stepy = 0;
    int counter,sum;

    points.push_back(Point(-WINDOWSIZE_X/2.0+stepx,0));
    std::cout<<points[0].x_cord<<","<<points[0].y_cord<<std::endl;

	for(int i=0;i<layers.size();i++)
    {

        std::cout<<layers[i]<<std::endl;
        stepy = static_cast<int>(WINDOWSIZE_Y/(layers[i]+1.0));

        for(int j=0;j<layers[i];j++)
        {
        points.push_back(Point(-WINDOWSIZE_X/2.0+stepx*(i+2),(j+1)*stepy-WINDOWSIZE_Y/2.0/*WINDOWSIZE_Y/2.0-(j+1)*stepy*/));
        std::cout<<points[i].x_cord<<","<<points[i].y_cord<<std::endl;
        }

        /*
        if(numberofNodes-(i/nodesperLattice)*nodesperLattice>=nodesperLattice)
        {
            nodesinthisLattice = nodesperLattice;
        }
        else
        {
            nodesinthisLattice = numberofNodes-(i/(nodesperLattice-1))*nodesperLattice;
        }
        */
        //IMPORTANT UNMAINTAINABLE CODE
        //points.push_back(Point(pow(latticesProportion,i/nodesperLattice)*200.0/720.0*WINDOWSIZE_X*cos(static_cast<float>(i%nodesinthisLattice)*2*M_PI/static_cast<float>(nodesinthisLattice)+i/nodesinthisLattice*360.0/static_cast<float>(nodesperLattice)),pow(latticesProportion,i/nodesperLattice)*200.0/480.0*WINDOWSIZE_Y*sin(static_cast<float>(i%nodesinthisLattice)*2*M_PI/static_cast<float>(nodesinthisLattice)+i/nodesinthisLattice*360.0/static_cast<float>(nodesperLattice))));
      


        
    }
    
    points.push_back(Point(WINDOWSIZE_X/2.0-stepx,0));

}

void GraphicObjects::createNames(bool numerateEdges,std::vector<std::vector<int>> &connectionArray,int numberofNodes,int nodesperLattice, float latticesProportion,std::vector<Point> &points,std::vector<sf::Text> &names,sf::Font &font)
{

	for(int i=0;i<numberofNodes;i++)
    {
       names.push_back(sf::Text());
       std::ostringstream ss;
       ss<<(i+1);
       names[i].setString(ss.str()); 
       names[i].setFont(font);
       names[i].setCharacterSize(14);
       names[i].setOrigin(6,6);
       names[i].setPosition(points[i].x_cord+13*cos(static_cast<float>(i)*2*M_PI/static_cast<float>(numberofNodes)),points[i].y_cord+13*sin(static_cast<float>(i)*2*M_PI/static_cast<float>(numberofNodes)));
       if(numerateEdges)
       names[i].setColor(sf::Color::Red);
       else
       names[i].setColor(sf::Color::Black);
    }

    int numberofweightsadded = 0;

    if(numerateEdges)
    for(int i=0;i<numberofNodes;i++)
    {
        for(int j=0;j<numberofNodes;j++)
        {
            if(connectionArray[i][j]!=0)
            {
               numberofweightsadded++;
               names.push_back(sf::Text());
               std::ostringstream ss2;
               ss2<<connectionArray[i][j];
               names[numberofNodes+numberofweightsadded-1].setString(ss2.str()); 
               names[numberofNodes+numberofweightsadded-1].setFont(font);
               names[numberofNodes+numberofweightsadded-1].setCharacterSize(14);
               names[numberofNodes+numberofweightsadded-1].setOrigin(6,6);
               names[numberofNodes+numberofweightsadded-1].setPosition((1.0*points[i].x_cord+2.0*points[j].x_cord)/3.0,(1.0*points[i].y_cord+2.0*points[j].y_cord)/3.0);
               names[numberofNodes+numberofweightsadded-1].setColor(sf::Color::Black);
            }
        }
    }
}

void GraphicObjects::createLines(int numberofNodes,std::vector<Point> &points,std::vector<std::vector<int>> &connectionArray,std::vector<sf::VertexArray> &lines,std::vector<sf::CircleShape> &arrows,int choice)
{

int counter=0;

int max=0;

int min=999;

    for(int i=0;i<numberofNodes;i++)
    {
        for(int j=0;j<numberofNodes;j++)
        {
            if(connectionArray[i][j]<min)
                min = connectionArray[i][j];
            if(connectionArray[i][j]>max)
                max = connectionArray[i][j];
        }
    }

    if(choice == 1)
    {
        for(int i=0;i<numberofNodes;i++)
        {
            for(int j=0;j<numberofNodes;j++)
            {
                 if(connectionArray[i][j])
                {
                    sf::CircleShape triangle(6,3);
                    triangle.setScale(0.6f,1.5f);
                    triangle.setFillColor(sf::Color(100,100,200));
                    triangle.setOrigin(6,0);
                    triangle.setPosition(points[j].x_cord,points[j].y_cord);
                    triangle.setRotation(((points[j].x_cord - points[i].x_cord < 0))*180.0+360.0/(2.0*M_PI)*atan((points[j].y_cord - points[i].y_cord)/(points[j].x_cord - points[i].x_cord))+90.0);
                    arrows.push_back(triangle);
                    lines.push_back(sf::VertexArray(sf::LineStrip, 2)); 
                    lines[counter][0].position = sf::Vector2f(points[i].x_cord,points[i].y_cord);
                    lines[counter][1].position = sf::Vector2f(points[j].x_cord,points[j].y_cord);
                    lines[counter][0].color = sf::Color(100,100,200);
                    lines[counter][1].color = sf::Color(100,100,200);
                    counter++;
                }
            }
        }
    }
    
    if(choice == 2)
    {
        for(int i=0;i<numberofNodes;i++)
        {
            for(int j=0;j<numberofNodes;j++)
            {
                 if(connectionArray[i][j])
                {
                    sf::CircleShape triangle(6,3);
                    triangle.setScale(0.6f,1.5f);
                    triangle.setFillColor(sf::Color(255*connectionArray[i][j]/max,0,255-255*connectionArray[i][j]/max));
                    triangle.setOrigin(6,0);
                    triangle.setPosition(points[j].x_cord,points[j].y_cord);
                    triangle.setRotation(((points[j].x_cord - points[i].x_cord < 0))*180.0+360.0/(2.0*M_PI)*atan((points[j].y_cord - points[i].y_cord)/(points[j].x_cord - points[i].x_cord))+90.0);
                    arrows.push_back(triangle);
                    lines.push_back(sf::VertexArray(sf::LineStrip, 2)); 
                    lines[counter][0].position = sf::Vector2f(points[i].x_cord,points[i].y_cord);
                    lines[counter][1].position = sf::Vector2f(points[j].x_cord,points[j].y_cord);
                    lines[counter][0].color = sf::Color(255*connectionArray[i][j]/max,0,255-255*connectionArray[i][j]/max);
                    lines[counter][1].color = sf::Color(255*connectionArray[i][j]/max,0,255-255*connectionArray[i][j]/max);
                    counter++;
                }
            }
        }
    }
}