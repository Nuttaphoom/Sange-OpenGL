#pragma once
#include "InteractableObjectManager.h"
#include "Player.h"


void InteractableObjectManager::addInteractableObjects(InteractableObject* io) {
	interactableObjects.push_back(io);
}
void InteractableObjectManager::DelInteractableObjects(InteractableObject* io) {
	for (int i = 0; i < interactableObjects.size(); i++) {
		if (interactableObjects[i] == io) {
			interactableObjects.erase(interactableObjects.begin() + i);
			return;
		}
	}

	cout << "ERROR - Can't Delete the Interactable Object" << endl;
	cout << "See more in InteractableObjectManager.cpp";
}

void InteractableObjectManager::HandleKey(char key) {
	switch (key) {
	case 'e': 	notify(Player::GetInstance()); break;
	}

}

void InteractableObjectManager::notify(Entity* e) {
 	for (int i = 0; i < interactableObjects.size(); i++)
		interactableObjects[i]->isCalled(e);
}

  

 void InteractableObjectManager::Update(int deltaTime) {
	 for (int i = 0; i < interactableObjects.size(); i++)
		 interactableObjects[i]->Update(deltaTime);
 }
