 
#include "Priest.h"
#include "Raycast.h"
#include "Player.h"
#include "InvisibleObject.h"
#include "AnimatorManager.h"
#include "GameStateController.h"

void CreatePriestDeadAnim(Entity* en, string fileName, int row, int col, int howManyFrame, int delayBetweenFrame, float lifespan) {
	vector<SpriteObject*> entities;
	entities.push_back(en);
	entities.push_back(Player::GetInstance());


	glm::vec3 size = Player::GetInstance()->GetSize();
	size.x *= 1.15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1);
	size.y *= 1;

	glm::vec3 animationPos;
	animationPos.x = (en->GetPos().x + Player::GetInstance()->GetPos().x) / 2;
	animationPos.y = Player::GetInstance()->GetPos().y  ;

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

Priest::Priest(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size):Enemy(fileName, row, column, 100, 80.0f, Pos, Size) {
	attack_delay = 1.5f;
	ChangeState(StateMachine::IDLE);
	lightBallTexture = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/Enemy/Priest/LightBall.png");
}

void Priest::Attack(Entity* target) {
	glm::vec3 lightBallSpawnPos; 
	lightBallSpawnPos.x = GetPos().x - (GetSize().x / 4 );
	lightBallSpawnPos.y = GetPos().y + (-1 * GetSize().y / 4); 
	PriestLightBall* newBall = new PriestLightBall(lightBallTexture, 1, 4, lightBallSpawnPos, glm::vec3(64, -64, 1), target->GetPos());
	_activePriestLightBalls.push_back(newBall);
	GameStateController::GetInstance()->currentLevel->AddObjectList(newBall);
	ChangeState(StateMachine::ATTACKING);
}

void Priest::EnterAttackZone(Entity* target) {

}

void Priest::Update(int deltatime) {
	if (IsPause())
		return;

	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);

	 
}

void Priest::StartAttack() {

}

void Priest::UpdateStateMachine(float deltatime) {
	if (GetState() == StateMachine::IDLE) {
		if (PlayerDetect(Player::GetInstance())) {
			ChangeState(StateMachine::CASTING);
		}
		else if (PatrolPos.size() > 0 ){
			ChangeState(StateMachine::RUNNING);
		}
	}

	if (GetState() == StateMachine::RUNNING) {
		if (PlayerDetect(Player::GetInstance())) {
			ChangeState(StateMachine::CASTING);

		}
		else {
			Patrol();
		}
	}

	if (GetState() == StateMachine::CASTING) {
		if (PlayerDetect(Player::GetInstance())) {
			attack_cooldown_counter += 1.0f / 1000.0f * deltatime;
			if (attack_cooldown_counter > attack_delay) {
				attack_cooldown_counter = 0;
				Attack(Player::GetInstance());
			}
		}
		else {
			ChangeState(StateMachine::RUNNING);
		}
	}

	if (GetState() == StateMachine::ATTACKING) {
		attack_cooldown_counter += 1.0f / 1000.0f * deltatime;
		if (attack_cooldown_counter > 1.8f) {
			attack_cooldown_counter = 0;
			ChangeState(StateMachine::IDLE);
		}
	}
}

void Priest::ChangeState(StateMachine nextState)
{
	_priestState = nextState;
	this->velocity = glm::vec3(0, 0, 0);

 	if (GetState() == StateMachine::IDLE)
	{
		SetAnimationLoop(1, 0, 5, 100);
	}
	else if (GetState() == StateMachine::RUNNING)
	{
		SetAnimationLoop(2, 0, 12, 100);

	}
	else if (GetState() == StateMachine::CHASING)
	{
		SetAnimationLoop(2, 0, 12, 100);
	}
	else if (GetState() == StateMachine::CASTING) {
		SetAnimationLoop(0, 0, 16, 100);
	}
	else if (GetState() == StateMachine::ATTACKING) {
		SetAnimationLoop(0,12, 30-12, 100);
	}
	else if (GetState() == StateMachine::Die) {
		SetPause(true);
		CreatePriestDeadAnim(this, "../Resource/Texture/Enemy/Priest/Priest_Dead_SpriteSheet.png", 2, 10, 19, 100, 2.1f);
	}
}

bool Priest::PlayerDetect(Entity* p) {
	Player::GetInstance()->RemoveDetectingEntity(this);
	if (p->GetState() == StateMachine::HIDING)
		return false;



	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);
 	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false;
	//cout << "ResultVec : " << resultVec.x << "," << resultVec.y << endl;
	//cout << "Distance between Player and this enemy : " << Distance.x << "," << Distance.y << endl; 

	if (Distance.x < 640 && Distance.y < 320) {
		glm::vec3 resultPoint = RayCast(this->GetPos(), p->GetPos()).GetOutPutPoint();
		if (abs(resultPoint.x - p->GetPos().x) < 1.0f && abs(resultPoint.y - p->GetPos().y) < 1.0f) {
			Player::GetInstance()->AddDetectingEntity(this);
			return true;
		}
	}


	//cout << "DON'T SEE PLAYER" << endl;
	return false;
}

void Priest::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}

void Priest::Patrol() {
	if (PatrolPos.size() == 0) return;

	glm::vec3 dest = PatrolPos.at(CurrentPatrolPos);

	if (abs(dest.x - GetPos().x) < 2) CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size();

	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1);

	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void  Priest::PlayerChase(Entity* p) {

}

StateMachine Priest::GetState() { return _priestState; }


void Priest::Render(glm::mat4 globalModelTransform)
{
	Entity::Render(globalModelTransform);
 

}

PriestLightBall::PriestLightBall(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size,glm::vec3 Destination ) :Entity(texture, row, column,100000,500 ,Pos, Size) {
	RayCast* ray = new RayCast(Pos, Destination);
 	_destination = ray->GetOutPutPointWithoutBound();
 
	glm::vec3 movingVelocity = _destination - Pos ;
	stateMachine = StateMachine::TRANSFORM;  
	SetAnimationLoop(1, 1, 4, 500);
	TranslateVelocity(glm::normalize(movingVelocity) * GetMoveSpeed()  );

}

void PriestLightBall::Update(int deltaTime) {
	if (IsPause())  
		return; 

 
	Entity::Update(deltaTime) ;
 	
 
	Entity* player = Player::GetInstance();
	InvisibleObject* invisibleObject = new InvisibleObject(); 
	invisibleObject->SetPosition(GetPos()); 
	invisibleObject->SetSize(GetSize().x / 2.0f,GetSize().y * -1 / 2.0f) ; 

 	if (invisibleObject->Collide_W_Entity(*player)) {
		SetPause(true);
		player->OnDamaged(1);
	}
	else if (abs(GetPos() - _destination).x <= 30 && abs(GetPos() - _destination).y <= 30) {
		SetPause(true);
	}

	delete invisibleObject;

	 
 }


