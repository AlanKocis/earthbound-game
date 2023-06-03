#pragma once
#include <string>
#include "HealthBar.h"
class Hero
{
private:
	HealthBar healthBar;
	std::string name;
	int health;
	int max_health;
	int xp;
	int xp_to_lvl;
	int level;
	bool myTurn;


public:
	void takeDMG();
	void create_health_bar(size_t vSize, const float vertices[], size_t iSize, const unsigned int indices[]);
	float* get_health_bar_vertices();
	unsigned int* get_health_bar_indices();
	int attack(Hero* target);
	std::string get_name();                                                                                              
	void print();
	int get_max_health();
	int get_health();
	int get_xp();
	int get_level();
	void add_xp(int xp_val);
	void set_myTurn(bool n);
	bool get_myTurn();
	Hero(int currHP, int maxHP);
};

