#pragma once
#include "Hero.h"
#include <vector>

class GameEngine
{
protected:
	std::vector<Hero*> turnContainer;
	int stage = 0;
public:
	void initiate_stage(int stage);
	GameEngine();
	virtual ~GameEngine();
	const std::vector<Hero*> & getContainer() { return turnContainer; }
	inline void next_stage() { stage++;  }
	inline int get_stage() { return stage; }

};
