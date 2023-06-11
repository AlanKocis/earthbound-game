#include "GameEngine.h"
#include <cstdlib>
#include <time.h>

int GameEngine::rollNumEnemies() {
	srand(time(NULL));

	// first encounter should only have 1 enemy
	if (firstEncounter == false) {
		return (rand() % 3 + 1);		//random 1 to 3
	}
	else {
		firstEncounter = false;
		return 1;
	}
}

int GameEngine::getGameState() {
	return gameState;
}

void GameEngine::setGameState(int n) {
	gameState = n;
}

GameEngine::GameEngine()
	: gameState{ 0 }, firstEncounter{ 1 }, currMobs{nullptr, nullptr, nullptr, nullptr} {}

Hero** GameEngine::get_currMobs_head()
{
	return currMobs;
}