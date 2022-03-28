#include "Decon.h"
#include "InvisibleObject.h"
#include "Player.h"
#include "Raycast.h"
#include "GameData.h"


Decon::Decon(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column,100, 80,Pos,Size)
{
 	DeconState = StateMachine::RUNNING;
 
} 

void Decon::Attack(Entity* target) {

 	InvisibleObject invWALLs[2];
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (16 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(64, 64);
	}
	for (int i = 0; i < 2; i++) {
		if (invWALLs[i].Collide_W_Entity(*target)) {
 			target->OnDamaged(1);
			return; 
		}
	}	

	ChangeState(StateMachine::CHASING); 
}

void Decon::Update(int deltatime) {
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	//cout << "Decon is " << GetPos().x << "," << GetPos().y << endl; 
}

void Decon::EnterAttackZone(Entity* target) {
	////////////
	if (GetState() == StateMachine::ATTACKING || target->GetState() == StateMachine::HIDING) return; 
	

	InvisibleObject invWALLs[2];
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (8 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(64, 64);
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
	if (GetState() == StateMachine::RUNNING)
	{
		if (PlayerDetect(Player::GetInstance()) == true)
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
		if (GetVelocity().x != 0)
		{
			ChangeState(StateMachine::RUNNING);
			//cout << "WALKING" << endl;
		}
	}
	
	if (GetState() == StateMachine::CHASING) {
		if (PlayerDetect(Player::GetInstance()) == false)
		{
			chasing_delay += deltatime;
			if (chasing_delay > 2000) {
				chasing_delay = 0; 
				ChangeState(StateMachine::RUNNING);
			}
			PlayerChase(Player::GetInstance());
		}
		else {
			chasing_delay = 0; 
			PlayerChase(Player::GetInstance());
		}
	}

	if (GetState() == StateMachine::ATTACKING) {
 		attack_delay += deltatime ;  
		if (attack_delay > 75*8) {
 			Attack(Player::GetInstance()); 
			attack_delay = 0;
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
	}
	else if (GetState() == StateMachine::CHASING)
	{
		SetAnimationLoop(0, 0, 12, 100);
	}
	else if (GetState() == StateMachine::ATTACKING) {
 		SetAnimationLoop(1, 0, 9, 75);
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