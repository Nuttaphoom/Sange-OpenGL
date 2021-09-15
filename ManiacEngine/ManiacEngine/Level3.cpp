#include "Level3.h"

using namespace glm; 
 
void Level3::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	//cout << "Load Level" << endl;
}

void Level3::LevelInit()
{
	GameObject* obj = new GameObject();
	obj->SetColor(1.0, 1.0, 0.0);
	objectsList.push_back(obj);

	player = obj;
	/*
	GameObject* obj2 = new GameObject();
	obj2->SetColor(0.0, 0.0, 1.0);
	obj2->SetPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	objectsList.push_back(obj2);

	GameObject* obj3 = new GameObject();
	obj3->SetColor(0.0, 0.0, 1.0);
	obj3->SetPosition(glm::vec3(-2.0f, -2.0f, 0.0f));
	objectsList.push_back(obj3);
	*/
	//cout << "Init Level" << endl;
}

void Level3::LevelUpdate()
{
	//cout << "Update Level" << endl;
	
	//Player out of bound 
	/*if (player->GetPos().x > 3.5) player->SetPosition(glm::vec3(player->GetPos().x * -1 + 1,player->GetPos().y,1)); 
	if (player->GetPos().x < -3.5) player->SetPosition(glm::vec3(player->GetPos().x * -1 - 1, player->GetPos().y, 1));
	if (player->GetPos().y < -3.5) player->SetPosition(glm::vec3(player->GetPos().x, player->GetPos().y * -1 - 1 , 1));
	if (player->GetPos().y > 3.5) player->SetPosition(glm::vec3(player->GetPos().x, player->GetPos().y * -1 + 1, 1));
	*/
	//cout << player->GetPos().x + (player->GetSize().x / 2) << endl; 

 }

void Level3::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void Level3::LevelFree()
{
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
}

void Level3::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void Level3::HandleKey(char key)
{

	switch (key)
	{
	case 'w': player->Translate(glm::vec3(0, 0.3, 0)); break;
	case 's': player->Translate(glm::vec3(0, -0.3, 0)); break;
	case 'a': player->Translate(glm::vec3(-0.3, 0, 0)); break;
	case 'd': player->Translate(glm::vec3(0.3, 0, 0)); break;
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL1; ; break;

	}
}

void Level3::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = (x - 300)   ;
	realY = (y - 300)   ;
	realX = (realX / 300)  	; 
	realY = (realY / 300)  	;

	cout << realX << "A,A" << realY << endl;

	player->SetPosition(glm::vec3(realX, realY, 0));
}