#pragma once
#include "Camera.h" 

enum class CameraMode {
	FollowPlayer 
};

class CameraController {
private :
 	CameraMode cameraMode;  
public : 
	CameraController(); 
	void Update(); 
	void ChangeMode(CameraMode cm); 
};



