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
		sf::Event event;
		while (finestra.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				finestra.close();
		}

		//restart del clock
		dt = clock.restart().asSeconds();
		//Update della scena
		update(dt);
		//Disegno della scena
		draw();

		/* DEBUG */
		//cout<<"Frame: "<< dt << "\n";
	}
}
void Engine::update(float dt) {	

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		finestra.close();
	}

	//Update del pianeta in cui ci si trova
	ship.update(dt,shipBullets);
	planet.update(dt,ship);

	for (int i = 0; i < shipBullets.size(); i++)
	{
		shipBullets[i].update(dt);
	}

	
}
void Engine::draw() {

	finestra.clear(Color::Black);
	ship.draw(finestra);
	planet.draw(finestra);
	
	//Disegno proiettili
	for (int i = 0; i < shipBullets.size(); i++)
	{
		shipBullets[i].draw(finestra);
	}

	//Disegno della scena
	finestra.display();
}




