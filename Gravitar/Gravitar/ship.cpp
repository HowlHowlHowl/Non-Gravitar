#include "ship.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "bullet.h"
#include "Global.h"
#include "utils.h"

using namespace sf;

//Costruttore e inizializzazione
ship::ship()
{
	shape.setSize(sf::Vector2f(30, 40));
	shape.setOrigin(shape.getSize() / 2.0f);		
	shape.setFillColor(Color::White);
	life = 3;
	ray.setTexture(resourceManager.getRayTexture());
	init();
	
}
void ship::init(){
	//Respawn
	std::cout << "SPAWN" << std::endl;
	carburante = max_carburante;
	this->xpos = 50.f;
	this->ypos = 50.f;
	shape.setPosition(xpos, ypos);

	speed = 0.0f;
}

//Sparo e raccolta
void ship::shoot(std::vector<Bullet> &bullets) {

	float angle = degToRad(shape.getRotation() - 90);
	Vector2f direction(cos(angle), sin(angle));
  	bullets.emplace_back(shape.getPosition(), direction, 5.f, false);
}
//Funzioni utili
void ship::update(float dt,std::vector<Bullet> &bullets,bool isInSystem) {


	//Carico Texture Ship
	shape.setTexture(resourceManager.getShipTexture());
	
	//Movimento ship
	if (carburante > 0) {
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			shape.setRotation(shape.getRotation() - 200 * dt);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			shape.setRotation(shape.getRotation() + 200 * dt);		
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			speed += dt * acceleration;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			speed -= dt * acceleration;
		}
		if (!(Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down))) {
			speed *= 0.95f;
		}


		speed = clamp(speed, -max_speed, max_speed);

		float angle = degToRad(shape.getRotation() - 90);
		Vector2f direction(cos(angle), sin(angle));

		xpos += direction.x * dt * speed;
		ypos += direction.y * dt * speed;
		carburante -= dt * speed;
		
		float halfShipSize = shape.getSize().x / 2.f;
		//Trattiene la ship nei margini if isInSystem
		if (isInSystem) {
			xpos = clamp(xpos, halfShipSize, VIEWPORT_WIDTH - halfShipSize);
			ypos = clamp(ypos, halfShipSize, VIEWPORT_HEIGHT - halfShipSize);
		}
		
		//Aggiornamento posizione
		shape.setPosition(xpos, ypos);


		ray.setPointCount(3);
		Vector2f pos1(shape.getPosition().x - 25, getPosition().y + 80);
		Vector2f pos2(shape.getPosition());
		Vector2f pos3(shape.getPosition().x + 25, getPosition().y + 80);
		ray.setPoint(0, pos1);
		ray.setPoint(1, pos2);
		ray.setPoint(2, pos3);
		ray.setFillColor(Color::White);
	
	}
	
	//Spara se non e' nel sistema
	if (!isInSystem) {
		shootTimer += dt;
		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer > shootCooldown) {
			shootTimer = 0;
 			shoot(bullets);
		}
	}
	
}

void ship::drawHUD(RenderWindow& finestra) {
	float temp_x = 10.f;

	for (int i = 0; i < life; i++) {
		Sprite temp_sprite;
		temp_sprite.setTexture(*resourceManager.getHealthTexture());

		//Posizione temporanea dei cuori
		temp_sprite.setPosition(temp_x, VIEWPORT_HEIGHT - 50);


		//Distanza temporanea tra un cuore e l'altro
		temp_x += 52;

		//Disegno del singolo cuore
		finestra.draw(temp_sprite);
	}

	RectangleShape fuelRect;

	if (carburante < 2500.f)
		fuelRect.setFillColor(Color::Red);
	else
		fuelRect.setFillColor(Color::Green);

	fuelRect.setSize(Vector2f(100 * carburante / max_carburante, 20));
	fuelRect.setPosition(VIEWPORT_WIDTH - fuelRect.getSize().x - 5, 5);
	finestra.draw(fuelRect);
}

void ship::draw(RenderWindow &finestra) {

	if (Keyboard::isKeyPressed(Keyboard::F)) {
		ray.setTexture(resourceManager.getRayTexture());
		finestra.draw(ray);
	}

	finestra.draw(shape);

}
void ship::Destroy() {

	//Astronave distrutta, respawn e vita in meno
	life--;
	std::cout << "Vite rimaste: "<<life<< std::endl;
	init();
	//Rimedia (0,0) di init();
	setPosition(PLANET_WIDTH / 2, 100);
}
Vector2f ship::getPosition() {
	return Vector2f(xpos,ypos);
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
Vector2f ship::getPointRay(int x) {
	return ray.getPoint(x);
}
void ship::setPosition(float x, float y) {
	xpos = x;
	ypos = y;
}
float ship::getFuel() {
	return carburante;
}