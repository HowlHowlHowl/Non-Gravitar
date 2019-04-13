#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

void ResourceManager::loadTextures() {
	bunkerTexture = new Texture();
	if(!bunkerTexture->loadFromFile("bunker.png"))
		std::cout << "Error: cannot loat bunker.png" << std::endl;
	bunkerTexture->setSmooth(true);

	bunker2Texture = new Texture();
	if(!bunker2Texture->loadFromFile("bunker2.png"))
		std::cout << "Error: cannot loat bunker2.png" << std::endl;
	bunker2Texture->setSmooth(true);

	shipTexture = new Texture();
	if(!shipTexture->loadFromFile("ship.png"))
		std::cout << "Error: cannot loat ship.png" << std::endl;
	shipTexture->setSmooth(true);

	bulletTexture = new Texture();
	if (!bulletTexture->loadFromFile("bullet.png"))
		std::cout << "Error: cannot loat bullet.png" << std::endl;
	bulletTexture->setSmooth(true);
	
	rayTexture = new Texture();
	if (!rayTexture->loadFromFile("ray.png"))
		std::cout << "Error: cannot load ray.png" << std::endl;
	

	healtTexture = new Texture();
	if(!healtTexture->loadFromFile("vita.png"))
		std::cout << "Error: cannot loat vita.png" << std::endl;
	healtTexture->setSmooth(true);
}

Texture * ResourceManager::getBunkerTexture()
{
	return bunkerTexture;
}

Texture * ResourceManager::getBunker2Texture()
{
	return bunker2Texture;
}

Texture * ResourceManager::getShipTexture()
{
	return shipTexture;
}

Texture * ResourceManager::getBulletTexture()
{
	return bulletTexture;
}
Texture * ResourceManager::getRayTexture()
{
	return rayTexture;
}
Texture * ResourceManager::getHealtTexture()
{
	return healtTexture;
}
