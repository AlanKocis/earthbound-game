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
	this->targeted = false;
}

void Player::attack(Hero* target)
{
	int hit = (1 * level) + 1;
	target->take_dmg(hit);
	std::cout << name << " attacks for " << hit << std::endl;
	if (target->get_health() <= 0)
	{
		this->xp += 10;
		std::cout << name << " killed " << target->get_name() << " and gained some xp" << std::endl;
	}
	myTurn = false;
}

void Player::take_dmg(int hit)
{
	this->health -= hit;
}