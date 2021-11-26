#pragma once
#include "InteractableObject.h"


class Flower : public InteractableObject{
	public :
		Flower(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
		void Called();
};