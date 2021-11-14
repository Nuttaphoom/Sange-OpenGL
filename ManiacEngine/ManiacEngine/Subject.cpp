#include "Subject.h"

void Subject::notify(int Type) {
	if (observers.size() <= Type) {
		printf("SOMETHING WRONG AT Subject.Notify()\n");
		return;
	};
	for (int i = 0; i < observers[Type].size(); i++) {
		printf("i : %d", i);
		observers[Type][i]->OnNotify(); 
	}
}

void Subject::attach(Observer* o, int Type) {
	while (this->observers.size() <= Type) {
 			this->observers.push_back(vector<Observer*>());
	}
	this->observers[Type].push_back(o);
}

void Subject::detach(Observer* o) {
	for (int i = 0; i < observers.size(); i++) {
		for (int j = 0; j < observers[i].size(); j++) {
			if (observers[i][j] == 0) {
				observers.erase(observers.begin() + i);
				break;
			}
		}
	}
}

Subject::~Subject() {
	/*for (int i = observers.size() - 1; i >= 0; i--) {
		for (int j = observers[i].size() - 1; j >= 0; j--) {
			//delete observers[i][j];
		//	observers[i].erase(observers[i].begin() + j);
		}
	}*/
}