#pragma once 
#include "Entity.h"
#include "GUI.h"
class MiniGame :public GUI {
public :
	MiniGame(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) :GUI(fileName, row, column, Pos, Size) {

	}	
	void virtual HandleKey(char s) = 0 ;
	void virtual Update(int deltaTime) = 0; 
	void virtual ExitMiniGame() = 0;
};

