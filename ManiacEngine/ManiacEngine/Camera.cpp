#include "Camera.h"
#include "GameEngine.h"
Camera* Camera::instance = nullptr;

Camera::Camera() {
	instance = this;
	CamOffset = glm::vec3(0); 
	zoomOffset = 1; 
}

Camera* Camera::GetInstance()
{
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}

void Camera::Translate(float x, float y) {

	CamOffset = glm::vec3(CamOffset.x + x, CamOffset.y + y, CamOffset.z);
}

void Camera::Zoom(float p) {
	if (zoomOffset > 0.1 && p < 0)
		zoomOffset += p; 
	if (zoomOffset < 3 && p > 0)
		zoomOffset += p;

	return;
}

glm::vec3 Camera::GetCamOffset() {
	return CamOffset;  
}

float Camera::GetZoomOffset() {
	return zoomOffset; 
}


bool Camera::IsInCamera(glm::vec3 pos, glm::vec3 size) {
	bool CollideX, CollideY;
	float LeftCam = (-1 * GameEngine::GetInstance()->GetWindowWidth() / 2 + this->GetCamOffset().x) / this->GetZoomOffset()  ;
	float RightCam = (GameEngine::GetInstance()->GetWindowWidth() / 2 + this->GetCamOffset().x ) / this->GetZoomOffset() ; 
	float TopCam = (GameEngine::GetInstance()->GetWindowHeight() / 2 + this->GetCamOffset().y) / this->GetZoomOffset() ; 
	float BottomCam = (-1 * GameEngine::GetInstance()->GetWindowHeight() / 2 + this->GetCamOffset().y) / this->GetZoomOffset() ;
 
	CollideX = (pos.x - size.x / 2 <= RightCam  && pos.x + size.x / 2 >= LeftCam);
	CollideY = (pos.y - size.y * -1 / 2 >= BottomCam && pos.y + size.y * -1 / 2 <= TopCam );
	if (CollideX && CollideY) cout << "true" << endl;
	else cout << "false" << endl; 
	return CollideX && CollideY ;
 }
