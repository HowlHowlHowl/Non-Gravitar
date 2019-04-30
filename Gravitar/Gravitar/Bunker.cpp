#include "Bunker.h"
#include "bullet.h"
#include "utils.h"
#include "ResourceManager.h"

Bunker::Bunker(Vector2f pos, float rotation)
{
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

void Bunker::update(float dt, std::vector<Bullet> &bullets) {
	shootTime += dt;
	if (shootTime > shootCooldown) {
		shoot(bullets);
		shootTime = 0;
	}

}
void Bunker::shoot(std::vector<Bullet> &bullets)
{
	Vector2f pos = shape.getPosition();
	Vector2f dir(0.0f, -1.0f);
	bullets.emplace_back(pos + Vector2f(20, 0), dir, BUNKER_BULLET_RADIUS, true);
	bullets.emplace_back(pos + Vector2f(-20, 0), dir, BUNKER_BULLET_RADIUS, true);
}

