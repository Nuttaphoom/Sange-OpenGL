#include "Player.h"
#include "CheckPoint.h"
#include "GameEngine.h"
#include "InvisibleObject.h"
#include "GameStateController.h"

#define ENTITYLIST GameStateController::GetInstance()->currentLevel->GetEntityList()
 
Player* Player::instance = nullptr; 
int delay = 0;
int delay1 = 0;


void Player::HandleMouse(glm::vec3 mouseRealPos) {
	
	cout << "here1" << endl;
	for (int i = 0 ; i < ENTITYLIST.size() ; i++) {
		cout << "here2" << endl;

		if (Enemy* eptr = dynamic_cast<Enemy*>(ENTITYLIST[i])) {
 			Attack(eptr);
		}
	};
}

void Player::HandleKey(char Key)
{
 	switch (Key)
	{
 		case 'w': if (Entity::OnGround) {
				TranslateVelocity(glm::vec3(0, 5, 0)); 
				Entity::OnGround = false;
			} 
			break;
		case 's': TranslateVelocity(glm::vec3(0, -3, 0)); break;
		case 'a': TranslateVelocity(glm::vec3(this->GetMoveSpeed() * -1, 0, 0)); SetDirection(-1);  break;
		case 'd': TranslateVelocity(glm::vec3(this->GetMoveSpeed(), 0, 0)); SetDirection(1); break;
 	}
}

Player::Player(string fileName, int row, int column,float HP, float IFrame) : Entity(fileName, row, column, HP, 0.29, IFrame)
{	
	PlayerState = StateMachine::FALLING;
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
	if (GetState() == StateMachine::RUNNING)
	{
		if (GetVelocity().x < 2 && GetVelocity().x > -2 && OnGround == true)
		{
			ChangeState(StateMachine::IDLE);
		}
	}
	if (GetState() == StateMachine::LANDING)
	{
		if (GetVelocity().x < 2 && GetVelocity().x > -2)
		{
			int deltatime = GameEngine::GetInstance()->GetDeltaTime();
			delay1 += deltatime;
			if (delay1 >= 500)
			{
				delay1 = 0;
				ChangeState(StateMachine::IDLE);
			}
		}
		else
		{
			ChangeState(StateMachine::RUNNING);
		}
	}
	if (GetState() == StateMachine::FALLING)
	{
		if (GetVelocity().y == 0 && OnGround == true)
		{
			ChangeState(StateMachine::LANDING);
		}
	}
	if (GetState() == StateMachine::IDLE || GetState() == StateMachine::FALLING)
	{
		if (GetVelocity().x >= 2 || GetVelocity().x <= -2)
		{
			if (OnGround == true)
			{
				ChangeState(StateMachine::RUNNING);
			}
			//ChangeState(StateMachine::RUNNING);
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
	if (GetState() == StateMachine::MIDJUMP && OnGround == false /*&& GetVelocity().y < 0*/)
	{
		int deltatime = GameEngine::GetInstance()->GetDeltaTime();
		delay += deltatime;
		if (delay > 1)
		{
			delay = 0;
			ChangeState(StateMachine::FALLING);
		}
		//ChangeState(StateMachine::FALLING);
	}
}


void Player::ChangeState(StateMachine NextState)
{
	PlayerState = NextState;

	if (this->GetState() == StateMachine::IDLE)
	{
		SetAnimationLoop(0, 0, 1, 100);
	}
	else if (this->GetState() == StateMachine::RUNNING)
	{
		SetAnimationLoop(2, 0, 8, 100);
	}
	else if (this->GetState() == StateMachine::JUMPPING)
	{
		SetAnimationLoop(1, 4, 2, 300);
	}
	else if (this->GetState() == StateMachine::MIDJUMP)
	{
		SetAnimationLoop(1, 6, 1, 100);

	}
	else if (this->GetState() == StateMachine::FALLING)
	{
		SetAnimationLoop(1, 7, 1, 300);
	}
	else if (this->GetState() == StateMachine::LANDING)
	{
		SetAnimationLoop(1, 8, 2, 300);
	}
}

void Player::Translate(glm::vec3 moveDistance)
{
	pos = pos + moveDistance;
}

Player* Player::GetInstance() {
	if (instance == nullptr) {
		while (instance == nullptr) {
			cout << "ERROR -- Player Instance is called before init" << endl; 
			cout << "See more at Player.cpp -- " << endl; 
		}
	}
	return instance;
}

Player* Player::GetInstance(string fileName, int row, int column, float HP, float IFrame) 
{
	instance = new Player(fileName, row, column, HP, IFrame);
	CheckPoint::GetInstance()->LoadCheckPoint();
	return instance;

}
 
void Player::OnDamaged(int damage) {
	this->HP -= damage;
	notify(0); //Notify HP Observer 
}

void Player::Attack(Entity* target) {
	InvisibleObject invWALLs[2] ;
	 
	for (int i = 0; i < 2; i++) {
		invWALLs[i].SetPosition(glm::vec3(this->GetPos().x + (64 * this->DirectionSet * i), this->GetPos().y + this->GetSize().y * -1 / 2, 1));
		invWALLs[i].SetSize(64, 64);
	}
	if (target->DirectionSet == this->DirectionSet) {
		for (int i = 0; i < 2; i++) {
			if (invWALLs[i].Collide_W_Entity(*target)) {
				target->OnDamaged(999999);

			}
		}
	}
}