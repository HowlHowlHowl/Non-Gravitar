#include "Planet.h"
#include <iostream>

Planet::Planet()
{
	nbunker = 0;
	circumnference = 0;
}
void Planet::update(float dt,ship &ship){
	//Aggiornamento gameobject
	
	//Check delle collisioni
	collisions(ship);
}
void Planet::collisions(ship &ship) {
	//astronvave collision
	if (rett.getGlobalBounds().intersects(ship.getShape().getGlobalBounds())) {
		std::cout << "COllision!" << std::endl;
		ship.Destroy();
	}
}
void Planet::draw(RenderWindow &window){


	//Disegno dei gameobject
	rett.setSize(sf::Vector2f(30, 30));
	rett.setFillColor(Color::Red);
	rett.setPosition(100, 400);
	window.draw(rett);

}
void Planet::destroyed(){}
void Planet::created(){
}