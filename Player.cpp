#include "Player.h"
#include <iostream>

Player::Player()
{
	this->name = "Player";
	this->health = 10;
	this->max_health = 10;
	this->xp = 0;
	this->max_xp = 10;
	this->level = 1; 
	this->myTurn = false;
}

void Player::attack(Hero* target)
{
	int hit = (1 * level) + 1;
	target->take_dmg(hit);
	this->myTurn = false;
	std::cout << name << " attacks for " << hit << std::endl;
}

void Player::take_dmg(int hit)
{
	this->health -= hit;
}