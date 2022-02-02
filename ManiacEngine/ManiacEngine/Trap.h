#pragma once
#include "InteractableObject.h"


class Trap: public InteractableObject {
private : 
	float trapSizeOffset = 0;
public:
	Trap(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize /*Defuse zone*/) ;
	void getTrap(); 
	void Called();
};