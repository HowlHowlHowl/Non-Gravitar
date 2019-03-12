#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "bullet.h"
#include "Global.h"
using namespace sf;

class ship
{
	protected:
		float carburante = 10000.f;
		float speed = 60.f;
		float xpos;
		float ypos;
		RectangleShape shape;
		int life;
		float shootCooldown = 0.5f;
		float shootTimer = 0.f;
		direction dir;

	public:	
		void left_m(float dt);
		void right_m(float dt);
		void up_m(float dt);
		void down_m(float dt);
		ship();		
		void update(float dt,std::vector<Bullet> &bullets);
		void draw(RenderWindow &finestra);
		void init();
		Vector2f getPosition();
		bool canMoving();
		RectangleShape getShape();
		void Destroy();
		void shoot(std::vector<Bullet> &bullets);
};

