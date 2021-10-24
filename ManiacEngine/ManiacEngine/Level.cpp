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
	Player* obj = new Player("../Resource/Texture/Sange/SangeRunning.png", 1, 8, 100, 10, 0);
	obj->SetSize(128, -128.0f);
	obj->SetPosition(glm::vec3(-50.0f, 0.0f, 0.0f));
	obj->SetAnimationLoop(0, 0, 8, 100);
	objectsList.push_back(obj);

	player = obj;
	

	ImageObject* img = new ImageObject();
	img->SetSize(100.0f, -100.0f);
	img->SetTexture("../Resource/Texture/penguin.png");
	objectsList.push_back(img);

	Button* butt = new Button(ButtonName::NEXT_LEVEL_BUTTON) ; 
	butt->SetPosition(glm::vec3(GameEngine::GetInstance()->GetWindowWidth() / 4 * -1 + GameEngine::GetInstance()->GetWindowWidth() / 13 * -1,
		GameEngine::GetInstance()->GetWindowHeight() / 2 - GameEngine::GetInstance()->GetWindowHeight() / 6, 0));
	butt->SetSize(451, -121); 
	butt->SetTexture("../Resource/Texture/HPBar.PNG");
	objectsList.push_back(butt);

	InvisibleObject* ivo = new InvisibleObject();
	ivo->SetPosition(glm::vec3(0, 0, 0));
	ivo->SetSize(64, 64);
	objectsList.push_back(ivo);


	
	//cout << "Init Level" << endl;
}

void Level::LevelUpdate()
{
	//cout << "Update Level" << endl;
	int deltaTime = GameEngine::GetInstance()->GetDeltaTime();

	for (DrawableObject* obj : objectsList) {
		//Player Update In every game object 
		obj->Update(deltaTime);

		/// Collision Check 
		if (InvisibleObject* Iptr = dynamic_cast<InvisibleObject*>(obj)) { //Entity Collide With Collision 
			for (DrawableObject* nObj : objectsList) {
				if (Entity* eptr = dynamic_cast<Entity*>(nObj)) {
					if (int CollideDetection = Iptr->Collide_W_Entity(*eptr))
						eptr->Collides_W_Inv_Wall(CollideDetection); 
				}
			}
		} 

		else if (Player* playerObj = dynamic_cast<Player*>(obj)) {
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

		///Apply Gravity to every Entities.
		if (Entity* eptr2 = dynamic_cast<Entity*>(obj)) {
			if (deltaTime % 2 == 0)
				eptr2->TranslateVelocity(glm::vec3(0, -0.5, 0));
		} 

		

		

	}

}

void Level::LevelDraw()
{
	GameEngine::GetInstance()->Render(objectsList);
	//cout << "Draw Level" << endl;
}

void Level::LevelFree()
{	
	/*for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();*/
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