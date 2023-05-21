#pragma once
class GameEngine
{
private:
	int gameState;
	int combatTurn;
	bool firstEncounter;

public:
	GameEngine();
	int getGameState();
	void setGameState(int n);
	int rollNumEnemies();

};

