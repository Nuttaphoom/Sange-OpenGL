#include "Level3.h"

using namespace glm; 
 
void Level3::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Example_Middle_Mapdata.txt");
	if (mapFile.is_open()) {
		mapFile >> MapHeight;
		mapFile >> MapWidth;
		sMiddleMapdata = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sMiddleMapdata[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
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

void Level3::LevelInit()
{
	#pragma region ground_test
	for (int i = 0 ; i < 12 ; i++)
	{ 
		InvisibleObject* ivo = new InvisibleObject();
		ivo->SetPosition(glm::vec3(i*64 - 64*4, -256, 0));
		ivo->SetSize(64, 64);
		invisibleObjectsList.push_back(ivo);
		objectsList.push_back(ivo); 
	}
	#pragma endregion 

	tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sColMapdata, "../Resource/Texture/Example_Glass_Dirt_Tile.png", 1, 3);
	for (int i = 0; i < tilemaps->GetTiles().size(); i++) {
		for (int j = 0; j < tilemaps->GetTiles()[i].size(); j++) {
			objectsList.push_back(tilemaps->GetTiles()[i][j]);
		}
	}

	for (int i = 0; i < tilemaps->GetColTiles().size(); i++) {
			invisibleObjectsList.push_back(tilemaps->GetColTiles()[i]);
			objectsList.push_back(tilemaps->GetColTiles()[i]);

	}

	Player* obj = new Player("../Resource/Texture/TestNumber.png", 4, 4, 100, 0.3, 0);
	obj->SetSize(128, -128.0f);
	obj->SetPosition(glm::vec3(-50.0f, 0.0f, 0.0f));
	obj->SetAnimationLoop(0, 0, 4, 100);
	//obj->SetColor(0.0, 1.0, 0.0);
	EntityObjectsList.push_back(obj); 
	objectsList.push_back(obj);

	player = obj;

}

void Level3::LevelUpdate()
{
 
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();

	/// Collision Check 
	// Check with Invisible Walls
	for (DrawableObject* en : EntityObjectsList) {
		if (Entity* eptr = dynamic_cast<Entity*>(en)) {
			int CollideDetection = 0;
			for (DrawableObject* i : invisibleObjectsList) {
				if (InvisibleObject* Iptr = dynamic_cast<InvisibleObject*>(i)) {
					cout << "Iptr : " << Iptr->GetPos().x << endl;
					int p = Iptr->Collide_W_Entity(*eptr);
 					if (p % 2 != 0) { //COLLIDE TOP
						if (CollideDetection % 2 == 0) CollideDetection += 1;
					}
					if ((p >> 1) % 2 != 0) { //COLLIDE BOTTOM
						if ((CollideDetection >> 1) % 2 == 0) CollideDetection += 2;
					}
					if ((p >> 2) % 2 != 0) { //COLLIDE RIGHT
						if ((CollideDetection >> 2) % 2 == 0) CollideDetection += 4;
					}
					if ((p >> 3) % 2 != 0) { //COLLIDE LEFT
						if ((CollideDetection >> 3) % 2 == 0) CollideDetection += 8;
					}
				}
				if (CollideDetection >= 8 + 4 + 2 + 1) break;
			}
			eptr->Collides_W_Inv_Wall(CollideDetection);
		}

		if (Player* playerObj = dynamic_cast<Player*>(en)) {
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


	for (DrawableObject* obj : objectsList) {
		//Player Update In every game object 
		obj->Update(deltaTime);
		
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