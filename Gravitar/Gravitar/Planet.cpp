#pragma	once
#include "Planet.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "utils.h"
#include "Bunker2.h"



Planet::Planet()
{
}

Planet::Planet(Vector2f pos)
{
	//Impostazioni icona del pianeta
	icon.setRadius(20.f);
	icon.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	icon.setPosition(pos);
	icon.setOrigin(Vector2f(10.f, 10.f));

	//Nome random del pianeta (random 10 lettere)
	char nomeRandom[11];
	int i = 0;
	int length = rand() % 10 + 1;
	while (i < length)
	{
		nomeRandom[i] = randAlphanum();
		i++;
	}
	nomeRandom[i] = 0;
	nomePianeta = String(nomeRandom);

	//Impostazioni del terreno e spawn degli oggetti
	terrainColor = Color::Green;
	generateRandomTerrain();
	max_bonus = 3;
	generateBunkers();
	
}
void Planet::generateFuel()
{
	float nil;
	Vector2f pos = getRandomPointOnTerrain(nil);
	fuelBonus = new Fuel(pos);

}
void Planet::update(float dt,ship &ship, Array<Bullet>& shipBullets, Array<Bullet> &bunkerBullets){
	//Aggiornamento gameobject
	for (int i = 0; i < bunkers.size(); i++) {
		bunkers[i]->update(dt, bunkerBullets);
	}
	collisions(ship, shipBullets, bunkerBullets);
	if (Keyboard::isKeyPressed(Keyboard::F) && fuelBonus != NULL && isInsideTriangle(ship)) {
		fuelBonus->update(ship);
		if (fuelBonus->isTaken()) {
			delete fuelBonus;
			fuelBonus = NULL;
		}
	}
	//Non va in Cooldown se il bonus non � stato raccolto
	if(fuelBonus==NULL)
	bonusCooldown += dt;

	if (fuelBonus == NULL && bonusCooldown > bonusSpawn && max_bonus>0) {
		max_bonus--;
		generateFuel();
		bonusCooldown = 0.f;
	}
	
}

bool Planet::isOutOfPlanet(Vector2f pos, float radius) {
	if (pos.y < -radius || pos.y > VIEWPORT_HEIGHT + radius || pos.x > PLANET_WIDTH + radius || pos.x < -radius) {
		return true;
	}
	else {
		return false;
	}
}

void Planet::collisions(ship &ship, Array<Bullet>& shipBullets, Array<Bullet>& bunkerBullets) {
	//astronvave collision
	if (intersectsTerrain(ship.getPosition(), ship.getShape().getSize().x / 2.f)) {
		//std::cout << "Collision!" << std::endl;
		ship.Destroy(true);
	}
	//Proiettili bunker - ship collision
	for (int i = 0; i < bunkerBullets.size(); i++) {
		Vector2f shipPos = ship.getPosition();
		float shipHalfSize = ship.getShape().getSize().x / 2;
		Vector2f  bunkBulletPos = bunkerBullets[i].getShape().getPosition();
		float bunkBulletRadius = bunkerBullets[i].getShape().getRadius();

		float radius = shipHalfSize + bunkBulletRadius;
		if (isOutOfPlanet(bunkBulletPos, bunkBulletRadius)) {
			bunkerBullets.remove(i);
			i--;
		}
		else {
			if (distance(shipPos, bunkBulletPos) < radius)
			{
				ship.Destroy(true);
				bunkerBullets.clear();
			}
		}
	}
	//Proiettili ship - Bunker collision
	for (int i = 0; i < shipBullets.size(); i++) {
		Vector2f shipBulletPos = shipBullets[i].getShape().getPosition();
		float shipBulletRadius = shipBullets[i].getShape().getRadius();
		if (isOutOfPlanet(shipBulletPos, shipBulletRadius)) {
			shipBullets.remove(i);
			i--;
		}
		else {
			bool projectileExists = true;
			for (int j = 0; j < bunkers.size() && projectileExists; j++) {
				Bunker* bunk = bunkers[j];
				Vector2f bunkPos = bunk->getShape().getPosition();
				Vector2f bunkSize = bunk->getShape().getSize();

				if (distance(shipBulletPos, bunkPos) < bunkSize.x / 2.f + shipBulletRadius) {
					bunk->takeDamage();
					if (!bunk->isAlive()) {
						globalScore += bunk->getScore();
						delete bunk;
						bunkers.remove(j);
						j--;
					}

					shipBullets.remove(i);
					i--;
					projectileExists = false;
				}
			}
		}
	}
	
	//Proiettili astronave - Terreno collision
	for (int i = 0; i < shipBullets.size(); i++) {
		CircleShape bullet = shipBullets[i].getShape();
		if (intersectsTerrain(bullet.getPosition(), bullet.getRadius())) {
			shipBullets.remove(i);
			i--;
		}
	}
	
}
void Planet::draw(RenderWindow &window) {
	window.draw(terrainVertices.data(), terrainVertices.size(), sf::LinesStrip);

	for (int i = 0; i < bunkers.size(); i++) {
		bunkers[i]->draw(window);
	}
	if (fuelBonus != NULL) {
		fuelBonus->draw(window);
	}
}

void Planet::drawIcon(RenderWindow &window){
	sf::Text text;
	//Selezione del font
	text.setFont(*resourceManager.getFont());
	//set the string to display
	text.setString(nomePianeta);
	//set the character size
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(icon.getPosition().x+icon.getRadius(),icon.getPosition().y+2*(icon.getRadius()));

	//Disegno icona e nome
	window.draw(icon);
	window.draw(text);
}
bool Planet::destroyed(){
	if (bunkers.size() == 0)
		return true;
	return false;
}

bool Planet::intersectsTerrain(Vector2f pos, float radius)
{
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
			if(distance < radius)
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
	int vertCount = 20;

	terrainVertices.clear();
	for (int i = 0; i <= vertCount; i++)
	{
		Vector2f pos((float)PLANET_WIDTH / vertCount * i, (float)(rand() % DeltaY + MinY));
		Vertex vert(pos, terrainColor);
		terrainVertices.add(vert);
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
	for (int i = 0; i < NUMERO_BUNKER; i++) {
		float rotation;
		Vector2f pos = getRandomPointOnTerrain(rotation);
		bunkers.add(new Bunker(pos, rotation));
	}
	for (int i = 0; i < NUMERO_BUNKER2; i++) {
		float rotation;
		Vector2f pos = getRandomPointOnTerrain(rotation);
		bunkers.add(new Bunker2(pos, rotation));
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
bool Planet::isInsideTriangle(ship& ship) {
	Vector2f a = ship.getPointRay(0);
	Vector2f b = ship.getPointRay(1);
	Vector2f c = ship.getPointRay(2);
	Vector2f p = fuelBonus->getPosition();
	float sum = area(p, a, b) + area(p, b, c) + area(p, a, c);
	//Il fuel � nel raggio?
	return (abs(area(a, b, c) - sum) < 0.01);
}

CircleShape Planet::getIcon() {
	return icon;
}

