#include "GameEngine.h"
#include <cstdlib>
#include <time.h>

int GameEngine::rollNumEnemies() {
	srand(time(NULL));

	if (firstEncounter != 1) {
		return (rand() % 3 + 1);		//random 1 to 3
	}
	else {
		firstEncounter = 0;
		return 1;
	}
}

int GameEngine::getGameState() {
	return gameState;
}

GameEngine::GameEngine()
	: gameState{ 0 }, firstEncounter{ 1 } {}

