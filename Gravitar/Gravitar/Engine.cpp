#include "Engine.h"
#include <SFML\Graphics.hpp>
using namespace sf;


Engine::Engine()
{
	//Gioco a tutta finestra
	//Vector2f resolution;
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;

	//Gioco in finestra
	m_Window.create(VideoMode(800, 600),
		"Gravitar Game Engine");
}
void Engine::start(){
	//Loop in game
	while (m_Window.isOpen())
	{		
		input();
		update();
		draw();
	}
}


void Engine::input() {
	//Chiusura con 'ESC'
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	//Controllo direzione
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		astronave.Left();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		astronave.Right();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		astronave.Up();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		astronave.Down();
	}

}
void Engine::update() {

	//Update dei GameObject
	astronave.update();
}
void Engine::draw() {

	m_Window.clear(Color::Black);
	m_Window.draw(astronave.getShape());

	//Disegno della scena
	m_Window.display();
}




