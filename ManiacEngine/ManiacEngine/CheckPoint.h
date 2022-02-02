#pragma once
#include "GameData.h"
#include "Player.h"
 
class CheckPoint {
	static CheckPoint* instance;
	glm::vec3 curCheckPoint = glm::vec3(0, 0, 0);
	public :
 	glm::vec3 LoadCheckPoint();
	void SetCheckPoint(glm::vec3 newPoint);
	static CheckPoint* GetInstance();
};

 
 