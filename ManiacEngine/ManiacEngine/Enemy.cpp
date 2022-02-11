#include "Enemy.h"
#include "Player.h"
#include "Raycast.h"
Enemy::Enemy(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size ): Entity(fileName, row, column, HP, MoveSpeed, Pos, Size)
{
	stateMachine = StateMachine::RUNNING;
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

 

void Enemy::ChangeState(StateMachine nextState)
{
	stateMachine = nextState;
	this->velocity = glm::vec3(0, 0, 0); 

	if (GetState() == StateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 1, 100);
	}
	else if (GetState() == StateMachine::RUNNING)
	{
		SetAnimationLoop(0, 0, 12, 100);
	}
}

bool Enemy::PlayerDetect(Entity* p)
{
	if (p->GetState() == StateMachine::HIDING)
		return false; 

	

	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);
	Player::GetInstance()->AddDetectingEntity(this);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false;  

	if (Distance.x < DetectedDistanceX && Distance.y < DetectedDistanceY) {
		glm::vec3 resultVec = RayCast(this->GetPos(), p->GetPos()).GetOutPutRayCast() ;
		if (abs(resultVec.x - abs(Distance.x)) < 0.1f && abs(resultVec.y - abs(Distance.y)) < 0.1f) {
			Player::GetInstance()->AddDetectingEntity(this); 
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

 

 