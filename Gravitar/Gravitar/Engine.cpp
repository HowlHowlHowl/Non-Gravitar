#include "Engine.h"
#include <SFML\Graphics.hpp>
#include <sstream>
#include "utils.h"

using namespace sf;
using namespace std;

ResourceManager resourceManager;

Engine::Engine()
{
	srand((unsigned int)time(0));

	finestra.create(VideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT), "Gravitar");
	finestra.setFramerateLimit(60);
	resourceManager.loadTextures();

	//Menu
	NPianeta = 0;
	generatePlanets();
}

void Engine::start() {

	//Loop in game
	Clock clock;
	float dt;

	//Background set
	Vector2f bg(VIEWPORT_WIDTH * 2, VIEWPORT_HEIGHT);
	background.setSize(bg);
	background.setTexture(resourceManager.getBackgroundTexture());

	while (finestra.isOpen())
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

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == Keyboard::BackSpace)
				{
					float rotation;
					mapPlanets[NPianeta].getRandomPointOnTerrain(rotation);
				}
				if (event.key.code == Keyboard::Return)
				{
					for (int i = 0; i < mapPlanets.size(); i++) {
						mapPlanets[i].deleteAllBunkers();
					}
					mapPlanets.clear();
					generatePlanets();
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

	//controlla se cambiare di game state
	if (ship.getPosition().y < -ship.getShape().getSize().y / 2.f) {
		state = GAMESTATE_SOLAR_SYSTEM;
		ship.setPosition(0, 0);
	}

	//Selezione pianeta
	switch (state) {
		case GAMESTATE_SOLAR_SYSTEM: {
			ship.update(dt, shipBullets, true);
			//Pulizia proiettili di bunker e nave
			shipBullets.clear();
			bunkerBullets.clear();

			planetSelection();
		}break;

		case GAMESTATE_PLANET: {
			ship.update(dt, shipBullets, false);
			
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

			//Check distruzione pianeta
			if (mapPlanets[NPianeta].destroyed()) {
				globalScore += 500;

				//Cancellazione pianeta dalla mappa
				mapPlanets.remove(NPianeta);

				if (mapPlanets.size() == 0) {
					globalScore += 10000;
					generatePlanets();
				}

				//Ritorno al menu
				state = GAMESTATE_SOLAR_SYSTEM;

				//Respawn dell'astronave
				ship.getShape().setPosition(0, 0);
				ship.getShape().setRotation(0);
			}

			//Check vite astronave
			if (!ship.isAlive()) {

				state = GAMESTATE_OVER;
			}
		}break;

		case GAMESTATE_OVER: {
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				restartGame();
			}
		}break;
	}
}

void Engine::draw() {

	
	//Disegno mappa pianeti
	switch (state) {
		case GAMESTATE_SOLAR_SYSTEM: {
			finestra.setView(finestra.getDefaultView());
			//Disegno background
			finestra.draw(background);

			ship.draw(finestra);

			for (int i = 0; i < mapPlanets.size(); i++) {
				mapPlanets[i].drawIcon(finestra);
			}

			ship.drawHUD(finestra);
		}break;
		case GAMESTATE_PLANET: {
			//Disegno background
			finestra.setView(finestra.getDefaultView());
			finestra.draw(background);

			//Disegno il giuoco
			float minCameraX = VIEWPORT_WIDTH / 2.f;
			float maxCameraX = PLANET_WIDTH - VIEWPORT_WIDTH / 2.f;
			float cameraX = clamp(ship.getPosition().x, minCameraX, maxCameraX);
			Vector2f cameraCenter(cameraX, VIEWPORT_HEIGHT / 2.f);

			finestra.setView(View(cameraCenter, Vector2f(VIEWPORT_WIDTH, VIEWPORT_HEIGHT)));

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
			ship.draw(finestra);

			//Disegno HUD
			finestra.setView(finestra.getDefaultView());
			ship.drawHUD(finestra);
		}break;

		case GAMESTATE_OVER: {
			//GameOverText
			sf::Text text;
			sf::Text retry;
			
			//Selezione del font
			text.setFont(*resourceManager.getFont());
			retry.setFont(*resourceManager.getFont());

			//set the string to display
			text.setString("GAME OVER");
			retry.setString("Press 'R' to try again...");
			//set the character size
			text.setCharacterSize(100);
			retry.setCharacterSize(50);
			text.setFillColor(sf::Color::White);
			retry.setFillColor(Color::White);
			text.setPosition(VIEWPORT_WIDTH / 2.0f, VIEWPORT_HEIGHT / 2.5f);
			retry.setPosition(text.getPosition().x, text.getPosition().y + 100);
			text.setOrigin(text.getLocalBounds().width / 2.0f,
				text.getLocalBounds().height / 2.0f);
			retry.setOrigin(retry.getLocalBounds().width / 2.f,
				retry.getLocalBounds().height / 2.f);
			finestra.setView(finestra.getDefaultView());

			std::stringstream scoreString;
			scoreString << "Score: " << globalScore;
			sf::Text scoreText(sf::String(scoreString.str()), *resourceManager.getFont());
			scoreText.setPosition(text.getPosition().x, text.getPosition().y + 200);
			scoreText.setOrigin(scoreText.getLocalBounds().width / 2.0f,
				                scoreText.getLocalBounds().height / 2.0f);
			finestra.draw(scoreText);


			finestra.draw(text);
			finestra.draw(retry);
		}break;
	};

	//Disegno della scena
	finestra.display();
}

void Engine::planetSelection(){
	int i = 0; 
	bool flag = false;
	while (i < mapPlanets.size() && !flag) {
		if (ship.getShape().getGlobalBounds().intersects(mapPlanets[i].getIcon().getGlobalBounds())) {
			NPianeta = i;
			state = GAMESTATE_PLANET;
			flag = true;

			//Riposizionamento quando si entra in un pianeta
			ship.setPosition(PLANET_WIDTH / 2, 100);
		}
		i++;
	}
}
void Engine::generatePlanets() {
	//Generazione mappa dei pianeti
	for (int i = 0; i < NUMERO_PIANETI; i++) {
		float theta = degToRad(360.0f / NUMERO_PIANETI * i);
		Vector2f pos(cos(theta), sin(theta));
		Vector2f center(VIEWPORT_WIDTH / 2.f, VIEWPORT_HEIGHT / 2.f);
		pos = pos * randrange(100, VIEWPORT_HEIGHT / 2.f) + center;

		mapPlanets.add(Planet(pos));
	}
	//cout << "Pianeta spawnato" << endl;
}


void Engine::restartGame(){
	state = GAMESTATE_SOLAR_SYSTEM;
	ship.init();
	globalScore = 0;
	for (int i = 0; i < mapPlanets.size(); i++) {
		mapPlanets[i].deleteAllBunkers();
	}
	mapPlanets.clear();
	generatePlanets();
}



