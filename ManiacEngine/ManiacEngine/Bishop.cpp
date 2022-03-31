#include "Bishop.h" 
#include "Player.h"
#include "AnimatorManager.h"
#include "Raycast.h"
void CastingThunder(glm::vec3 posToCast);


Bishop::Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 0.21f, Pos, Size) {
	MoveSpeed = 25;
	_bishopState = StateMachine::IDLE;
	SetAnimationLoop(1, 8, 8, 100.0f);
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
		//cout << "Bishop is in idle" << endl;


		if (_countDownTime >= 3.0f) {
			_countDownTime = 0;
			ChangeState(StateMachine::RUNNING);
		}
	}
	else if (_bishopState == StateMachine::ATTACKING) {
		//cout << "Bishop is in Attacking" << endl;

		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		if (_countDownTime >= 1.0f) {
			ChangeState(StateMachine::RUNNING);
			_countDownTime = 0;
		}
		
	}
	else if (_bishopState == StateMachine::RUNNING) {
		//cout << "Bishop is in Running" << endl;

		Patrol(); 
 
	}
	else if (_bishopState == StateMachine::CASTING) {
		//cout << "Bishop is in Casting" << endl;

		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		

		if (_countDownTime >= 5) {
			ChangeState(StateMachine::RUNNING);
			_countDownTime = 0; 
		}
	}

	if (PlayerDetect(p) && _bishopState != StateMachine::ATTACKING) {
		Attack(p);
	}
}

void Bishop::PlayerChase(Entity* p) {

}

bool Bishop::PlayerDetect(Entity* p)
{
	Player::GetInstance()->RemoveDetectingEntity(this);
	if (p->GetState() == StateMachine::HIDING)
		return false;



	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false;
	//cout << "ResultVec : " << resultVec.x << "," << resultVec.y << endl;
	//cout << "Distance between Player and this enemy : " << Distance.x << "," << Distance.y << endl; 

	if (Distance.x < 1800 && Distance.y < 100) {
		glm::vec3 resultVec = RayCast(this->GetPos(), p->GetPos()).GetOutPutRayCast();
		if (abs(resultVec.x - abs(Distance.x)) < 0.1f && abs(resultVec.y - abs(Distance.y)) < 0.1f) {
			Player::GetInstance()->AddDetectingEntity(this);
			return true;
		}
	}


	//cout << "DON'T SEE PLAYER" << endl;
	return false;

}
void Bishop::Patrol() {
	if (PatrolPos.size() == 0) return;

	glm::vec3 dest = PatrolPos.at(CurrentPatrolPos);


	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1);

	if (abs(dest.x - GetPos().x) < 2.0f) {
		if (CurrentPatrolPos == 0) { // Get back to right side 
			SetDirection(1);
			ChangeState(StateMachine::IDLE);
		}
		else if (CurrentPatrolPos == 1) { //Get to left skill position 
			SetDirection(-1);
			ChangeState(StateMachine::CASTING);
		}

		CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size();
	}
	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void Bishop::Attack(Entity* target) {
	ChangeState(StateMachine::ATTACKING);
	CastingThunder(glm::vec3(Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y + 256 * 1 - -1 * Player::GetInstance()->GetSize().y / 2, 1));
 	//target->OnDamaged(10);  
}
void Bishop::ChangeState(StateMachine NextState) {
	_countDownTime = 0;

	if (NextState == StateMachine::IDLE) 
		SetAnimationLoop(0, 0, 1, 100.0f);
	else if (NextState == StateMachine::ATTACKING) {
		SetAnimationLoop(1, 0, 6, 150.0f);
	}
	else if (NextState == StateMachine::CASTING)
	{
		SetAnimationLoop(0, 3, 6, 150.0f);
	}

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
	cout << "THUNDER WAS CASTED" << endl;
	AnimatorManager::GetInstance()->CreateAnimationFactory(vector<SpriteObject*>(), posToCast , glm::vec3(128, 256 * -2, 1), 0.5f, "../Resource/Texture/VisualEffect/Thunder.png"
		, 1, 8, 8, 50);
}
