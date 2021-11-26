#include "Flower.h"
#include "CheckPoint.h"
 

Flower::Flower(string fileName, int row, int column,glm::vec3 Pos,glm::vec3 Size) : InteractableObject(fileName,row,column,Pos,Size) {

}

void Flower::Called() {
	CheckPoint::GetInstance()->SetCheckPoint(GetPos());
}