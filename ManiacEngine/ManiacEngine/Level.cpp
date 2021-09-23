#include "Level.h"
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT; 
void Level::LevelLoad()
{
	SquareMeshVbo * square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	GameObject * obj = new GameObject();
	obj->SetColor(1.0, 0.0, 0.0);
	obj->SetSize(100, 100);
	objectsList.push_back(obj);

	player = obj;

	ImageObject* img = new ImageObject();
	img->SetSize(100.0f, -100.0f);
	img->SetTexture("../Resource/Texture/penguin.png");
	objectsList.push_back(img);

	GUI* img2 = new GUI(GUIName::GUI_TEST);
		//new GUI(GUIName::GUI_TEST,glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 2 * -1 , GameEngine::GetInstance()->GetWindowHeight() , 1), glm::vec3(451, -121, 0));
	img2->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 4 * -1 + GameEngine::GetInstance()->GetWindowWidth() / 13 * -1,
		GameEngine::GetInstance()->GetWindowHeight() / 2 - GameEngine::GetInstance()->GetWindowHeight() / 6, 0));
	img2->SetSize(451, -121); 
	img2->SetTexture("../Resource/Texture/HPBar.PNG");
	objectsList.push_back(img2);

	SpriteObject* sprite = new SpriteObject("../Resource/Texture/TestSprite.png", 4, 7);
	sprite->SetSize(200.0f, -200.0f);
	sprite->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	sprite->SetAnimationLoop(0, 0, 27, 50);
	objectsList.push_back(sprite);

	//cout << "Init Level" << endl;
}

void Level::LevelUpdate()
{
	//cout << "Update Level" << endl;
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();
	for (DrawableObject* obj : objectsList) {
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
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();
	//cout << "Free Level" << endl;
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
		case 'w': player->Translate(glm::vec3(0, 0.3, 0)); break;
		case 's': player->Translate(glm::vec3(0, -0.3, 0)); break;
		case 'a': player->Translate(glm::vec3(-0.3, 0, 0)); break;
		case 'd': player->Translate(glm::vec3(0.3, 0, 0)); break;
		case 'q': GameData::GetInstance()->gGameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameData::GetInstance()->gGameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameData::GetInstance()->gGameStateNext = GameState::GS_LEVEL2; ; break;
		case 'g': Camera::GetInstance()->Translate(10.0f, 0);  break;//Move the cam to right
		case 'f': Camera::GetInstance()->Translate(-10.0f, 0); break;//Move the cam to left  
		case 'z': Camera::GetInstance()->Zoom(0.1f);  break;//zoom in the cam 
		case 'x': Camera::GetInstance()->Zoom(-0.1f);  break;//zoom the cam 
	}
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX = x, realY = y;

	// Calculate Real X Y 
	Level::WorldToCam(realX, realY);

	cout << "Mouse Pos : (" << realX  << "," << realY <<")" << endl;

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