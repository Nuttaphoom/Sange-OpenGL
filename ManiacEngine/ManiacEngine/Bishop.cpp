#include "Bishop.h" 
#include "Player.h"
#include "AnimatorManager.h"
#include "Raycast.h"
void CastingThunder(glm::vec3 posToCast);


Bishop::Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 25, Pos, Size, Size) {
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
 		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime() ; 
		if (_countDownTime >= 5.0f) {
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
 
		Patrol(); 
 
	}
	else if (_bishopState == StateMachine::CASTING) {
		//cout << "Bishop is in Casting" << endl;

		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		

		if (_countDownTime >= 3.0f) {
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
	if (p->GetState() == StateMachine::HIDING || p->_inv == true)
		return false;



	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false;

	if (Distance.x < 1800 && Distance.y < 100) {
		RayCast* ray = new RayCast(GetPos()  , p->GetPos()) ;
		glm::vec3 resultVec = ray->GetOutPutPoint() ;  
		
		if (resultVec.x == p->GetPos().x && resultVec.y == p->GetPos().y) {
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
		else if (CurrentPatrolPos == 1) { //Get to left skill position ddddd
			SetDirection(-1);
			ChangeState(StateMachine::CASTING);
		}

		CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size();
	}
	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void Bishop::Attack(Entity* target) {
	ChangeState(StateMachine::ATTACKING);
	CastingThunder(glm::vec3(Player::GetInstance()->GetPos().x, GetPos().y + 256 * 1 - -1 * Player::GetInstance()->GetSize().y / 2, 1));
 	target->OnDamaged(100);  
}
void Bishop::ChangeState(StateMachine NextState) {
	_countDownTime = 0;

	if (NextState == StateMachine::IDLE) {
		SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/EnemySounds/Bishop/Speaking.mp3");
		SetAnimationLoop(0, 0, 1, 100.0f);
	}
	else if (NextState == StateMachine::ATTACKING) {
		SetAnimationLoop(1, 0, 6, 150.0f);
	}
	else if (NextState == StateMachine::CASTING)
	{
		SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/EnemySounds/Bishop/Casting.mp3");
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
			randomXPos = rand() % 6 - rand() % 6;
		} while (randomXPos == 0);
		CastingThunder(glm::vec3(Player::GetInstance()->GetPos().x + 64 * randomXPos, GetPos().y + 256 * 1 - -1 * Player::GetInstance()->GetSize().y / 2, 1));
		_bishopState = NextState;
	}
}

StateMachine  Bishop::GetState() {
	return _bishopState; 
}
void CastingThunder(glm::vec3 posToCast) {
	SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/EnemySounds/Bishop/ThunderSound.mp3");

	AnimatorManager::GetInstance()->CreateAnimationFactory(vector<SpriteObject*>(), posToCast , glm::vec3(128+32, 256 * -2, 1), 36.0f * 25.0f / 1000.0f, "../Resource/Texture/VisualEffect/Thunder.png"
		, 1, 26, 26, 25, ETextureName::BishopThunder);
}
