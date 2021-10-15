#include "Player.h"

Player::Player(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame) : Entity(fileName, row, column, HP, MoveSpeed, IFrame)
{
	PlayerState = StateMachine::IDLE;
}

StateMachine Player::GetState()
{
	return PlayerState;
}

void Player::Update(float deltatime)
{
	UpdateStateMachine(deltatime);
}

void Player::UpdateStateMachine(float deltatime)
{

}

void Player::HandleKey(char Key)
{
	switch (Key)
	{
		case 'w': Translate(glm::vec3(0.0, 10, 0)); break;
		case 's': Translate(glm::vec3(0.0, -10, 0)); break;
		case 'a': Translate(glm::vec3(-10, 0, 0)); break;
		case 'd': Translate(glm::vec3(10, 0, 0)); break;
	}
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