#include "ship.h"
#include <SFML\Graphics.hpp>
#include "bullet.h"
#include <iostream>
#include <sstream>
#include "Global.h"

using namespace sf;
int const ALT = 600;
int const LAR = 800;

//Costruttore e inizializzazione
ship::ship()
{
	shape.setSize(sf::Vector2f(50, 50));
	shape.setOrigin(shape.getSize() / 2.0f);		
	shape.setFillColor(Color::White);
	life = 3;
	

	if (!lifeTexture.loadFromFile("vita.png"))
		std::cout << "Error: cannot load vita.png" << std::endl;

	if (!shipTexture.loadFromFile("ship.png"))
		std::cout << "Error: cannot load ship.png" << std::endl;

	lifeTexture.setSmooth(true);
	shipTexture.setSmooth(true);

	shape.setTexture(&shipTexture);

	init();
	
}
void ship::init(){
	//Respawn
	std::cout << "SPAWN" << std::endl;
	carburante = max_carburante;

	/*
	this->xpos = VIEWPORT_WIDTH / 2.0f;
	this->ypos = VIEWPORT_HEIGHT / 10.0f;
	*/
	this->xpos = 50.f;
	this->ypos = 50.f;
	shape.setPosition(xpos, ypos);
}
//Funzioni di Movimento
void ship::up_m(float dt) {
	xpos += 0.f;
	ypos -= dt*speed;
	
	carburante -= dt * speed;

	shape.setRotation(0.0f);
}
void ship::down_m(float dt) {
	xpos += 0.f;
	ypos += dt*speed;
	carburante -= dt * speed;
	shape.setRotation(180.0f);
}
void ship::right_m(float dt) {
	xpos += dt*speed;
	ypos += 0.f;
	carburante -= dt * speed;


	shape.setRotation(90.0f);
}
void ship::left_m(float dt) {
	xpos -= dt*speed;
	ypos += 0.f;
	carburante -= dt * speed;


	shape.setRotation(270.0f);
}
//Sparo e raccolta
void ship::shoot(std::vector<Bullet> &bullets) {
	std::cout << "BIm"<< std::endl;
	bullets.emplace_back(xpos, ypos, dir, 10.f);
}
//Funzioni utili
void ship::update(float dt,std::vector<Bullet> &bullets,bool isInSystem){

	//Movimento ship
	if (canMoving()) {
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			left_m(dt);
			dir = LEFT;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			right_m(dt);
			dir = RIGHT;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			up_m(dt);
			dir = UP;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			down_m(dt);
			dir = DOWN;
		}
	}
	
	//Spara se non e' nel sistema
	if (!isInSystem) {
		shootTimer += dt;
		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer > shootCooldown) {
			shootTimer = 0;
			shoot(bullets);
		}
	}

	//Aggiornamento posizione
	shape.setPosition(xpos, ypos);

}
void ship::draw(RenderWindow &finestra) {
	finestra.draw(shape);
	float temp_x = 10.f;
	for (int i = 0; i < life; i++) {
		Sprite temp_sprite;
		temp_sprite.setTexture(lifeTexture);

		//Posizione temporanea dei cuori
		temp_sprite.setPosition(temp_x,550);
	

		//Distanza temporanea tra un cuore e l'altro
		temp_x += 52;

		//Disegno del singolo cuore
		finestra.draw(temp_sprite);
	}
	
	RectangleShape fuelRect;

	if(carburante < 1000.f)
		fuelRect.setFillColor(Color::Red);
	else
		fuelRect.setFillColor(Color::Green);

	fuelRect.setSize(Vector2f(100 * carburante / max_carburante, 20));
	fuelRect.setPosition(VIEWPORT_WIDTH - fuelRect.getSize().x - 5, 5);
	finestra.draw(fuelRect);

}
void ship::Destroy() {

	//Astronave distrutta, respawn e vita in meno
	life--;
	std::cout << "Vite rimaste: "<<life<< std::endl;
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
bool ship::isAlive() {
	if (life <= 0)
		return false;
	return true;
}
void ship::getBonus(float fuelAmount) {
	carburante += fuelAmount;
}