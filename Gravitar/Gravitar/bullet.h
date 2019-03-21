#pragma once
#include <SFML\Graphics.hpp>
#include "Global.h"
using namespace sf;

class Bullet
{
protected:
	float xpos;
	float ypos;
	float speed = 180.f;
	CircleShape shape;
	bool isEnemy;
	direction dir;
public:
	Bullet(float spawn_xpos, float spawn_ypos, direction dir_I,bool isEnemy_I);
	void update(float dt);
	void draw(RenderWindow &finestra);
	void spawn();
	CircleShape getShape();

};

