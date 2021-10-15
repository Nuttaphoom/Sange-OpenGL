#pragma once
#include "SpriteObject.h"

class Entity : public SpriteObject
{
	float HP;
	float MoveSpeed;
	float IFrame;

	public:
	Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
	bool Death();
	bool Collides(Entity other);
	void InvincibleFrame(float deltatime);
	void Update(float deltatime);
	void Translate(glm::vec3 moveDistance);
};