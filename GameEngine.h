#pragma once
class GameEngine
{
private:
	int gameState;
	bool firstEncounter;

public:
	GameEngine();
	int getGameState();
	int rollNumEnemies();

};

