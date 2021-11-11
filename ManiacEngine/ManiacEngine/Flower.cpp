#include "Flower.h"
#include "CheckPoint.h"



Flower::Flower(string fileName, int row, int column) : InteractableObject(fileName,row,column) {

}

void Flower::Called() {
	Static_SetCheckPoint(this->GetPos()); 
}