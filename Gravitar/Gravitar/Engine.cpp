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
	finestra.create(VideoMode(800, 600),
		"Gravitar Game Engine");
	finestra.setFramerateLimit(60);
}
void Engine::start(){

	//Loop in game
	Clock clock;
	float dt;
	
	while (finestra.isOpen())
	{
		//restart del clock
		dt = clock.restart().asSeconds();
		
		//Lettura input, passo il moltiplicatore per fps
		input(dt);
		//Update della scena
		update();
		//Disegno della scena
		draw();

		/* DEBUG */
		cout<<"Frame: "<< dt << "\n";
	}
}


void Engine::input(float dt) {
	//Chiusura con 'ESC'
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		finestra.close();
	}
	//Controllo direzione
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		astronave.left_m(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		astronave.right_m(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		astronave.up_m(dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		astronave.down_m(dt);
	}

}
void Engine::update() {
	//Update dei GameObject
	astronave.update();
}
void Engine::draw() {

	finestra.clear(Color::Black);
	finestra.draw(astronave.getShape());

	//Disegno della scena
	finestra.display();
}




