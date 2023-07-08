#include "GameEngine.h"
#include "Enemy.h"
#include "Player.h"

void GameEngine::initiate_stage(int stage)
{
	this->stage += 1;

	if (stage != 1)
	{
		auto it = turnContainer.begin() + 1; // pls dont delete player object so + 1
		while (it != turnContainer.end())
		{
			delete (*it);
			it++;
		}
	}

	int numEnemies = 1;

	if (stage > 2) { numEnemies = 2; }
	if (stage > 4) { numEnemies = 3; }



	Hero* p_array[3];

	for (int i = 0; i < numEnemies; i++)
	{
		p_array[i] = new Enemy(i + 1);	// i + 1 will be enemy level - starts at 1 goes to 4 possible
		turnContainer.push_back(p_array[i]);	// OK -- numEnemies only possible to go to 3,  i only goes to 2
	}

}

GameEngine::GameEngine()
{
	turnContainer.reserve(4);
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