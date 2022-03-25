#include "PlayerHandleKey.h"
#include "Player.h"
#include "PlayerClimbHandleKey.h"

void PlayerHandleKey::PlayerControl(char key) {
	switch (key)
	{
		case 'w':
			if (Player::GetInstance()->OnGround == true && Player::GetInstance()->GetState() != StateMachine::JUMPPING) {
				cout << "here" << endl;
				Player::GetInstance()->TranslateVelocity(glm::vec3(0, Player::GetInstance()->GetJump(), 0));
				Player::GetInstance()->OnGround = false;
				Player::GetInstance()->ChangeState(StateMachine::JUMPPING);
			}
			break;
		case 's':
			break;
		case 'a':
			Player::GetInstance()->TranslateVelocity(glm::vec3(Player::GetInstance()->GetMoveSpeed() * -1, 0, 0)); Player::GetInstance()->SetDirection(-1);
			break;
		case 'd':
			Player::GetInstance()->TranslateVelocity(glm::vec3(Player::GetInstance()->GetMoveSpeed(), 0, 0)); Player::GetInstance()->SetDirection(1);
			break;
		case 'e' :
			Player::GetInstance()->SetClimbing();
			break;
	}
}

void PlayerHandleKey::PlayerStateCheck(char key) {
	if (Player::GetInstance()->GetState() != StateMachine::CLIMBING && Player::GetInstance()->GetState() != StateMachine::CLIFFEDGE && Player::GetInstance()->GetState() != StateMachine::CLIFFEDGEDOWN)
	{
		PlayerControl(key);
	}
	else if (Player::GetInstance()->GetState() == StateMachine::CLIMBING) {
		PlayerClimbHandleKey i;
		i.PlayerClimbControl(key);
	}
}