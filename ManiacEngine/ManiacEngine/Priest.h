 #pragma once 
#include "Enemy.h"


class PriestLightBall  ; 

class Priest : public Enemy {
private:
	StateMachine _priestState;

	//counter ; 
	float attack_delay = 0;
	int chasing_delay = 0;
	float attack_cooldown_counter = 0;

	unsigned int lightBallTexture; 

	vector<PriestLightBall*> _activePriestLightBalls;  

public:
	Priest(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
	Priest(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size);

	virtual void Attack(Entity* target);
	virtual void EnterAttackZone(Entity* target);
	virtual void Update(int deltaTime);
	virtual void StartAttack();
	virtual void UpdateStateMachine(float deltatime);
	virtual void ChangeState(StateMachine nextState);
	virtual StateMachine GetState();
	virtual void AddPatrolPos(glm::vec3 pos);
	virtual void Patrol();
	virtual bool PlayerDetect(Entity* p);
	virtual void  PlayerChase(Entity* p);
	virtual void  Render(glm::mat4 globalModelTransform);
};

class PriestLightBall : public Entity {
private:
	glm::vec3 _destination;
	Entity* _followedTarget;
	float _speed;
public:
	PriestLightBall(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 Destination);
	virtual void Update(int deltaTime);
};