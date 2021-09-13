#include "GameData.h"

GameData* GameData::instance = nullptr;

GameData * GameData::GetInstance()
{
	if (instance == nullptr) {
		instance = new GameData();
	}
	return instance;
}