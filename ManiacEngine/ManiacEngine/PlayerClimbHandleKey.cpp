#include "PlayerClimbHandleKey.h"
#include "Player.h"

void PlayerClimbHandleKey::PlayerClimbControl(char key) {
	switch (key)
	{
		case 'w':
			Player::GetInstance()->TranslateVelocity(glm::vec3(0, Player::GetInstance()->GetClimbSpeed(), 0));
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
	}
}