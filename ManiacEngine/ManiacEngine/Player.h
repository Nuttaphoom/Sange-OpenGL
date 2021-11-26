#ifndef ENTITY
#define ENTITY

#include "Entity.h"
#include "Subject.h"
#include "Observer.h"

enum class StateMachine {
	IDLE,
	RUNNING,
	JUMPPING,
	HOPPING,
	MIDJUMP,
	FALLING,
	LANDING
};

class Player : public Entity, public Subject
{
	private :
	static Player* instance;
	enum StateMachine PlayerState;
 	
	public :
	Player(string fileName, int row, int column, float HP, glm::vec3 Pos, glm::vec3 Size);
	StateMachine GetState();
	void Update(int deltatime);
	void UpdateStateMachine(float deltatime);
 	void ChangeState(StateMachine NextState);
	void Translate(glm::vec3 moveDistance);
	void HandleKey(char key);
	void HandleMouse(glm::vec3 mouseRealPos);  
	virtual void Attack(Entity* target);
	 
	static Player* GetInstance();
	static Player* GetInstance(string fileName, int row, int column, float HP, glm::vec3 Pos, glm::vec3 Size);

	void OnDamaged(int damage);

 };




#endif ; 