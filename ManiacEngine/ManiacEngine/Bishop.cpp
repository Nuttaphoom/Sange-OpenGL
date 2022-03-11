#include "Bishop.h" 
#include "Player.h"
#include "AnimatorManager.h"
void CastingThunder(glm::vec3 posToCast);


Bishop::Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 0.21f, Pos, Size) {
	MoveSpeed = 100;
	_bishopState = StateMachine::IDLE;
} 

void Bishop::Update(int deltatime) {
	if (IsPause())
		return;

	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	 

}
void Bishop::UpdateStateMachine(float deltatime) {
	Player* p = Player::GetInstance();

	if (_bishopState == StateMachine::IDLE) {
		//Count Time until Attack time 
		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime() ; 
 
		if (PlayerDetect(p)) {
			Attack(p);
 		}

		else if (_countDownTime >= 1.5f) {
			_countDownTime = 0;
			ChangeState(StateMachine::RUNNING);
		}
	}
	else if (_bishopState == StateMachine::ATTACKING) {
		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		if (_countDownTime >= 3) {
			ChangeState(StateMachine::RUNNING);
			_countDownTime = 0;
		}
		
	}
	else if (_bishopState == StateMachine::RUNNING) {
		Patrol(); 
		if (PlayerDetect(p)) {
			Attack(p);
 		}
	}
	else if (_bishopState == StateMachine::CASTING) {
		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		
		if (PlayerDetect(p)) {
			Attack(p);
		}

		if (_countDownTime >= 5) {
			ChangeState(StateMachine::RUNNING);
			_countDownTime = 0; 
		}
	}
}

void Bishop::PlayerChase(Entity* p) {

}
void Bishop::Patrol() {
	if (PatrolPos.size() == 0) return;

	glm::vec3 dest = PatrolPos.at(CurrentPatrolPos);

	if (abs(dest.x - GetPos().x) < 2) {
		if (CurrentPatrolPos == 0) { // Get back to right side 
			ChangeState(StateMachine::IDLE);
		}
		else if (CurrentPatrolPos == 1) { //Get to left skill position  
			ChangeState(StateMachine::CASTING);  
		}

		CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size();

	}
	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1);

	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void Bishop::Attack(Entity* target) {
 
	CastingThunder(glm::vec3(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y + 256 * 1 - -1 * Player::GetInstance()->GetSize().y / 2, 1));
	ChangeState(StateMachine::ATTACKING); 
 	//target->OnDamaged(10);  
}
void Bishop::ChangeState(StateMachine NextState) {
	if (_bishopState == StateMachine::IDLE) {
		_bishopState = NextState;

	}
	else if (_bishopState == StateMachine::ATTACKING) {
		_bishopState = NextState;

	}
	else if (_bishopState == StateMachine::RUNNING) {
		_bishopState = NextState;

	}
	else if (_bishopState == StateMachine::CASTING) {
		int randomXPos;
		do {
			randomXPos = rand() % 4 - rand() % 4;
		} while (randomXPos == 0);
		CastingThunder(glm::vec3(Player::GetInstance()->GetPos().x + 64 * randomXPos, Player::GetInstance()->GetPos().y + 256 * 1 - -1 * Player::GetInstance()->GetSize().y / 2, 1));
		_bishopState = NextState;
	}
}

void CastingThunder(glm::vec3 posToCast) {
	AnimatorManager::GetInstance()->CreateAnimationFactory(vector<SpriteObject*>(), posToCast , glm::vec3(128, 256 * -2, 1), 1, "../Resource/Texture/VisualEffect/Thunder.png"
		, 1, 8, 8, 50);
}
