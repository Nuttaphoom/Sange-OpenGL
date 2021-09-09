#pragma once
#include "GameStateList.h"

class GameData
{
	static GameData* instance;

public :
	GameState gGameStateInit;
	GameState gGameStateCurr;
	GameState gGameStatePrev;
	GameState gGameStateNext;

	static GameData* GetInstance();
};

