#include "Flower.h"
#include "CheckPoint.h"

Flower::Flower(string fileName, int row, int column,glm::vec3 Pos,glm::vec3 Size,glm::vec3 collisionSize) : InteractableObject(fileName,row,column,Pos,Size, collisionSize) {

}

void Flower::Called() {
	glm::vec3 savedPos = GetPos(); 
	savedPos.y += 32;
	CheckPoint::GetInstance()->SetCheckPoint(savedPos);
}