#pragma once
#include <SFML\Graphics.hpp>
#include "ship.h"
#include "bullet.h"
#include "Planet.h"
#include "ResourceManager.h"
#include "Array.h"

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
	Array<Bullet> shipBullets;
	Array<Bullet> bunkerBullets;
	Array<Planet> mapPlanets;
	int NPianeta;


	// Funzioni interne
	void update(float dt);
	void draw();
	void planetSelection();
	void generatePlanets();
	void restartGame();
public:
	Engine();
	void start();
};

