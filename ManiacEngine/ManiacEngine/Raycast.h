#pragma once 
#include "GameEngine.h" 
 
class RayCast {
private:
	glm::vec3 p1;
	glm::vec3 p2;
public:
	bool Collide(glm::vec3 point, DrawableObject* objects);
	RayCast(glm::vec3 p1, glm::vec3 p2);
	glm::vec3 GetOutPutRayCast();
	glm::vec3 GetOutPutPoint();
	glm::vec3 GetOutPutPointWithoutBound(); 
}; 
