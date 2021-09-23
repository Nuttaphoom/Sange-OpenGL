#pragma once 
#include "ImageObject.h" 
#include "Camera.h"
#include "SquareMeshVbo.h"
#include "GameEngine.h" 

enum class GUIName {
	GUI_TEST
};

class GUI : public ImageObject {
private:
	GUIName GUIname;
  
public:
	GUI(GUIName GUIname) :GUIname(GUIname) {};
	void Render(glm::mat4 globalModelTransform);
	void Update(float deltaTime);  
 
};

