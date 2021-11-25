#pragma once
#include "Entity.h"
#include "Player.h"
#include <vector>

enum class EnemyStateMachine {
	IDLE,
	WALKING,
	ATTACKING,
	CHASE,
	FOLLOW
};

class Enemy : public Entity
{
	private:
	enum EnemyStateMachine EnemyState;
	vector <glm::vec3> PatrolPos;
	Player* Target;

	public:
	Enemy(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame, glm::vec3 PatrolPos1, glm::vec3 PatrolPos2, Player* p);
	EnemyStateMachine GetState();
	void Update(int deltatime);
	void AddPatrolPos(glm::vec3 pos);
	void UpdateStateMachine(float deltatime);
	void ChangeState(EnemyStateMachine NextState);
	void Translate(glm::vec3 moveDistance);
	bool PlayerDetect(Player* p);
	void PlayerChase(Player* p);
	void Patrol();
};