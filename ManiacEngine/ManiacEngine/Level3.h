#pragma once
#pragma once
#include "Level.h"
#include "Player.h"
#include "Enemy.h"

class Level3 : public Level
{
private:
	vector<DrawableObject*> objectsList;
	vector< DrawableObject*> invisibleObjectsList;
	vector < DrawableObject*> EntityObjectsList;
	Player* player;
	Enemy* enemy;
	CameraController* cameraController;
 	int MapHeight;
	int MapWidth;
	int** sBackGroundMapData ;
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

#pragma region getter 
	vector<DrawableObject*> GetInvisibleWallList() { 
		return Level3::invisibleObjectsList; }
	vector<DrawableObject*> GetEntityList() { return Level3::EntityObjectsList; }

#pragma endregion 
};
