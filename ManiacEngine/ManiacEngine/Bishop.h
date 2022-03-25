#pragma once
#include "Enemy.h" 

class Bishop : public Enemy {
private:
	StateMachine _bishopState;

	int CurrentPatrolPos = 0;

	//counter ; 
	float _attackDelay = 0;
	float _countDownTime = 0 ;  
public:
	Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
	void virtual PlayerChase(Entity* p)  ;
	bool virtual PlayerDetect(Entity* p);
	void virtual Patrol() ;
	void virtual Attack(Entity* target) ;
	void virtual ChangeState(StateMachine NextState)  ;
	void virtual Update(int deltaTime);
	void UpdateStateMachine(float deltatime);

};