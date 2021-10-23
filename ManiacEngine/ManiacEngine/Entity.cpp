#include "Entity.h"

Entity::Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame) : SpriteObject(fileName, row, column), HP(HP), MoveSpeed(MoveSpeed), IFrame(IFrame){
	this->velocity = glm::vec3(0, 0, 0); 
}

 
bool Entity::Collides(Entity other)
{
	bool CollideX = this->GetPos().x + this->GetSize().x >= other.GetPos().x && other.GetPos().x + other.GetSize().x >= this->GetPos().x;
	bool CollideY = this->GetPos().y + (this->GetSize().y * -1) >= other.GetPos().y && other.GetPos().y + (other.GetSize().y * -1) >= this->GetPos().y;
	return CollideX && CollideY;
}

bool Entity::Death()
{
	if (this->HP <= 0) { return true; }
	else { return false; }
}

/*void Entity::Render(glm::mat4 globalModelTransform)
{

}*/

void Entity::InvincibleFrame(int deltatime)
{
	if (IFrame >= 0)
	{
		IFrame--;
	}
}

void Entity::Update(int deltatime)
{
	this->Translate(velocity);
	SpriteObject::Update(deltatime);
}

void Entity::Translate(glm::vec3 moveDistance)
{
	printf("x");
	pos = pos  + moveDistance   ;
}

void Entity::TranslateVelocity(glm::vec3 velocity) {
	this->velocity = this->velocity + velocity;
	if (this->velocity.y > 10) this->velocity.y = 10;
	else if (this->velocity.y < -10) this->velocity.y = -10; 
}

void Entity::SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame)
{
	SpriteObject::SetAnimationLoop(startRow, startColumn, howManyFrame, delayBetaweenFrame);
}

void Entity::AnimationFlip()
{
	
}