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
};