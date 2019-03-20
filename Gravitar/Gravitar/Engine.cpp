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
	finestra.create(VideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT),"Gravitar Game Engine");
	finestra.setFramerateLimit(60);
	srand(time(0));

	
	//Menu
	MenuCamper = true;
	NPianeta = 0;

	//Generazione mappa dei pianeti
	int i = 0;
	while(i <= 6) {
		Planet *p = new Planet();
		mapPlanets.push_back(*p);
			i++;
	}
}

void Engine::start(){

	//Loop in game
	Clock clock;
	float dt;	
	while (finestra.isOpen())
	{
		//Eventi
		sf::Event event;
		while (finestra.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				finestra.close();

			if (event.key.code == Keyboard::Tab) {
				MenuCamper = true;
			}
			
			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == Keyboard::Return)
				{
					mapPlanets[NPianeta].generateRandomTerrain();
				}
				if (event.key.code == Keyboard::BackSpace)
				{
					mapPlanets[NPianeta].getRandomPointOnTerrain();
				}
				
			}
		}

		//restart del clock
		dt = clock.restart().asSeconds();

		//Update della scena
		update(dt);

		//Disegno della scena
		draw();

	}
}

void Engine::update(float dt) {	

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		finestra.close();
	}

	//Update astronave
	ship.update(dt,shipBullets,MenuCamper);

	//Planets intersect
	if(MenuCamper)
	planetSelection();

	//Update del pianeta in cui ci si trova
	if (!MenuCamper) {

		//Spawn dei proiettili
		for (int i = 0; i < shipBullets.size(); i++)
		{
			shipBullets[i].update(dt);
		}

		//Update pianeta
		mapPlanets[NPianeta].update(dt, ship);

		//Collisioni del pianeta
		mapPlanets[NPianeta].collisions(ship, shipBullets);

		//Check distruzione pianeta
		if (mapPlanets[NPianeta].destroyed()) {
			mapPlanets.erase(mapPlanets.begin() + NPianeta);
			NTotalePianeti--;
			MenuCamper = true;
		}
	}
}

void Engine::draw() {

	finestra.clear(Color::Black);

	//Disegno astronave
	ship.draw(finestra);

	//Disegno mappa pianeti
	if (MenuCamper) {
		int i = 0;
		while (i < NTotalePianeti) {
			mapPlanets[i].drawIcon(finestra);
			i++;
		}
	}

	//Disegno pianeta e dei proiettili
	if (!MenuCamper) {
		mapPlanets[NPianeta].draw(finestra);

		//Disegno proiettili
		for (int i = 0; i < shipBullets.size(); i++)
		{
			shipBullets[i].draw(finestra);
		}

	}
	
	//Disegno della scena
	finestra.display();
}

void Engine::planetSelection(){
	int i = 0; bool flag = false;
	while (i <= NTotalePianeti && !flag) {
		if (ship.getShape().getGlobalBounds().intersects(mapPlanets[i].getIcon().getGlobalBounds())) {
			NPianeta = i;
			MenuCamper = false;
			flag = true;

			//Respawn momentaneo quando si entra in un pianeta
			ship.Destroy();
		}
		i++;
	}
}




