#pragma once
#include "Enemy.h" 

class Bishop : public Enemy {
private:
	StateMachine _bishopState;

	int CurrentPatrolPos = 0;

	//counter ; 
	float _attackDelay = 0;
	float _countDownTime = 0 ;  

	//Beam
	SpriteObject* beam; 
public:
	Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
	void virtual PlayerChase(Entity* p)  ;
	void virtual Patrol() ;
	void virtual Attack(Entity* target) ;
	void virtual ChangeState(StateMachine NextState)  ;
	void virtual Update(int deltaTime);
	void virtual Render(glm::mat4 globalModelTransform);

	void UpdateStateMachine(float deltatime);

};