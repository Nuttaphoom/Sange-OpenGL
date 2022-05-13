#include "Level.h"
#include "TileMap.h"
#include "Audio.h"
#include "TextObject.h" 
#include "GameStateController.h"

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
			}
		}
		BackGroundMapFile.close();
	}
}

void Level::LevelInit()
{
	#pragma region tilemapss
 
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

	Flower* flower_3 = new Flower("../Resource/Texture/Interactable/Flower.png", 1, 1, glm::vec3(1800, -850 - 64 - 16, 0.0f), glm::vec3(64, -64, 1), glm::vec3(128, -128, 1));
	interactableObjectManager->addInteractableObjects(flower_3);
	objectsList.push_back(flower_3);

	Trap* trap_1 = new Trap("../Resource/Texture/Interactable/Cross.png", 1, 1, glm::vec3(2216, -850 - 32, 0.0f), glm::vec3(128, -168, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(trap_1);
	objectsList.push_back(trap_1);

	Gate* gate_1 = new Gate(GameState::GS_LEVEL2,"../Resource/Texture/Interactable/Gate.png", 1, 1, glm::vec3(9680 , -1176 + 65 - 60 + 64, 0.0f), glm::vec3(64 * 3.5f, -64 * 3.5f, 1), glm::vec3(128, -128, 1)); 

	interactableObjectManager->addInteractableObjects(gate_1); 
	objectsList.push_back(gate_1);

	Hiding* hiding2 = new Hiding("../Resource/Texture/Interactable/Barrel.png", 1, 1, glm::vec3(8131.87, -1152.0f - 32, 0.0f), glm::vec3(90, -100, 1), glm::vec3(128, -128, 1));

	interactableObjectManager->addInteractableObjects(hiding2);
	objectsList.push_back(hiding2);

	#pragma endregion 
#pragma region GUITEXT
	SDL_Color whilteColor;
	whilteColor.r = 255; whilteColor.g = 255; whilteColor.b = 255;

	TextObject* Controller_Text = new TextObject(true);
	Controller_Text->LoadText("Press A,D,W to Move", whilteColor, 20);
	Controller_Text->SetPosition(glm::vec3(164, -1152.0f + 64 * 2, 0.0f));
	objectsList.push_back(Controller_Text);

	TextObject* TakeDown_Text1 = new TextObject(true);
	TakeDown_Text1->LoadText("Mouse 1 to Take Down", whilteColor, 20);
	TakeDown_Text1->SetPosition(glm::vec3(164 + 64 * 8 + 32, -1152.0f + 64 * 1, 0.0f));
	objectsList.push_back(TakeDown_Text1);
	TextObject* TakeDown_Text2 = new TextObject(true);
	TakeDown_Text2->LoadText("Enemy From Behind", whilteColor, 20);
	TakeDown_Text2->SetPosition(glm::vec3(164 + 64 * 8 + 32, -1152.0f + 32, 0.0f));
	objectsList.push_back(TakeDown_Text2);

	TextObject* WallClimb_Text = new TextObject(true);
	WallClimb_Text->LoadText("Press E to Climb The Wall", whilteColor, 20);
	WallClimb_Text->SetPosition(glm::vec3(164 + 64 * 19, -1152.0f + 64 * 2, 0.0f));
	objectsList.push_back(WallClimb_Text);

	TextObject* flower_Text = new TextObject(true);
	flower_Text->LoadText("Press E to Save", whilteColor, 20);
	flower_Text->SetPosition(glm::vec3(glm::vec3(1800, -850 - 64 - 16 + 32 + 16, 0.0f)));
	objectsList.push_back(flower_Text);

	TextObject* cross_Text = new TextObject(true);
	cross_Text->LoadText("Press E to Defuse The Cross", whilteColor, 20);
	cross_Text->SetPosition(glm::vec3(glm::vec3(2216, -850 - 32 + 64 + 32, 0.0f)));
	objectsList.push_back(cross_Text);

	TextObject* hiding_Text = new TextObject(true);
	hiding_Text->LoadText("Press E to Hide in an Object", whilteColor, 20);
	hiding_Text->SetPosition(glm::vec3(glm::vec3(125 + 64 * 58, -1135.0f - 32 + 64 + 32, 0.0f)));
	objectsList.push_back(hiding_Text);
#pragma endregion 

#pragma region Entities 



	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 10, 16, 3, glm::vec3(164, -1152.0f + 5 + 64, 0.0f), glm::vec3(128, -128, 0), false, false);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	Decon* tuitorialDecon = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(164 + 64 * 8, -1152.0f + 5 + 64, 0.0f), glm::vec3(128, -128, 1));
	tuitorialDecon->SetDirection(1);
	tuitorialDecon->ChangeState(StateMachine::IDLE);
	EntityObjectsList.push_back(tuitorialDecon);
	objectsList.push_back(tuitorialDecon);

	Decon* test = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(4886, -920 + 64, 0.0f), glm::vec3(128, -128,1) );
	test->AddPatrolPos(glm::vec3(4886, -920, 0.0f)); 
	test->AddPatrolPos(glm::vec3(5416, -920, 0.0f));
	test->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test);
	objectsList.push_back(test);
	
	Decon* test2 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(5203, -1152.0f + 64, 1), glm::vec3(128, -128, 1));
	test2->AddPatrolPos(glm::vec3(5203, -1176, 1));
	test2->AddPatrolPos(glm::vec3(3010, -1176, 1));
	test2->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test2);
	objectsList.push_back(test2);

	Decon* test3 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(7669, -1152.0f + 64, 0.0f), glm::vec3(128, -128, 1));
	test3->AddPatrolPos(glm::vec3(7669, -1176, 0.0f));
	test3->AddPatrolPos(glm::vec3(9045, -920, 0.0f));
	test3->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test3);
	objectsList.push_back(test3);

	Decon* test4 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(8400, -1152.0f + 64, 0.0f), glm::vec3(128, -128, 1));
	test4->AddPatrolPos(glm::vec3(8400, -1176, 0.0f));
	test4->AddPatrolPos(glm::vec3(9641, -920, 0.0f));
	test4->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test4);
	objectsList.push_back(test4); 

	Decon* test5 = new Decon("../Resource/Texture/Enemy/Decon/Decon_SpriteSheet.png", 2, 12, glm::vec3(7292.79, -648.7 + 64, 0.0f), glm::vec3(128, -128, 1));
	test5->AddPatrolPos(glm::vec3(7292.79, -648.7, 0.0f));
	test5->AddPatrolPos(glm::vec3(7460.29, -648.7, 0.0f));
	test5->SetAnimationLoop(0, 0, 12, 100);
	EntityObjectsList.push_back(test5);
	objectsList.push_back(test5);
 
	#pragma endregion
	respawner = new ReSpawner();


	#pragma region GUI 
	GUI* SangeImage = new GUI("../Resource/Texture/GUI/Sange.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0),glm::vec3(1668 / 11, 2224 / 11 * -1,1));
 
	objectsList.push_back(SangeImage);
	GUIObjectsList.push_back(SangeImage); 

	HPBar* hpbar = new HPBar("../Resource/Texture/GUI/HPPoint.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 180, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1) );
	
	objectsList.push_back(hpbar);
	
	GUIObjectsList.push_back(hpbar);

	
	GUI * TakeDownIcon = new GUI("../Resource/Texture/GUI/AttackIcon.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 + 90    , -GameEngine::GetInstance()->GetWindowHeight() / 2 + 64+16, 0), glm::vec3(128 , -128, 1));
	objectsList.push_back(TakeDownIcon);
	GUIObjectsList.push_back(TakeDownIcon);
 

	MenuHolder* pauseMenuHolder = new MenuHolder("PauseMenu");
	Button* b1 = new Button(ButtonName::CONTINUE_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));
	pauseMenuHolder->addButton(b1);
	objectsList.push_back(b1);
	GUIObjectsList.push_back(b1);

	Button* b2 = new Button(ButtonName::EXIT_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight()/ 2 - 500, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1));
	pauseMenuHolder->addButton(b2);
	objectsList.push_back(b2);
	GUIObjectsList.push_back(b2);
	pauseMenuHolder->disableButton();

	_menuHolderList.push_back(pauseMenuHolder);

	#pragma endregion

	#pragma  Manager
	AnimatorManager* animatorManager = AnimatorManager::GetInstance() ; 
	managersList.push_back(animatorManager);
	objectsList.push_back(animatorManager);

	#pragma endregion  

	#pragma PlaySound
	SoundPlayer::GetInstance()->ClearSound();
	SoundPlayer::GetInstance()->PlayMusic("../Resource/Sound/BGM/Level1OST.mp3",100);

	#pragma endregion 

}
 
void Level::LevelUpdate()
{
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 
 	for (DrawableObject* en : EntityObjectsList) {
		if (Entity* eptr = dynamic_cast<Entity*>(en)) {
			if (eptr->IsPause())
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

void Level::LevelDraw()
{

	GameEngine::GetInstance()->Render(objectsList);
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
 }

void Level::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
}

void Level::HandleKey(char key)
{
	player->HandleKey(key);

	switch (key)
	{
	case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
	case 'e': player->HandleKey(key); break;
	case 'p': CheckPoint::GetInstance()->LoadCheckPoint(); break;
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2 ; break;
	case 'f': break;
	case 't': break;
	case 'h': break;
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	case 'E': _menuHolderList[0]->enableButton(); GameStateController::GetInstance()->currentLevel->SetPause(true);  break;
	case '1': player->HandleKey(key); break;
	case '2': player->HandleKey(key); break;

 
	}

	interactableObjectManager->HandleKey(key);
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level::WorldToCam(realX, realY);
	mouseVec3 = glm::vec3(realX, realY, 1);

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