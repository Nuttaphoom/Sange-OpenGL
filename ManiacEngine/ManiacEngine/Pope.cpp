#include "Pope.h"
#include "Player.h"
#include "Raycast.h"
#include "GameStateController.h"


void CreatePopeDeadAnim(Entity* en) {
 	float lifespan = 2.0f;
	string fileName = "../Resource/Texture/Enemy/Pope/Pope_Dead_SpriteSheet.png";
	int row = 2;
	int col = 10;
	int howManyFrame = 19;
	float delayBetweenFrame = 100;

	vector<SpriteObject*> entities;
	entities.push_back(en);
	entities.push_back(Player::GetInstance());


	glm::vec3 size = Player::GetInstance()->GetSize();
	size.x *= 1.15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1);
	size.y *= 1;

	glm::vec3 animationPos;
	animationPos.x = (en->GetPos().x + Player::GetInstance()->GetPos().x) / 2;
	animationPos.y = en->GetPos().y  ;

	AnimatorManager::GetInstance()->CreateAnimationFactory(entities, animationPos, size, lifespan, fileName, row, col, howManyFrame, delayBetweenFrame, ETextureName::PopeDeadAnimationTexture);
	glm::vec3 movePos;
	movePos.x = animationPos.x + 15 * (Player::GetInstance()->GetPos().x > en->GetPos().x ? -1 : 1);
	movePos.y = Player::GetInstance()->GetPos().y;
	movePos.z = Player::GetInstance()->GetPos().z;

	if (en->GetPos().x < Player::GetInstance()->GetPos().x) {
		Player::GetInstance()->SetDirection(1);
	}
	else if (en->GetPos().x > Player::GetInstance()->GetPos().x) {
		Player::GetInstance()->SetDirection(-1);
	}

	Player::GetInstance()->ResetVelocity();
	Player::GetInstance()->SetPosition(movePos);
	Player::GetInstance()->ChangeState(StateMachine::IDLE);


}

Pope::Pope(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 300.0f, 200.0f, Pos, Size, glm::vec3(Size.x / 2, Size.y, 0)) {
 	ChangeState(StateMachine::IDLE);
	SetDirection(1);

 	 

}

Pope::Pope(unsigned int texture, int row, int column, glm::vec3 Pos, glm::vec3 Size): Enemy(texture, row, column, 300.0f, 200.0f, Pos, Size, glm::vec3(Size.x / 2, Size.y, 0)) {
    ChangeState(StateMachine::IDLE);
	SetDirection(1) ;
 

}

void Pope::Update(int deltaTime) {
	if (IsPause())
		return;

	Entity::Update(deltaTime);
	UpdateStateMachine(deltaTime);

 }

float delay = 0; 
//Only Idle Walking and Die
void Pope::UpdateStateMachine(float deltatime) {
	if (GetState() == StateMachine::IDLE) {
		if (PlayerDetect(Player::GetInstance())) {
			ChangeState(StateMachine::RUNNING);
 		}
	}
	else if (GetState() == StateMachine::RUNNING) {
		Patrol();
	}
	else if (GetState() == StateMachine::Die) {
		delay += 1.0f / 1000.0f * deltatime;
		if (delay >= 0.75f) {
			GameData::GetInstance()->gGameStateNext = GameState::GS_CUTSCENES2;
		}
	}
}

void Pope::ChangeState(StateMachine nextState) {
    if (nextState == StateMachine::IDLE) {
        SetAnimationLoop(0, 0, 4, 300);
	}
	else if (nextState == StateMachine::Die) {
		CreatePopeDeadAnim(this);
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
}

 
