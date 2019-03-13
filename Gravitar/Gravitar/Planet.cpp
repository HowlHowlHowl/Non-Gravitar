#include "Planet.h"
#include <iostream>
#include <vector>

Planet::Planet()
{
	nbunker = 0;
	circumnference = 0;
	rett.setPosition(100, 400);
}
void Planet::update(float dt,ship &ship){
	//Aggiornamento gameobject
	
}
void Planet::collisions(ship &ship, std::vector<Bullet> shipBullets) {
	//astronvave collision
	if (rett.getGlobalBounds().intersects(ship.getShape().getGlobalBounds())) {
		std::cout << "COllision!" << std::endl;
		ship.Destroy();


	}

	//Proiettili collision
	for (int i = 0; i < shipBullets.size(); i++) {
		if (shipBullets[i].getShape().getGlobalBounds().intersects(rett.getGlobalBounds())) {

			//Spawn del rettangolo random
			srand((unsigned)time(0));
			int i = (rand() % 800) + 1;
			int j = (rand() % 600) + 1;
			rett.setPosition(i, j);

		}
	}
}
void Planet::draw(RenderWindow &window){


	//Disegno dei gameobject
	rett.setSize(sf::Vector2f(30, 30));
	rett.setFillColor(Color::Red);
	
	window.draw(rett);

}
void Planet::destroyed(){}
void Planet::created(){
}