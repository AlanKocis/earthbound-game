#pragma once
#include "Hero.h"
#include <vector>

class GameEngine
{
protected:
	std::vector<Hero*> turnContainer;
	int stage;
public:
	GameEngine();
	virtual ~GameEngine();
	inline std::vector<Hero*> getContainer() { return turnContainer; }

};
