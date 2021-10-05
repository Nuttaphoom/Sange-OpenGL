#include "LevelTest.h"
#include <fstream>

int MapHeight ;
int MapWidth ;
static int** sMapdata;
void LevelTest::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Card.txt");
	if (mapFile.is_open()) {
		mapFile >> MapHeight;
		mapFile >> MapWidth;
		sMapdata = new int* [MapHeight];
		for (int y = 0;y < MapHeight;y++) {
			sMapdata[y] = new int[MapWidth];
			for (int x = 0;x < MapWidth;x++) {
				mapFile >> sMapdata[y][x];
				//cout << sMapdata[y][x] << endl;
				
			}
		}
		mapFile.close();
		for (int i = 0;i < MapHeight;i++) {
			for (int j = 0;j < MapWidth;j++) {
				cout << sMapdata[i][j] << "\t";
			}
			cout << endl;
		}
		
	}

	//cout << "Load Level" << endl;
}

void LevelTest::LevelInit()
{
	GameObject* obj = new GameObject();
	obj->SetColor(0.0, 1.0, 0.0);
	objectsList.push_back(obj);

	player = obj;

	GameObject* obj2 = new GameObject();
	obj2->SetColor(0.0, 0.0, 1.0);
	obj2->SetPosition(glm::vec3(2.0f, 2.0f, 0.0f));
	objectsList.push_back(obj2);

	GameObject* obj3 = new GameObject();
	obj3->SetColor(0.0, 0.0, 1.0);
	obj3->SetPosition(glm::vec3(-2.0f, -2.0f, 0.0f));
	objectsList.push_back(obj3);



	//cout << "Init Level" << endl;
}

void LevelTest::LevelUpdate()
{
 
	//cout << "Update Level" << endl;
}

void LevelTest::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
 	//cout << "Draw Level" << endl;
}

void LevelTest::LevelFree()
{
	/*for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
<<<<<<< Updated upstream
	//cout << "Free Level" << endl;
=======
	cout << "Free Level" << endl;*/
//>>>>>>> Stashed changes
}

void LevelTest::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void LevelTest::HandleKey(char key)
{

	switch (key)
	{
	case 'w': player->Translate(glm::vec3(0, 0.3, 0)); break;
	case 's': player->Translate(glm::vec3(0, -0.3, 0)); break;
	case 'a': player->Translate(glm::vec3(-0.3, 0, 0)); break;
	case 'd': player->Translate(glm::vec3(0.3, 0, 0)); break;
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL3; ; break;
	}
}

void LevelTest::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	realX = x;
	realY = y;

	player->SetPosition(glm::vec3(realX, realY, 0));
}