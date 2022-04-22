#pragma once
#include "GUI.h"
#include <map>
#include "Button.h"


class MenuHolder : DrawableObject {
	private :
		vector<Button*> buttonHolder =  vector<Button*>();
	public :
			void addButton(Button* add);
			void deleteButton(Button* del);
			void disableButton();
			void enableButton();
			MenuHolder(){}
			virtual void Render(glm::mat4 globalModelTransform);
};