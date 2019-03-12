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

	//Finestra
	RenderWindow finestra;

	//GameObject
	Planet planet;
	ship ship;
	std::vector<Bullet> shipBullets;

	// Funzioni interne
	void update(float dt);
	void draw();

public:
	Engine();
	void start();
};

