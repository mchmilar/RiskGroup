#include "Observable.h"
#include "Observer.h"

Observable::Observable() {
	_observers = new std::list<Observer*>;
};


Observable::~Observable() {
	delete _observers;
};

void Observable::attach(Observer* o) {
	_observers->push_back(o);
};

void Observable::detach(Observer* o) {
	_observers->remove(o);
};

void Observable::notify() {
	std::list<Observer*>::iterator i = _observers->begin();
	for (i; i != _observers->end(); i++)
		(*i)->update();
};