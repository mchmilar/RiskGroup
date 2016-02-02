
#ifndef LOGGERATTACK_H
#define LOGGERATTACK_H
#include <string>
#include <iostream>
#include "Logger.h"
#include "LoggerDecorator.h"

/** Decorator that adds attack information to the Logger.
*  It is a subclass of LoggerDecorator, and thus a subclass of Logger.
*/
class LoggerAttack : public LoggerDecorator {
public:
	/**
	* When creating a decorated Logger, pass a Logger to be decorated
	* as a parameter. Note that this can be an already-decorated Logger.
	*/
	LoggerAttack(Logger *decoratedLogger) : LoggerDecorator(decoratedLogger){
		gameObservable = decoratedLog->getGame();
		gameObservable->detach(decoratedLogger);
		gameObservable->attach(this);
		log = gameObservable->getAttackLog();
	}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Logger methods
	*/

	void LoggerAttack::update(){
		decoratedLog->update();
		log = decoratedLog->getLog() + gameObservable->getAttackLog();
	}


};

#endif