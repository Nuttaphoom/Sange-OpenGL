#include "Enemy.h"
#include "Player.h"
#include "Raycast.h"
Enemy::Enemy(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size ): Entity(fileName, row, column, HP, MoveSpeed, Pos, Size)
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

bool Enemy::PlayerDetect(Entity* p)
{
	Player::GetInstance()->RemoveDetectingEntity(this);
	if (p->GetState() == StateMachine::HIDING)
		return false; 

	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);

	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false; 
	//cout << "ResultVec : " << resultVec.x << "," << resultVec.y << endl;
	//cout << "Distance between Player and this enemy : " << Distance.x << "," << Distance.y << endl; 

	if (Distance.x < 200 && Distance.y < 100) {
		glm::vec3 resultVec = RayCast(this->GetPos(), p->GetPos()).GetOutPutRayCast() ;
		if (abs(resultVec.x - abs(Distance.x)) < 0.1f && abs(resultVec.y - abs(Distance.y)) < 0.1f) {
			Player::GetInstance()->AddDetectingEntity(this); 
			return true;
		}
	}

	
	//cout << "DON'T SEE PLAYER" << endl;
	return false;
 
}

void Enemy::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}

 

 