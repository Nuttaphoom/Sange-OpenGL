#include "Enemy.h"
#include "Player.h"
#include "Raycast.h"
Enemy::Enemy(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size, glm::vec3 CollisionSize) : Entity(fileName, row, column, HP, MoveSpeed, Pos, Size, CollisionSize)
{
	stateMachine = StateMachine::RUNNING;
}

Enemy::Enemy(unsigned int text, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size, glm::vec3 CollisionSize) : Entity(text, row, column, HP, MoveSpeed, Pos, Size, CollisionSize)
{
	stateMachine = StateMachine::RUNNING;
}


 

 

void Enemy::Update(int deltatime)
{
	if (IsPause())
		return;

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

bool Enemy::PlayerDetect(Entity* p )
{
	Player::GetInstance()->RemoveDetectingEntity(this);
	if (p->GetState() == StateMachine::HIDING || p->isInv() == true || p->IsPause())
		return false; 

	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false; 

	if (Distance.x < 64*6 && Distance.y < 32) {
 
		RayCast* ray = new RayCast(this->GetPos(), p->GetPos());
		glm::vec3 resultPoint = ray->GetOutPutPoint();
		if (resultPoint.x == p->GetPos().x && resultPoint.y == p->GetPos().y)  {
 
			Player::GetInstance()->AddDetectingEntity(this); 

			return true;
		}
	}

	return false;
 
}

void Enemy::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}

 

 