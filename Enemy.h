#pragma once
#include "Hero.h"
class Enemy : public Hero
{
public:
	Enemy(int level);
	bool targeted;
	virtual void take_dmg(int hit) override;
	virtual void attack(Hero* target) override;
private:
	static int ID;
};
