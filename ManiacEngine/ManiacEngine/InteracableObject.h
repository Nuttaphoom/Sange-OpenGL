#pragma once
#include "SpriteObject.h"
#include "Entity.h"

class InteracableObject : public SpriteObject {
	public :
		InteracableObject(string fileName, int row, int column);
		virtual void isCalled(Entity e);
		virtual void called() = 0;
};