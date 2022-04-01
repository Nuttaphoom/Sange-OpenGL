#pragma once
#include "GUI.h";

class Manager : public GUI{
	
public:
	Manager(string fileName = "", int row  = -1, int column = -1, glm::vec3 Pos = glm::vec3(0,0,0)  , glm::vec3 Size = glm::vec3(0,0,0)) :GUI(fileName, row, column, Pos, Size) {

	}
	virtual void Update(int deltaTime) {
	};
	virtual void Render(glm::mat4 globalModelTransform) {

	}
	virtual void HandleKey(char s) {

	};
};



