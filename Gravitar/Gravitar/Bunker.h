#pragma once

#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <vector>
#include "Global.h"

using namespace sf;

class Bunker
{
protected:
	RectangleShape shape;
	int life = 3;
	float bunkerHeight = 15.f;
	float bunkerWidth = 30.f;
	float shootTime = 0.f;
	const float shootCooldown = 2.0f;

public:
	Bunker(Vector2f pos, float rotation);
	void draw(RenderWindow &finestra);
	RectangleShape getShape();
	bool isAlive();
	void takeDamage();
	virtual void shoot(std::vector<Bullet>& bullets);
	void update(float dt, std::vector<Bullet> &bullets);
};

