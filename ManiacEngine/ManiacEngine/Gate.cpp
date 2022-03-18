#include "Gate.h" 

Gate::Gate(GameState gameState,string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : InteractableObject(fileName, row, column, Pos, Size, collisionSize) {
	this->_gameState = gameState;
}

void Gate::Called() {
	GameData::GetInstance()->gGameStateNext = this->_gameState ;
}