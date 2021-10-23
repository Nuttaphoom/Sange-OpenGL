#pragma once
#include "SpriteObject.h"

class Entity : public SpriteObject
{
	float HP;
	float MoveSpeed;
	glm::vec3 velocity; 
	float IFrame;
	float DirectionSet = -1;

	public:
	Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame);
	bool Death();
	bool Collides(Entity other);
	//void Render(glm::mat4 globalModelTransform);
	void InvincibleFrame(int deltatime);
	void Update(int deltatime);
	void Translate(glm::vec3 moveDistance);
	void TranslateVelocity(glm::vec3 velocity); 
	void SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame);
	void AnimationFlip();
};