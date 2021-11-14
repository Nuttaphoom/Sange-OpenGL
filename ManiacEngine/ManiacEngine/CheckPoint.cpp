#pragma 
#include "CheckPoint.h"

CheckPoint* CheckPoint::instance = nullptr; 

 
CheckPoint* CheckPoint::GetInstance() {
	if (instance == nullptr) {
		instance = new CheckPoint(); 
	}
	return instance;
}


glm::vec3 CheckPoint::LoadCheckPoint() {
	printf("l");
	Player::GetInstance()->SetPosition(curCheckPoint);
	return curCheckPoint; 
}

void CheckPoint::SetCheckPoint(glm::vec3 newPoint){
	printf("s");
	curCheckPoint = newPoint;
	
}