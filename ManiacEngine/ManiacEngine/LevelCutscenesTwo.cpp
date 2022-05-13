#include "LevelCutscenesTwo.h"
#include "Audio.h"
#include "Director.h"
#include "SoundPlayer.h"
#include "GameStateController.h"

void LevelCutscenesTwo::LevelLoad()
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
			}
		}
		BackGroundMapFile.close();
	}
}

void LevelCutscenesTwo::LevelInit()
{

	vector<DrawableObject*> storageScenes;
	Player* obj = Player::GetInstance("../Resource/Texture/Sange_Sprite.png", 5, 10, 3, glm::vec3(7000, -1176.0f, 0.0f), glm::vec3(128, -128, 0), true, true);
	obj->SetAnimationLoop(0, 0, 4, 100);
	EntityObjectsList.push_back(obj);
	objectsList.push_back(obj);
	player = obj;

	GUI* background = new GUI("../Resource/Cutscenes/Cut_2/1.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth() + 2, -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background);
	storageScenes.push_back(background);

	GUI* background2 = new GUI("../Resource/Cutscenes/Cut_2/2.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth() + 2, -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background2);
	storageScenes.push_back(background2);

	GUI* background3 = new GUI("../Resource/Cutscenes/Cut_2/3.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth() + 2, -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background3);
	storageScenes.push_back(background3);

	GUI* background4 = new GUI("../Resource/Cutscenes/Cut_2/Credits.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth() + 2, -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background4);
	storageScenes.push_back(background4);

	GUI* background5 = new GUI("../Resource/Cutscenes/Cut_2/Credit.png", 1, 1, glm::vec3(0, 0, 0), glm::vec3(GameEngine::GetInstance()->GetWindowWidth() + 2, -GameEngine::GetInstance()->GetWindowHeight(), 1));
	objectsList.push_back(background5);
	storageScenes.push_back(background5);

	Director* director = new Director(storageScenes, GameEngine::GetInstance()->GetWindowWidth(), GameState::GS_MAINMENU, 31 * 5 - 46  , 29 - 15);
	objectsList.push_back(director);

#pragma endregion

#pragma  Manager
	AnimatorManager* animatorManager = AnimatorManager::GetInstance();
	managersList.push_back(animatorManager);
	objectsList.push_back(animatorManager);

#pragma endregion  

#pragma Sound
	SoundPlayer::GetInstance()->ClearSound();
	SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/BGM/CompleteIntroCutSceneTwo.mp3");

#pragma endregion 
}

void LevelCutscenesTwo::LevelUpdate()
{
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	//Camera Controller Behavior
	cameraController->Update();

	/// Collision Check 




	//Update InteractableObject 
	interactableObjectManager->Update(deltaTime);

	// Update Game Objs

	for (DrawableObject* obj : objectsList) {
		obj->Update(deltaTime);
	}

}

void LevelCutscenesTwo::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
}

void LevelCutscenesTwo::LevelFree()
{
	/*for (int i = objectsList.size() - 1; i >= 0 ; i--) {
		delete objectsList[i];
	}*/

	//delete player;
	//delete cameraController;
	//delete tilemaps;
	//delete checkPoint;

	SoundPlayer::GetInstance()->ClearSound();


}

void LevelCutscenesTwo::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
}

void LevelCutscenesTwo::HandleKey(char key)
{
	switch (key)
	{
		case 'n': GameData::GetInstance()->gGameStateNext = GameState::GS_MAINMENU; break;
	}
}

void LevelCutscenesTwo::HandleMouse(int type, int x, int y)
{

}

void LevelCutscenesTwo::WorldToCam(float& realX, float& realY) {
	int x, y;
	x = realX; y = realY;

	realX = (x - GameEngine::GetInstance()->GetWindowWidth() / 2);
	realY = (y - GameEngine::GetInstance()->GetWindowHeight() / 2);
	realX = (realX / GameEngine::GetInstance()->GetWindowWidth());
	realY = (realY / GameEngine::GetInstance()->GetWindowHeight());
	realX = (realX * 1280.0f);
	realY = (realY * 720.0f) * -1;


}