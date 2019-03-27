#include "Bunker.h"
#include "bullet.h"
#include "utils.h"


Bunker::Bunker(Vector2f pos, float rotation)
{
	shape.setPosition(pos);
	shape.setRotation(rotation);
	shape.setSize(Vector2f(bunkerWidth, bunkerHeight));
	shape.setOrigin(bunkerWidth / 2.0f, bunkerHeight);
	shootTime = randf01() * shootCooldown;

	bunkerTexture.loadFromFile("bunker.png");
	shape.setTexture(&bunkerTexture);
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
	bullets.emplace_back(pos.x + 20, pos.y, UP, BUNKER_BULLET_RADIUS);
	bullets.emplace_back(pos.x - 20, pos.y, UP, BUNKER_BULLET_RADIUS);
}

