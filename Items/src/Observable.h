#pragma once

#include "Observer.h"
#include <list>
using std::list;

//Needs to have a forward reference due to 
//circular reference between Observer and Subject
class Observer;

// the use of a template allows the different Observers of objects to be listed
class Observable
{
public:
	virtual ~Observable();
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();
	
protected:
	Observable();

private:
	list<Observer*> *observers;
};


