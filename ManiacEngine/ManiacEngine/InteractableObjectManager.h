#pragma once
#include "InteractableObject.h"
#include <vector>
using namespace std;

class InteractableObjectManager {
	vector<InteractableObject*> interactableObjects;
	public:
		void addInteractableObjects(InteractableObject* io);
		void DelInteractableObjects(InteractableObject* io);
};