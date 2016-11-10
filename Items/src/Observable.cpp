#include "Observable.h"
#include "Observer.h"

Observable::Observable() {
	observers = new list<Observer*>;
}
Observable::~Observable() {
	delete observers;
}
void Observable::attach(Observer* o) {
	observers->push_back(o);
};
void Observable::detach(Observer* o) {
	observers->remove(o);
};
void Observable::notify() {
	list<Observer *>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->update();
};