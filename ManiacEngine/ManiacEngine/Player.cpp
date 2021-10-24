#include "Player.h"
 
void Player::HandleKey(char Key)
{
 	switch (Key)
	{
		cout << "input is " << Key << endl;
		case 'w': TranslateVelocity(glm::vec3(0.0, 3, 0)); break;
		case 's': TranslateVelocity(glm::vec3(0, -3, 0)); break;
		case 'a': TranslateVelocity(glm::vec3(-0.3, 0, 0)); break;
		case 'd': TranslateVelocity(glm::vec3(0.3, 0, 0)); break;
	}

}

Player::Player(string fileName, int row, int column,float HP, float MoveSpeed, float IFrame) : Entity(fileName, row, column, HP, MoveSpeed, IFrame)
{	
	PlayerState = StateMachine::IDLE;
}

StateMachine Player::GetState()
{
	return PlayerState;
}

void Player::Update(int deltatime)
{
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
}

void Player::UpdateStateMachine(float deltatime)
{

}


void Player::ChangeState(StateMachine NextState)
{
	PlayerState = NextState;

	if (this->GetState() == StateMachine::IDLE)
	{
		//SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame);
	}
	else if (this->GetState() == StateMachine::RUNNING)
	{
		//SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame);
	}
}

void Player::Translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

 