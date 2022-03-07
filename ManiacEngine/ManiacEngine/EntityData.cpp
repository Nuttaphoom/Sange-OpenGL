#include "EntityData.h"
#include <fstream>

void EntityData::Read() {
	ifstream EntityDataFile("../Resource/Entity/EntityData.txt");
	if (EntityDataFile.is_open()) {
		EntityDataFile >> _playerMoveSpeed;
		EntityDataFile >> _playerJumpHeight;
		EntityDataFile >> _playerHp;
		
		EntityDataFile.close();
	}
}

float EntityData::GetPlayerMoveSpeed() {
	return _playerMoveSpeed;
}

float EntityData::GetPlayerJumpHeight() {
	return _playerJumpHeight;
}

float EntityData::GetPlayerHP() {
	return _playerHp;
}