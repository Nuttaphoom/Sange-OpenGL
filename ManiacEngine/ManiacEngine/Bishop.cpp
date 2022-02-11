#include "Bishop.h" 
#include "Player.h"

Bishop::Bishop(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :Enemy(fileName, row, column, 100, 0.21f, Pos, Size) {
	_bishopState = StateMachine::IDLE;
	DetectedDistanceX = 1000.0f;
	DetectedDistanceY = 100.0f;

} 

void Bishop::Update(int deltatime) {
	Entity::Update(deltatime);
	UpdateStateMachine(deltatime);
	 

}
void Bishop::UpdateStateMachine(float deltatime) {
	if (_bishopState == StateMachine::IDLE) {
		//Count Time until Attack time 
		_countDownTime += 1 * 1 / deltatime;
		cout << _countDownTime << endl; 
 		if (_countDownTime >= 3) {
			_countDownTime = 0;
 			ChangeState(StateMachine::RUNNING); 
		}
	}
	else if (_bishopState == StateMachine::ATTACKING) {
		//CountDelayTime , when delay == 0, turn around and get back to Idle 
		//if in Attack state, do damage to player if they see the player. check every single frame 
		Player* p = Player::GetInstance() ; 
		if (p->GetState() != StateMachine::HIDING) {
			if (PlayerDetect(p)) {
				Attack(p);
			}
		}

		_countDownTime += 1 * 1 / deltatime;
		cout << _countDownTime << endl;
		if (_countDownTime >= 3) {
			_countDownTime = 0;
			ChangeState(StateMachine::RUNNING);
		}
	}
	else if (_bishopState == StateMachine::RUNNING) {
		Patrol(); 
	}
}

void Bishop::PlayerChase(Entity* p) {

}
void Bishop::Patrol() {
	if (PatrolPos.size() == 0) return;

	glm::vec3 dest = PatrolPos.at(CurrentPatrolPos);

	if (abs(dest.x - GetPos().x) < 2) {
 		if (CurrentPatrolPos == 0) { // Get back to right side 
			ChangeState(StateMachine::IDLE);
		}
		else if (CurrentPatrolPos == 1) { //Get to casting skill position  
			ChangeState(StateMachine::ATTACKING);  
		}

		CurrentPatrolPos = (CurrentPatrolPos + 1) % PatrolPos.size();

		return;

	}
	if (dest.x > GetPos().x) SetDirection(1);
	else SetDirection(-1);

	TranslateVelocity(glm::vec3(this->GetMoveSpeed() * DirectionSet, 0, 0));
}

void Bishop::Attack(Entity* target) {
	if (target->GetState() == StateMachine::HIDING)
		return;  
 
	if (beam == nullptr) 
		beam = new SpriteObject("../Resource\Texture\Enemy\Pope_Dummy.png", 1, 1, Player::GetInstance()->GetPos() , glm::vec3(128, -1280, 1));

}
void Bishop::ChangeState(StateMachine NextState) {
	if (_bishopState == StateMachine::IDLE) {
		_bishopState = NextState;

	}
	else if (_bishopState == StateMachine::ATTACKING) {
		_bishopState = NextState;

	}
	else if (_bishopState == StateMachine::RUNNING) {
		_bishopState = NextState;

	}
}

void Bishop::Render(glm::mat4 globalModelTransform) {
	if (GetState() != StateMachine::HIDING) {
		SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

		GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
		GLuint modeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

		glBindTexture(GL_TEXTURE_2D, GetTexture());
		if (modelMatixId == -1) {
			cout << "Error: Can't perform transformation " << endl;
			return;
		}

		glm::mat4 currentMatrix = this->getTransform();
		/*Instead of rendering it directly, we apply a scale matrix according to the DirectionSet value*/
		currentMatrix = glm::scale(currentMatrix, glm::vec3(DirectionSet, 1, 1));

		if (squareMesh != nullptr) {
			currentMatrix = globalModelTransform * currentMatrix;
			glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
			glUniform1i(modeId, 1);
			squareMesh->AdjustTexcoord(GetUV());
			squareMesh->Render();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
