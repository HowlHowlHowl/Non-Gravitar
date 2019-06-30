#pragma once
#include <SFML\Graphics.hpp>
#include "Array.h"
#include "bullet.h"
#include "Global.h"
#include "ResourceManager.h"
using namespace sf;

class ship
{
	protected:
		const float max_carburante = SHIP_MAX_FUEL;
		const float max_speed = 250.f;
		const float angular_speed = 150.f;
		const float acceleration = 800.f;
		float carburante;
		float speed;
		RectangleShape shape;
		int life;
		float shootCooldown = 0.3f;
		float shootTimer = 0.f;
		ConvexShape ray;
	
	public:	
		ship();		
		void update(float dt, Array<Bullet> &bullets, bool isInSystem);
		void draw(RenderWindow &finestra);
		void drawHUD(RenderWindow& finestra);
		void init();
		Vector2f getPosition();
		RectangleShape getShape();
		void Destroy(bool inPlanet);
		void shoot(Array<Bullet> &bullets);
		bool isAlive();
		void getBonus(float dt);
		Vector2f getPointRay(int x);
		void setPosition(float x, float y);
		float getFuel();
};

