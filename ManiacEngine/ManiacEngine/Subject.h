#pragma once

#include "Observer.h" 
using namespace std; 
class Subject {
	public :
	vector<vector<Observer*>> observers ;  
	virtual void notify(int Type)   ;
	virtual void attach(Observer* o, int Type)  ; 
	virtual void detach(Observer* o)   ; 

	~Subject(); 
};