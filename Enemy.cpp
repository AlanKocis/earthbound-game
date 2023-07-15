#include "Enemy.h"
#include <iostream>

int Enemy::ID = 0;
Enemy::Enemy(int lvl)
{
	this->targeted = false;
	++ID;
	level = lvl;
	name = "Enemy";
	health = 10 + (2 * lvl);		//should be 10 change later TESTING
	this->max_health = 10 + (2 * lvl);
	targeted = false;
}

void Enemy::take_dmg(int hit)
{
	this->health -= hit;
}

void Enemy::attack(Hero* target)
{
	int hit = 1 * level;
	target->take_dmg(hit);
	myTurn = false;
	std::cout << name << ' ' << this << " attacks for " << hit << std::endl;

}

//lol