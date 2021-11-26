#pragma once 
#include "SpriteObject.h" 
#include "Camera.h"
#include "SquareMeshVbo.h"
#include "GameEngine.h" 

 

class GUI : public SpriteObject {
 
  
public:
	GUI(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) : SpriteObject(fileName, row, column, Pos, Size) {};
	virtual void RespawnThisObject();
	virtual void Render(glm::mat4 globalModelTransform);
   
};

