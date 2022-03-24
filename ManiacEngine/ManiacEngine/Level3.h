#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "GameData.h"
#include "ImageObject.h"
#include "SpriteObject.h"
#include "Button.h" 
#include "InvisibleObject.h" 
#include "Level.h" 

class Level3 : public Level
{
private:

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
	virtual vector<DrawableObject*> GetInvisibleWallList() { return invisibleObjectsList; }
	virtual vector<DrawableObject*> GetEntityList() { return EntityObjectsList; }
	virtual vector<DrawableObject*> GetGUIObjectsList() { return GUIObjectsList; }
#pragma endregion 
};
