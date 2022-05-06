#pragma once
#include "InteractableObject.h"

class ToxicGas : public InteractableObject {
private:
   
public:
	ToxicGas(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize /*Defuse zone*/);
	virtual void RespawnThisObject();
	virtual void getTrap();
	virtual void Called();
	virtual void Update(int deltaTime);
 	virtual void HandleKey(char key);


};

