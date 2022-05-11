#include "ReSpawner.h" 
#include "GameStateController.h" 

ReSpawner::ReSpawner() {
	_menuHolder = new MenuHolder("DeadMenu");

	SDL_Color SDL_WhiteColor = SDL_Color();
	SDL_WhiteColor.r = 255;  SDL_WhiteColor.g = 255;  SDL_WhiteColor.b = 255;
	Button* restartButton = new Button(ButtonName::RESTART_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 550, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "Continue", SDL_WhiteColor, 20);
	_menuHolder->addButton(restartButton);

	GameStateController::GetInstance()->currentLevel->AddObjectList(restartButton);
	GameStateController::GetInstance()->currentLevel->AddGUIObject(restartButton);

	_menuHolder->disableButton(); 

 	Player::GetInstance()->attach(this,1); 
} 

void ReSpawner::ReSpawn() {
 
	_menuHolder->disableButton();

	for (int i = 0; i < GameStateController::GetInstance()->currentLevel->GetEntityList().size(); i++) {
		dynamic_cast<Entity*>(GameStateController::GetInstance()->currentLevel->GetEntityList()[i])->RespawnThisObject() ;  
	}

	for (int i = 0; i < GameStateController::GetInstance()->currentLevel->GetGUIObjectsList().size(); i++) {
		dynamic_cast<GUI*>(GameStateController::GetInstance()->currentLevel->GetGUIObjectsList()[i])->RespawnThisObject();
	}

	GameStateController::GetInstance()->currentLevel->GetInteractableObjectManager()->RespawnThisObject();

}

void ReSpawner::OnNotify() {
	_menuHolder->enableButton();


	 
	
 }

ReSpawner::~ReSpawner() {
	Player::GetInstance()->detach(this);
}