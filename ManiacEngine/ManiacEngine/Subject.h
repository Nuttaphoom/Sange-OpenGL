#pragma once

#include "Observer.h" 
using namespace std; 
class Subject {
	public :
	vector<Observer*> observers ;  
	virtual void notify() = 0 ;
	virtual void attach(Observer* o) = 0 ; 
	virtual void detach(Observer* o) = 0 ; 
};