#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Global.h"
#include "ship.h"

using namespace sf;

class Fuel
{
protected:
	float fuelAmount = 5000.f;
	CircleShape shape;
	float radius = 5.f;
	bool took=false;
	Texture* fuelTexture;
public:
	Fuel(Vector2f pos);
	void draw(RenderWindow &finestra);
	void update(ship &ship);
	Vector2f getPosition();
	float getVal();
	bool isTook();
};

