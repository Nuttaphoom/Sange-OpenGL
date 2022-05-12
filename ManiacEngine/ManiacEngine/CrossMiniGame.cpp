#include "CrossMiniGame.h"
#include <math.h>
#include <time.h>
#include "SoundPlayer.h"
void CrossMiniGame::StartTheBar() {

}
void CrossMiniGame::StopTheBar() {
	if (abs(_keyBar->GetPos().x - _movingBar->GetPos().x) < _movingBar->GetSize().x / 2) {
		SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/SF/TrapActivate.mp3");
		_done = true;

	}
	else {
		RandomPlaceKeyBar();
	}

}

CrossMiniGame::CrossMiniGame(string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size,float MaxValue,float MinValue):MiniGame(fileName,row,column,Pos,Size) {
	srand(time(NULL));

	this->_movingBar = new GUI("../Resource/Texture/Plain/Red Rectangle.png", row, column, glm::vec3(0,-200,0), glm::vec3(12,50,1));
	this->_boarder = new GUI(fileName, row, column, Pos, Size);
	this->_keyBar = new GUI("../Resource/Texture/Plain/Green Rectangle.png", row, column, Pos, glm::vec3(5, 50, 1));

	this->_maxValue = (_boarder->GetPos().x + _boarder->GetSize().x / 3) - _movingBar->GetSize().x / 2 ;
	this->_minValue = (_boarder->GetPos().x - _boarder->GetSize().x / 3) + _movingBar->GetSize().x / 2;
	this->_currentValue = (_maxValue + _minValue) / 2;

	this->speed = _boarder->GetSize().x / 2 - _movingBar->GetSize().x / 2 / 2.5f ; 

	RandomPlaceKeyBar();

}
void CrossMiniGame::HandleKey(char key) {
	if (key == 'e') {
		StopTheBar(); 
	}
	else if (key == 'E') {
		ExitMiniGame();
	}
}

void CrossMiniGame::RandomPlaceKeyBar() {
	do {
		this->_keyBar->SetPosition(glm::vec3((rand() % (int)_maxValue) - (rand() % (int)_minValue), -200, 0));
	} while (abs(_keyBar->GetPos().x - _movingBar->GetPos().x) < _movingBar->GetSize().x / 2);
}

void CrossMiniGame::Update(int deltaTime) {
	if (!_done) {
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
		glm::vec3 gotoPos = glm::vec3(_currentValue, _movingBar->GetPos().y, 0);
		this->_movingBar->SetPosition(gotoPos);
	}
}


void CrossMiniGame::ExitMiniGame() {
	delete this; 
}

void CrossMiniGame::Render(glm::mat4 globalModelTransform) {
	_boarder->Render(globalModelTransform);
	this->_keyBar->Render(globalModelTransform); 
	_movingBar->Render(globalModelTransform);

}