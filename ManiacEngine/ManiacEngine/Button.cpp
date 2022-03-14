#include "Button.h"

void NextLevelButton_Func();
void ContinueButton_Func();
void ExitButton_Func();
void RestartButton_Func();
void StartgameButton_Func();
void SettingButton_Func();
 Button::Button(ButtonName buttonName, string fileName, int row, int column, glm::vec3 Pos, glm::vec3 Size) : buttonName(buttonName), GUI(fileName, row, column, Pos, Size)
{
	
		buttonTypesFunc.push_back(NextLevelButton_Func);
		buttonTypesFunc.push_back(RestartButton_Func);
		buttonTypesFunc.push_back(StartgameButton_Func);

		buttonTypesFunc.push_back(ContinueButton_Func);
		cout << "BB1" << endl;
	 
	 
		buttonTypesFunc.push_back(ExitButton_Func);
		cout << "BB2" << endl;
		buttonTypesFunc.push_back(SettingButton_Func);
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

void NextLevelButton_Func() {
	cout << "AAA" << endl; 
}
  
void ContinueButton_Func() {
	cout << "Continue" << endl;
}
 

void ExitButton_Func() {
	cout << "Out" << endl;
}

void RestartButton_Func() {
	cout << "Restart" << endl;
}

void StartgameButton_Func() {
	cout << "Start" << endl;
}

void SettingButton_Func() {
	cout << "Option" << endl;
}