#include "Bunker2.h"
#include "ResourceManager.h"

Bunker2::Bunker2(Vector2f pos, float rotation) : Bunker(pos, rotation)
{
	shape.setTexture(resourceManager.getBunker2Texture());
}


void Bunker2::shoot(std::vector<Bullet> &bullets)
{
	Vector2f pos = shape.getPosition();
	Vector2f dir(0.0f, -1.0f);
	bullets.emplace_back(pos + Vector2f(20, 0), dir, BUNKER_BULLET_RADIUS, true);
	bullets.emplace_back(pos + Vector2f(-20, 0), dir, BUNKER_BULLET_RADIUS, true);
	bullets.emplace_back(pos, dir, BUNKER_BULLET_RADIUS, true);
}

int Bunker2::getScore()
{
	return 100;
}
