#include <iostream>
#include <SFML\Graphics.hpp>
#include "Engine.h"

using namespace std;
using namespace sf;

int main(int argc, char* args[])
{
	//Uso un Engine per controllare il gioco
	Engine GameEngine;
	GameEngine.start();

	return 0;
}