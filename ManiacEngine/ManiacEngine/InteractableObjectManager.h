#pragma once
#include "InteractableObject.h"
#include <vector>
#include "Entity.h"
#include "Flower.h"
#include "Trap.h"
#include "Hiding.h" 
using namespace std;

class InteractableObjectManager {
	vector<InteractableObject*> interactableObjects;
	public:
		virtual void HandleKey(char key);
		void addInteractableObjects(InteractableObject* io);
		void DelInteractableObjects(InteractableObject* io);
		void notify(Entity* e); 
		void Update(int deltaTime);
		void RespawnThisObject();
 };