#include "Enemy.h"

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
}
