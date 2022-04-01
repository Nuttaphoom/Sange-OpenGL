#include "MiniGameManager.h" 
MiniGameManager* MiniGameManager::instance = nullptr ;

MiniGameManager* MiniGameManager::GetInstance() {
	if (instance == nullptr) {
		instance = new MiniGameManager();
	}

	return instance;
}

void MiniGameManager::Render(glm::mat4 globalModelTransform){
	for (int i = 0; i < this->_minigames.size(); i++) {
		_minigames[i]->Render(globalModelTransform);
	}
}

void MiniGameManager::Update(int deltaTime) {
	for (int i = 0; i < this->_minigames.size(); i++) {
		_minigames[i]->Update(deltaTime); 
	}
}
void MiniGameManager::AddMiniGame(MiniGame* mg) {
	this->_minigames.push_back(mg); 
}
void MiniGameManager::RemoveMiniGame(MiniGame* mg) {
	for (int i = 0; i < this->_minigames.size(); i++) {
		if (_minigames[i] == mg) {
			this->_minigames.erase(_minigames.begin() + i);
			return; 
		}
	}
}

void MiniGameManager::HandleKey(char key) {
	for (int i = 0; i < this->_minigames.size(); i++) {
		_minigames[i]->HandleKey(key); 
	}
}
