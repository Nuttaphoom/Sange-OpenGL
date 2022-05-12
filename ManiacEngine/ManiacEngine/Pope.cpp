#include "Pope.h"
#include "Player.h"
#include "Raycast.h"
#include "GameStateController.h"
Pope::Pope(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 300.0f, 200.0f, Pos, Size, glm::vec3(Size.x / 2, Size.y, 0)) {
 	ChangeState(StateMachine::IDLE);
	DirectionSet = -1;

	_popeCutscenePlayer = new PopeCutscenePlayer(); 
	_popeCutscenePlayer->SetPosition(Pos); 
	_popeCutscenePlayer->SetSize(Size.x / 4,Size.y / 4); 
	_popeCutscenePlayer->SetRender(true);

}

Pope::Pope(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size): Enemy(texture, row, column, 300.0f, 200.0f, Pos, Size, glm::vec3(Size.x / 2, Size.y, 0)) {
    ChangeState(StateMachine::IDLE);
	DirectionSet = -1;

	_popeCutscenePlayer = new PopeCutscenePlayer();
	_popeCutscenePlayer->SetPosition(GetPos());
	_popeCutscenePlayer->SetSize(Size.x, Size.y);
	_popeCutscenePlayer->SetRender(true);

}

void Pope::Update(int deltaTime) {
	if (IsPause())
		return;

	Entity::Update(deltaTime);
	UpdateStateMachine(deltaTime);

	_popeCutscenePlayer->Update(deltaTime);
}

//Only Idle and Walking
void Pope::UpdateStateMachine(float deltatime) {
	if (GetState() == StateMachine::IDLE) {
		if (PlayerDetect(Player::GetInstance())) {
			ChangeState(StateMachine::RUNNING);
 		}
	}
	else if (GetState() == StateMachine::RUNNING) {
		Patrol();
	}
}

void Pope::ChangeState(StateMachine nextState) {
    if (nextState == StateMachine::IDLE) {
        SetAnimationLoop(0, 0, 4, 300);
    }

	_popeState = nextState;
}

StateMachine Pope::GetState() {
    return _popeState;
}

void Pope::AddPatrolPos(glm::vec3 pos) {

}

void Pope::Patrol() {
 	DirectionSet = 1;
	TranslateVelocity(glm::vec3(this->GetMoveSpeed(), 0, 0));
}

bool Pope::PlayerDetect(Entity* p) {
	Player::GetInstance()->RemoveDetectingEntity(this);
	if (p->GetState() == StateMachine::HIDING || p->_inv == true)
		return false;

	glm::vec3 Distance = glm::vec3(abs(GetPos().x - p->GetPos().x), abs(GetPos().y - p->GetPos()).y, 0);
	if (p->GetPos().x > GetPos().x && DirectionSet != 1) return false;
	if (p->GetPos().x < GetPos().x && DirectionSet != -1) return false;


	if (Distance.x < 320 && Distance.y < 320) {
		glm::vec3 resultPoint = RayCast(this->GetPos(), p->GetPos()).GetOutPutPoint();
		if (abs(resultPoint.x - p->GetPos().x) < 1.0f && abs(resultPoint.y - p->GetPos().y) < 1.0f) {
			Player::GetInstance()->AddDetectingEntity(this);
			return true;
		}
	}
	return false;
}

void  Pope::PlayerChase(Entity* p) {
	
}

void  Pope::Render(glm::mat4 globalModelTransform) {
	Entity::Render(globalModelTransform);
	_popeCutscenePlayer->Render(globalModelTransform);
 }

PopeCutscenePlayer::PopeCutscenePlayer() {

}

void PopeCutscenePlayer::Update(float deltaTime) {
	if (Collide_W_Entity(*Player::GetInstance())) {
		GameData::GetInstance()->gGameStateNext  = GameState::GS_CUTSCENES2 ;
	}
}
