#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ship.h"

class Planet
{
protected:
	int circumnference;
	int nbunker;
	RectangleShape rett;
	std::vector<Vertex> terrainVertices;
	Color terrainColor;
	CircleShape icon;
public:
	Planet();
	void update(float dt,ship &ship);
	void draw(RenderWindow &window);
	void collisions(ship &ship, std::vector<Bullet>& shipBullets);
	bool destroyed();
	void created();
	bool intersectsTerrain(RectangleShape rect);
	void generateRandomTerrain();
	Vector2f getRandomPointOnTerrain();
	CircleShape getIcon();
	void drawIcon(RenderWindow &window);
};

