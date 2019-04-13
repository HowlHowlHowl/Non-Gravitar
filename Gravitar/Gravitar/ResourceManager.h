#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class ResourceManager
{
	Texture* bunkerTexture;
	Texture* bunker2Texture;
	Texture* bulletTexture;
	Texture* shipTexture;
	Texture* rayTexture;
	Texture* healtTexture;

public:
	ResourceManager();

	void loadTextures();

	Texture* getBunkerTexture();
	Texture* getBunker2Texture();
	Texture* getShipTexture();
	Texture* getBulletTexture();
	Texture* getRayTexture();
	Texture* getHealtTexture();
};

extern ResourceManager resourceManager;
