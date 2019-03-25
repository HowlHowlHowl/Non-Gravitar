#include "Planet.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "utils.h"

Planet::Planet()
{
	//Impostazioni icona del pianeta
	icon.setRadius(20.f);
	icon.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	icon.setPosition((float)(rand() % VIEWPORT_WIDTH), (float)(rand() % VIEWPORT_HEIGHT));

	nbunker = 3;
	circumnference = 0;

	terrainColor = Color::Green;
	generateRandomTerrain();

	generateBunkers();
}
void Planet::update(float dt,ship &ship, std::vector<Bullet>& shipBullets){
	//Aggiornamento gameobject
	collisions(ship, shipBullets);
}
void Planet::collisions(ship &ship, std::vector<Bullet>& shipBullets) {
	//astronvave collision
	if (intersectsTerrain(ship.getShape())) {
		std::cout << "COllision!" << std::endl;
		ship.Destroy();
	}

	//Proiettili collision
	for (int i = 0; i < shipBullets.size(); i++) {

		for (int j = 0; j < bunkers.size(); j++) {
			Bunker* bunk = bunkers[j];
			Vector2f bunkPos = bunk->getShape().getPosition();
			Vector2f bunkSize = bunk->getShape().getSize();
			if (distance(shipBullets[i].getShape().getPosition(), bunkPos)< bunkSize.x / 2.f + shipBullets[i].getShape().getRadius()) {
				bunk->takeDamage();
				if (!bunk->isAlive()) {
					delete bunk;
					bunkers.erase(bunkers.begin() + j); 
					j--;
				}

				shipBullets.erase(shipBullets.begin() + i);
				i--;
				// wait what, a wild break has appeared
				break;
			}
		}
	}

}
void Planet::draw(RenderWindow &window){
	window.draw(terrainVertices.data(), terrainVertices.size(), sf::LinesStrip);
	
	for (int i = 0; i < bunkers.size(); i++) {
		bunkers[i]->draw(window);
	}
}
void Planet::drawIcon(RenderWindow &window){
	window.draw(icon);
}
bool Planet::destroyed(){
	if (bunkers.size() == 0)
		return true;
	return false;
}
void Planet::created(){
}
bool Planet::intersectsTerrain(RectangleShape rect)
{
	Vector2f pos = rect.getPosition();
	for (int i = 0; i < terrainVertices.size() - 1; i++)
	{
		Vector2f a = terrainVertices[i].position;
		Vector2f b = terrainVertices[i + 1].position;

		if (pos.x >= a.x && pos.x <= b.x)
		{
			// retta passante per a e b
			float m = (b.y - a.y) / (b.x - a.x);
			float q = b.y - m * b.x;

			float distance = abs(pos.y - (m * pos.x + q)) / sqrt(1 + m * m);
			if(distance < rect.getSize().x / 2.0f)
			{
				return true;
			}
		}		
	}

	return false;
}
void Planet::generateRandomTerrain()
{
	int MinY = VIEWPORT_HEIGHT / 2;
	int MaxY = VIEWPORT_HEIGHT - VIEWPORT_HEIGHT / 8;
	int DeltaY = MaxY - MinY;
	int vertCount = 10;

	terrainVertices.clear();
	for (int i = 0; i <= vertCount; i++)
	{
		Vector2f pos((float)(VIEWPORT_WIDTH / vertCount * i), (float)(rand() % DeltaY + MinY));
		Vertex vert(pos, terrainColor);
		terrainVertices.push_back(vert);
	}
}

void Planet::deleteAllBunkers() {
	for (int i = 0; i < bunkers.size(); i++) {
		delete bunkers[i];
	}
	bunkers.clear();
}

void Planet::generateBunkers()
{
	deleteAllBunkers();
	for (int i = 0; i < nbunker; i++) {
		float rotation;
		Vector2f pos = getRandomPointOnTerrain(rotation);
		bunkers.push_back(new Bunker(pos, rotation));
	}
}


Vector2f Planet::getRandomPointOnTerrain(float& rotation)
{
	int vertIndex = rand() % (terrainVertices.size() - 1);
	Vector2f a = terrainVertices[vertIndex].position;
	Vector2f b = terrainVertices[vertIndex + 1].position;

	// retta passante per a e b
	float m = (b.y - a.y) / (b.x - a.x);
	float q = b.y - m * b.x;

	float x = ((b.x - a.x) - 40.0f) * randf01() + a.x + 20.0f;
	float y = m * x + q;

	rotation =  radToDeg(atan(m));
	return Vector2f(x, y);
}
CircleShape Planet::getIcon() {
	return icon;
}