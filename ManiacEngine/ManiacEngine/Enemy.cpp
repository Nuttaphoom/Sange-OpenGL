#include "Enemy.h"

Enemy::Enemy(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame, glm::vec3 PatrolPos1, glm::vec3 PatrolPos2, Player* p) : Entity(fileName, row, column, HP, MoveSpeed, IFrame)
{
	EnemyState = EnemyStateMachine::IDLE;
	Target = p;
	AddPatrolPos(PatrolPos1);
	AddPatrolPos(PatrolPos2);
}

EnemyStateMachine Enemy::GetState()
{
	return EnemyState;
}

void Enemy::Translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

void Enemy::Update(int deltatime)
{
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	if (PlayerDetect(Target) == true)
	{
		PlayerChase(Target);
	}
	else
	{
		Patrol();
	}
}

void Enemy::UpdateStateMachine(float deltatime)
{
	if (GetState() == EnemyStateMachine::WALKING)
	{
		if (GetVelocity().x == 0)
		{
			ChangeState(EnemyStateMachine::IDLE);
		}
	}
	if (GetState() == EnemyStateMachine::IDLE)
	{
		if (GetVelocity().x != 0)
		{
			ChangeState(EnemyStateMachine::WALKING);
		}
	}
}

void Enemy::ChangeState(EnemyStateMachine nextState)
{
	if (GetState() == EnemyStateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 4, 100);
	}
	if (GetState() == EnemyStateMachine::WALKING)
	{
		SetAnimationLoop(1, 0, 4, 100);
	}
}

bool Enemy::PlayerDetect(Player* p)
{
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
	}
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

void Enemy::PlayerChase(Player* p)
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