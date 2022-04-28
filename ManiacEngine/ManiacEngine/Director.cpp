#include "Director.h"
#include "GameStateController.h"

Director::Director(vector<DrawableObject*> scenes, float offsetX, GameState levelLoad,float lifespan,float scPausetime) {
	for (int i = 0;i < scenes.size();i++) {
		storagePic.push_back(scenes[i]);
	}
	for (int i = 0;i < storagePic.size();i++) {
		glm::vec3 pos = glm::vec3(0 + i * offsetX, 0, 0);
		storagePic[i]->SetPosition(pos);
	}
	this->scPausetimeMax = scPausetime;
	this->scPausetimeCount = 0;
	this->lifespan = lifespan;

	_levelToLoad = levelLoad; 
}


void Director::Update(int deltatime) {

	if (IsPause()) {
		return;
	}

	for (int i = 0;i < storagePic.size();i++) {
		if (ScPausetime) {
			scPausetimeCount += 1.0f/1000.0f*(float)deltatime;
			if (scPausetimeCount >= scPausetimeMax) {
				ScPausetime = false;
				scPausetimeCount = 0;
			}
		}
		else {
			glm::vec3 move = glm::vec3(-1, 0, 0);
			storagePic[i]->Translate(move);
			if (storagePic[count]->GetPos().x <= 0) {
				ScPausetime = true;
				count += 1;
				if (count > storagePic.size() - 1) {
					count = storagePic.size() - 1;
				}
			}
		}
		cout << lifespan << " " << scPausetimeCount << endl;
		
	}
	
	lifespan -= 1.0f / 1000.0f * (float)deltatime;
	cout << lifespan << endl;
	if (lifespan <= 0) {
		SetPause(true);
		GameData::GetInstance()->gGameStateNext = this->_levelToLoad ;
	}

}


