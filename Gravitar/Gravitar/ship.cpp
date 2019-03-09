#include "ship.h"
#include <SFML\Graphics.hpp>
using namespace sf;

//Costruttore
ship::ship()
{
	xpos = 0;
	ypos = 0;
	shape.setSize(sf::Vector2f(30, 30));
	shape.setFillColor(Color::Red);
	shape.setPosition(xpos, ypos);
}

//Movimento
void ship::Left() {
	xpos -= speed;
}
void ship::Right()
{
	xpos += speed;
}
void ship::Down(){
	ypos += speed;
}
void ship::Up(){
	ypos -= speed; 
}

//Funzioni utili
void ship::update(){
	shape.setPosition(xpos, ypos);
}
RectangleShape ship::getShape() {
	return shape;
}
