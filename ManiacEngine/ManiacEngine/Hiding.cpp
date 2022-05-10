#include "Hiding.h"
#include "Player.h" 
#include "SoundPlayer.h"
Hiding::Hiding(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : InteractableObject(fileName, row, column, Pos, Size, collisionSize) {

}

void Hiding::Called() {
	Player* p = Player::GetInstance();
	
	if (! p->GetInstance()->isSeen()) {
		SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/Hiding.mp3");
		glm::vec3 newPos = glm::vec3(this->GetPos().x,p->GetPos().y, 0);
		p->SetPosition(newPos);
		p->TranslateVelocity(-p->GetVelocity());
		p->ChangeState(StateMachine::HIDING);
	}
}