#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "Camera.h"
#include "GameData.h"

using namespace std;
class GameEngine
{
	static GameEngine* instance;
	int winWidth, winHeight;
	
	GLRenderer *renderer;
	GameEngine();
public:
	static GameEngine* GetInstance();
	GLRenderer * GetRenderer();
	void Init(int width, int height);
	void SetDrawArea(float left, float right, float bottom, float top);
	void SetBackgroundColor(float r, float g, float b);
	void AddMesh(string name, MeshVbo* mesh);
	void ClearMesh();
	void Render(vector<DrawableObject*> renderObjects);
	int GetWindowWidth();
	int GetWindowHeight();
};