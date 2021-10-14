#include "Camera.h"
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