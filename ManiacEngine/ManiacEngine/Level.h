#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "GameData.h"
#include "ImageObject.h"
#include "SpriteObject.h"
#include "Button.h" 
#include "TileMap.h"
#include "InvisibleObject.h" 
#include "Player.h"
#include <fstream>


class Level
{
private:
	vector<DrawableObject*> objectsList;
	vector< DrawableObject*> invisibleObjectsList;
	vector < DrawableObject*> EntityObjectsList;
	Player* player;

	TileMap* tilemaps;
	int MapHeight;
	int MapWidth;
	int** sMiddleMapdata;
	int** sColMapdata;
	int** sFrontMapData;
public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate();
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);

	void WorldToCam(float& x, float& y);
};
