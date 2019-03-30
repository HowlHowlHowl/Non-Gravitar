#pragma	once
#include "Fuel.h"
#include "ship.h"
#include "utils.h"
#include "Planet.h"
#include <iostream>


Fuel::Fuel(Vector2f pos)
{
	shape.setPosition(pos.x, (pos.y - rand() % 200));
	shape.setRadius(5.f);
	shape.setFillColor(Color::White);
}
void Fuel::draw(RenderWindow&finestra)
{
	finestra.draw(shape);
}
float Fuel::getVal() {
	return fuelAmount;
}
void Fuel::update(float dt, ship &ship) {

	if ((distance(getPosition(), ship.getPosition()) < ship.getShape().getSize().x / 2.f + shape.getRadius())) {
		std::cout << "FUELLLLLLLLL!";
		this->took = true;
		ship.getBonus(getVal());
	}
}
bool Fuel::isTook() {
	return took;
}
Vector2f Fuel::getPosition() {
	return shape.getPosition();
}