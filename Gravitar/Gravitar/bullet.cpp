#include "bullet.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Bullet::Bullet(Vector2f pos, Vector2f dir_I, float radius)
{
	shape.setPosition(pos);
	dir = dir_I;
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setFillColor(Color::Yellow);
	//bulletTexture.loadFromFile("bullet.png");    shape.setTexture(&bulletTexture);
}

void Bullet::update(float dt){
	shape.setPosition(shape.getPosition() + dir * speed * dt);
}

void Bullet::draw(RenderWindow &finestra) {
	finestra.draw(shape);
}

void Bullet::spawn() {

}

CircleShape Bullet::getShape() { 
	return shape; 
};