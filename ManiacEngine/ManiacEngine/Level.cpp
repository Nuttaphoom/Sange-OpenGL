#include "Level.h"
#include "ImageObject.h"

void Level::LevelLoad()
{
	SquareMeshVbo * square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	GameObject * obj = new GameObject();
	obj->SetColor(1.0, 0.0, 0.0);
	objectsList.push_back(obj);

	player = obj;

	ImageObject* img = new ImageObject();
	img->SetSize(2.0f, -2.0f);
	img->SetTexture("../Resource/Texture/penguin.png");
	objectsList.push_back(img);

	ImageObject* img2 = new ImageObject(); 
	img2->SetPosition(glm::vec3(3,3,1));
	img2->SetSize(1.0f, -2.0f); 
	img2->SetTexture("../Resource/Texture/cartoon.PNG");
	objectsList.push_back(img2);

	//cout << "Init Level" << endl;
}

void Level::LevelUpdate()
{
	//cout << "Update Level" << endl;
}

void Level::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void Level::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void Level::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void Level::HandleKey(char key)
{

	switch (key)
	{
		case 'w': player->Translate(glm::vec3(0, 0.3, 0)); break;
		case 's': player->Translate(glm::vec3(0, -0.3, 0)); break;
		case 'a': player->Translate(glm::vec3(-0.3, 0, 0)); break;
		case 'd': player->Translate(glm::vec3(0.3, 0, 0)); break;
		case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2; ; break;

		case 'g': Camera::GetInstance()->Translate(0.3f, 0);  break;//Move the cam 
			 
	}
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = (x - 300);
	realY = (y - 300);
	realX = (realX / 300);
	realY = (realY / 300);

	cout << realX << "A,A" << realY << endl;

	player->SetPosition(glm::vec3(realX, realY, 0));
}