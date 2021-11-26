#include "ReSpawner.h" 
#include "GameStateController.h" 

ReSpawner::ReSpawner() {
	cout << "ReSpawner" << endl;
	Player::GetInstance()->attach(this,1); 
} 

void ReSpawner::ReSpawn() {
	for (int i = 0; i < GameStateController::GetInstance()->currentLevel->GetEntityList().size(); i++) {
		dynamic_cast<Entity*>(GameStateController::GetInstance()->currentLevel->GetEntityList()[i])->RespawnThisObject() ;  
	}
}

void ReSpawner::OnNotify() {
	ReSpawn(); 
}

ReSpawner::~ReSpawner() {
	Player::GetInstance()->detach(this);
}