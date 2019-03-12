#include "bullet.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Bullet::Bullet(float spawn_xpos, float spawn_ypos,direction dir_I,bool isEnemy_I)
{
	xpos = spawn_xpos,
	ypos = spawn_ypos;
	dir = dir_I;
	isEnemy = isEnemy_I;
	shape.setRadius(10.f);
	shape.setFillColor(Color::Green);
}
void Bullet::update(float dt){
	if (dir == LEFT)
	{
		xpos -= speed * dt;
	}
	if (dir == RIGHT)
	{
		xpos += speed * dt;
	}
	if (dir == UP)
	{
		ypos -= speed*dt;
	}
	if (dir == DOWN) {
		ypos += speed*dt;
	}

	shape.setPosition(xpos,ypos);
}
void Bullet::draw(RenderWindow &finestra) {
	finestra.draw(shape);
}
void Bullet::spawn() {

}
CircleShape Bullet::getShape() { return shape; };