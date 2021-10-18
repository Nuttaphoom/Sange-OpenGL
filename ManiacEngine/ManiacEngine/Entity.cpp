#include "Entity.h"

Entity::Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame) : SpriteObject(fileName, row, column), HP(HP), MoveSpeed(MoveSpeed), IFrame(IFrame){

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

void Entity::InvincibleFrame(float deltatime)
{
	if (IFrame >= 0)
	{
		IFrame--;
	}
}

void Entity::Update(float deltatime)
{

}

void Entity::Translate(glm::vec3 moveDistance)
{
	pos.x = pos.x + moveDistance.x;
}