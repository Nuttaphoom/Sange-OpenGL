#include "PlayerClimbHandleKey.h"
#include "Player.h"

void PlayerClimbHandleKey::PlayerClimbControl(char key) {
	Player* player = Player::GetInstance();
	switch (key)
	{
		case 'w':
			if (Player::GetInstance()->GetBlock() != true) {
				Player::GetInstance()->TranslateVelocity(glm::vec3(0, Player::GetInstance()->GetClimbSpeed(), 0));
			}
			break;
		case 's':
			if (Player::GetInstance()->OnGround != true){
					Player::GetInstance()->TranslateVelocity(glm::vec3(0, Player::GetInstance()->GetClimbSpeed() * -1, 0));
			}
			break;
		case 'a':
			if (Player::GetInstance()->GetDirection() == 1) {
				Player::GetInstance()->ChangeState(StateMachine::FALLING);
			}
			break;
		case 'd':
			if (Player::GetInstance()->GetDirection() == -1) {
				Player::GetInstance()->ChangeState(StateMachine::FALLING);
			}
			break;
		case '1':
			player->BatChange(true);
			player->SetBat();
			break;
	}
}