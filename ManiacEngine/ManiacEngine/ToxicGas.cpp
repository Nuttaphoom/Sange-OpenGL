#include "ToxicGas.h" 
#include "Player.h"

 

ToxicGas::ToxicGas(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : InteractableObject(fileName, row, column, Pos, Size, collisionSize) {
	SetAnimationLoop(0, 0, 4,500, true);
}
void ToxicGas::getTrap() {

}
void ToxicGas::Called() {
 
}

void ToxicGas::Update(int deltaTime) {
	InteractableObject::Update(deltaTime);

	Player* player = Player::GetInstance();
	glm::vec3 insideColliderSize = glm::vec3(0, ColliderSize.y, 1);
	float offsetX = 30 + 26 + 128 / 8;
	InteractableObject* testObj = new InteractableObject(InteractableObject::InteractableObject("../Resource/Texture/Interactable/Cross.png", 0, 0, glm::vec3(GetPos().x + offsetX, GetPos().y, GetPos().z), GetSize(), glm::vec3(128 / 4 - 30, -128, 1)));

	if (testObj->InCollideRadius(testObj, player) > 0) {
		player->OnDamaged(10);
	}

	delete testObj;
}

void ToxicGas::HandleKey(char key) {
	
}
 

void ToxicGas::RespawnThisObject() {
 
}

