#pragma once

#include <SFML/Graphics.hpp>
#include "bullet.h"

using namespace sf;

class Bunker
{
protected:
	RectangleShape shape;
	int life = 3;
	float bunkerHeight = 10.f;
	float bunkerWidth = 20.f;
	float shootTime = 0.f;
	const float shootCooldown = 3.0f;
public:
	Bunker(Vector2f pos, float rotation);
	void draw(RenderWindow &finestra);
	RectangleShape getShape();
	bool isAlive();
	void takeDamage();
	virtual void shoot(std::vector<Bullet>& bullets);
	void update(float dt, std::vector<Bullet> &bullets);


};

