#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class bullet
{
protected:
	float xpos;
	float ypos;
	float speed = 120.f;
	CircleShape shape;
public:
	bullet(float spawn_xpos, float spawn_ypos);
	void update();
	void shoot();
	CircleShape getShape();
};

