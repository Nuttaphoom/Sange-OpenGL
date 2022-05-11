#pragma once
//#include "GUI.h"
#include <map>
#include "Button.h"



class MenuHolder : DrawableObject {
	private :
		vector<GUI*> buttonHolder =  vector<GUI*>();
		string _menuName; 
	public :
		MenuHolder(string menuName);
		void addButton(GUI* add);
		void deleteButton(Button* del);
		void disableButton();
		void enableButton();
		bool isMenu(string name);
		virtual void Render(glm::mat4 globalModelTransform);
};