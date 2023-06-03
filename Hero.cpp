#include "Hero.h"
#include <cmath>
#include <iostream>

void Hero::takeDMG() {
	health -= 1;
}

Hero::Hero(int currHP, int maxHP)
	: name{ "Player" }, health{ currHP }, max_health{ maxHP }, level{ 1 }, xp{ 0 }, xp_to_lvl{ 10 } {

}

void Hero::create_health_bar(size_t vSize, const float vertices[], size_t iSize, const unsigned int indices[]) {
	healthBar.create_vertices(vSize, vertices);
	healthBar.create_indices(iSize, indices);
}

void Hero::print() {
	{
		std::cout << "Health: " << health << " Max_Health " << max_health << " xp: " 
			<< xp << " xp_to_lvl: " << xp_to_lvl << " level: " << level << std::endl;
	}
}

int Hero::attack(Hero* target) {
	int atk;
	unsigned seed = time(0);
	srand(seed);

	atk = (level * 10);			//add crit later
	return atk;
}

int Hero::get_max_health() {
	return max_health;
}

int Hero::get_health() {
	return health;
}

int Hero::get_xp() {
	return xp;
}

int Hero::get_level() {
	return level;
}

std::string Hero::get_name() {
	return name;
}

void Hero::add_xp(int xp_val) {
	if (xp_to_lvl < xp_val) {
		level += 1;
		xp = abs(xp_val - xp);
		xp_to_lvl += pow(level, 2);
		max_health += pow(level, 2) / 2;
	}
	else {
		xp += xp_val;
	}
}

void Hero::set_myTurn(bool n)
{
	myTurn = n;
}

bool Hero::get_myTurn()
{
	return myTurn;
}

float* Hero::get_health_bar_vertices() {
	return healthBar.get_vertices();
}

unsigned int* Hero::get_health_bar_indices() {
	return healthBar.get_indices();
}
