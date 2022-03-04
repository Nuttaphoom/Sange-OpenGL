#pragma once

class Manager : public GUI{
	
public:
	Manager(string fileName , int row  , int column , glm::vec3 Pos  , glm::vec3 Size  ) :GUI(fileName, row, column, Pos, Size) {

	}
	virtual void Update(int deltaTime) = 0 ;
	virtual void Render(glm::mat4 globalModelTransform) = 0;
};



