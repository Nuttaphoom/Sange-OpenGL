#pragma once
#include "Entity.h"

enum class StateMachine {
	IDLE,
	RUNNING
};

class Player : public Entity
{
	private :
	enum StateMachine PlayerState;
	
	public :
	Player(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
	StateMachine GetState();
	void Update(float deltatime);
	void UpdateStateMachine(float deltatime);
	void HandleKey(char Key);
	void ChangeState(StateMachine NextState);
	void Translate(glm::vec3 moveDistance);
};