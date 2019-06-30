#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.h"
#include "ship.h"

using namespace sf;

class Fuel
{
protected:
	float fuelAmount;
	CircleShape shape;
	bool taken=false;
	Texture* fuelTexture;
	bool isBig;
public:
	Fuel(Vector2f pos);
	void draw(RenderWindow &finestra);
	void update(ship &ship);
	Vector2f getPosition();
	float getVal();
	bool isTaken();
};

