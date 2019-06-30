#pragma	once
#include "Fuel.h"
#include "ship.h"
#include "utils.h"
#include "Planet.h"
#include <iostream>


Fuel::Fuel(Vector2f pos)
{
	if ((rand() % 4) != 0) {
		isBig = false;
	}
	else {
		isBig = true;
	}
	if (isBig) {
		shape.setRadius(12.f);
		shape.setFillColor(Color::White);
		shape.setOrigin(shape.getRadius(), shape.getRadius() * 2);
		shape.setPosition(pos.x, pos.y);
		fuelAmount = 7500.f;
	} else {
		shape.setRadius(9.f);
		shape.setFillColor(Color::White);
		shape.setOrigin(shape.getRadius(), shape.getRadius() * 2);
		shape.setPosition(pos.x, pos.y);
		fuelAmount = 5000.f;
	}
	fuelTexture = resourceManager.getFuelTexture(isBig);
	std::cout << "spawnBonus "<<fuelAmount<<std::endl;
	shape.setTexture(fuelTexture);
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