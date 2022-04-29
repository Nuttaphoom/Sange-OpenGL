#pragma once 
#include "Enemy.h"


class Decon : public Enemy {
	private :
		StateMachine DeconState;

		//counter ; 
		float attack_delay = 0;
		float chasing_delay = 0;
		float attack_cooldown_counter = 0;

	public :
	Decon(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);

	virtual void Attack(Entity* target);
	virtual void EnterAttackZone(Entity* target); 
	virtual void Update(int deltaTime); 
	virtual void StartAttack(); 
	virtual void UpdateStateMachine(float deltatime); 
	virtual void ChangeState(StateMachine nextState); 
	virtual StateMachine GetState();
	virtual void AddPatrolPos(glm::vec3 pos);
	virtual void Patrol();
	virtual void  PlayerChase(Entity* p)  ;
 };