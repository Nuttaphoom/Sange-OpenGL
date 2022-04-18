#pragma once
#include "InteractableObject.h" 
#include "GameEngine.h"

//Used for transition to other levels 
class Gate : public InteractableObject {
private:
		GameState _gameState;
public:
	Gate(GameState gameState ,string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize);

	virtual void Called();
	virtual void HandleKey(char key);
};