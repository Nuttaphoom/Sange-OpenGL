#pragma once 
#include "Enemy.h"


class Decon : public Enemy {
 
	Decon(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame, glm::vec3 PatrolPos1, glm::vec3 PatrolPos2); 
	
	virtual void Attack(Entity* target); 


};