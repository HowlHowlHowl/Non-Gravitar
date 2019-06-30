#pragma once
#include <SFML\Graphics.hpp>
#include "Global.h"


using namespace sf;

class Bullet
{
protected:
	float speed = 220.f;
	CircleShape shape;
	Vector2f dir;
public:
	Bullet();
	Bullet(Vector2f pos, Vector2f dir_I, float radius, bool isEvil);
	void update(float dt);
	void draw(RenderWindow &finestra);
	CircleShape getShape();

};

