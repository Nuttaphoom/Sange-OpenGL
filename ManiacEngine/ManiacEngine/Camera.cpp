#include "Camera.h"
Camera* Camera::instance = nullptr;

Camera::Camera() {
	instance = this;
	CamOffset = glm::vec3(0); 
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
	printf("CamOffset is %.2f\n", CamOffset.x); 
}

glm::vec3 Camera::GetCamOffset() {
	return CamOffset;  
}