#pragma once 
#include "Enemy.h"


 
class Pope : public Enemy {
private:
	StateMachine _popeState ;

 public:
	 Pope(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
	 Pope(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size);

 	virtual void Update(int deltaTime);
 	virtual void UpdateStateMachine(float deltatime);
	virtual void ChangeState(StateMachine nextState);
	virtual StateMachine GetState();
	virtual void AddPatrolPos(glm::vec3 pos);
	virtual void Patrol();
	virtual bool PlayerDetect(Entity* p);
	virtual void  PlayerChase(Entity* p);
	virtual void  Render(glm::mat4 globalModelTransform);
};

 