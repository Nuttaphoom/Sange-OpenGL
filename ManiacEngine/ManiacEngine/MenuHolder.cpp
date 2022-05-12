#include "MenuHolder.h"

MenuHolder::MenuHolder(string menuName):_menuName(menuName) {
	
}

bool MenuHolder::isMenu(string name) {
	return name == _menuName; 
}

void MenuHolder::addButton(GUI* add) {
	buttonHolder.push_back(add);
}

void MenuHolder::deleteButton(Button* del) {
	for (int i = 0;i < buttonHolder.size();i++) {
		if (buttonHolder[i] == del) {
			delete buttonHolder[i];
			buttonHolder.erase(buttonHolder.begin() + i);
		}
	}
}

void MenuHolder::enableButton() {
	for (int i = 0;i < buttonHolder.size();i++) {
		buttonHolder.at(i)->SetPause(false);
	}
	//for (int i = 0;i < textHolder.size();i++) {
		//textHolder.at(i)->SetPause(false);
	//}
}
void MenuHolder::disableButton() {
	for (int i = 0;i < buttonHolder.size();i++) {
		buttonHolder.at(i)->SetPause(true);
	}
	//for (int i = 0;i < textHolder.size();i++) {
		//textHolder.at(i)->SetPause(true);
	//}
}

/*void MenuHolder::addText(TextObject* add) {
	textHolder.push_back(add);
}*/

/*void MenuHolder::deleteText(TextObject* del) {
	for (int i = 0;i < textHolder.size();i++) {
		if (textHolder[i] == del) {
			delete textHolder[i];
			textHolder.erase(textHolder.begin() + i);
		}
	}
}*/

void MenuHolder::Render(glm::mat4 globalModelTransform) {
	for (int i = 0;i < buttonHolder.size();i++) {
		buttonHolder[i]->Render(globalModelTransform);
	}
	//for (int i = 0;i < textHolder.size();i++) {
		//textHolder[i]->Render(globalModelTransform);
	//}
}