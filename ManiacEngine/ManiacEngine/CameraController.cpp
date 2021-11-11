#pragma once
#include "CameraController.h"
#include "Camera.h"
#include "Player.h"
 
 
CameraController::CameraController() {
	cameraMode = CameraMode::FollowPlayer; 
}
void CameraController::Update() {
 	glm::vec3 n = Player::GetInstance()->GetPos();
	Camera::GetInstance()->SetPosition(n);
}
	
void CameraController::ChangeMode(CameraMode cm) {
	this->cameraMode = cm; 
}
 