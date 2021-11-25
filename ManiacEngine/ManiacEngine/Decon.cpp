#include "Decon.h"
#include "InvisibleObject.h"
void Decon::Attack(Entity* target) {
	InvisibleObject invWALL; 

	invWALL.SetPosition(glm::vec3(this->GetPos().x + (64 * this->DirectionSet), this->GetPos().y ,1));

	if (invWALL.Collide_W_Entity(*target)) {
		target->OnDamaged(1) ; 
	}
}