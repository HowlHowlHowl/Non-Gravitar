#include "bullet.h"
#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "utils.h"

using namespace sf;

Bullet::Bullet()
{
}

Bullet::Bullet(Vector2f pos, Vector2f dir_I, float radius, bool isEvil)
{
	
 	shape.setRotation(radToDeg(std::atan2(dir_I.y, dir_I.x))-90);
	shape.setPosition(pos);
	dir = dir_I;
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	if (isEvil) {
		shape.setFillColor(Color::White);
	} else {
		shape.setFillColor(Color::Cyan);
	}
	shape.setTexture(resourceManager.getBulletTexture());
	
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