#pragma once

#include "GameEngine.h"
#include "GameStateList.h"
#include "GameData.h"
#include "Level.h"
#include "LevelTest.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h" 
#include "LevelCutscenesOne.h"
#include "LevelCutscenesTwo.h"

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

 