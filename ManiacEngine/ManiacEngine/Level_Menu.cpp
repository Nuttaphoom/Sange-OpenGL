#include "Level_Menu.h" 

#include "Level.h"
#include "TileMap.h"
#include "Audio.h"
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;



void Level_Menu::LevelLoad()
{
	SquareMeshVbo* square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);
	ifstream mapFile("../Resource/Map/Level_1.2/Middle_Mapdata.txt");
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


	ifstream FrontMapFile("../Resource/Map/Level_1.2/Front_Mapdata.txt");
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

	ifstream cMapFile("../Resource/Map/Level_1.2/Col_Mapdata.txt");
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

	ifstream BackGroundMapFile("../Resource/Map/Level_1.2/Background_Mapdata.txt");
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

void Level_Menu::LevelInit()
{
	SoundPlayer::GetInstance()->PlayMusic("../Resource/Sound/BGM/MainMenuOST.mp3");

	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 5, 10, 3, glm::vec3(7000, -1176.0f, 0.0f), glm::vec3(128, -128, 0), true, true);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	GUI* background = new GUI("../Resource/Texture/Button/Background.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth(), -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background);
	GUI* Sangeimage = new GUI("../Resource/Texture/GUI/Sangeideal.png", 1, 1, glm::vec3(GameEngine::GetInstance()->GetWindowWidth()/2 - 350, -50, 0), glm::vec3(-300, -600, 1));
	objectsList.push_back(Sangeimage);

	MenuHolder* mainMenuHolder = new MenuHolder("MainMenu");
	SDL_Color SDL_WhiteColor = SDL_Color(); 
	SDL_WhiteColor.r = 255; SDL_WhiteColor.g = 255; SDL_WhiteColor.b = 255; 

	Button* m1 = new Button(ButtonName::START_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 -650, GameEngine::GetInstance()->GetWindowHeight() / 2 -200, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1),"Play",SDL_WhiteColor,20);
	mainMenuHolder->addButton(m1);
	objectsList.push_back(m1);
	GUIObjectsList.push_back(m1);

	Button* m2 = new Button(ButtonName::EXIT_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 550, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1),"Exit", SDL_WhiteColor,20);
	mainMenuHolder->addButton(m2);
	objectsList.push_back(m2);
	GUIObjectsList.push_back(m2);
	//mainMenuHolder->disableButton();

	Button* m3 = new Button(ButtonName::SETTING_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 350, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "Option", SDL_WhiteColor, 20);
	mainMenuHolder->addButton(m3);
	objectsList.push_back(m3);
	GUIObjectsList.push_back(m3);
	//mainMenuHolder->disableButton();

	MenuHolder* optionHolder = new MenuHolder("Option");
	Button* s1masterup = new Button(ButtonName::MASTER_SOUND_VOLUME_UP, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 450, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), ">", SDL_WhiteColor, 20);
	optionHolder->addButton(s1masterup);
	objectsList.push_back(s1masterup);
	GUIObjectsList.push_back(s1masterup);

	Button* s1masterdown = new Button(ButtonName::MASTER_SOUND_VOLUME_DOWN, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 800, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "<", SDL_WhiteColor, 20);
	optionHolder->addButton(s1masterdown);
	objectsList.push_back(s1masterdown);
	GUIObjectsList.push_back(s1masterdown);

	Button* s2musicup = new Button(ButtonName::MUSIC_SOUND_VOLUME_UP, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 450, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), ">", SDL_WhiteColor, 20);
	optionHolder->addButton(s2musicup);
	objectsList.push_back(s2musicup);
	GUIObjectsList.push_back(s2musicup);

	Button* s2musicrdown = new Button(ButtonName::MUSIC_SOUND_VOLUME_DOWN, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 800, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "<", SDL_WhiteColor, 20);
	optionHolder->addButton(s2musicrdown);
	objectsList.push_back(s2musicrdown);
	GUIObjectsList.push_back(s2musicrdown);

	Button* closeOption = new Button(ButtonName::CLOSE_OPTION_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 650, GameEngine::GetInstance()->GetWindowHeight() / 2 - 650, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "Close", SDL_WhiteColor, 20);
	optionHolder->addButton(closeOption);
	objectsList.push_back(closeOption);
	GUIObjectsList.push_back(closeOption);
	
	
	Button* master = new Button(ButtonName::NONE_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4,4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 1100, GameEngine::GetInstance()->GetWindowHeight() / 2 - 85, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "Master", SDL_WhiteColor, 20);
	optionHolder->addButton(master);
	objectsList.push_back(master);
	GUIObjectsList.push_back(master);

	Button* music = new Button(ButtonName::NONE_GAME_BUTTON, "../Resource/Texture/Button/button_frame.png", 4, 4, glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 - 1100, GameEngine::GetInstance()->GetWindowHeight() / 2 - 250, 0), glm::vec3(1668 / 11, 2224 / 11 * -1, 1), "Music", SDL_WhiteColor, 20);
	optionHolder->addButton(music);
	objectsList.push_back(music);
	GUIObjectsList.push_back(music);
	optionHolder->disableButton();


	_menuHolderList.push_back(mainMenuHolder);
	_menuHolderList.push_back(optionHolder);
#pragma endregion

#pragma  Manager
	AnimatorManager* animatorManager = AnimatorManager::GetInstance();
	managersList.push_back(animatorManager);
	objectsList.push_back(animatorManager);

#pragma endregion  

#pragma Sound
	SoundPlayer::GetInstance()->ClearSound();

#pragma endregion 

	//cout << "Init Level" << endl;

}

void Level_Menu::LevelUpdate()
{
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 
	



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

void Level_Menu::LevelDraw()
{

	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void Level_Menu::LevelFree()
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

void Level_Menu::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void Level_Menu::HandleKey(char key)
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
	case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL1;   break;
	case 'g':  player->OnDamaged(1); break;
	case 'f':
	case 't':
	case 'h':
	case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
	case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	}
}

void Level_Menu::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;
	glm::vec3 mouseVec3;
	// Calculate Real X Y 
	Level_Menu::WorldToCam(realX, realY);
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

void Level_Menu::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}