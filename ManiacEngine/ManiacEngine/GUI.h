#pragma once 
#include "SpriteObject.h" 
#include "Camera.h"
#include "SquareMeshVbo.h"
#include "GameEngine.h" 

enum class GUIName {
	Decroative,
	Button
};

class GUI : public SpriteObject {
private:
	GUIName GUIname;
  
public:
	GUI(GUIName GUIname, string fileName, int row, int column) : SpriteObject(fileName,row,column) , GUIname(GUIname) {};
	void Render(glm::mat4 globalModelTransform);
	void Update(float deltaTime);   
  
};

