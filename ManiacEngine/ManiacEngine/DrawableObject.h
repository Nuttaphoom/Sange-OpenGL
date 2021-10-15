#pragma once
#include "glm.hpp"
#include <iostream>
#include <vector>

using namespace std;

class DrawableObject
{
protected:
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 size = glm::vec3(0, 0, 0);

public:
	glm::mat4 getTransform();
	
	DrawableObject();
	~DrawableObject();
	virtual void Render(glm::mat4 globalModelTransform) = 0;
	virtual void Update(float deltaTime);
	glm::vec3 GetPos(); 
	glm::vec3 GetSize(); 
	void SetSize(float sizeX, float sizeY);
	void SetPosition(glm::vec3 newPosition);
	void Translate(glm::vec3 moveDistance);

	//Rotate, Scale ???

};

