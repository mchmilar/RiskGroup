#pragma once

/*
Forward reference to accomodate circular reference between Observable and
Observer objects
*/
class Observable;

//Observer is an abstract class which will subscribe to a derived Observable class to check for updates to the Observable.
class Observer
{
public:
	~Observer(){};
	virtual void update() = 0;
protected:
	Observer(){};
};