#pragma once
#include "InteracableObject.h"


class Flower : public InteracableObject{
	public :
		Flower(string fileName, int row, int column);
		void called();

};