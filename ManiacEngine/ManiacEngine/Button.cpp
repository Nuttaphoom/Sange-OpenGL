#include "Button.h"
#include "GameStateList.h"
#include "GameStateController.h" 
#include "SoundPlayer.h"
#include "Level_Menu.h"
#include <string>
void NextLevelButton_Func();
void ContinueButton_Func();
void ExitButton_Func();
void RestartButton_Func();
void StartgameButton_Func();
void SettingButton_Func();
void MasterVolumeDown();
void MasterVolumeUp();
void MusicVolumeUp();
void MusicVolumeDown();
void SFXVolumeUp();
void SFXVolumeDown();
void CloseOptionButton_Func();

Button::Button(ButtonName buttonName, string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size ):GUI(fileName,row,column,Pos,Size)
{
	_textObject = new TextObject();
	this->buttonName = buttonName;


	buttonTypesFunc.push_back(NextLevelButton_Func);
	buttonTypesFunc.push_back(RestartButton_Func);
	buttonTypesFunc.push_back(StartgameButton_Func);

	buttonTypesFunc.push_back(ContinueButton_Func);


	buttonTypesFunc.push_back(ExitButton_Func);
	buttonTypesFunc.push_back(SettingButton_Func);
}

Button::Button(ButtonName buttonName, string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size, string textString , SDL_Color textColor  , int frontSize ) :GUI(fileName, row, column, Pos, Size)
{

	_textObject = new TextObject();

	if (frontSize != 0) {
		_textObject->SetPosition(Pos);
		_textObject->LoadText(textString, textColor, frontSize);
	}

	this->buttonName = buttonName;

		buttonTypesFunc.push_back(NextLevelButton_Func);
		buttonTypesFunc.push_back(RestartButton_Func);
		buttonTypesFunc.push_back(StartgameButton_Func);

		buttonTypesFunc.push_back(ContinueButton_Func);
	 
	 
		buttonTypesFunc.push_back(ExitButton_Func);
		buttonTypesFunc.push_back(SettingButton_Func);
		buttonTypesFunc.push_back(MasterVolumeUp);
		buttonTypesFunc.push_back(SFXVolumeUp);
		buttonTypesFunc.push_back(MusicVolumeUp);
		buttonTypesFunc.push_back(MasterVolumeDown);
		buttonTypesFunc.push_back(MusicVolumeDown);
		buttonTypesFunc.push_back(SFXVolumeDown);
		buttonTypesFunc.push_back(CloseOptionButton_Func);
}

void Button::Render(glm::mat4 globalModelTransform) {
	GUI::Render(globalModelTransform); 
	if (_textObject != nullptr)
		_textObject->Render(globalModelTransform); 
}

bool Button::isClick(glm::vec3 CamSpace_MousePosition ) {
	bool CollideX;
	bool CollideY;
	CollideX = CamSpace_MousePosition.x <= GetPos().x + GetSize().x / 2 && CamSpace_MousePosition.x >= GetPos().x - GetSize().x / 2   ;
	CollideY = CamSpace_MousePosition.y <= GetPos().y + GetSize().y * -1 / 2 && CamSpace_MousePosition.y >= GetPos().y - GetSize().y * -1 / 2  	;

  	return CollideX && CollideY;

 }
void Button::OnClick(glm::vec3 CamSpace_MousePosition) {
	if (IsPause())
		return;

	if (!isClick(CamSpace_MousePosition))
		return; 

	SoundPlayer::GetInstance()->PlaySound("../Resource/Sound/GUI/ButtonClick.mp3");
	buttonTypesFunc[(int) this->buttonName](); 

}
 


void NextLevelButton_Func() {
	cout << "AAA" << endl; 
}
  
void ContinueButton_Func() {
	GameStateController::GetInstance()->currentLevel->SetPause(false); 
	GameStateController::GetInstance()->currentLevel->GetMenuHolder()[0]->disableButton();
}
 

void ExitButton_Func() {
	GameData::GetInstance()->gGameStateNext = GameState::GS_MAINMENU ;
}

void RestartButton_Func() {
	GameStateController::GetInstance()->currentLevel->GetRespawner()->ReSpawn(); 
}

void StartgameButton_Func() {
	GameData::GetInstance()->gGameStateNext = GameState::GS_CUTSCENES1 ;
}

void SettingButton_Func() {
	GameStateController::GetInstance()->currentLevel->GetMenuHolder()[0]->disableButton();
	GameStateController::GetInstance()->currentLevel->GetMenuHolder()[1]->enableButton();
}

void CloseOptionButton_Func() {
	GameStateController::GetInstance()->currentLevel->GetMenuHolder()[0]->enableButton();
	GameStateController::GetInstance()->currentLevel->GetMenuHolder()[1]->disableButton();
}

void Button::SetPause(bool b) {
	SpriteObject::SetPause(b); 
	if (_textObject != nullptr)
		_textObject->SetPause(b); 
}


void MasterVolumeDown() {
	AudioEngine* master;
	master = AudioEngine::GetInstance();
	if (master->masterVolume > 0) {
		master->masterVolume = master->masterVolume - 0.1f;
	}
	master->setMastervolume(master->masterVolume);

	if (Level_Menu* s = dynamic_cast<Level_Menu*>(GameStateController::GetInstance()->currentLevel)) {
		SDL_Color white = SDL_Color();
		white.r = 255; white.g = 255; white.b = 255;
		int showText = master->masterVolume * 10  ; 
		s->soundScalerText[0]->LoadText(to_string(showText).c_str(), white, 30);
	}
}

void MasterVolumeUp() {
	AudioEngine* master;
	master = AudioEngine::GetInstance();
	if (master->masterVolume < 1.0f) {
		master->masterVolume = master->masterVolume + 0.1f;
	}
	master->setMastervolume(master->masterVolume);

	if (Level_Menu* s = dynamic_cast<Level_Menu*>(GameStateController::GetInstance()->currentLevel)) {
		SDL_Color white = SDL_Color();
		white.r = 255; white.g = 255; white.b = 255;
		int showText = master->masterVolume * 10  ;
		s->soundScalerText[0]->LoadText(to_string(showText).c_str(), white, 30);
	}
}

void MusicVolumeUp() {
	AudioEngine* music;
	music = AudioEngine::GetInstance();
	if (music->musicVolume < 1) {
		music->musicVolume = music->musicVolume + 0.1f;
	}
	music->setMusicVolume(music->musicVolume);

	if (Level_Menu* s = dynamic_cast<Level_Menu*>(GameStateController::GetInstance()->currentLevel)) {
		SDL_Color white = SDL_Color();
		white.r = 255; white.g = 255; white.b = 255;
		int showText = music->musicVolume * 10;
		s->soundScalerText[1]->LoadText(to_string(showText).c_str(), white, 30);
	}
}

void MusicVolumeDown() {
	AudioEngine* music;
	music = AudioEngine::GetInstance();
	if (music->musicVolume > 0 ) {
		music->musicVolume = music->musicVolume - 0.1f;
	}
	music->setMusicVolume(music->musicVolume);

	if (Level_Menu* s = dynamic_cast<Level_Menu*>(GameStateController::GetInstance()->currentLevel)) {
		SDL_Color white = SDL_Color();
		white.r = 255; white.g = 255; white.b = 255;
		int showText = music->musicVolume * 10;
		s->soundScalerText[1]->LoadText(to_string(showText).c_str(), white, 30);
	}
}

void SFXVolumeUp() {
	AudioEngine* sfx;
	sfx = AudioEngine::GetInstance();
	if (sfx->sfxVolume < 1) {
		sfx->sfxVolume = sfx->sfxVolume + 0.1f;
	}
	sfx->setsfxVolume(sfx->sfxVolume);


}
void SFXVolumeDown() {
	AudioEngine* sfx;
	sfx = AudioEngine::GetInstance();
	if (sfx->sfxVolume > 0) {
		sfx->sfxVolume = sfx->sfxVolume - 0.1f;
	}
	sfx->setsfxVolume(sfx->sfxVolume);
}