#include "ObjectTexture.h"

using namespace sf;

ObjectTexture::ObjectTexture(Bunker & bunker, Bunker2 & bunker2, Bullet & bullets)
{
	
	 bunkerTxt.loadFromFile("bunker.png");
	bunker.getShape().setTexture(&bunkerTxt);

	bunker2Txt.loadFromFile("bunker2.png");
	bunker2.getShape().setTexture(&bunker2Txt);

	bulletTxt.loadFromFile("bullet.png");
	bullets.getShape().setTexture(&bulletTxt);
}
