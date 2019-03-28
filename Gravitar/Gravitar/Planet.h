#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "Bunker.h"

class Planet
{
protected:
	int circumnference;
	int nbunker;
	std::vector<Vertex> terrainVertices;
	Color terrainColor;
	CircleShape icon;
	std::vector<Bunker*> bunkers;
	String nomePianeta;

public:
	Planet();
	void update(float dt,ship &ship, std::vector<Bullet>& shipBullets, std::vector<Bullet> &bunkerBullets);
	void draw(RenderWindow &window);
	void collisions(ship &ship, std::vector<Bullet>& shipBullets, std::vector<Bullet> &bunkerBullets);
	bool destroyed();
	void created();
	bool intersectsTerrain(Vector2f pos, float radius);
	void generateRandomTerrain();
	void deleteAllBunkers();
	void generateBunkers();

	Vector2f getRandomPointOnTerrain(float & rotation);
	CircleShape getIcon();
	void drawIcon(RenderWindow &window);
};

