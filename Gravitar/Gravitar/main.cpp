#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	RenderWindow window(VideoMode(200, 200), "SFML works!");
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}