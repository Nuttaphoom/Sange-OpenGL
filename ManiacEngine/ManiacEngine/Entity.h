#pragma once
#include "SpriteObject.h"

class Entity : public SpriteObject
{
	float HP;
	float MoveSpeed;
	glm::vec3 velocity; 
	float IFrame;

	public:
	Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
	bool Death();
	bool Collides(Entity other);
	void InvincibleFrame(int deltatime);
	void Update(int deltatime);
	void Translate(glm::vec3 moveDistance);
	void TranslateVelocity(glm::vec3 velocity); 
};