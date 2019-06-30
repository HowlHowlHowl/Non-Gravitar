#include "Bunker.h"
#include "bullet.h"
#include "utils.h"
#include "ResourceManager.h"

Bunker::Bunker(Vector2f pos, float rotation)
{
	life = BUNK_LIFE;
	shape.setPosition(pos);
	shape.setRotation(rotation);
	shape.setSize(Vector2f(bunkerWidth, bunkerHeight));
	shape.setOrigin(bunkerWidth / 2.0f, bunkerHeight);
	shootTime = randf01() * shootCooldown;
	shape.setTexture(resourceManager.getBunkerTexture());
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

int Bunker::getScore()
{
	return 50;
}

void Bunker::update(float dt, Array<Bullet> &bullets) {
	shootTime += dt;
	if (shootTime > shootCooldown) {
		shoot(bullets);
		shootTime = 0;
	}

}
void Bunker::shoot(Array<Bullet> &bullets)
{
	Vector2f pos = shape.getPosition();
	float angle1 = degToRad(randrange(60.0f, 90.0f));
	float angle2 = degToRad(randrange(90.0f, 120.0f));
	Vector2f dir1(cos(angle1), -sin(angle1));
	Vector2f dir2(cos(angle2), -sin(angle2));
	bullets.add(Bullet(pos + Vector2f(20, 0), dir1, BUNKER_BULLET_RADIUS, true));
	bullets.add(Bullet(pos + Vector2f(-20, 0), dir2, BUNKER_BULLET_RADIUS, true));
}

