#pragma once
#include "InteractableObject.h"


class Trap: public InteractableObject {
public:
	Trap(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) ;
	void Called();
};