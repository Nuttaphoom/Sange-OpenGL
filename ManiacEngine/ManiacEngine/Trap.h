#pragma once
#include "InteractableObject.h"
#include "CrossMiniGame.h"

class Trap: public InteractableObject {
private : 
	float trapSizeOffset = 64; //Plus or minus from normal collision
	bool refused = false;
	float coolDown = 0 ; 
	CrossMiniGame* _crossMiniGamePtr = nullptr;

public:
	Trap(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize /*Defuse zone*/) ;
	virtual void RespawnThisObject();
	virtual void getTrap(); 
	virtual void Called();
 	virtual void Update(int deltaTime); 
	virtual void Render(glm::mat4 globalModelTransform);
	virtual void HandleKey(char key);


};

