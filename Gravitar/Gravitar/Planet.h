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
public:
	Planet();
	void update(float dt,ship &ship);
	void draw(RenderWindow &window);
	void collisions(ship &ship, std::vector<Bullet>& shipBullets);
	void destroyed();
	void created();
	bool intersectsTerrain(RectangleShape rect);
	void generateRandomTerrain();
	Vector2f getRandomPointOnTerrain();
};

