#include "Level.h"
#include "TileMap.h"
#include "Audio.h"

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;	



void Level::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_1.1/Middle_Mapdata.txt");
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


	ifstream FrontMapFile("../Resource/Map/Level_1.1/Front_Mapdata.txt");
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

	ifstream cMapFile("../Resource/Map/Level_1.1/Col_Mapdata.txt");
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

	ifstream BackGroundMapFile("../Resource/Map/Level_1.1/Background_Mapdata.txt");
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

	

	AudioEngine audio;
	audio.init();

	
	SoundEffect sound1 = audio.loadSoundEffect("../Resource/Sound/Sword_Draw.mp3");
	//sound1.play();

	checkPoint = CheckPoint::GetInstance();

	#pragma region tilemapss
	//TileMap* tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/SpriteSheet/Map Asset/Level1.2 SpriteSheet.png", 33, 40);

	TileMap* tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/SpriteSheet/Map Asset/Level1.1 SpriteSheet.png", 21, 40);
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
 

	Hiding* hiding = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(125 + 64 * 58, -1135.0f - 32, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding); 
	objectsList.push_back(hiding);

	Flower* flower_3 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(7422, -920 - 32, 0.0f), glm::vec3(64, -64, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(flower_3);
	objectsList.push_back(flower_3);

	Trap* trap_1 = new Trap("../Resource/Texture/Interactable/Cross.png", 1, 1, glm::vec3(2216, -850 - 32, 0.0f), glm::vec3(128, -168, 1), glm::vec3(256, -256, 1));
		
	interactableObjectManager->addInteractableObjects(trap_1);
	objectsList.push_back(trap_1);
	#pragma endregion 

	#pragma region Entities 
	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite_V2.png", 4, 10, 3, glm::vec3(125, -1176.0f, 0.0f),glm::vec3(128,-128,0));
	obj->SetAnimationLoop(0, 0, 4, 100);
 	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	Decon* test = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(4886, -920, 0.0f), glm::vec3(128, -128,1) );
	test->AddPatrolPos(glm::vec3(4886, -920, 0.0f)); 
	test->AddPatrolPos(glm::vec3(5416, -920, 0.0f));
	test->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test);
	objectsList.push_back(test);

	Decon* test2 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(5203, -1176, 1),glm::vec3(128,-128,1));
	test2->AddPatrolPos(glm::vec3(5203, -1176, 1));
	test2->AddPatrolPos(glm::vec3(3010, -1176, 1));
 	test2->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test2);
	objectsList.push_back(test2);

	Decon* test3 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(7669, -1176, 0.0f), glm::vec3(128, -128, 1));
	test3->AddPatrolPos(glm::vec3(7669, -1176, 0.0f));
	test3->AddPatrolPos(glm::vec3(9045, -920, 0.0f));
	test3->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test3);
	objectsList.push_back(test3);

	Decon* test4 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(8400, -1176, 0.0f), glm::vec3(128, -128, 1));
	test4->AddPatrolPos(glm::vec3(8400, -1176, 0.0f));
	test4->AddPatrolPos(glm::vec3(9641, -920, 0.0f));
	test4->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test4);
	objectsList.push_back(test4);

	Bishop* _bishopTest = new Bishop("../Resource/Texture/Enemy/Bishop/Pope_Dummy.png", 1, 1, glm::vec3(189, -1176.0f, 0.0f), glm::vec3(128, -128, 1));
	_bishopTest->SetAnimationLoop(0, 0, 12, 100);
	_bishopTest->AddPatrolPos(glm::vec3(189 + 1 * 64, -1176.0f, 0.0f));
	_bishopTest->AddPatrolPos(glm::vec3(189 , -1176.0f, 0.0f));

	EntityObjectsList.push_back(_bishopTest);
	objectsList.push_back(_bishopTest);
	#pragma endregion
	respawner = new ReSpawner();


	#pragma region GUI 
	//GUI* SangeImage = new GUI("../Resource/Texture/GUI/Sange.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0),glm::vec3(1668 / 11, 2224 / 11 * -1,1));
 
	//objectsList.push_back(SangeImage);
	//GUIObjectsList.push_back(SangeImage); 

	//HPBar* hpbar = new HPBar("../Resource/Texture/GUI/HPPoint.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 180, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1) );
	
	//objectsList.push_back(hpbar);
	
	//GUIObjectsList.push_back(hpbar);
	_menuHolder = new MenuHolder();
	Button* b1 = new Button(ButtonName::NEXT_LEVEL_BUTTON, "../Resource/Texture/TestNumber.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));
	_menuHolder->addButton(b1);
	objectsList.push_back(b1);
	GUIObjectsList.push_back(b1);

	Button* b2 = new Button(ButtonName::NEXT_LEVEL_BUTTON, "../Resource/Texture/TestNumber.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight()* -1 / 2 + 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));
	_menuHolder->addButton(b2);
	objectsList.push_back(b2);
	GUIObjectsList.push_back(b2);
	_menuHolder->disableButton();
	#pragma endregion

	AnimatorManager* animatorManager = new AnimatorManager(); 
	managersList.push_back(animatorManager);
	 
	vector<SpriteObject*> stest;
	stest.push_back(_bishopTest);
	stest.push_back(obj);

 
	animatorManager->CreateAnimationFactory(stest,Player::GetInstance()->GetPos() , Player::GetInstance()->GetSize(), 2, "../Resource/Texture/TestNumber.png"
	,4,4,16,1);

	objectsList.push_back(animatorManager);

	//cout << "Init Level" << endl;

}

void Level::LevelUpdate()
{
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 
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

	



	//Update InteractableObject 
	interactableObjectManager->Update(deltaTime);

	// Update Game Objs
	for (DrawableObject* obj : EntityObjectsList) {
		//Play Update In every game object 
		if (Entity* eptr = dynamic_cast<Entity*>(obj))
			if (eptr->isDead())
				continue;
		obj->Update(deltaTime);
	}

	//Update Manager 
	for (Manager* m : managersList) {
		m->Update(deltaTime);
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
	//case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
	case 'e': interactableObjectManager->notify(player); player->HandleKey(key); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2;   break;
	case 'g':  player->OnDamaged(1); break;
	case 'f':
	case 't':
	case 'h':
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	case 'E': _menuHolder->enableButton(); break;

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