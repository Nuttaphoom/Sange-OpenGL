#include "LevelTest.h"
#include <fstream>



void LevelTest::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	ifstream mapFile("../Resource/Map/Example_Middle_Mapdata.txt");
	if (mapFile.is_open()) {
		mapFile >> MapHeight;
		mapFile >> MapWidth;
		sMiddleMapdata = new int* [MapHeight];
		for (int y = 0;y < MapHeight;y++) {
			sMiddleMapdata[y] = new int[MapWidth];
			for (int x = 0;x < MapWidth;x++) {
				mapFile >> sMiddleMapdata[y][x];
			}
		}
		mapFile.close();
 	}

	ifstream FrontMapFile("../Resource/Map/Example_Front_Mapdata.txt");
	if (FrontMapFile.is_open()) {
		FrontMapFile >> MapHeight;
		FrontMapFile >> MapWidth;
		sFrontMapData = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sFrontMapData[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				FrontMapFile >> sFrontMapData[y][x];
			}
		}
		FrontMapFile.close();
	}

	ifstream cMapFile("../Resource/Map/Col_Example_Mapdata.txt");
	if (cMapFile.is_open()) {
		cMapFile >> MapHeight;
		cMapFile >> MapWidth;
		sColMapdata = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sColMapdata[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				cMapFile >> sColMapdata[y][x];
			}
		}
		cMapFile.close();
 	}

	//cout << "Load Level" << endl;
}

void LevelTest::LevelInit()
{
 
	/*tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/Example_Glass_Dirt_Tile.png", 1, 3);
	for (int i = 0; i < tilemaps->GetTiles().size(); i++) {
		for (int j = 0; j < tilemaps->GetTiles()[i].size(); j++) {
			objectsList.push_back(tilemaps->GetTiles()[i][j]);
		}
	}

	for (int i = 0; i < tilemaps->GetColTiles().size(); i++) {
		invisibleObjectsList.push_back(tilemaps->GetColTiles()[i]);
		objectsList.push_back(tilemaps->GetColTiles()[i]);
	}*/

	Player* obj = Player::GetInstance("../Resource/Texture/TestNumber.png", 4, 4, 5, 0.3, 0);
	obj->SetSize(128, -128.0f);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
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
	/*for (int i = objectsList.size() - 1; i >= 0; i--) {
		delete objectsList[i];
	}*/

	delete player;
	delete cameraController;
	delete tilemaps;
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
	case 'w': player->Translate(glm::vec3(0.0, 10, 0)); break;
	case 's': player->Translate(glm::vec3(0.0, -10, 0)); break;
	case 'a': player->Translate(glm::vec3(-10, 0, 0)); break;
	case 'd': player->Translate(glm::vec3(10, 0, 0)); break;
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
	case 'e': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL3;    ; break;
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