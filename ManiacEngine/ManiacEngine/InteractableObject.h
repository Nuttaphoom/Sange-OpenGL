#pragma once
#include "SpriteObject.h"
#include "Entity.h"
 
class InteractableObject : public SpriteObject {
	public :
		glm::vec3 ColliderSize; ;
		InteractableObject(string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size, glm::vec3 ColliderSize);
		int InCollideRadius(InteractableObject* in, Entity* e); 
		virtual void isCalled(Entity* e);
		virtual void Called() = 0;
		virtual void Update(int deltaTime);

};