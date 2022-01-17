#ifndef ENTITY
#define ENTITY

#include "Entity.h"
#include "Subject.h"
#include "Observer.h"
#include "Skill.cpp"



class Player : public Entity, public Subject
{
	private :
		static Player* instance;
 

	public :
		Player(string fileName, int row, int column, float HP, glm::vec3 Pos, glm::vec3 Size);
 		void Update(int deltatime);
		void UpdateStateMachine(float deltatime);
		void UpdateCollision(); 
  		void ChangeState(StateMachine NextState);
		void Translate(glm::vec3 moveDistance);
		void HandleKey(char key);
		void HandleMouse(glm::vec3 mouseRealPos);  
		virtual void Attack(Entity* target);
		virtual void RespawnThisObject();
	 
		static Player* GetInstance();
		static Player* GetInstance(string fileName, int row, int column, float HP, glm::vec3 Pos, glm::vec3 Size);

		void OnDamaged(int damage);

 };




#endif  