#pragma once
#include "SpriteObject.h"
#include "Entity.h"
 
class InteractableObject : public SpriteObject {
	private : 
		SpriteObject* feedbackImage;

	public :
		glm::vec3 ColliderSize; ;
		InteractableObject(string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Size, glm::vec3 ColliderSize);
		virtual void RespawnThisObject() ;
		virtual void HandleKey(char key) ; 
		virtual void Called() ;

		int InCollideRadius(InteractableObject* in, Entity* e); 
		virtual void isCalled(Entity* e);
		virtual void Update(int deltaTime);

};