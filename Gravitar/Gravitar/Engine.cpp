#include "Engine.h"
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

Engine::Engine()
{
	//Gioco a tutta finestra
	//Vector2f resolution;
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	//Gioco in finestra
	finestra.create(VideoMode(800, 600),"Gravitar Game Engine");
	finestra.setFramerateLimit(60);
}
void Engine::start(){

	//Loop in game
	Clock clock;
	float dt;	
	while (finestra.isOpen())
	{
		//restart del clock
		dt = clock.restart().asSeconds();
		
		input(dt);
		//Update della scena
		update(dt);
		//Disegno della scena
		draw();

		/* DEBUG */
		cout<<"Frame: "<< dt << "\n";
	}
}
void Engine::input(float dt) {
	if (ship.canMoving()) {
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
	}
}
void Engine::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		finestra.close();
	}

	//Update del pianeta in cui ci si trova
	ship.update();
	planet.update(dt,ship);
	
}
void Engine::draw() {

	finestra.clear(Color::Black);
	finestra.draw(ship.getShape());
	planet.draw(finestra);
	
	//Disegno della scena
	finestra.display();
}




