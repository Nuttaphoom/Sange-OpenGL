#pragma once
#include "Entity.h"
#include <vector>

 

class Enemy : public Entity
{
	private:
 	vector <glm::vec3> PatrolPos;
 
	public:
	Enemy(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size);
 	void Update(int deltatime);
	void AddPatrolPos(glm::vec3 pos);
	void UpdateStateMachine(float deltatime);
	void ChangeState(StateMachine NextState);
	void Translate(glm::vec3 moveDistance);
	bool PlayerDetect(Entity* p);
	void PlayerChase(Entity* p);
	void Patrol();
	virtual void Attack(Entity* target);

};