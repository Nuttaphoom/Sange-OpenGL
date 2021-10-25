#ifndef ENTITY
#define ENTITY

#include "Entity.h"

enum class StateMachine {
	IDLE,
	RUNNING,
	JUMPPING,
	MIDJUMP,
	FALLING
};

class Player : public Entity
{
	private :
	enum StateMachine PlayerState;
 	
	public :
	Player(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
	StateMachine GetState();
	void Update(int deltatime);
	void UpdateStateMachine(float deltatime);
 	void ChangeState(StateMachine NextState);
	void Translate(glm::vec3 moveDistance);
	void HandleKey(char key); 

 };




#endif ; 