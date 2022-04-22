#pragma once  
#include "GameEngine.h"
#include "Player.h"
#include "Decon.h"
#include "Observer.h"

class ReSpawner : public Observer  {
 
	public :
	ReSpawner();
	~ReSpawner(); 
	void ReSpawn();
	void OnNotify(); 
}; 