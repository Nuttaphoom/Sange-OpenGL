#pragma once
#pragma once
#include "Level.h"

class Level3 : public Level
{
private:
	vector<DrawableObject*> objectsList;
	GameObject* player;

public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);
};
