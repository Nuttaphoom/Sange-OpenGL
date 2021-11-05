#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame) : Entity(fileName, row, column, HP, MoveSpeed, IFrame)
{
	EnemyState = EnemyStateMachine::IDLE;
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

bool Enemy::PlayerDetect()
{
	return false;
}

void Enemy::AddPatrolPos(glm::vec3 pos)
{
	PatrolPos.push_back(pos);
}