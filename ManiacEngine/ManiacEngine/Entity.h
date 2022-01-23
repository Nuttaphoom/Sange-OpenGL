#pragma once
#include "SpriteObject.h"
enum class StateMachine {
	IDLE,
	RUNNING,
	JUMPPING,
	HOPPING,
	MIDJUMP,
	FALLING,
	LANDING,
	ATTACKING,
	CHASING,
	HIDING,
};

class Entity : public SpriteObject
{
	protected:
		float HP;
		float MoveSpeed;
		glm::vec3 velocity; 
		glm::vec3 applyingVelocity; 
		float IFrame;
		enum StateMachine stateMachine ;
		int collisionNumber; //1 = TOP, 2 = BOTTOM , 3 = LEFT , 4 = RIGHT  

	/*Default Value that will be used when we respawn this obj*/ 
		glm::vec3 Default_pos; 
		float Default_HP;  
		float Default_MoveSpeed;

	public:
		bool OnGround = false;
		int DirectionSet = 1;

		//Will be changed when StateMachine is changed 
		glm::vec3 collisionSize;

		Entity(string fileName, int row, int column, float HP, float MoveSpeed, glm::vec3 Pos,glm::vec3 Size);
		virtual bool Death();
		virtual void Render(glm::mat4 globalModelTransform);
		virtual int Collides(Entity e);
		virtual void Collides_W_Inv_Wall(int CollisionDetection, glm::vec3 ivbObj[4][2]);
 		virtual void InvincibleFrame(int deltatime);
		virtual void Update(int deltatime);
		virtual void Translate(glm::vec3 moveDistance);
		virtual void TranslateVelocity(glm::vec3 velocity);
		virtual void SetAnimationLoop(int startRow, int startColumn, int howManyFrame, int delayBetaweenFrame);
 		virtual float GetMoveSpeed();
		virtual void SetDirection(int x);
		virtual void OnDamaged(int damage); 
		virtual void Attack(Entity* target) ;
		virtual bool isDead();
		virtual glm::vec3 GetVelocity();
		virtual void RespawnThisObject(); 
		virtual void VelocityControl();
		StateMachine  GetState();
		float GetHP(); 
};