#pragma once
#include <SFML\Graphics.hpp>
#include "ship.h";

using namespace sf;
class Engine
{
protected:

	//Finestra
	RenderWindow m_Window;

	//GameObject
	ship astronave;

	// Funzioni interne
	void input();
	void update();
	void draw();

public:
	Engine();
	void start();
};

