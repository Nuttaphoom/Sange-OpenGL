#include "Flower.h"




Flower::Flower(string fileName, int row, int column) : InteracableObject(fileName,row,column) {

}

void Flower::called() {
	printf("A\n");
}