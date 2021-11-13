#pragma once
#include "InteractableObject.h"
#include <vector>
#include "Entity.h"
using namespace std;

class InteractableObjectManager {
	vector<InteractableObject*> interactableObjects;
	public:
		void addInteractableObjects(InteractableObject* io);
		void DelInteractableObjects(InteractableObject* io);
		void notify(Entity* e); 
};