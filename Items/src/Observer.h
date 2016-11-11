#pragma once

#include "Observable.h"

//Needs to have a forward reference due to 
//circular reference between Observer and Subject
class Observable;

class Observer {
public:
	virtual ~Observer();
	virtual void update() = 0;
protected:
	Observer();
};
