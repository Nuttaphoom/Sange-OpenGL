#pragma once
#include "GameObject.h" 
#include "SquareMeshVbo.h" 
#include "Entity.h"

class InvisibleObject : public DrawableObject {
	private:
		bool render = false ; 
		glm::vec3 color;
 
	public : 
		InvisibleObject();  

		virtual void Render(glm::mat4 globalModelTransform)  ;
		virtual void Update(float deltaTime);

		void SetRender(bool b); 
		int Collide_W_Entity(Entity e); 
};

 

