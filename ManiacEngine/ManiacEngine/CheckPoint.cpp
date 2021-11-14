#pragma 
#include "CheckPoint.h"

glm::vec3 CheckPoint = glm::vec3(0, 0, 0);

glm::vec3 LoadCheckPoint() {
	printf("l");
	Player::GetInstance()->SetPosition(CheckPoint); 
	return CheckPoint; 
}

void SetCheckPoint(glm::vec3 newPoint){
	printf("s");
	CheckPoint = newPoint; 
	
}