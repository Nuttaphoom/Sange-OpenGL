#include "Entity.h"

Entity::Entity(string fileName, int row, int column, float HP, float MoveSpeed, float IFrame) : SpriteObject(fileName, row, column), HP(HP), MoveSpeed(MoveSpeed), IFrame(IFrame){
	this->velocity = glm::vec3(0, 0, 0); 
}

 
int Entity::Collides(Entity e)
{
	int CollideDetection = 0; //Check where it collide with Entity (In Other Entity POV) 
						  // 1 FOR TOP, 2 FOR BOTTOM, 4 FOR LEFT, AND 8 FOR RIGHT 

	float LeftX_Inv_Obj = (float)this->GetPos().x - this->GetSize().x / 2;
	float RightX_Inv_Obj = (float)this->GetPos().x + this->GetSize().x / 2;

	float TOPY_Inv_Obj = (float)this->GetPos().y + this->GetSize().y * -1 / 2;
	float BOTTOMY_Inv_Obj = (float)this->GetPos().y - this->GetSize().y * -1 / 2;

	float TOP_BOTTOM_X = (float)e.GetPos().x - e.GetSize().x / 4;
	float TOP_Y = (float)e.GetPos().y + e.GetSize().y / 2 * -1;

	float Middle_1_2_X = (float)e.GetPos().x - e.GetSize().x / 2;
	float Middle_1_Y = (float)e.GetPos().y + e.GetSize().y * -1 / 4;

	float Middle_2_Y = (float)e.GetPos().y - e.GetSize().y * -1 / 4;

	float BOTTOM_Y = (float)e.GetPos().y - e.GetSize().y * -1 / 2;

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.GetSize().x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.GetSize().x / 2 > LeftX_Inv_Obj)) {
		if (TOP_Y > TOPY_Inv_Obj && TOP_Y < BOTTOMY_Inv_Obj) {
			CollideDetection += 1;
		}
	}

	//MIDDLE_LEFT
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y > TOPY_Inv_Obj && Middle_1_Y < BOTTOMY_Inv_Obj) ||
			(Middle_2_Y > TOPY_Inv_Obj && Middle_2_Y < BOTTOMY_Inv_Obj)) {
			CollideDetection += 4;
		}
	}

	//MIDDLE_RIGHT
	Middle_1_2_X += e.GetSize().x;
	if ((Middle_1_2_X < RightX_Inv_Obj && Middle_1_2_X > LeftX_Inv_Obj)) {
		if ((Middle_1_Y > TOPY_Inv_Obj && Middle_1_Y < BOTTOMY_Inv_Obj) ||
			(Middle_2_Y > TOPY_Inv_Obj && Middle_2_Y < BOTTOMY_Inv_Obj)) {
			CollideDetection += 8;
		}
	}

	//TOP 
	if ((TOP_BOTTOM_X < RightX_Inv_Obj && TOP_BOTTOM_X > LeftX_Inv_Obj) ||
		(TOP_BOTTOM_X + e.GetSize().x / 2 < RightX_Inv_Obj && TOP_BOTTOM_X + e.GetSize().x / 2 > LeftX_Inv_Obj)) {
		if (BOTTOM_Y > TOPY_Inv_Obj && BOTTOM_Y < BOTTOMY_Inv_Obj) {
			CollideDetection += 2;
		}
	}

	cout << CollideDetection << endl;
	return  CollideDetection;
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

void Entity::Collides_W_Inv_Wall(int CollisionDetection) {
	//CollisionDetection :: 1 = TOP , 2 = BOTTOM , 4 = RIGHT , 8 = LEFT 
	if (CollisionDetection % 2 != 0) { //COLLIDE TOP

	}

	if ((CollisionDetection >> 1) % 2 != 0) { //COLLIDE BOTTOM
		this->velocity.y = 0;
	}

	if ((CollisionDetection >> 2) % 2 != 0) { //COLLIDE RIGHT
		 
	}

	if ((CollisionDetection >> 3) % 2 != 0) { //COLLIDE LEFT

	}


}
