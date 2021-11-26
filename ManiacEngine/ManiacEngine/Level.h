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
#include "CameraController.h"
#include "InteractableObjectManager.h"
#include "Flower.h"
#include "HPBar.h"
#include "CheckPoint.h"
#include "Raycast.h"
#include "Decon.h"
#include <fstream>
#include "ReSpawner.h"

class Level
{
private:
	vector<DrawableObject*> objectsList;
	vector< DrawableObject*> invisibleObjectsList;
	vector < DrawableObject*> EntityObjectsList;
	vector <DrawableObject*>   GUIObjectsList;

	Player* player;

	CameraController* cameraController;

	InteractableObjectManager interactableManager;
	CheckPoint* checkPoint;

	TileMap* tilemaps;
	int MapHeight;
	int MapWidth;
	int** sMiddleMapdata;
	int** sColMapdata;
	int** sFrontMapData;
	int** sBackGroundMapData;
	ReSpawner* respawner; 
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

	#pragma region getter 
	virtual vector<DrawableObject*> GetInvisibleWallList() { return this->invisibleObjectsList; }
	virtual vector<DrawableObject*> GetEntityList() { return this->EntityObjectsList; }
	virtual vector<DrawableObject*> GetGUIObjectsList() { return this->GUIObjectsList; }
	#pragma endregion 
};
