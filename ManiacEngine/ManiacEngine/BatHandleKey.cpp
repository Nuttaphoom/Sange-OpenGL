#include "BatHandleKey.h"
#include "Player.h"

void BatHandleKey::BatControl(char key)
{
	Player* player = Player::GetInstance();
	switch (key)
	{
		case 'w':
			player->TranslateVelocity(glm::vec3(0, 10, 0));
			break;
		case 's':
			if (player->OnGround == false) 
				player->TranslateVelocity(glm::vec3(0, -10, 0));
			break;
		case 'a':
			player->TranslateVelocity(glm::vec3(-250, 0, 0));
			player->SetDirection(-1);
			break;
		case 'd':
			player->TranslateVelocity(glm::vec3(250, 0, 0));
			player->SetDirection(1);
			break;
		case 'W':
			break;
		case 'S':
			break;
		case 'A':
			player->TranslateVelocity(glm::vec3(250, 0, 0));
			break;
		case 'D':
			player->TranslateVelocity(glm::vec3(-250, 0, 0));
	}
}