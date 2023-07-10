#include "Enemy.h"
#include <iostream>

int Enemy::ID = 0;

Enemy::Enemy(int level)
{
	this->targeted = false;
	++ID;
	this->ID = ID;
	this->level = level;
	this->name = "Enemy";
	this->health = 10 + (2 * level);
	this->max_health = 10 + (2 * level);
	this->targeted = false;
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
