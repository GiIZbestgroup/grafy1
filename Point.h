#pragma once

#include <SFML/Graphics.hpp>

class Point
{
    public:
    const float x_cord;
    const float y_cord;
    sf::CircleShape point_graphic;

    Point(float x,float y):
    x_cord(x+WINDOWSIZE_X/2.0),
    y_cord(y+WINDOWSIZE_Y/2.0)
    {
    point_graphic = sf::CircleShape(4);
    point_graphic.setFillColor(sf::Color(200,100,0));
    point_graphic.setOutlineThickness(0);
    point_graphic.sf::Transformable::setOrigin(point_graphic.getRadius(),point_graphic.getRadius());
    point_graphic.sf::Transformable::setPosition(x_cord,y_cord);
    };

    ~Point()
    {

    };

};