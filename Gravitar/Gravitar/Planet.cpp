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
	icon.setPosition(rand() % VIEWPORT_WIDTH ,rand() % VIEWPORT_HEIGHT);

	nbunker = 2;
	circumnference = 0;
	rett.setPosition(100, 400);

	terrainColor = Color::Green;
	generateRandomTerrain();
}
void Planet::update(float dt,ship &ship){
	//Aggiornamento gameobject
	
}
void Planet::collisions(ship &ship, std::vector<Bullet>& shipBullets) {
	//astronvave collision
	if (intersectsTerrain(ship.getShape())) {
		std::cout << "COllision!" << std::endl;
		ship.Destroy();
	}

	//Proiettili collision
	for (int i = 0; i < shipBullets.size(); i++) {

		//Collisione con il rettangolo ( bunker temporaneo )
		if (shipBullets[i].getShape().getGlobalBounds().intersects(rett.getGlobalBounds())) {

			nbunker--;
			//Spawn del rettangolo random
			int i = (rand() % 800) + 1;
			int j = (rand() % 600) + 1;
			rett.setPosition(i, j);
			
		}
	}
}
void Planet::draw(RenderWindow &window){


	//Disegno dei gameobject
	rett.setSize(Vector2f(30, 30));
	rett.setFillColor(Color::Red);
	
	window.draw(terrainVertices.data(), terrainVertices.size(), sf::LinesStrip);
	window.draw(rett);
}
void Planet::drawIcon(RenderWindow &window){
	window.draw(icon);
}
bool Planet::destroyed(){
	if (nbunker <= 0)
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
		Vector2f pos(VIEWPORT_WIDTH / vertCount * i, rand() % DeltaY + MinY);
		Vertex vert(pos, terrainColor);
		terrainVertices.push_back(vert);
	}
}
Vector2f Planet::getRandomPointOnTerrain()
{
	int vertIndex = rand() % (terrainVertices.size() - 1);
	Vector2f a = terrainVertices[vertIndex].position;
	Vector2f b = terrainVertices[vertIndex + 1].position;

	// retta passante per a e b
	float m = (b.y - a.y) / (b.x - a.x);
	float q = b.y - m * b.x;

	float x = (b.x - a.x) * randf01() + a.x;
	float y = m * x + q;

	rett.setPosition(x, y);
	return Vector2f(x, y);
}
CircleShape Planet::getIcon() {
	return icon;
}