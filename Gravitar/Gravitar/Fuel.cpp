#pragma	once
#include "Fuel.h"
#include "ship.h"
#include "utils.h"
#include "Planet.h"
#include <iostream>


Fuel::Fuel(Vector2f pos)
{
	shape.setRadius(10.f);
	shape.setFillColor(Color::White);
	shape.setOrigin(shape.getRadius(), shape.getRadius()*2);
	shape.setPosition(pos.x, pos.y);
	

	if (!fuelTexture.loadFromFile("fuel.png"))
		std::cout << "Error: cannot load fuel.png" << std::endl;

	fuelTexture.setSmooth(true);
	std::cout << "spawnBonus"<<std::endl;
	shape.setTexture(&fuelTexture);
}
void Fuel::draw(RenderWindow&finestra)
{
	finestra.draw(shape);
}
float Fuel::getVal() {
	return fuelAmount;
}
void Fuel::update(ship &ship) {

		std::cout << "FUELLLLLLLLL!"<<std::endl;
		this->took = true;
		ship.getBonus(getVal());
}
bool Fuel::isTook() {
	return took;
}
Vector2f Fuel::getPosition() {
	return shape.getPosition();
}