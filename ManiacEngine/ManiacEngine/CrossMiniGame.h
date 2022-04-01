#pragma once
#include "MiniGame.h"
#include "GUI.h" 

class CrossMiniGame : public MiniGame {
private :
	GUI* _movingBar; 
	GUI* _boarder; 
	GUI* _keyBar ; 
	int indicate = 1;
	float _maxValue = 0; 
	float _currentValue = 0;
	float _minValue = 0;
	float speed = 2;

public :
	CrossMiniGame(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, float MaxValue, float MinValue); 
	void virtual HandleKey(char s);
	void virtual Update(int deltaTime);
	void virtual ExitMiniGame();

	void Render(glm::mat4 globalModelTransform);
	
	void StartTheBar();
	void StopTheBar();
};