#include "Bunker2.h"
#include "ResourceManager.h"
#include "utils.h"

Bunker2::Bunker2(Vector2f pos, float rotation) : Bunker(pos, rotation)
{
	life = BUNK2_LIFE;
	shape.setTexture(resourceManager.getBunker2Texture());
}


void Bunker2::shoot(Array<Bullet> &bullets)
{
	Vector2f pos = shape.getPosition();
	float angle1 = degToRad(randrange(60.0, 80.0));
	float angle2 = degToRad(randrange(80.0, 100.0));
	float angle3 = degToRad(randrange(100.0, 120.0));
	Vector2f dir1 = Vector2f(cos(angle1), -sin(angle1));
	Vector2f dir2 = Vector2f(cos(angle2), -sin(angle2));
	Vector2f dir3 = Vector2f(cos(angle3), -sin(angle3));
	bullets.add(Bullet(pos + Vector2f(20, 0), dir1, BUNKER_BULLET_RADIUS, true));
	bullets.add(Bullet(pos, dir2, BUNKER_BULLET_RADIUS, true));
	bullets.add(Bullet(pos + Vector2f(-20, 0), dir3, BUNKER_BULLET_RADIUS, true));
}

int Bunker2::getScore()
{
	return 100;
}
