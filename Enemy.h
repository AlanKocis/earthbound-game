#pragma once
#include "Hero.h"
class Enemy : public Hero
{
public:
	Enemy(int level);
private:
	static int ID;
};
