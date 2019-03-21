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
	while(i <= NTotalePianeti) {
		Planet *p = new Planet();
		mapPlanets.push_back(*p);
			i++;
	}
}

void Engine::start(){

	//Loop in game
	Clock clock;
	float dt;

	inGame = true;

	while (finestra.isOpen() && inGame)
	{
		//Cancellazione finestra
		finestra.clear(Color::Black);

		//Eventi
		sf::Event event;
		while (finestra.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				finestra.close();

			if (event.key.code == Keyboard::Tab) {
				MenuCamper = true;

				//Respawn momentaneo
				ship.init();
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

	//Selezione pianeta
	if (MenuCamper) {

		planetSelection();

		//Pulizia proiettili della nave
		shipBullets.clear();
	}

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

		//Check vite astronave
		if (!ship.isAlive()) {
			gameOver();
			return;
		}

		//Check distruzione pianeta
		if (mapPlanets[NPianeta].destroyed()) {

			//Cancellazione pianeta dalla mappa
			mapPlanets.erase(mapPlanets.begin() + NPianeta);
			NTotalePianeti--;

			//Ritorno al menu
			MenuCamper = true;

			//Respawn dell'astronave
			ship.init();
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
			ship.init();
		}
		i++;
	}
}

void Engine::gameOver() {

	finestra.clear(Color::Black);

	//GameOverText
	sf::Font font;
	sf::Text text;
	font.loadFromFile("C:\\Users\\Colo\\Desktop\\retro.ttf");

	//Selezione del font
	text.setFont(font);

	//set the string to display
	text.setString("GAME OVER");
	//set the character size
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);

	finestra.draw(text);
	finestra.display();
	
	while (finestra.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			finestra.close();
		
		if (Keyboard::isKeyPressed(Keyboard::N)) {
			inGame = false;
			break;
		}

	}

	return;
}



