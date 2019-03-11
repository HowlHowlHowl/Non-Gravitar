#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class ship
{
	protected:
		float carburante = 10000.f;
		float speed = 60.f;
		float xpos;
		float ypos;
		RectangleShape shape;
		bool isShooting;
		int life;
	public:	
		void left_m(float dt);
		void right_m(float dt);
		void up_m(float dt);
		void down_m(float dt);
		ship();		
		void update();
		void init();
		RectangleShape getShape();
		Vector2f getPosition();
		bool canMoving();
		void Destroy();
};

