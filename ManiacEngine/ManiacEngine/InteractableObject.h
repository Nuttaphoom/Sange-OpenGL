#pragma once
#include "SpriteObject.h"
#include "Entity.h"
 
class InteractableObject : public SpriteObject {
	public :
		InteractableObject(string fileName, int row, int column);
		virtual void isCalled(Entity* e);
		virtual void Called() = 0;
};