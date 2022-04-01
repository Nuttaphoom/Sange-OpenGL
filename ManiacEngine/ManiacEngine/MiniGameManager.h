#pragma once
#include "Manager.h"
#include "MiniGame.h"

class MiniGameManager : public Manager {
private : 
	vector<MiniGame*> _minigames; 
	static MiniGameManager* instance; 
public : 
	MiniGameManager(string fileName = "", int row = -1, int column = -1, glm::vec3 Pos = glm::vec3(0, 0, 0), glm::vec3 Size = glm::vec3(0, 0, 0)) :Manager(fileName, row, column, Pos, Size) {

	}
	static MiniGameManager* GetInstance(); 
	virtual void HandleKey(char s); 
	virtual void Render(glm::mat4 globalModelTransform); 
	virtual void Update(int deltaTime);
	void AddMiniGame(MiniGame* mg); 
	void RemoveMiniGame(MiniGame* mg); 


};
