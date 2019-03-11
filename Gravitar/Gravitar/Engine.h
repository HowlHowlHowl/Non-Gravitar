#pragma once
#include <SFML\Graphics.hpp>
#include "ship.h";
#include "bullet.h";
#include "Planet.h";

using namespace sf;
class Engine
{
protected:

	//Finestra
	RenderWindow finestra;

	//GameObject
	Planet planet;

	// Funzioni interne
	void update(float dt);
	void draw();

public:
	Engine();
	void start();
};

