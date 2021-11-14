#pragma once
#include "InteractableObject.h"


class Flower : public InteractableObject{
	public :
		Flower(string fileName, int row, int column);
		void Called();
};