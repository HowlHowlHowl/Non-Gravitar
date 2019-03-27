#pragma once
#include "Bunker.h"
class Bunker2 : public Bunker
{
	Texture bunker2Texture;
public:
	Bunker2(Vector2f pos, float rotation);
	virtual void shoot(std::vector<Bullet> &bullets) override;
};

