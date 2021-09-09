
#include "GameEngine.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine()
{
	renderer = nullptr;
}

GameEngine * GameEngine::GetInstance()
{
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return instance;
}

GLRenderer * GameEngine::GetRenderer()
{
	return this->renderer;
}

void GameEngine::Init(int width, int height)
{
	winWidth = width;
	winHeight = height;
	renderer = new GLRenderer(width, height);
	renderer->InitGL("../Resource/Shader/vertext.shd", "../Resource/Shader/fragment.shd");
	SetDrawArea(-3, 3, -3, 3);
	SetBackgroundColor(1.0f, 1.0f, 200.0f / 255);

}

void GameEngine::Render(vector<DrawableObject*> renderObjects)
{
	this->GetRenderer()->Render(renderObjects);
}

void GameEngine::SetDrawArea(float left, float right, float bottom, float top)
{
	renderer->SetOrthoProjection(-3, 3, -3, 3);
}

void GameEngine::SetBackgroundColor(float r, float g, float b)
{
	renderer->SetClearColor(1.0f, 1.0f, 200.0f / 255);
}

void GameEngine::AddMesh(string name, MeshVbo* mesh)
{
	renderer->AddMesh(name, mesh);
}

void GameEngine::ClearMesh()
{
	renderer->ClearMesh();
}

int GameEngine::GetWindowWidth()
{
	return winWidth;
}

int GameEngine::GetWindowHeight()
{
	return winHeight;
}