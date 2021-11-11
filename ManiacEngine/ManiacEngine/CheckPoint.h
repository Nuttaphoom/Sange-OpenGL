#pragma once
#include "GameData.h"
#include "Player.h"

glm::vec3 CheckPoint; 

void Static_LoadCheckPoint() {
	Player::GetInstance("../Resource/Texture/TestNumber.png", 4, 4, PlayerData::GetInstance()->HP, PlayerData::GetInstance()->MoveSpeed, 0); 
	Player::GetInstance()->SetPosition(CheckPoint);
}

static void Static_SetCheckPoint(glm::vec3 newCheckPoint) {
	CheckPoint = newCheckPoint ;
}