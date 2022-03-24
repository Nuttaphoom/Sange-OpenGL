#pragma once
#include "HandleKey.h"

class PlayerHandleKey :  HandleKey
{
	public:
		void PlayerControl(char key);
		void PlayerStateCheck(char key);
};