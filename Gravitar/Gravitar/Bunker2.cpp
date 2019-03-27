#include "Bunker2.h"

Bunker2::Bunker2(Vector2f pos, float rotation) : Bunker(pos, rotation)
{
	Bunker::shape.setFillColor(Color::Red);
}


void Bunker2::shoot(std::vector<Bullet> &bullets)
{
	Vector2f pos = shape.getPosition();
	bullets.emplace_back(pos.x + 20, pos.y, UP, BUNKER_BULLET_RADIUS);
	bullets.emplace_back(pos.x - 20, pos.y, UP, BUNKER_BULLET_RADIUS);
	bullets.emplace_back(pos.x, pos.y, UP, BUNKER_BULLET_RADIUS);
}