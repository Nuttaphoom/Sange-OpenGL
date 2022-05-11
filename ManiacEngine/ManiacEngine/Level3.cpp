#include "Level3.h" 

 #include "TileMap.h"
#include "Audio.h"
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;



void Level3::LevelLoad()
{
	/*
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_2.1/Middle_Mapdata.txt");
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


	ifstream FrontMapFile("../Resource/Map/Level_2.1/Front_Mapdata.txt");
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

	ifstream cMapFile("../Resource/Map/Level_2.1/Col_Mapdata.txt");
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

	ifstream BackGroundMapFile("../Resource/Map/Level_2.1/Background_Mapdata.txt");
	if (BackGroundMapFile.is_open()) {
		BackGroundMapFile >> MapHeight;
		BackGroundMapFile >> MapWidth;
		cout << MapWidth << "::" << MapHeight << endl;
		sBackGroundMapData = new int* [MapHeight];
		for (int y = 0; y < MapHeight; y++) {
			sBackGroundMapData[y] = new int[MapWidth];
			for (int x = 0; x < MapWidth; x++) {
				BackGroundMapFile >> sBackGroundMapData[y][x];
 			}
 		}
		BackGroundMapFile.close();
	}

	//cout << "Load Level" << endl;*/


	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_2.1/Middle_Mapdata.txt");
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


	ifstream FrontMapFile("../Resource/Map/Level_2.1/Front_Mapdata.txt");
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

	ifstream cMapFile("../Resource/Map/Level_2.1/Col_Mapdata.txt");
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

	ifstream BackGroundMapFile("../Resource/Map/Level_2.1/Background_Mapdata.txt");
	if (BackGroundMapFile.is_open()) {
		BackGroundMapFile >> MapHeight;
		BackGroundMapFile >> MapWidth;
		cout << MapWidth << "::" << MapHeight << endl;
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
}

void Level3::LevelInit()
{
#pragma region tilemapss

	TileMap* tilemaps = new TileMap(MapHeight, MapWidth, sFrontMapData, sMiddleMapdata, sBackGroundMapData, sColMapdata, "../Resource/Texture/SpriteSheet/Map Asset/Level2.1 SpriteSheet.png", 21, 40);
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

	Flower* flower_1 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(5082.13, -1152 - 32, 0.0f), glm::vec3(64, -64, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(flower_1);
	objectsList.push_back(flower_1);

	Gate* gate_1 = new Gate(GameState::GS_LEVEL4, "../Resource/Texture/Interactable/Gate.png", 1, 1, glm::vec3(9680, -1176 + 65 - 60 + 64, 0.0f), glm::vec3(64 * 3.5f, -64 * 3.5f, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(gate_1);
	objectsList.push_back(gate_1);

	ToxicGas* toxicGas = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1470 + 32, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas);
	objectsList.push_back(toxicGas);


	ToxicGas* toxicGas2 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1470 + 32 + 128, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas2);
	objectsList.push_back(toxicGas2);

	ToxicGas* toxicGas3 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1470 + 32 + 256, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas3);
	objectsList.push_back(toxicGas3);


	ToxicGas* toxicGas4 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1470 + 32 + 256 + 256 + 128, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(128, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas4);
	objectsList.push_back(toxicGas4);

	ToxicGas* toxicGas5 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1470 + 32 + 256 + 256 + 128 + 128, -1152, 0.0f), glm::vec3(128, -128, 1), glm::vec3(125, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas5);
	objectsList.push_back(toxicGas5);

	ToxicGas* toxicGas6 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(1470 + 32 + 256 + 256 + 128 + 128 + 64 + 32, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas6);
	objectsList.push_back(toxicGas6);

	ToxicGas* toxicGas7 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(3897.82, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas7);
	objectsList.push_back(toxicGas7);

	ToxicGas* toxicGas8 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(4033.34, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas8);
	objectsList.push_back(toxicGas8);

	ToxicGas* toxicGas9 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(4152.86, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas9);
	objectsList.push_back(toxicGas9);

	ToxicGas* toxicGas10 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(4273.13, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas10);
	objectsList.push_back(toxicGas10);

	ToxicGas* toxicGas11 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(5943.58, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas11);
	objectsList.push_back(toxicGas11);

	ToxicGas* toxicGas12 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(7937.57, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas12);
	objectsList.push_back(toxicGas12);

	ToxicGas* toxicGas13 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(8068.66, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas13);
	objectsList.push_back(toxicGas13);

	ToxicGas* toxicGas14 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(7742.1, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas14);
	objectsList.push_back(toxicGas14);

	ToxicGas* toxicGas15 = new ToxicGas("../Resource/Texture/Interactable/ToxicGas.png", 1, 4, glm::vec3(7599.15, -1152, 0.0f), glm::vec3(64, -128, 1), glm::vec3(64, 128, 1));
	interactableObjectManager->addInteractableObjects(toxicGas15);
	objectsList.push_back(toxicGas15);

#pragma endregion 


#pragma region Entities 
	unsigned int priestTexture = GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png");

	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 10, 16, 3, glm::vec3(125, -1176.0f, 0.0f), glm::vec3(128, -128, 0), true, false);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	Priest* d1 = new Priest(priestTexture, 3, 30, glm::vec3(1353.42, -648, 0.0f), glm::vec3(128, -128, 1));
	d1->AddPatrolPos(glm::vec3(1353.42, -648, 0.0f));
	d1->AddPatrolPos(glm::vec3(1158.15, -648, 0.0f));
	d1->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d1);
	objectsList.push_back(d1);

	Priest* d2 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(2016.43, -522, 0.0f), glm::vec3(128, -128, 1));
	d2->AddPatrolPos(glm::vec3(2016.43, -522, 0.0f));
	d2->AddPatrolPos(glm::vec3(1742.1, -522, 0.0f));
	d2->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d2);
	objectsList.push_back(d2);

	Priest* d3 = new Priest("../Resource/Texture/Enemy/Priest/PriestSpriteSheet.png", 3, 30, glm::vec3(2882.88, -522, 0.0f), glm::vec3(128, -128, 1));
	d3->AddPatrolPos(glm::vec3(2882.88, -522, 0.0f));
	d3->AddPatrolPos(glm::vec3(3032.72, -522, 0.0f));
	d3->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d3);
	objectsList.push_back(d3);

	Decon* d4 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(2793.97, -1152, 0.0f), glm::vec3(128, -128, 1));
	d4->AddPatrolPos(glm::vec3(2793.97, -1152, 0.0f));
	d4->AddPatrolPos(glm::vec3(2793.97, -1152, 0.0f));
	d4->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d4);
	objectsList.push_back(d4);

	Decon* d5 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(3103.51, -1152, 0.0f), glm::vec3(128, -128, 1));
	d5->AddPatrolPos(glm::vec3(3103.51, -1152, 0.0f));
	d5->AddPatrolPos(glm::vec3(3103.51, -1152, 0.0f));
	d5->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d5);
	objectsList.push_back(d5);

	Decon* d6 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(6069.72, -522, 0.0f), glm::vec3(128, -128, 1));
	d6->AddPatrolPos(glm::vec3(6330, -522, 0.0f));
	d6->AddPatrolPos(glm::vec3(5791.45, -522, 0.0f));
	d6->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d6);
	objectsList.push_back(d6);

	Decon* d7 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(6350.96, -837, 0.0f), glm::vec3(128, -128, 1));
	d7->AddPatrolPos(glm::vec3(6350.96, -837, 0.0f));
	d7->AddPatrolPos(glm::vec3(6350.96, -837, 0.0f));
	d7->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d7);
	objectsList.push_back(d7);

	Decon* d8 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(6119.69, -837, 0.0f), glm::vec3(128, -128, 1));
	d8->AddPatrolPos(glm::vec3(6119.69, -837, 0.0f));
	d8->AddPatrolPos(glm::vec3(6241.46, -837, 0.0f));
	d8->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d8);
	objectsList.push_back(d8);

	Decon* d9 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(7441.46, -1152, 0.0f), glm::vec3(128, -128, 1));
	d9->AddPatrolPos(glm::vec3(7441.46, -1152, 0.0f));
	d9->AddPatrolPos(glm::vec3(7441.46, -1152, 0.0f));
	d9->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d9);
	objectsList.push_back(d9);
	
	Decon* d10 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(8326.04, -1152, 0.0f), glm::vec3(128, -128, 1));
	d10->AddPatrolPos(glm::vec3(8326.04, -1152, 0.0f));
	d10->AddPatrolPos(glm::vec3(8714.85, -1152, 0.0f));
	d10->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d10);
	objectsList.push_back(d10);

	Decon* d11 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(8714.85, -1152, 0.0f), glm::vec3(128, -128, 1));
	d11->AddPatrolPos(glm::vec3(8714.85, -1152, 0.0f));
	d11->AddPatrolPos(glm::vec3(8326.04, -1152, 0.0f));
	d11->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(d11);
	objectsList.push_back(d11);

#pragma endregion
	respawner = new ReSpawner();


#pragma region GUI 
	GUI* SangeImage = new GUI("../Resource/Texture/GUI/Sange.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));

	objectsList.push_back(SangeImage);
	GUIObjectsList.push_back(SangeImage);

	GUI* TakeDownIcon = new GUI("../Resource/Texture/GUI/AttackIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64 + 16, 0), glm::vec3(128, -128, 1));
	objectsList.push_back(TakeDownIcon);
	GUIObjectsList.push_back(TakeDownIcon);

	GUI* BatIcon = new GUI("../Resource/Texture/GUI/BatIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90 + 128, -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64 + 16, 0), glm::vec3(128, -128, 1));
	objectsList.push_back(BatIcon);
	GUIObjectsList.push_back(BatIcon);

	HPBar* hpbar = new HPBar("../Resource/Texture/GUI/HPPoint.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 180, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));

	objectsList.push_back(hpbar);

	GUIObjectsList.push_back(hpbar);

#pragma endregion

#pragma  Manager
	AnimatorManager* animatorManager = AnimatorManager::GetInstance();
	managersList.push_back(animatorManager);
	objectsList.push_back(animatorManager);

#pragma endregion  

#pragma Sound
	SoundPlayer::GetInstance()->ClearSound();

#pragma endregion 
}

void Level3::LevelUpdate()
{
	//cout << Player::GetInstance()->GetPos().x << "X" << Player::GetInstance()->GetPos().y << "Y" << endl;
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
							playerObj->OnDamaged(999);
						}
					}
				}
			}
		}
	}



	if (isPause)
		return;

	//Update every objects 
	for (DrawableObject* obj : objectsList) {
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
	/*for (int i = objectsList.size() - 1; i >= 0 ; i--) {
		delete objectsList[i];
	}*/

	//delete player;
	//delete cameraController;
	//delete tilemaps;
	//delete checkPoint;
	//cout << "Free Level" << endl;*/
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
	case 'w': player->HandleKey(key); break;
	case 's': player->HandleKey(key); break;
	case 'a': player->HandleKey(key); break;
	case 'd': player->HandleKey(key); break;
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
		//case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
	case 'e': interactableObjectManager->notify(player); player->HandleKey(key); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL4;   break;
	case 'g':  player->OnDamaged(1); break;
	case 'f':
	case 't':
	case 'h':
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	case '1': player->HandleKey(key); break;
	case '2': player->HandleKey(key); break;
	}
}

void Level3::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level3::WorldToCam(realX, realY);
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

void Level3::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}