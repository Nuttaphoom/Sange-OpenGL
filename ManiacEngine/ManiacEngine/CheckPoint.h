#pragma once
#include "GameData.h"
#include "Player.h"
#include "Manager.h"

class CheckPoint : public Manager{
	private:
		static CheckPoint* instance;
		glm::vec3 curCheckPoint = glm::vec3(0, 0, 0);
	public :
		CheckPoint() :Manager() {};
 		glm::vec3 LoadCheckPoint();
		void SetCheckPoint(glm::vec3 newPoint);
		static CheckPoint* GetInstance();
		void Update(int deltaTime)  ;
		void Render(glm::mat4 globalModelTransform)  ;
};

 
 