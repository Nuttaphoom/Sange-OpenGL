#pragma once
#include "GameObject.h" 
#include "SquareMeshVbo.h" 
#include "Entity.h"

class InvisibleObject : public DrawableObject {
	private:
		bool render = false ; 
		glm::vec3 color;
		bool climbable = false ; 
 
	public : 
		InvisibleObject();  
		InvisibleObject(bool c);
		virtual void Render(glm::mat4 globalModelTransform)  ;
		virtual void Update(float deltaTime);
		bool IsClimbable();

		void SetRender(bool b); 
		int Collide_W_Entity(Entity e); 
 };

 

