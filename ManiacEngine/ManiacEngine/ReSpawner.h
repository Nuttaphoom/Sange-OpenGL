#pragma once  
#include "GameEngine.h"
#include "Player.h"
#include "Decon.h"
#include "Observer.h"
#include "MenuHolder.h"
class ReSpawner :   public Observer  {
private :
	MenuHolder* _menuHolder ; 
	public :
	ReSpawner();
	~ReSpawner(); 
	void ReSpawn();
	void OnNotify(); 
 }; 