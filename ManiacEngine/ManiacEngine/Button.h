#pragma once
#include "TextObject.h"
#include <map>
typedef void (*FuncPtr_ButtonType)();

enum class ButtonName {
	NEXT_LEVEL_BUTTON = 0,
	RESTART_BUTTON = 1,
	START_GAME_BUTTON = 2,
	CONTINUE_GAME_BUTTON = 3,
	EXIT_GAME_BUTTON = 4,
	SETTING_GAME_BUTTON = 5,
	MASTER_SOUND_VOLUME_UP = 6,
	SFX_SOUND_VOLUME_UP = 7,
	MUSIC_SOUND_VOLUME_UP = 8,
	MASTER_SOUND_VOLUME_DOWN = 9,
	MUSIC_SOUND_VOLUME_DOWN = 10,
	SFX_SOUND_VOLUME_DOWN = 11,
	CLOSE_OPTION_GAME_BUTTON = 12,
	NONE_GAME_BUTTON = 13
};

 
class Button : public GUI {
private :
	map<string, bool> a;
	ButtonName buttonName ; 
	vector<FuncPtr_ButtonType> buttonTypesFunc; 
	TextObject* _textObject ; 
public : 
		Button(ButtonName buttonName, string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size);
		Button(ButtonName buttonName, string fileName, int row, int column,glm::vec3 Pos, glm::vec3 Sizez, string textString  , SDL_Color textColor  , int frontSize   );
		bool isClick(glm::vec3 CamSpace_MousePosition);
		void OnClick(glm::vec3 CamSpace_MousePosition); 
		virtual void SetPause(bool b);

		virtual void Render(glm::mat4 globalModelTransform);

 };
 