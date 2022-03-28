#include "PlayerHandleKey.h"
#include "Player.h"
#include "PlayerClimbHandleKey.h"
#include "GameEngine.h"

void PlayerHandleKey::PlayerControl(char key) {

	Player* player = Player::GetInstance(); 
	switch (key)
	{
		case 'w':
			if (player->OnGround == true && player->GetState() != StateMachine::JUMPPING) {
				cout << "apply jump force : " << GameEngine::GetInstance()->GetDeltaTime() << endl ;
				player->OnGround = false;
				player->TranslateVelocity(glm::vec3(0, player->GetJump(), 0));
				player->ChangeState(StateMachine::JUMPPING);
			}
			break;
		case 's':
			break;
		case 'a':
			player->TranslateVelocity(glm::vec3(player->GetMoveSpeed() * -1, 0, 0)); player->SetDirection(-1);
			break;
		case 'd':
			player->TranslateVelocity(glm::vec3(player->GetMoveSpeed(), 0, 0)); player->SetDirection(1);
			break;
		case 'e' :
			player->SetClimbing();
			break;

		case 'A' :
			player->SetVelocity(glm::vec3(0, Player::GetInstance()->GetVelocity().y, 0));
		case 'D' :
			player->SetVelocity(glm::vec3(0, Player::GetInstance()->GetVelocity().y, 0));
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