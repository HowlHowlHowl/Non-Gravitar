#pragma once
#include "Bunker.h"
#include "Bunker2.h"
#include "Bullet.h"
#include "ship.h"
class ObjectTexture
{
	Texture bunkerTxt;
	Texture bunker2Txt;
	Texture bulletTxt;
public:
	ObjectTexture(Bunker &bunker, Bunker2 &bunker2, Bullet &bullets);
	
};

