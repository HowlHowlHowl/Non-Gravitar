#include "bullet.h"
#include <SFML\Graphics.hpp>
using namespace sf;

bullet::bullet(float spawn_xpos, float spawn_ypos)
{
	xpos = spawn_xpos,
	ypos = spawn_ypos;
}
void bullet::update(){
	shape.setPosition(xpos,ypos);
}
void bullet::shoot() {

}
CircleShape bullet::getShape() { return shape; };