#ifndef INVISIBLEOBJECT
#define INVISIBLEOBJECT
#include "GameObject.h" 
#include "SquareMeshVbo.h" 
#include "Entity.h"

class InvisibleObject : public DrawableObject {
	private:
		bool render; 
		glm::vec3 color;
		glm::vec3 pos;
		glm::vec3 size;
	public : 
		InvisibleObject();  

		virtual void Render(glm::mat4 globalModelTransform)  ;
		virtual void Update(float deltaTime);

		void SetRender(bool b); 
		int Collide_W_Entity(Entity e); 
};

#endif 

