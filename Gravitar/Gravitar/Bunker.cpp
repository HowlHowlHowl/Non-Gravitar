#include "Bunker.h"


Bunker::Bunker(Vector2f pos, float rotation)
{
	shape.setPosition(pos);
	shape.setRotation(rotation);
	shape.setSize(Vector2f(bunkerWidth, bunkerHeight));
	shape.setOrigin(bunkerWidth / 2.0f, bunkerHeight);
	shape.setFillColor(Color::Blue);

}

void Bunker::draw(RenderWindow & finestra)
{
	finestra.draw(shape);
}

RectangleShape Bunker::getShape()
{
	return shape;
}

bool Bunker::isAlive()
{
	return life > 0;
}

void Bunker::takeDamage()
{
	life--;
}


