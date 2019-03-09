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
void ship::up_m(float dt) {
	xpos += 0.f;
	ypos -= 10.f*dt*speed;
	
}
void ship::down_m(float dt) {
	xpos += 0.f;
	ypos += 10.f*dt*speed;

}
void ship::right_m(float dt) {
	xpos += 10.f*dt*speed;
	ypos += 0.f;

}
void ship::left_m(float dt) {
	xpos -= 10.f*dt*speed;
	ypos += 0.f;
	
}

//Funzioni utili
void ship::update(){
	shape.setPosition(xpos, ypos);
}
RectangleShape ship::getShape() {
	return shape;
}
