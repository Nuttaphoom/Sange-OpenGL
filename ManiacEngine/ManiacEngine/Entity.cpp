#include "Entity.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h" 
#include "InvisibleObject.h"
#include "GameStateController.h"
void Entity::ResetVelocity() {
	this->applyingVelocity.x = 0 ;
	this->applyingVelocity.y = 0;
	this->applyingVelocity.z = 0;
}

void Entity::VelocityControl() {
	velocity += applyingVelocity;

	if (abs(velocity.x) > GetMoveSpeed() )
	{
 		velocity.x = GetMoveSpeed() * (velocity.x > 0 ? 1 : -1) ;
	}


	if ((collisionNumber >> 2) % 2 != 0) //Can't walk left
		if (velocity.x < 0) {
			velocity.x = 0;
		}
	if ((collisionNumber >> 3) % 2 != 0)  //Can't walk right
		if (velocity.x > 0) {
			velocity.x = 0;
		}

	this->Translate(velocity);
	applyingVelocity = glm::vec3(0, 0, 0);


	if (GetState() == StateMachine::CLIMBING || GetState() == StateMachine::BAT)
	{
		if (velocity.y != 0)
		{
			velocity.y = velocity.y / 200;
			if (velocity.y < 0.02 && velocity.y > -0.02)
			{
				velocity.y = 0;
			}
		}
	}
	if (velocity.x != 0 && GetState() != StateMachine::TRANSFORM)
	{
		velocity.x = velocity.x / 200;
		if (velocity.x < 0.02 && velocity.x > -0.02)
		{
			velocity.x = 0;
		}
	}
}
 Entity::Entity(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos, glm::vec3 Size, glm::vec3 collisionSize) : SpriteObject(fileName, row, column,Pos,Size), HP(HP), MoveSpeed(MoveSpeed) {
	this->velocity = glm::vec3(0, 0, 0);
	this->collisionSize = collisionSize;
	Default_pos = Pos ;
	Default_HP = HP ;
	Default_MoveSpeed = MoveSpeed ;
}

 Entity::Entity(unsigned int texture, int row, int column, float HP, float MoveSpeed,  glm::vec3 Pos, glm::vec3 Size,glm::vec3 collisionSize) : SpriteObject(texture, row, column, Pos, Size), HP(HP), MoveSpeed(MoveSpeed) {
	 this->velocity = glm::vec3(0, 0, 0);
	 this->collisionSize = collisionSize;
	 Default_pos = Pos;
	 Default_HP = HP;
	 Default_MoveSpeed = MoveSpeed;
 }


int Entity::Collides(Entity e)
{
	if (e.IsPause() || IsPause() || e.isDead() || isDead() || e.GetState() == StateMachine::HIDING || GetState() == StateMachine::HIDING || e.isInv() || isInv())
		return 0; 

	InvisibleObject* invWall = new InvisibleObject() ;
	invWall->SetPosition(GetPos());
	invWall->SetSize(collisionSize.x, abs(collisionSize.y));
	invWall->SetRender(true);
	int result = invWall->Collide_W_Entity(e);
 
	delete invWall;
	return result;	 
}

bool Entity::Death()
{
	if (this->HP <= 0) { return true; }
	else { return false; }
}


void Entity::Render(glm::mat4 globalModelTransform)
{
	if (GetState() != StateMachine::HIDING && IsPause() == false && isDead() == false) {
		SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

		GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
		GLuint modeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();
 
		glBindTexture(GL_TEXTURE_2D, GetTexture());
		if (modelMatixId == -1) {
			cout << "Error: Can't perform transformation " << endl;
			return;
		}

		glm::mat4 currentMatrix = this->getTransform();
		/*Instead of rendering it directly, we apply a scale matrix according to the DirectionSet value*/
		currentMatrix = glm::scale(currentMatrix, glm::vec3(DirectionSet, 1, 1));

		if (squareMesh != nullptr) {
			currentMatrix = globalModelTransform * currentMatrix;
			glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
			glUniform1i(modeId, _renderType);
 			squareMesh->AdjustTexcoord(GetUV());
			squareMesh->Render();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void Entity::InvincibleFrame(int deltatime)
{
	
}

void Entity::Update(int deltatime)
{
	if (IsPause())
		return; 

	SpriteObject::Update(deltatime);

	if (!OnGround && GetState() != StateMachine::CLIMBING && GetState() != StateMachine::BAT && GetState() != StateMachine::TRANSFORM && GetState() != StateMachine::CLIMBINGIDLE && GetState() != StateMachine::CLIFFEDGE && GetState() != StateMachine::CLIFFEDGEDOWN) { //Apply velocity 
		TranslateVelocity(glm::vec3(0, -600.0f / 1000.0f * deltatime, 0));
 	}	
 

	 
	VelocityControl(); 

	
}

void Entity::Translate(glm::vec3 moveDistance)
{
 	pos.x = pos.x +( moveDistance.x / 1000 * GameEngine::GetInstance()->GetDeltaTime()) ;
	pos.y = pos.y + (moveDistance.y / 1000 * GameEngine::GetInstance()->GetDeltaTime());

}

void Entity::TranslateVelocity(glm::vec3 velocity) {
	this->applyingVelocity.x += velocity.x    ;
	this->applyingVelocity.y += velocity.y     ;
	this->applyingVelocity.z += velocity.z      ;
}

void Entity::SetVelocity(glm::vec3 velocity) {
	this->velocity = velocity;
}

void Entity::SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame, bool loop)
{
	SpriteObject::SetAnimationLoop(startRow, startColumn, howManyFrame, delayBetaweenFrame,loop);
}

 

void Entity::Collides_W_Inv_Wall(int CollisionDetection, glm::vec3 ivbObj[4][2]) {
 	//CollisionDetection :: 1 = TOP , 2 = BOTTOM , 4 = RIGHT , 8 = LEFT 
	if (CollisionDetection % 2 != 0) { //COLLIDE TOP
		this->velocity = glm::vec3(this->velocity.x, 0, this->velocity.z);
	}
	 
	if ((CollisionDetection >> 1) % 2 != 0) { //COLLIDE BOTTOM
		if (!OnGround) {
			OnGround = true;
			this->velocity = glm::vec3(this->velocity.x, 0, this->velocity.z); 
			this->SetPosition ( glm::vec3(GetPos().x,ivbObj[1][0].y + ivbObj[1][1].y  + ivbObj[1][1].y / 2  , GetPos().z));
 		}
	}
	else {
 		OnGround = false; 
	}

	if ((CollisionDetection >> 2) % 2 != 0) { //COLLIDE LEFT
		//this->TranslateVelocity(glm::vec3(this->GetVelocity().x * -1, 0,0));
		//this->SetPosition(glm::vec3(ivbObj[2][0].x + ivbObj[2][1].x + ivbObj[2][1].x / 2 + 1 , GetPos().y, GetPos().z));

	}

	if ((CollisionDetection >> 3) % 2 != 0) { //COLLIDE RIGHT
		//this->TranslateVelocity(glm::vec3(this->GetVelocity().x * -1, 0, 0));
		//this->SetPosition(glm::vec3(ivbObj[3][0].x - ivbObj[3][1].x - ivbObj[3][1].x / 2 - 1,GetPos().y, GetPos().z));
	}

	collisionNumber = CollisionDetection;
	
}

float Entity::GetMoveSpeed()
{
	return MoveSpeed;
}

void Entity::SetDirection(int x)
{
	DirectionSet = x;
}

glm::vec3 Entity::GetVelocity()
{
	return velocity;
}

void Entity::OnDamaged(int damage) {
 	if (IsPause())
		true;

	HP -= damage;
	if (HP <= 0) {
		ChangeState(StateMachine::Die);
	}

 
}

void Entity::ChangeState(StateMachine s) {

}


float Entity::GetHP() {
	return HP; 
}

bool Entity::isDead() {
	if (HP > 0) return false; 
	return true;
}

void Entity::Attack(Entity* target) {
	InvisibleObject invWALL;

	invWALL.SetPosition(glm::vec3(this->GetPos().x + (64 * this->DirectionSet), this->GetPos().y, 1));

	if (invWALL.Collide_W_Entity(*target)) {
		target->OnDamaged(1);
	}
}

StateMachine Entity::GetState() {
	return stateMachine; 
}


void Entity::SetHP(float data)
{
	HP = data;
}


void Entity::RespawnThisObject() {
	SetPause(false);
	SetDirection(1);
	ChangeState(StateMachine::IDLE); 
	SetPosition(Default_pos); 
	this->HP = Default_HP;  
	this->MoveSpeed = Default_MoveSpeed; 
}

int Entity::GetDirection()
{
	return DirectionSet;
}

void Entity::Stop()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Entity::Heal(int heal) {
	if (HP < 4) {
		HP += heal;
	}
}

void Entity::SetRenderType(int x) {
	_renderType = x;
}