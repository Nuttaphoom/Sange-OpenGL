#pragma once

#include "GameEngine.h"
#ifndef GameStateControllerHEADER 
#define GameStateControllerHEADER
#include "GameStateList.h"
#include "GameData.h"
#include "Level.h"
#include "LevelTest.h"
#include "Level3.h"

using namespace std;
class GameStateController
{

private :
	static GameStateController* instance;
protected :
	GameStateController();
public:
	Level* currentLevel;
	static GameStateController* GetInstance();
	void Init(GameState gameStateInit);
	void Update();
};

#endif 