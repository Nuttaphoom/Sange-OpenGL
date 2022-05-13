#pragma once
#include "CameraController.h"
#include "Camera.h"
#include "Player.h"
#include "GameEngine.h"
 
CameraController::CameraController() {
	cameraMode = CameraMode::FollowPlayer; 
}
void CameraController::Update() {
	glm::vec3 n = Player::GetInstance()->GetPos();

	float offsetX = 0;
	float offsetY = GameEngine::GetInstance()->GetWindowHeight() /6 - 128; 


	n += glm::vec3(offsetX, offsetY, 1);

  	Camera::GetInstance()->SetPosition(n);
}
	
void CameraController::ChangeMode(CameraMode cm) {
	this->cameraMode = cm; 
}
 