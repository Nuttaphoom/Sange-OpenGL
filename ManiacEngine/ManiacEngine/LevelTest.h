#pragma once
#include "Level.h"
#include "TriangleMeshVbo.h"
#include "SquareMeshVbo.h"
class LevelTest : public Level
{
private:
	vector<DrawableObject*> objectsList;
	SpriteObject* player;
	TileMap* tilemaps;

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
