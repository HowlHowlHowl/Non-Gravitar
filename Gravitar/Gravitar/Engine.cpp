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


	srand((unsigned int)time(0));

	
	//Menu
	MenuCamper = true;
	NPianeta = 0;

	//Generazione mappa dei pianeti
	int i = 0;
	while (i <= NTotalePianeti) {
		generatePlanets(i);
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
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
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
					mapPlanets[NPianeta].generateBunkers();
				}
				if (event.key.code == Keyboard::BackSpace)
				{
					float rotation;
					mapPlanets[NPianeta].getRandomPointOnTerrain(rotation);
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

	//Update astronave
	ship.update(dt,shipBullets,MenuCamper);

	//Selezione pianeta
	if (MenuCamper) {
		planetSelection();

		//Pulizia proiettili della nave
		shipBullets.clear();
		bunkerBullets.clear();
	}
	else {
		//Update del pianeta in cui ci si trova

		//Update pianeta
		mapPlanets[NPianeta].update(dt, ship, shipBullets, bunkerBullets);

		//update dei proiettili
		for (int i = 0; i < shipBullets.size(); i++)
		{
			shipBullets[i].update(dt);
		}

		for (int i = 0; i < bunkerBullets.size(); i++)
		{
			bunkerBullets[i].update(dt);
		}

		

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
	else {
		mapPlanets[NPianeta].draw(finestra);

		//Disegno proiettili
		for (int i = 0; i < shipBullets.size(); i++)
		{
			shipBullets[i].draw(finestra);
		}
		for (int i = 0; i < bunkerBullets.size(); i++)
		{
			bunkerBullets[i].draw(finestra);
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
void Engine::generatePlanets(int i) {
	
	//Generazione del pianeta
	Planet *p = new Planet();

	//Primo pianeta
	if (i == 0) {
		mapPlanets.push_back(*p);
		return;
	}

	//Piu' pianeti, check dei pianeti
	int k = 0;
	while (k < i) {
		
		//Se l'icona del pianeta *p interseca il pianeta mapPlanets[k]
		if (p->getIcon().getGlobalBounds().intersects(mapPlanets[k].getIcon().getGlobalBounds())) {
			cout << "INTERSECO UN PIANETA" << endl;
			Planet tmp;
			*p = tmp;

			k = 0;
		}
		//Se l'icona e' nello spawn dell'astronave
		else if (p->getIcon().getGlobalBounds().intersects(ship.getShape().getGlobalBounds())) {
			cout << "SPAWN ERRATO" << endl;
			Planet tmp;
			*p = tmp;

			k = 0;
		}
		//Se l'icona e' fuori dallo schermo
		else if (p->getIcon().getPosition().x + (p->getIcon().getRadius()) > VIEWPORT_WIDTH || p->getIcon().getPosition().y +(p->getIcon().getRadius()) > VIEWPORT_HEIGHT || p->getIcon().getPosition().x < 0 || p->getIcon().getPosition().y < 0) {
			cout << "SPAWN FUORI DAI LIMITI" << endl;
			Planet tmp;
			*p = tmp;

			k = 0;
		}
		else
			k++;
	}

	mapPlanets.push_back(*p);
		
	//DEBUG
	cout << "Pianeta spawnato" << endl;
}
void Engine::gameOver() {

	finestra.clear(Color::Black);

	//GameOverText
	sf::Font font;
	sf::Text text;
	font.loadFromFile("gamefont.ttf");

	//Selezione del font
	text.setFont(font);

	//set the string to display
	text.setString("GAME OVER");
	//set the character size
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(VIEWPORT_WIDTH/4,text.getPosition().y);

	finestra.draw(text);
	finestra.display();

	sf::Event event;
	
	while (finestra.isOpen()) {
		while (finestra.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				finestra.close();

			if (event.key.code == Keyboard::Escape) {
				finestra.close();
			}
			if (event.key.code == Keyboard::N) {
				inGame = false;
			}
		}
	}

	return;
}



