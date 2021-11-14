#include "Button.h"
void NextLevel_Button(); 
Button::Button(ButtonName buttonName, string fileName, int row, int column) :buttonName(buttonName), GUI(GUIName::Button, fileName, row, column)
{
	buttonTypesFunc.push_back(NextLevel_Button);  // NEXT_LEVEL_BUTTON
}


bool Button::isClick(glm::vec3 CamSpace_MousePosition ) {

	bool CollideX;
	bool CollideY;
	CollideX = CamSpace_MousePosition.x <= GetPos().x + GetSize().x / 2 && CamSpace_MousePosition.x >= GetPos().x - GetSize().x / 2   ;
	CollideY = CamSpace_MousePosition.y <= GetPos().y + GetSize().y * -1 / 2 && CamSpace_MousePosition.y >= GetPos().y - GetSize().y * -1 / 2  	;

  	return CollideX && CollideY;

 }
void Button::OnClick(glm::vec3 CamSpace_MousePosition) {
	if (!isClick(CamSpace_MousePosition))
		return; 

	buttonTypesFunc[(int) this->buttonName](); 

}

void NextLevel_Button() {
	cout << "A" << endl; 
	return; 
}

 