#pragma once
#include "Hero.h"
class Player : public Hero
{
public:
	virtual void attack(Hero* target) override;
	virtual void take_dmg(int hit) override;
	Player();
};