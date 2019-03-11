#include "Planet.h"

Planet::Planet()
{
	nbunker = 0;
	circumnference = 0;
}
void Planet::update(float dt){
// Lettura input
//dt = tempo totale di ogni frame
//cosi da rendere il gioco indipendente dal frame-rate
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		ship.left_m(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		ship.right_m(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		ship.up_m(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		ship.down_m(dt);
	}

	//Aggiornamento gameobject
	ship.update();
}
void Planet::draw(RenderWindow &window){
	//Disegno dei gameobject
	window.draw(ship.getShape());	
}
void Planet::destroyed(){}
void Planet::created(){
}