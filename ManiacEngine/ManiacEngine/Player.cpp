#include "Player.h"
 
#define PlayerIsJumpingOrFalling PlayerState == StateMachine::JUMPPING || PlayerState == StateMachine::MIDJUMP || PlayerState == StateMachine :: FALLING 
void Player::HandleKey(char Key)
{
 	switch (Key)
	{
		cout << "input is " << Key << endl;
		case 'w': if (Entity::OnGround) {
				TranslateVelocity(glm::vec3(0, 3, 0)); 
				Entity::OnGround = false;
			} 
			break;
		case 's': TranslateVelocity(glm::vec3(0, -3, 0)); break;
		case 'a': TranslateVelocity(glm::vec3(this->GetMoveSpeed() * -1, 0, 0)); SetDirection(-1);  break;
		case 'd': TranslateVelocity(glm::vec3(this->GetMoveSpeed(), 0, 0)); SetDirection(1); break;
	}

}

Player::Player(string fileName, int row, int column,float HP, float MoveSpeed, float IFrame) : Entity(fileName, row, column, HP, MoveSpeed, IFrame)
{	
	PlayerState = StateMachine::JUMPPING;
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
	if (GetState() == StateMachine::RUNNING || GetState() == StateMachine::FALLING)
	{
		if (GetVelocity().x == 0 && GetVelocity().y == 0 )
		{
			ChangeState(StateMachine::IDLE);
		}
	}
	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::FALLING)
	{
		if (GetVelocity().x != 0 && OnGround == true)
		{
			ChangeState(StateMachine::RUNNING);
		}
	}
	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::RUNNING || GetState() == StateMachine::FALLING)
	{
		if (GetVelocity().y > 0)
		{
			ChangeState(StateMachine::JUMPPING);
		}
	}
	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::RUNNING || GetState() == StateMachine::JUMPPING)
	{
		if (GetVelocity().y == 0 && OnGround == false)
		{
			ChangeState(StateMachine::MIDJUMP);
		}
	}
	if (GetState() == StateMachine::MIDJUMP && OnGround == false && GetVelocity().y < 0)
	{
		ChangeState(StateMachine::FALLING);
	}
}


void Player::ChangeState(StateMachine NextState)
{
	PlayerState = NextState;

	if (this->GetState() == StateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 4, 100);
	}
	else if (this->GetState() == StateMachine::RUNNING)
	{
		SetAnimationLoop(1, 0, 4, 100);
	}
	else if (this->GetState() == StateMachine::JUMPPING)
	{
		SetAnimationLoop(2, 0, 3, 100);
	}
	else if (this->GetState() == StateMachine::MIDJUMP)
	{
		SetAnimationLoop(2, 3, 1, 100);
	}
	else if (this->GetState() == StateMachine::FALLING)
	{
		SetAnimationLoop(3, 0, 4, 100);
	}
}

void Player::Translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

 
