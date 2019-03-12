#pragma once
#include "ship.h"

class Planet
{
protected:
	int circumnference;
	int nbunker;
	RectangleShape rett;
public:
	Planet();
	void update(float dt,ship &ship);
	void draw(RenderWindow &window);
	void collisions(ship &ship);
	void destroyed();
	void created();
};

