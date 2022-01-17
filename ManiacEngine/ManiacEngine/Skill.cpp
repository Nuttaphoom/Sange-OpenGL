#ifndef SKILLH
#define SKILLH

#include "Player.h"

class Skill {
	private :
		bool unlocked = false ; 
		float cooldown = 0.00f; 
		float maxCooldown = 0.00f; 

	public :
		Skill(float maxCooldown) {
			this->maxCooldown = maxCooldown; 
			this->unlocked = false; 
		}

		virtual void UnlockAbility() {
			unlocked = true; 
		}
};

 

#endif 
