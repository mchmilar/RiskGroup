//reinforcementLogString in Game
#ifndef LOGGERREINFORCEMENTS_H
#define LOGGERREINFORCEMENTS_H
#include <string>
#include <iostream>
#include "Logger.h"
#include "LoggerDecorator.h"

/** Decorator that adds reinforcements to the Logger.
*  It is a subclass of LoggerDecorator, and thus a subclass of Logger.
*/
class LoggerReinforcements : public LoggerDecorator {
public:
	/**
	* When creating a decorated Logger, pass a Logger to be decorated
	* as a parameter. Note that this can be an already-decorated Logger.
	*/
	LoggerReinforcements(Logger *decoratedLogger) : LoggerDecorator(decoratedLogger){
		gameObservable = decoratedLog->getGame();
		gameObservable->detach(decoratedLogger);
		gameObservable->attach(this);
		log = gameObservable->getReinforcementsLog();
	}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Logger methods
	*/
	void LoggerReinforcements::update(){
		decoratedLog->update();
		log = decoratedLog->getLog() + gameObservable->getReinforcementsLog();
	}
};

#endif