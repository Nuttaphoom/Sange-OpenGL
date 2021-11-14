#pragma once 
#include "SpriteObject.h" 
#include "Camera.h"
#include "SquareMeshVbo.h"
#include "GameEngine.h" 

 

class GUI : public SpriteObject {
 
  
public:
	GUI(string fileName, int row, int column) : SpriteObject(fileName,row,column) {};
	void Render(glm::mat4 globalModelTransform);
   
};

