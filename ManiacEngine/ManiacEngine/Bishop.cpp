#include "Bishop.h" 
#include "Player.h"
#include "AnimatorManager.h"
#include "Raycast.h"
void CastingThunder(glm::vec3 posToCast);

void CreateBishopDeadAnim(Entity* en   ) {
	float lifespan = 2.0f; 
	string fileName = "../Resource/Texture/Enemy/Bishop/Bishop_Dead_SpriteSheet.png";
	int row = 2;
	int col = 10;
	int howManyFrame = 19;
	float delayBetweenFrame = 100;
 
	vector<SpriteObject*> entities;
	entities.push_back(en);
	entities.push_back(Player::GetInstance());


	glm::vec3 size = Player::GetInstance()->GetSize();
	size.x *= 1.15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1);
	size.y *= 1;

	glm::vec3 animationPos;
	animationPos.x = (en->GetPos().x + Player::GetInstance()->GetPos().x) / 2;
	animationPos.y = en->GetPos().y - 5;

	AnimatorManager::GetInstance()->CreateAnimationFactory(entities, animationPos, size, lifespan, fileName, row, col, howManyFrame, delayBetweenFrame, ETextureName::BishopDeadAnimationTexture);
	glm::vec3 movePos;
	movePos.x = animationPos.x + 15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1);
	movePos.y = Player::GetInstance()->GetPos().y;
	movePos.z = Player::GetInstance()->GetPos().z;

	if (en->GetPos().x < Player::GetInstance()->GetPos().x) {
		Player::GetInstance()->SetDirection(1);
	}
	else if (en->GetPos().x > Player::GetInstance()->GetPos().x) {
		Player::GetInstance()->SetDirection(-1);
	}

	Player::GetInstance()->ResetVelocity();
	Player::GetInstance()->SetPosition(movePos);
	Player::GetInstance()->ChangeState(StateMachine::IDLE);


}

Bishop::Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 25, Pos, Size, Size) {
	_bishopState = StateMachine::IDLE;
	SetAnimationLoop(1, 8, 8, 100.0f);
	CurrentPatrolPos = 1;
} 

void Bishop::Update(int deltatime) {
	if (IsPause())
		return;
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	 

}
void Bishop::UpdateStateMachine(float deltatime) {
	Player* p = Player::GetInstance();
	if (IsPause() || p->isDead())
		return;

	if (_bishopState == StateMachine::IDLE) {
 		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime() ; 
		SetDirection(1);
		if (_countDownTime >= 5.0f) {
			_countDownTime = 0;
			ChangeState(StateMachine::RUNNING);
		}
	}
	else if (_bishopState == StateMachine::ATTACKING) {
		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		if (_countDownTime >= 0.8f) {
			ChangeState(StateMachine::RUNNING);
			_countDownTime = 0;
		}
		
	}
	else if (_bishopState == StateMachine::RUNNING) {
 
		Patrol(); 
 
	}
	else if (_bishopState == StateMachine::CASTING) {
		_countDownTime += 1.0f / 1000 * GameEngine::GetInstance()->GetDeltaTime();
		if (_countDownTime >= 3.0f) {
			ChangeState(StateMachine::IDLE);
			int randomXPos;
			do {
				randomXPos = rand() % 6 - rand() % 6;
			} while (randomXPos == 0);
			CastingThunder(glm::vec3(Player::GetInstance()->GetPos().x + 64 * randomXPos, GetPos().y + 256 * 1 - -1 * Player::GetInstance()->GetSize().y / 2, 1));
			
			_countDownTime = 0; 
		}
	}

	if (PlayerDetect(p) && _bishopState != StateMachine::ATTACKING && ! isDead() ){
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
	if (target->isDead()) {
		return;
	}
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
	else if (NextState == StateMachine::Die) {
		SetPause(true);
		CreateBishopDeadAnim(this);
	}
 
	_bishopState = NextState;
}

StateMachine  Bishop::GetState() {
	return _bishopState; 
}

void CastingThunder(glm::vec3 posToCast) {
	SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/EnemySounds/Bishop/ThunderSound.mp3");
	AnimatorManager::GetInstance()->CreateAnimationFactory(vector<SpriteObject*>(), posToCast , glm::vec3(128+32, 256 * -2, 1), 2.50f/3.0f , "../Resource/Texture/VisualEffect/Thunder.png"
		, 1, 26, 26, 24, ETextureName::BishopThunder);
}
