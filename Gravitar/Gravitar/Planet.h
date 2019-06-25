#pragma once
#include "Fuel.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "Bunker.h"
#include "Fuel.h"


class Planet
{
protected:
	Array<Vertex> terrainVertices;
	Color terrainColor;
	CircleShape icon;
	Array<Bunker*> bunkers;
	String nomePianeta;
	Fuel *fuelBonus = NULL;
	float bonusSpawn = 15.f;
	float bonusCooldown = 0.f;
	float max_bonus = 3;
	bool isOutOfPlanet(Vector2f pos, float radius);

public:
	Planet();
	Planet(Vector2f pos);
	bool isInsideTriangle(ship&ship);
	void update(float dt,ship &ship, Array<Bullet>& shipBullets, Array<Bullet> &bunkerBullets);
	void draw(RenderWindow &window);
	void collisions(ship &ship, Array<Bullet>& shipBullets, Array<Bullet> &bunkerBullets);
	bool destroyed();
	bool intersectsTerrain(Vector2f pos, float radius);
	void generateRandomTerrain();
	void deleteAllBunkers();
	void generateBunkers();
	void generateFuel();
	Vector2f getRandomPointOnTerrain(float & rotation);
	CircleShape getIcon();
	void drawIcon(RenderWindow &window);
};