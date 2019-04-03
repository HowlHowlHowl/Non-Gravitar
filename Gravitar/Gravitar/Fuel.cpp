#pragma	once
#include "Fuel.h"
#include "ship.h"
#include "utils.h"
#include "Planet.h"
#include <iostream>


Fuel::Fuel(Vector2f pos)
{
	shape.setFillColor(Color::White);
	shape.setPosition(pos.x, (pos.y - rand() % 200 - 20));
	shape.setRadius(10.f);

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