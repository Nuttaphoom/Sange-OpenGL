#include "GameData.h"

GameData* GameData::instance = nullptr;
PlayerData* PlayerData::instance = nullptr;

GameData * GameData::GetInstance()
{
	if (instance == nullptr) {
		instance = new GameData();
	}
	return instance;
}

PlayerData::PlayerData(int HP, int MoveSpeed) {
	this->HP = HP;
	this->MoveSpeed = MoveSpeed;
}

PlayerData* PlayerData::GetInstance() {
	if (instance == nullptr) {
		instance = new PlayerData(1, 1);
	}
	return instance;
}

void PlayerData::LoadData() {
	while (true) {
		cout << "ERROR -- LoadData haven't been implemented yet" << endl;
		cout << "Check on GameData.h" << endl;
	}
}

void PlayerData::SaveData() {
	while (true) {
		cout << "ERROR -- SaveData haven't been implemented yet" << endl;
		cout << "Check on GameData.h" << endl;
	}
}