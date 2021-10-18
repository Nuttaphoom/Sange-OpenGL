#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
class GameObject :public DrawableObject
{
	glm::vec3 color	;
	glm::vec3 pos	;
	glm::vec3 size	; 
public:
	GameObject();
	~GameObject();
	glm::vec3 GetColor(); 
	void SetColor(float r, float g, float b);
	void Render(glm::mat4 globalModelTransform);
  
};

