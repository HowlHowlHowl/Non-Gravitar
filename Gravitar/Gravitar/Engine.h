#pragma once
#include <SFML\Graphics.hpp>
#include "ship.h"
#include "bullet.h"
#include "Planet.h"
#include "ResourceManager.h"
#include <vector>

enum GameState {
	GAMESTATE_SOLAR_SYSTEM,
	GAMESTATE_PLANET,
	GAMESTATE_OVER,
};

using namespace sf;
class Engine
{
protected:
	GameState state = GAMESTATE_SOLAR_SYSTEM;
	
	//Sfondo
	RectangleShape background;
	//Finestra
	RenderWindow finestra;
	//GameObject
	ship ship;
	std::vector<Bullet> shipBullets;
	std::vector<Bullet> bunkerBullets;
	std::vector<Planet> mapPlanets;
	int NPianeta;


	// Funzioni interne
	void update(float dt);
	void draw();
	void planetSelection();
	void generatePlanets();
	//void gameOver();
	void restartGame();
public:
	Engine();
	void start();
	
};

