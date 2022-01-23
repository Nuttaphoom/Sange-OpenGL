#pragma once 
#include "InteractableObject.h" 

class Hiding : public InteractableObject {
public:
	Hiding(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize);
 	void Called() ;
};

 
