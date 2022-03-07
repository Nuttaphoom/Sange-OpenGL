#pragma once
#include <string>

using namespace std;

class EntityData
{
	private:
		float _playerMoveSpeed;
		float _playerJumpHeight;
		float _playerHp;

	public:
		void Read();
		float GetPlayerMoveSpeed();
		float GetPlayerJumpHeight();
		float GetPlayerHP();
};