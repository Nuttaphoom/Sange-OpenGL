#include "Enemy.h"
#include "Player.h"
#include "Raycast.h"
Enemy::Enemy(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame, glm::vec3 PatrolPos1, glm::vec3 PatrolPos2 ) : Entity(fileName, row, column, HP, MoveSpeed, IFrame)
{
	EnemyState = EnemyStateMachine::WALKING;
 	AddPatrolPos(PatrolPos1);
	AddPatrolPos(PatrolPos2);
}

EnemyStateMachine Enemy::GetState()
{
	return EnemyState;
}

void Enemy::Attack(Entity* target) {

}

void Enemy::Translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

void Enemy::Update(int deltatime)
{
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
  
}

void Enemy::UpdateStateMachine(float deltatime)
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
	else if (GetState() == EnemyStateMachine::IDLE)
	{
		if (GetVelocity().x != 0)
		{
			ChangeState(EnemyStateMachine::WALKING);
			//cout << "WALKING" << endl;
		}
	}
	else if (GetState() == EnemyStateMachine::CHASING) {
		if (PlayerDetect(Player::GetInstance()) == false)
		{
			ChangeState(EnemyStateMachine::WALKING);
		}
		else {
			PlayerChase(Player::GetInstance());
		}
	}
}

void Enemy::ChangeState(EnemyStateMachine nextState)
{
	EnemyState = nextState;
	this->velocity = glm::vec3(0, 0, 0); 

	if (GetState() == EnemyStateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 1, 100);
	}
	else if (GetState() == EnemyStateMachine::WALKING)
	{
		SetAnimationLoop(0, 0, 12, 100);
	}
}

bool Enemy::PlayerDetect(Entity* p)
{
	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false; 
	//cout << "ResultVec : " << resultVec.x << "," << resultVec.y << endl;
	//cout << "Distance between Player and this enemy : " << Distance.x << "," << Distance.y << endl; 

	if (Distance.x < 300 && Distance.y < 100) {
		glm::vec3 resultVec = RayCast(this->GetPos(), p->GetPos());
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

void Enemy::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}

void Enemy::Patrol()
{
	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
	if (GetPos().x >= PatrolPos.at(0).x)
	{
		SetDirection(-1);
	}
	if (GetPos().x <= PatrolPos.at(1).x)
	{
		SetDirection(1);
	}
}

void Enemy::PlayerChase(Entity* p)
{
 	if (p->GetPos().x - GetPos().x < 0)
	{
		TranslateVelocity(glm::vec3(this->GetMoveSpeed() * -1, 0, 0));
	}
	if (p->GetPos().x - GetPos().x > 0)
	{
		TranslateVelocity(glm::vec3(this->GetMoveSpeed(), 0, 0));
	}
}