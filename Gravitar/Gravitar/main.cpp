#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	int windowWidth = 1024;
	int windowHeight = 768;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Gravitar");
	
	return 0;
}