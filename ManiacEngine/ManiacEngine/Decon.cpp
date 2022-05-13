#include "Decon.h"
#include "InvisibleObject.h"
#include "Player.h"
#include "Raycast.h"
#include "GameData.h"
#include "AnimatorManager.h"

bool CanWalkToNextTile(Entity* en) {
	glm::vec3 posTarget =  glm::vec3(en->GetPos().x + 64 * en->DirectionSet ,en->GetPos().y - 64 , en->GetPos().z) ;
	RayCast ray = RayCast(en->GetPos(), posTarget) ;
	glm::vec3 output = ray.GetOutPutPoint();
	if (output.y == posTarget.y) {
		return false ;
	}

	return true;

}
void CreateDeadAnim(Entity* en, string fileName, int row, int col, int howManyFrame, int delayBetweenFrame,float lifespan) {
	vector<SpriteObject*> entities;
	entities.push_back(en);
	entities.push_back(Player::GetInstance());


	glm::vec3 size = Player::GetInstance()->GetSize();
	size.x *= 1.15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1) ;
	size.y *= 1  ;

	glm::vec3 animationPos ;
	animationPos.x = (en->GetPos().x + Player::GetInstance()->GetPos().x) / 2;
	animationPos.y = en->GetPos().y - 10 ;
	 
	AnimatorManager::GetInstance()->CreateAnimationFactory(entities, animationPos, size, lifespan, fileName, row, col, howManyFrame, delayBetweenFrame,ETextureName::DeconDeadAnimationTexture);
 	glm::vec3 movePos; 
	movePos.x = animationPos.x + 15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1);
	movePos.y = Player::GetInstance()->GetPos().y;
	movePos.z = Player::GetInstance()->GetPos().z;

	if (en->GetPos().x < Player::GetInstance()->GetPos().x) {
		Player::GetInstance()->SetDirection(1);
	}
	else if (en->GetPos().x > Player::GetInstance()->GetPos().x)  {
		Player::GetInstance()->SetDirection(-1);
	}

	Player::GetInstance()->ResetVelocity();
 	Player::GetInstance()->SetPosition(movePos);
	Player::GetInstance()->ChangeState(StateMachine::IDLE);


}

Decon::Decon(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(texture, row, column, 100, 80, Pos, Size, glm::vec3(Size.x / 2, Size.y / 2, 0))
{
	DeconState = StateMachine::RUNNING;
	attack_delay = 2.0f;
}

Decon::Decon(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column,100, 80,Pos,Size,glm::vec3(Size.x / 2,Size.y,0))
{
 	DeconState = StateMachine::RUNNING;
	attack_delay = 2.0f; 
} 

void Decon::Attack(Entity* target) {
 	InvisibleObject invWALLs[2];
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (16 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(80, 80);
	}
	for (int i = 0; i < 2; i++) {
		if (invWALLs[i].Collide_W_Entity(*target)) {
 			target->OnDamaged(0);
			break;
		}
	}	

	ChangeState(StateMachine::CHASING); 
}

void Decon::Update(int deltatime) {
	if (IsPause())
		return; 

	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
}

void Decon::EnterAttackZone(Entity* target) {
	////////////
 
	if (GetState() == StateMachine::ATTACKING || GetState() == StateMachine::Die|| target->GetState() == StateMachine::HIDING) 
		return; 
	

	InvisibleObject invWALLs[2];
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (8 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(80, 32);
	}

 
 	for (int i = 0; i < 2; i++) {
		if (invWALLs[i].Collide_W_Entity(*target)) {
 			StartAttack();
		}
		
	}
}

void Decon::StartAttack() {
	ChangeState(StateMachine::ATTACKING) ; 

}

void Decon::UpdateStateMachine(float deltatime)
{
	if (IsPause())
		return;

	if (GetState() == StateMachine::RUNNING)
	{
		if (PlayerDetect(Player::GetInstance()) == true && CanWalkToNextTile(this))
		{
			ChangeState(StateMachine::CHASING);
		}
		else
		{
 			Patrol();
		}
	}
	
	if (GetState() == StateMachine::IDLE)
	{
		ChangeState(StateMachine::RUNNING);
	}
	
	if (GetState() == StateMachine::CHASING) {
		if (PlayerDetect(Player::GetInstance()) == false)
		{
			chasing_delay += deltatime;

			if (! CanWalkToNextTile(this)) {
				ChangeState(StateMachine::RUNNING);
			}
			else {
				PlayerChase(Player::GetInstance());
			}

			if (chasing_delay > 2000) {
				chasing_delay = 0; 
				ChangeState(StateMachine::RUNNING);

			}
		}
		else {
			if (!CanWalkToNextTile(this)) {
				ChangeState(StateMachine::RUNNING);
			}
			chasing_delay = 0; 
			PlayerChase(Player::GetInstance());
		}
	}

	if (GetState() == StateMachine::ATTACKING) {
 		attack_delay += deltatime ;  
		if (attack_delay > 75*8-(14/100)) {
			if (PlayerDetect(Player::GetInstance())) {
				Attack(Player::GetInstance());
				attack_delay = 0;
			}
			else {
				ChangeState(StateMachine::CHASING);
			}
		}
	}
	else {
		EnterAttackZone(Player::GetInstance()); 
	}
}

void Decon::ChangeState(StateMachine nextState)
{
	DeconState = nextState;
	this->velocity = glm::vec3(0, 0, 0);

	if (GetState() == StateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 1, 100);
	}
	else if (GetState() == StateMachine::RUNNING)
	{
		SetAnimationLoop(0, 0, 12, 100);
		MoveSpeed = 80;
	}
	else if (GetState() == StateMachine::CHASING)
	{
		SetAnimationLoop(0, 0, 12, 100);
		MoveSpeed = 160;
	}
	else if (GetState() == StateMachine::ATTACKING) {
		SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/Deacon_Attack.mp3");
 		SetAnimationLoop(1, 0, 9, 60);
	}
	else if (GetState() == StateMachine::Die) {
		SetPause(true) ; 
  		CreateDeadAnim(this, "../Resource/Texture/Enemy/Decon/Decon_Dead_SpriteSheet.png",2,10,19,100,2.0f);
	}
}


StateMachine Decon::GetState() {
	return this->DeconState ; 
}
 

void Decon::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}

 
void Decon::Patrol()
{
	if (PatrolPos.size() == 0) return; 

	glm::vec3 dest = PatrolPos.at(CurrentPatrolPos); 

	if (abs(dest.x - GetPos().x) < 2) CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size(); 

	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1); 

	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void Decon::PlayerChase(Entity* p) {
	if (p->GetPos().x - GetPos().x < -50)
	{
		SetDirection(-1);
		TranslateVelocity(glm::vec3(this->GetMoveSpeed() * -1, 0, 0));
	}
	if (p->GetPos().x - GetPos().x > 50)
	{
		SetDirection(1);
		TranslateVelocity(glm::vec3(this->GetMoveSpeed(), 0, 0));
	}
}