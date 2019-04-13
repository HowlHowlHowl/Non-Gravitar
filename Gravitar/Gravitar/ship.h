#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "bullet.h"
#include "Global.h"
#include "ResourceManager.h"
using namespace sf;

class ship
{
	protected:
		const float max_carburante = 10000.f;
		const float max_speed = 350.f;
		const float acceleration = 650.f;
		float carburante;
		float speed;
		float xpos;
		float ypos;
		RectangleShape shape;
		int life;
		float shootCooldown = 0.3f;
		float shootTimer = 0.f;
		direction dir;
		ConvexShape ray;
	
	public:	
		ship();		
		void update(float dt,std::vector<Bullet> &bullets, bool isInSystem);
		void draw(RenderWindow &finestra);
		void drawHUD(RenderWindow& finestra);
		void init();
		Vector2f getPosition();
		RectangleShape getShape();
		void Destroy();
		void shoot(std::vector<Bullet> &bullets);
		bool isAlive();
		void getBonus(float dt);
		Vector2f getPointRay(int x);
		void setPosition(float x, float y);
		float getFuel();
};

