#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "bullet.h"
#include "Global.h"
using namespace sf;

class ship
{
	protected:
		const float max_carburante = 10000.f;
		float carburante;
		float speed = 350.f;
		float xpos;
		float ypos;
		RectangleShape shape;
		int life;
		float shootCooldown = 0.5f;
		float shootTimer = 0.f;
		direction dir;
		ConvexShape ray;
		void left_m(float dt);
		void right_m(float dt);
		void up_m(float dt);
		void down_m(float dt);
		Texture rayTexture;
		Texture lifeTexture;
		Texture shipTexture;
	public:	
		ship();		
		void update(float dt,std::vector<Bullet> &bullets, bool isInSystem);
		void draw(RenderWindow &finestra);
		void drawHUD(RenderWindow& finestra);
		void init();
		Vector2f getPosition();
		bool canMoving();
		RectangleShape getShape();
		void Destroy();
		void shoot(std::vector<Bullet> &bullets);
		bool isAlive();
		void getBonus(float dt);
		Vector2f getPointRay(int x);
};

