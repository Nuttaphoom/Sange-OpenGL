#include "Hiding.h"
#include "Player.h" 
 
Hiding::Hiding(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : InteractableObject(fileName, row, column, Pos, Size, collisionSize) {

}

void Hiding::Called() {
	Player* p = Player::GetInstance();
	if (! p->GetInstance()->isSeen()) {
		p->SetPosition(this->GetPos());
		p->TranslateVelocity(-p->GetVelocity());
		p->ChangeState(StateMachine::HIDING);
	}
}