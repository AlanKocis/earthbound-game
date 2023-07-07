#pragma once
#include "Hero.h"
class Enemy : public Hero
{
public:
	Enemy(int level);
	bool targeted;
private:
	static int ID;
};
