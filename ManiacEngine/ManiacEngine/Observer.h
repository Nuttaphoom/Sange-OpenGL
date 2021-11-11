#pragma once 
#include <iostream> 
#include <vector> 
 
using namespace std;

class Observer {
	public : 
	virtual void OnNotify() = 0;
};

