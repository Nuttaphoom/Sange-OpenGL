#include "Decon.h"
#include "InvisibleObject.h"
#include "Player.h"
#include "Raycast.h"
#include "GameData.h"


Decon::Decon(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 PatrolPos1, glm::vec3 PatrolPos2) :Enemy(fileName, row, column,100, 0.18f,Pos,Size,PatrolPos1,PatrolPos2)
{
 	DeconState = EnemyStateMachine::WALKING; 
	PatrolPos.push_back(PatrolPos1); 
	PatrolPos.push_back(PatrolPos2); 
} 

void Decon::Attack(Entity* target) {

	InvisibleObject invWALLs[2];
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (8 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(64, 64);
	}
	for (int i = 0; i < 2; i++) {
		if (invWALLs[i].Collide_W_Entity(*target)) {
			cout << "ATTACK!" << endl;
			target->OnDamaged(1);
			return; 
		}
	}	

	ChangeState(EnemyStateMachine::CHASING); 
}

void Decon::Update(int deltatime) {
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	cout << "Decon is " << GetPos().x << "," << GetPos().y << endl; 
}

void Decon::EnterAttackZone(Entity* target) {
	if (GetState() == EnemyStateMachine::ATTACKING) return; 

	InvisibleObject invWALLs[2];
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (8 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(64, 64);
	}

 
 	for (int i = 0; i < 2; i++) {
		if (invWALLs[i].Collide_W_Entity(*target)) {
			cout << "start attacking" << endl;
			StartAttack();
		}
		
	}
}

void Decon::StartAttack() {
	ChangeState(EnemyStateMachine::ATTACKING) ; 
}

void Decon::UpdateStateMachine(float deltatime)
{
	if (GetState() == EnemyStateMachine::WALKING)
	{
		if (PlayerDetect(Player::GetInstance()) == true)
		{
			ChangeState(EnemyStateMachine::CHASING);
		}
		else
		{
 			Patrol();
		}


	}
	
	if (GetState() == EnemyStateMachine::IDLE)
	{
		if (GetVelocity().x != 0)
		{
			ChangeState(EnemyStateMachine::WALKING);
			//cout << "WALKING" << endl;
		}
	}
	
	if (GetState() == EnemyStateMachine::CHASING) {
		if (PlayerDetect(Player::GetInstance()) == false)
		{
			chasing_delay += deltatime;
			if (chasing_delay > 2000) {
				chasing_delay = 0; 
				ChangeState(EnemyStateMachine::WALKING);
			}
			PlayerChase(Player::GetInstance());
		}
		else {
			chasing_delay = 0; 
			PlayerChase(Player::GetInstance());
		}
	}

	if (GetState() == EnemyStateMachine::ATTACKING) {
		cout << "attacking" << endl; 
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

void Decon::ChangeState(EnemyStateMachine nextState)
{
	DeconState = nextState;
	this->velocity = glm::vec3(0, 0, 0);

	if (GetState() == EnemyStateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 1, 100);
	}
	else if (GetState() == EnemyStateMachine::WALKING)
	{
		SetAnimationLoop(0, 0, 12, 100);
	}
	else if (GetState() == EnemyStateMachine::CHASING)
	{
		SetAnimationLoop(0, 0, 12, 100);
	}
	else if (GetState() == EnemyStateMachine::ATTACKING) {
 		SetAnimationLoop(1, 0, 9, 75);
	}
}
 
EnemyStateMachine Decon::GetState() {
	return this->DeconState ; 
}

bool Decon::PlayerDetect(Entity* p)
{
	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false;


	if (Distance.x < 300 && Distance.y < 100) {
		glm::vec3 resultVec = RayCast(this->GetPos(), p->GetPos()); 

		//cout << "ResultVec : " << resultVec.x << "," << resultVec.y << endl;
		//cout << "Distance between Player and this enemy : " << Distance.x << "," << Distance.y << endl; 

		if (abs(resultVec.x - abs(Distance.x)) < 0.1f && abs(resultVec.y - abs(Distance.y)) < 0.1f) {
			//	cout << "SEE PLAYER" << endl; 
			return true;
		}
	}


	//cout << "DON'T SEE PLAYER" << endl;
	return false;

	/*
	glm::vec3 Distance = glm::vec3(GetPos().x - p->GetPos().x, GetPos().y - p->GetPos().y, 0);
	if (Distance.x < 300 && Distance.y < 100)
	{
		if (p->GetPos().x <= GetPos().x && DirectionSet == -1)
		{
			return true;
		}
		if (p->GetPos().x >= GetPos().x && DirectionSet == 1)
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}*/
}

void Decon::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}

void Decon::Patrol()
{
	glm::vec3 dest = PatrolPos.at(CurrentPatrolPos); 

	if (abs(dest.x - GetPos().x) < 2) CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size(); 

	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1); 

	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));


 
}