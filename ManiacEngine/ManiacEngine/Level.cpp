#include "Level.h"
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT; 
 


void Level::LevelLoad()
{
	SetCheckPoint(glm::vec3(0, 0, 0));
 
	SquareMeshVbo * square = new SquareMeshVbo();
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

void Level::LevelInit()
{
	SetCheckPoint(glm::vec3(0, 0, 0)); 

	#pragma region ground_test
		for (int i = 0; i < 12; i++)
		{
			InvisibleObject* ivo = new InvisibleObject();
			ivo->SetPosition(glm::vec3(64, -256 - 64 * i, 0));
			ivo->SetSize(64, 64);
			invisibleObjectsList.push_back(ivo);
			objectsList.push_back(ivo);
		}
	#pragma endregion 

	#pragma region tilemaps
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
	#pragma endregion 

	#pragma region interactableObject 
	Flower* flower_1 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1);
	flower_1->SetPosition(glm::vec3(-64*2, -64*9 + 15, 0));
	flower_1->SetSize(64, -128);
	interactableManager.addInteractableObjects(flower_1);

	objectsList.push_back(flower_1); 
	#pragma endregion 

	Player* obj = Player::GetInstance("../Resource/Texture/TestNumber.png", 4, 4, 100, 0.3, 0) ;
	obj->SetSize(128, -128.0f);
 	obj->SetAnimationLoop(0, 0, 4, 100);
 	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;
	
	#pragma region GUI 
	GUI* SangeImage = new GUI(GUIName::Decroative, "../Resource/Texture/GUI/Sange.png",1,1);
	SangeImage->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2*-1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2  - 85 , 0));
	SangeImage->SetSize(1668 / 11, 2224 / 11 * -1);
	objectsList.push_back(SangeImage); 
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
	for (DrawableObject* obj : EntityObjectsList) {
		//Player Update In every game object 
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

	delete player; 
	delete cameraController; 
	delete tilemaps;  
 
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
		case 'e': interactableManager.notify(player)  ; break;
		case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2 ;   break;
		case 'g': Camera::GetInstance()->Translate(100.0f, 0);  break;//Move the cam to right
		case 'f': Camera::GetInstance()->Translate(-100.0f, 0); break;//Move the cam to left 
		case 't': Camera::GetInstance()->Translate(0, 10); break;
		case 'h': Camera::GetInstance()->Translate(0, -10); break;
		case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
		case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	}
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3 ; 
	// Calculate Real X Y 
	Level::WorldToCam(realX, realY);
	mouseVec3 = glm::vec3(realX, realY,1);

	//cout << "Mouse Pos : (" << realX  << "," << realY <<")" << endl;

	//Detecting Button 
	for (int i = 0; i < objectsList.size(); i++) {
		if (Button* bptr = dynamic_cast<Button*>(objectsList[i])) {
			bptr->OnClick(mouseVec3); 
		}
	}

	//move object to current position with respect to Camera position 
	glm::vec3 MoveObjectToMuseVec3 = (glm::vec3(realX, realY, 0) );
	MoveObjectToMuseVec3.x /= Camera::GetInstance()->GetZoomOffset();
	MoveObjectToMuseVec3.y /= Camera::GetInstance()->GetZoomOffset();

	MoveObjectToMuseVec3 += Camera::GetInstance()->GetCamOffset(); 

	player->SetPosition(MoveObjectToMuseVec3);
}

void Level::WorldToCam(float &realX, float &realY) {
	int x , y ;
	x = realX; y = realY ; 

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;
 

}