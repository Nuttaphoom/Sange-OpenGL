#include "CrossMiniGame.h"
#include <math.h>
void CrossMiniGame::StartTheBar() {

}
void CrossMiniGame::StopTheBar() {
	if (_keyBar->GetPos().x - _movingBar->GetPos().x) {
		cout << "PASS" << endl;
	}
	else {
		cout << "NOT PASS" << endl; 
	}
}

CrossMiniGame::CrossMiniGame(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size,float MaxValue,float MinValue):MiniGame(fileName,row,column,Pos,Size) {
	this->_movingBar = new GUI("../Resource/Texture/Red_Texture.png", row, column, glm::vec3(0,0,0), glm::vec3(30,100,1));
	this->_boarder = new GUI(fileName, row, column, Pos, Size);
	this->_keyBar = new GUI("../Resource/Texture/Red_Texture.png", row, column, Pos, glm::vec3(20, 100, 1));

	this->_maxValue = (_boarder->GetPos().x + _boarder->GetSize().x / 2) - _movingBar->GetSize().x / 2 ;
	this->_minValue = (_boarder->GetPos().x - _boarder->GetSize().x / 2) + _movingBar->GetSize().x / 2;
	this->_currentValue = (_maxValue + _minValue) / 2;

	this->speed = _boarder->GetSize().x / 2 - _movingBar->GetSize().x / 2 / 2.5f ; 
	srand(time(NULL));
	this->_keyBar->SetPosition(glm::vec3((rand() % (int) _maxValue )+ this->_minValue,0,0)); 
	
}
void CrossMiniGame::HandleKey(char s) {
	if (s == 'e') {
		StopTheBar(); 
	}
	else if (s == 'E') {
		ExitMiniGame();
	}
}

void CrossMiniGame::Update(int deltaTime) {
	if (_currentValue <= _maxValue && _currentValue >= _minValue) {
		_currentValue += speed * indicate / 1000.0f * deltaTime;
	}
	else {
		indicate *= -1;
		if (_currentValue < _minValue) 
			_currentValue = _minValue;
		else if (_currentValue > _maxValue)
			_currentValue = _maxValue;
	}
	glm::vec3 gotoPos = glm::vec3(_currentValue,_movingBar->GetPos().y,0);
	this->_movingBar->SetPosition(gotoPos);

	cout << "keybar pos of CrossMiniGame : " << _keyBar->GetPos().x << endl;
}


void CrossMiniGame::ExitMiniGame() {
	delete this; 
}

void CrossMiniGame::Render(glm::mat4 globalModelTransform) {
	_boarder->Render(globalModelTransform);
	this->_keyBar->Render(globalModelTransform); 
	_movingBar->Render(globalModelTransform);

}