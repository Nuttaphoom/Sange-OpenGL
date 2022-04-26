 
#include "Priest.h"
#include "Raycast.h"

Priest::Priest(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size):Enemy(fileName, row, column, 100, 0.21f, Pos, Size) {
	_priestState = StateMachine::RUNNING ; 
}

void Priest::Attack(Entity* target) {

}

void Priest::EnterAttackZone(Entity* target) {

}

void Priest::Update(int deltaTime) {

}

void Priest::StartAttack() {

}

void Priest::UpdateStateMachine(float deltatime) {

}

void Priest::ChangeState(StateMachine nextState) {

}


void Priest::AddPatrolPos(glm::vec3 pos) {

}

void Priest::Patrol() {

}

void  Priest::PlayerChase(Entity* p) {

}

StateMachine Priest::GetState() { return _priestState; }




PriestLightBall::PriestLightBall(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size,glm::vec3 Destination ) :Entity(fileName, row, column,100000,1 ,Pos, Size) {
 
	RayCast* ray = new RayCast(GetPos(), Destination);
 	_destination = ray->GetOutPutPoint();  
	glm::vec3 movingVelocity = _destination - GetPos();
	movingVelocity /= 10;
	TranslateVelocity(movingVelocity);
}

void PriestLightBall::Update(int deltaTime) {
 	Entity::Update(deltaTime) ;

	if ((GetPos() - _destination).x <= 1 && (GetPos() - _destination).y <= 1)
		SetPause(true); 

	 
 }


