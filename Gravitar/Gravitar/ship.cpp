#include "ship.h"
#include <SFML\Graphics.hpp>
#include "bullet.h"
#include <iostream>

using namespace sf;
int const ALT = 600;
int const LAR = 800;

//Costruttore e inizializzazione
ship::ship()
{
	
	shape.setSize(sf::Vector2f(30, 30));
	shape.setFillColor(Color::Red);
	life = 4;
	init();
}
void ship::init(){

	//Respawn
	std::cout << "SPAWN" << std::endl;
	this->xpos = 0.f;
	this->ypos = 0.f;
	life--;
}
//Funzioni di Movimento
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
//Sparo e raccolta
void ship::shoot(std::vector<Bullet> &bullets) {
	std::cout << "BIm"<< std::endl;
	Bullet *b = new Bullet(xpos, ypos, DOWN,false);
	bullets.push_back(*b);
}
//Funzioni utili
void ship::update(float dt,std::vector<Bullet> &bullets){
	shootTimer += dt;
	//Movimento ship
	if (canMoving()) {
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			left_m(dt);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			right_m(dt);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			up_m(dt);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			down_m(dt);
		}
	}

	//Sparo
	if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer > shootCooldown) {
		shootTimer = 0;
		shoot(bullets);
	}
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
void ship::draw(RenderWindow &finestra) {
	finestra.draw(shape);
}
void ship::Destroy() {

	//Astronave distrutta, ripristino le impotazioni e aggiorno la vita
	init();
}
Vector2f ship::getPosition() {
	return Vector2f(xpos,ypos);
}
bool ship::canMoving() {
	if (carburante > 0)
		return true;
	return false;
}
RectangleShape ship::getShape() { return shape; }