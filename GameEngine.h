#pragma once
#include "Hero.h"
class GameEngine
{
private:
	Hero* currMobs[4];
	int gameState;
	bool firstEncounter;

public:
	GameEngine();
	int getGameState();
	void setGameState(int n);
	int rollNumEnemies();
	Hero** get_currMobs_head();

};

