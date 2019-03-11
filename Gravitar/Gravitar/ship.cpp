#include "ship.h"
#include <SFML\Graphics.hpp>
#include "bullet.h";
using namespace sf;
int const ALT = 600;
int const LAR = 800;

//Costruttore
ship::ship()
{
	isShooting = false;
	xpos = 0.f;
	ypos = 0.f;
	shape.setSize(sf::Vector2f(30, 30));
	shape.setFillColor(Color::Red);
	shape.setPosition(xpos, ypos);
}
//Movimento
void ship::up_m(float dt) {
	xpos += 0.f;
	ypos -= 10.f*dt*speed;
	
	carburante -= 10.f*dt * speed;
}
void ship::down_m(float dt) {
	xpos += 0.f;
	ypos += 10.f*dt*speed;
	carburante -= 10.f*dt * speed;
}
void ship::right_m(float dt) {
	xpos += 10.f*dt*speed;
	ypos += 0.f;
	carburante -= 10.f*dt * speed;
}
void ship::left_m(float dt) {
	xpos -= 10.f*dt*speed;
	ypos += 0.f;
	carburante -= 10.f*dt * speed;
}
//Funzioni utili
void ship::update(){

	//EFFETTO PACMAN
	if (xpos > LAR)
		xpos = 0;
	else if (xpos < 0)
		xpos = LAR;
	else if (ypos > ALT)
		ypos = 0;
	else if (ypos < 0)
		ypos = ALT;
	
	shape.setPosition(xpos, ypos);
	if(isShooting)
	bullet bull(xpos, ypos);

}
RectangleShape ship::getShape() {
	return shape;
}
Vector2f ship::getPosition() {
	return Vector2f(xpos,ypos);
}
bool ship::canMoving() {
	if (carburante > 0)
		return true;
	return false;
}