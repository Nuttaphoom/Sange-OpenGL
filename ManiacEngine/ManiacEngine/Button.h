#ifndef BUTTONH
#define BUTTONH
#include "GUI.h"

typedef void (*FuncPtr_ButtonType)();

enum class ButtonName {
	NEXT_LEVEL_BUTTON = 0  
};

 
class Button : public GUI {
	ButtonName buttonName ; 
	vector<FuncPtr_ButtonType> buttonTypesFunc; 
public : 
		Button(ButtonName buttonName, string fileName, int row, int column);
		bool isClick(glm::vec3 CamSpace_MousePosition);
		void OnClick(glm::vec3 CamSpace_MousePosition);
		 
};

#endif 