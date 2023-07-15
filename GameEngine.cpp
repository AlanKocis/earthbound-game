#include "GameEngine.h"
#include "Enemy.h"
#include "Player.h"

void GameEngine::initiate_stage(int stage)
{
	if (stage != 1 && stage != 0)
	{
		auto it = turnContainer.begin() + 1; // pls dont delete player object so + 1
		while (it != turnContainer.end())
		{
			delete (*it);
			it++;
		}

		it = turnContainer.begin() + 1;
		while (turnContainer.size() >= 2)
		{
			turnContainer.pop_back();
		}
	}
	//else { stage = 3; }	//TEST

	int numEnemies = 1;

	if (stage >= 2) { numEnemies = 2; }
	else if (stage >= 4) { numEnemies = 3; }



	Hero* p_array[3]{};

	for (int i = 0; i < numEnemies; i++)
	{
		p_array[i] = new Enemy(1);	// i + 1 will be enemy level - starts at 1 goes to 4 possible this is RETARDED
		p_array[i]->take_dmg(stage);	//testing phase change
		turnContainer.push_back(p_array[i]);	// OK -- numEnemies only possible to go to 3,  i only goes to 2
	}


}

GameEngine::GameEngine()
	: stage{ 0 }
{
	turnContainer.reserve(4);		//EXTREMELY IMPORTANT -- std::iterators become useless after push_back() unless you reserve memory first.
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