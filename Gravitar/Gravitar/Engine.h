#pragma once
#include <SFML\Graphics.hpp>
#include "ship.h";

using namespace sf;
class Engine
{
protected:
	//Finestra
	RenderWindow finestra;

	//GameObject
	ship astronave;

	// Funzioni interne
	void input(float dt);
	void update();
	void draw();

public:
	Engine();
	void start();
};

