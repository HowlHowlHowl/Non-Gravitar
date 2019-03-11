#pragma once
#include "ship.h";
class Planet
{
protected:
	int circumnference;
	ship ship;
	int nbunker;
public:
	Planet();
	void update(float dt);
	void draw(RenderWindow &window);
	void destroyed();
	void created();
};

