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

	for (int i = 0; i < GameStateController::GetInstance()->currentLevel->GetGUIObjectsList().size(); i++) {
		dynamic_cast<GUI*>(GameStateController::GetInstance()->currentLevel->GetGUIObjectsList()[i])->RespawnThisObject();
	}

}

void ReSpawner::OnNotify() {
	ReSpawn(); 
}

ReSpawner::~ReSpawner() {
	Player::GetInstance()->detach(this);
}