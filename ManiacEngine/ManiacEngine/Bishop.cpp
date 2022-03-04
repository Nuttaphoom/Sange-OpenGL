#include "Bishop.h" 
#include "Player.h"

Bishop::Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 0.21f, Pos, Size) {
	_bishopState = StateMachine::IDLE;
} 

void Bishop::Update(int deltatime) {
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	 

}
void Bishop::UpdateStateMachine(float deltatime) {
	if (_bishopState == StateMachine::IDLE) {
		//Count Time until Attack time 
		_countDownTime += 1 *  deltatime;
		std::cout << _countDownTime << endl; 
		if (_countDownTime >= 30) {
			_countDownTime = 0;
			ChangeState(StateMachine::RUNNING); 
		}
	}
	else if (_bishopState == StateMachine::ATTACKING) {
		//CountDelayTime , when delay == 0, turn around and get back to Idle 
		//if in Attack state, do damage to player if they see the player. check every single frame 
		Player* p = Player::GetInstance() ; 
		if (p->GetState() != StateMachine::HIDING)
			Attack(p);
	}
	else if (_bishopState == StateMachine::RUNNING) {
		Patrol(); 
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
		else if (CurrentPatrolPos == 1) { //Get to casting skill position  
			ChangeState(StateMachine::ATTACKING);  
		}

		CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size();

	}
	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1);

	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void Bishop::Attack(Entity* target) {
	if (target->GetState() == StateMachine::HIDING)
		return;  

	target->OnDamaged(10);  
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
}
