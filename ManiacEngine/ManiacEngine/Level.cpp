#include "Level.h"
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;



void Level::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_1/Example_Middle_Mapdata.txt");
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


	ifstream FrontMapFile("../Resource/Map/Level_1/Example_Front_Mapdata.txt");
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

	ifstream cMapFile("../Resource/Map/Level_1/Col_Example_Mapdata.txt");
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

	ifstream BackGroundMapFile("../Resource/Map/Level_1/Example_Background_Mapdata.txt");
	if (BackGroundMapFile.is_open()) {
		BackGroundMapFile >> MapHeight;
		BackGroundMapFile >> MapWidth;
		sBackGroundMapData = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sBackGroundMapData[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				BackGroundMapFile >> sBackGroundMapData[y][x];
				//cout << sBackGroundMapData[y][x] << "     "; 
			}
			//cout << endl; 
		}
		BackGroundMapFile.close();
	}

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	#pragma region RAYCAST_TSET 
	glm::vec3 P1 = glm::vec3(-5, 0, 1);

	glm::vec3 P2 = glm::vec3(-50, -100, 1);

	InvisibleObject* ivo = new InvisibleObject();
	ivo->SetPosition(glm::vec3(-25, -50, 0));
	ivo->SetSize(64, 64);
	invisibleObjectsList.push_back(ivo);
	objectsList.push_back(ivo);

	glm::vec3 outputvec = RayCast(P1, P2);
	cout << "Lenght" << outputvec.x << "," << outputvec.y << endl;
	#pragma endregion 
	checkPoint = CheckPoint::GetInstance();


	#pragma region tilemaps
	tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/Example_Glass_Dirt_Tile.png", 21, 40);
	for (int i = 0; i < tilemaps->GetTiles().size(); i++) {
		for (int j = 0; j < tilemaps->GetTiles()[i].size(); j++) {
			objectsList.push_back(tilemaps->GetTiles()[i][j]);
		}
	}

	for (int i = 0; i < tilemaps->GetColTiles().size(); i++) {
		invisibleObjectsList.push_back(tilemaps->GetColTiles()[i]);
		objectsList.push_back(tilemaps->GetColTiles()[i]);
	}

	#pragma endregion 

	#pragma region interactableObject 
	Flower* flower_1 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(glm::vec3(-64 * 2, -64 * 9 + 15, 0)), glm::vec3(64,-64,1));
 
	interactableManager.addInteractableObjects(flower_1);
	objectsList.push_back(flower_1);

	#pragma endregion 



	#pragma region ground_test
	for (int i = 0; i < 12; i++)
	{
		InvisibleObject* ivo = new InvisibleObject();
		ivo->SetRender(true);
		ivo->SetPosition(glm::vec3(64, -256 - 64 * i, 0));
		ivo->SetSize(64, 64);
		invisibleObjectsList.push_back(ivo);
		objectsList.push_back(ivo);
	}
	#pragma endregion 
#pragma region Entities 
	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite_Re.png", 3, 10, 3, glm::vec3(-50.0f, 0.0f, 0.0f),glm::vec3(128,-128,0));
	obj->SetAnimationLoop(0, 0, 4, 100);
 	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	Decon* test = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(300.0f, 0.0f, 0.0f), glm::vec3(128, -128,1), glm::vec3(700.0f, 0.0f, 0.0f), glm::vec3(200.0f, 0.0f, 0.0f));
	test->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test);
	objectsList.push_back(test);

	Decon* test2 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(128.0, -128.0f, 1),glm::vec3(2000,0,1), glm::vec3(1101, -280, 0.0f), glm::vec3(2026, -280, 0.0f));
	test2->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test2);
	objectsList.push_back(test2);
#pragma endregion
	respawner = new ReSpawner();


	#pragma region GUI 
	GUI* SangeImage = new GUI("../Resource/Texture/GUI/Sange.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0),glm::vec3(1668 / 11, 2224 / 11 * -1,1));
 
	objectsList.push_back(SangeImage);

	//HPBar* hpbar = new HPBar("../Resource/Texture/GUI/HPPoint.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 165, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 150, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(238, 448 * -1,1));
	HPBar* hpbar = new HPBar("../Resource/Texture/GUI/HPPoint.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1),glm::vec3(0,0,0));
	
	objectsList.push_back(hpbar);
	#pragma endregion


	 

	//cout << "Init Level" << endl;

}

void Level::LevelUpdate()
{
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 
	// Check with Invisible Walls
	for (DrawableObject* en : EntityObjectsList) {
		if (Entity* eptr = dynamic_cast<Entity*>(en)) {
			if (eptr->isDead())
				continue;

			int CollideDetection = 0;
			glm::vec3 ivbobjs[4][2];
			for (DrawableObject* i : invisibleObjectsList) {
				if (InvisibleObject* Iptr = dynamic_cast<InvisibleObject*>(i)) {
					int p = Iptr->Collide_W_Entity(*eptr);
					if (p % 2 != 0) { //COLLIDE TOP
						if (CollideDetection % 2 == 0) {
							CollideDetection += 1;
							ivbobjs[0][0] = Iptr->GetPos();
							ivbobjs[0][1] = Iptr->GetSize();
						}
					}
					if ((p >> 1) % 2 != 0) { //COLLIDE BOTTOM
						if ((CollideDetection >> 1) % 2 == 0) {
							CollideDetection += 2;
							ivbobjs[1][0] = Iptr->GetPos();
							ivbobjs[1][1] = Iptr->GetSize();
						}
					}
					if ((p >> 2) % 2 != 0) { //COLLIDE LEFT
						if ((CollideDetection >> 2) % 2 == 0) {
							CollideDetection += 4;
							ivbobjs[2][0] = Iptr->GetPos();
							ivbobjs[2][1] = Iptr->GetSize();
						};
					}
					if ((p >> 3) % 2 != 0) { //COLLIDE RIGHT
						if ((CollideDetection >> 3) % 2 == 0) {
							CollideDetection += 8;
							ivbobjs[3][0] = Iptr->GetPos();
							ivbobjs[3][1] = Iptr->GetSize();
						}
					}
				}
				if (CollideDetection >= 8 + 4 + 2 + 1) break;
			}
			eptr->Collides_W_Inv_Wall(CollideDetection, ivbobjs);
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

	// Update Game Objs
	for (DrawableObject* obj : EntityObjectsList) {
		//Play Update In every game object 
		if (Entity* eptr = dynamic_cast<Entity*>(obj))
			if (eptr->isDead())
				continue;

		obj->Update(deltaTime);
	}

}

void Level::LevelDraw()
{

	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void Level::LevelFree()
{
	/*for (int i = objectsList.size() - 1; i >= 0 ; i--) {
		delete objectsList[i];
	}*/

	//delete player;
	//delete cameraController;
	//delete tilemaps;
	//delete checkPoint;
	//cout << "Free Level" << endl;*/
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
	case 'w': player->HandleKey(key); break;
	case 's': player->HandleKey(key); break;
	case 'a': player->HandleKey(key); break;
	case 'd': player->HandleKey(key); break;
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
	case 'e': interactableManager.notify(player); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2;   break;
	case 'g':  player->OnDamaged(1); break;
	case 'f':
	case 't':
	case 'h':
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	}
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level::WorldToCam(realX, realY);
	mouseVec3 = glm::vec3(realX, realY, 1);

	//cout << "Mouse Pos : (" << realX  << "," << realY <<")" << endl;

	//Player HandleMouse 
	this->player->HandleMouse(mouseVec3); 
	//Detecting Button 
	for (int i = 0; i < objectsList.size(); i++) {
		if (Button* bptr = dynamic_cast<Button*>(objectsList[i])) {
			bptr->OnClick(mouseVec3);
		}
	}

	//move object to current position with respect to Camera position 
	/*glm::vec3 MoveObjectToMuseVec3 = (glm::vec3(realX, realY, 0));
	MoveObjectToMuseVec3.x /= Camera::GetInstance()->GetZoomOffset();
	MoveObjectToMuseVec3.y /= Camera::GetInstance()->GetZoomOffset();

	MoveObjectToMuseVec3 += Camera::GetInstance()->GetCamOffset();

	player->SetPosition(MoveObjectToMuseVec3);*/
}

void Level::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}