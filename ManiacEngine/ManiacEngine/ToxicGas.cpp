#include "ToxicGas.h" 
#include "Player.h"

 

ToxicGas::ToxicGas(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : InteractableObject(fileName, row, column, Pos, Size, collisionSize) {
	SetAnimationLoop(0, 0, 4,100, true);
}
void ToxicGas::getTrap() {

}
void ToxicGas::Called() {
 
}

void ToxicGas::Update(int deltaTime) {
	InteractableObject::Update(deltaTime);

	Player* player = Player::GetInstance();
	if (InCollideRadius(this, player)) {
		cout << "Collider size.x : " << ColliderSize.x << endl; 
		player->OnDamaged(10);
	}

  

 }

void ToxicGas::HandleKey(char key) {
	
}
 

void ToxicGas::RespawnThisObject() {
 
}

