#include "GameEngine.h"
#include "Player.h"

GameEngine::GameEngine()
{
	Hero* playerPtr = new Player;
	turnContainer.push_back(playerPtr);
}

GameEngine::~GameEngine()
{
	auto it = turnContainer.begin();

	while (it != turnContainer.end())
	{
		delete (*it);
		it++;
	}
}