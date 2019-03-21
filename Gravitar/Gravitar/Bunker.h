#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Bunker
{
	RectangleShape shape;
	int life = 3;
	float bunkerHeight = 10.f;
	float bunkerWidth = 20.f;
public:
	Bunker(Vector2f pos, float rotation);
	void draw(RenderWindow &finestra);
	RectangleShape getShape();
	bool isAlive();
	void takeDamage();

};

