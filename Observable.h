#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <list>

/*
Forward reference to accomodate circular reference between Observable and
Observer objects
*/
class Observer;

//The Observable base class which subscribes Observers and adds them to a list
class Observable
{
public:
	virtual void attach(Observer* o);
	virtual void detach(Observer* o);
	virtual void notify();
	Observable();
	~Observable();
//protected:
	std::list<Observer*> *_observers;
};

#endif