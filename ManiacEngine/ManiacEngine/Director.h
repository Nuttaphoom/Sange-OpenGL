#pragma once
#include "SpriteObject.h"
#include "Level.h"
#include "GameStateList.h"


class Director : public SpriteObject {
protected:
	vector<DrawableObject*> storagePic;
	float lifespan;
	float scPausetimeMax;
	float scPausetimeCount;
	int count = 0;
	bool ScPausetime = false;
	GameState _levelToLoad; 
public :
	Director(vector<DrawableObject*> scenes, float offsetX,GameState levelLoad,float lifespan,float scPausetime);
	void Update(int deltatime);
};