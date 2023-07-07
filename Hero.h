#pragma once
#include <string>
#include "HealthBar.h"
class Hero
{
protected:
	HealthBar healthBar;
	std::string name;
	int health;
	int max_health;
	int xp;
	int max_xp;
	int level;
	bool myTurn;

public:
	bool targeted;
	virtual void attack(Hero* target) = 0;
	virtual void take_dmg(int hit) = 0;
	bool get_myTurn() const;
	virtual ~Hero() {}
};

