/*@file Chest.cpp
* @brief Implementation file for the Observable .cpp file
*/
#include "Observable.h"
#include "Observer.h"

//! Observale default constructor.
Observable::Observable() 
{
	observers = new list<Observer*>;
}
//! Observable destructructor
Observable::~Observable() 
{
	delete observers;
}
//! attach function
//! Attaches the observer to the Observable class
//! @param o observer to attach
void Observable::attach(Observer* o) 
{
	observers->push_back(o);
};
//! detach function
//! Attaches the observer to the Observable class
//! @param o observer to detach
void Observable::detach(Observer* o) 
{
	observers->remove(o);
};
//! notify function
//! tells the observers to update values.
void Observable::notify() 
{
	list<Observer *>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->update();
};