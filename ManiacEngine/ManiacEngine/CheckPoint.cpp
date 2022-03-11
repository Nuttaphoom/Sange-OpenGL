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
	Player::GetInstance()->SetPosition(curCheckPoint);
	return curCheckPoint; 
}

void CheckPoint::SetCheckPoint(glm::vec3 newPoint){
	cout << "Set Check Point" << endl;
	curCheckPoint = newPoint;
	
}

void CheckPoint::Update(int deltaTime) {

}

void CheckPoint::Render(glm::mat4 globalModelTransform) {

}