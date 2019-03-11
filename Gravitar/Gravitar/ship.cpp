#include "ship.h"
#include <SFML\Graphics.hpp>
#include "bullet.h"
#include <iostream>

using namespace sf;
int const ALT = 600;
int const LAR = 800;

//Costruttore
ship::ship()
{
	
	shape.setSize(sf::Vector2f(30, 30));
	shape.setFillColor(Color::Red);
	life = 3;
	init();
}
void ship::init(){

	//Respawn
	std::cout << "SPAWN";
	isShooting = false;
	this->xpos = 100.f;
	this->ypos = 100.f;
	this->update();
	life--;
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
		xpos = LAR;
	else if (xpos < 0)
		xpos = 0;
	else if (ypos > ALT)
		ypos = ALT;
	else if (ypos < 0)
		ypos = 0;
	
	shape.setPosition(xpos, ypos);

}
void ship::Destroy() {

	//Astronave distrutta, ripristino le impotazioni e aggiorno la vita
	init();
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