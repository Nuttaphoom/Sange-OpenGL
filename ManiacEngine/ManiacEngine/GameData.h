#pragma once
#include "GameStateList.h"
#include "iostream"
using namespace std;
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

class PlayerData {
	static PlayerData* instance; 

	public :
	int HP; 
	int MoveSpeed;
	
	
	PlayerData(int HP, int MoveSpeed);

	static PlayerData* GetInstance();

	void LoadData();

	void SaveData();
};
 

struct EntityDefaultValue {
	int HP = 100 ; 
	float MoveSpeed = 0.18f;  
};


 