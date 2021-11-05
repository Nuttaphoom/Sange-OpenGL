#pragma once
#include "Entity.h"
#include <vector>

enum class EnemyStateMachine {
	IDLE,
	WALKING
};

class Enemy : public Entity
{
	private:
	enum EnemyStateMachine EnemyState;
	vector <glm::vec3> PatrolPos;

	public:
	Enemy(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
	EnemyStateMachine GetState();
	void Update(int deltatime);
	void AddPatrolPos(glm::vec3 pos);
	void UpdateStateMachine(float deltatime);
	void ChangeState(EnemyStateMachine NextState);
	void Translate(glm::vec3 moveDistance);
	bool PlayerDetect();
};