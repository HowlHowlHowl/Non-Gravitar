#pragma once
#include <SFML\Graphics.hpp>
#include "ship.h"
#include "bullet.h"
#include "Planet.h"
#include <vector>

using namespace sf;
class Engine
{
protected:

	//Numeri di pianeti
	int NTotalePianeti = 6;

	//Finestra
	RenderWindow finestra;

	//GameObject
	ship ship;
	std::vector<Bullet> shipBullets;
	std::vector<Planet> mapPlanets;
	bool MenuCamper;
	int NPianeta;

	// Funzioni interne
	void update(float dt);
	void draw();
	void planetSelection();

public:
	Engine();
	void start();
};

