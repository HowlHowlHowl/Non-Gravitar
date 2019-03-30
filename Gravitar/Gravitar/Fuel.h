#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.h"
#include "ship.h"

using namespace sf;

class Fuel
{
protected:
	float fuelAmount = 2500.f;
	CircleShape shape;
	float radius = 150.f;
	bool took=false;
public:
	Fuel(Vector2f pos);
	void draw(RenderWindow &finestra);
	void update(float dt, ship &ship);
	Vector2f getPosition();
	float getVal();
	bool isTook();
};

