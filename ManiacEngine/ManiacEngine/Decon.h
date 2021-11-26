#pragma once 
#include "Enemy.h"


class Decon : public Enemy {
	private :
		EnemyStateMachine DeconState; 
		vector<glm::vec3> PatrolPos;
		int CurrentPatrolPos = 0; 
		//counter ; 
		float attack_delay = 0;
		float chasing_delay = 0;
		float attack_cooldown_counter = 0;

	public :
		Decon(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 PatrolPos1, glm::vec3 PatrolPos2);

	virtual void Attack(Entity* target);
	virtual void EnterAttackZone(Entity* target); 
	virtual void Update(int deltaTime); 
	virtual void StartAttack(); 
	virtual void UpdateStateMachine(float deltatime); 
	virtual void ChangeState(EnemyStateMachine nextState); 
	virtual EnemyStateMachine GetState(); 
	virtual void AddPatrolPos(glm::vec3 pos);
	virtual bool PlayerDetect(Entity* p);
	virtual void Patrol();
};