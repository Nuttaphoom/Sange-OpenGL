#include "MenuHolder.h"

void MenuHolder::addButton(Button* add) {
	cout << "Before Push" << endl;
	buttonHolder.push_back(add);
	cout << "After Push" << endl;
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
}
void MenuHolder::disableButton() {
	for (int i = 0;i < buttonHolder.size();i++) {
		buttonHolder.at(i)->SetPause(true);
	}
}


void MenuHolder::Render(glm::mat4 globalModelTransform) {
	for (int i = 0;i < buttonHolder.size();i++) {
		buttonHolder[i]->Render(globalModelTransform);
	}
}