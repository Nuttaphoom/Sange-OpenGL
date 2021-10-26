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
	#pragma region ground_test
	for (int i = 0 ; i < 12 ; i++)
	{ 
	InvisibleObject* ivo = new InvisibleObject();
	ivo->SetPosition(glm::vec3(i*64 - 64*4, -128, 0));
	ivo->SetSize(64, 64);
	objectsList.push_back(ivo);
	}
	#pragma endregion 

	Player* obj = new Player("../Resource/Texture/Sange/SangeRunning.png", 1, 8, 100, 0.3, 0);
	obj->SetSize(128, -128.0f);
	obj->SetPosition(glm::vec3(-50.0f, 0.0f, 0.0f));
	obj->SetAnimationLoop(0, 0, 8, 100);
	//obj->SetColor(0.0, 1.0, 0.0);
	objectsList.push_back(obj);
	/*Entity* E1 = new Entity("../Resource/Texture/TestSprite.png", 4, 7, 100.0, 9.0, 0.0);
	E1->SetSize(200.0f, -200.0f);
	E1->SetPosition(glm::vec3(50.0f, 0.0f, 0.0f));
	E1->SetAnimationLoop(0, 0, 27, 50);
	objectsList.push_back(E1);
	Entity* E2 = new Entity("../Resource/Texture/TestSprite.png", 4, 7, 100.0, 9.0, 0.0);
	E2->SetSize(200.0f, -200.0f);
	E2->SetPosition(glm::vec3(-50.0f, 0.0f, 0.0f));
	E2->SetAnimationLoop(0, 0, 27, 50);
	objectsList.push_back(E2);*/
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

	/*SpriteObject* SangeTest = new SpriteObject("../Resource/Texture/Sange/SangeRunning.png", 1, 8);
	SangeTest->SetSize(200.0f, -200.0f);
	SangeTest->SetPosition(glm::vec3(-50.0f, 0.0f, 0.0f));
	SangeTest->SetAnimationLoop(0, 0, 8, 50);
	objectsList.push_back(SangeTest);*/
}

void Level3::LevelUpdate()
{
 
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();

	for (DrawableObject* obj : objectsList) {
		//Player Update In every game object 
		obj->Update(deltaTime);

		/// Collision Check 
		/// Collision Check 
		if (InvisibleObject* Iptr = dynamic_cast<InvisibleObject*>(obj)) { //Entity Collide With Collision 
			for (DrawableObject* nObj : objectsList) {
				if (Entity* eptr = dynamic_cast<Entity*>(nObj)) {
					eptr->Collides_W_Inv_Wall(Iptr->Collide_W_Entity(*eptr));
				}
			}
		}

		else if (Player* playerObj = dynamic_cast<Player*>(obj)) {
			for (DrawableObject* nObj : objectsList) {
				if (Entity* eptr2 = dynamic_cast<Entity*>(nObj)) {
					if (playerObj != eptr2) {
						if (playerObj->Collides(*eptr2)) {
							cout << "ENTITY COL" << endl;
						}
					}
				}
			}
		}

 





	}

 
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
		case 'w': player->HandleKey('w'); break;
		case 's': player->HandleKey('s'); break;
		case 'a': player->HandleKey('a'); break;
		case 'd': player->HandleKey('d'); break;
		case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL1; ; break;
		case 'g': Camera::GetInstance()->Translate(10.0f, 0);  break;//Move the cam to right
		case 'f': Camera::GetInstance()->Translate(-10.0f, 0); break;//Move the cam to left  
		case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
		case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	}
}

void Level3::HandleMouse(int type, int x, int y)
{
	Level::HandleMouse(type, x, y); 
}