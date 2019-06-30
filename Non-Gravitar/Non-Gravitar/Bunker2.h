#pragma once
#include "Bunker.h"
class Bunker2 : public Bunker
{
public:
	Bunker2(Vector2f pos, float rotation);
	virtual void shoot(Array<Bullet> &bullets) override;
	virtual int getScore() override;
};

