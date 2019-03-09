#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class ship
{
	protected:
		float xpos;
		float ypos;
		float speed = .1f;
		RectangleShape shape;

	public:		
		ship();
		void Left();
		void Right();
		void Up();
		void Down();
		void update();
		RectangleShape getShape();
};

