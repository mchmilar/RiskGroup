#ifndef PLAYERSTATSARMIES_H
#define PLAYERSTATSARMIES_H
#include <string>
#include <iostream>
#include "StatsDecorator.h"
#include "Stats.h"

/** Decorator that adds attack information to the Logger.
*  It is a subclass of LoggerDecorator, and thus a subclass of Logger.
*/
class PlayerStatsArmies : public StatsDecorator {
public:
	/**
	* When creating a decorated Logger, pass a Logger to be decorated
	* as a parameter. Note that this can be an already-decorated Logger.
	*/
	PlayerStatsArmies(Stats *decoratedLogger) : StatsDecorator(decoratedLogger){}
	/**
	* Overriding methods defined in the abstract superclass.
	* Enables to provide different behavior for decorated Logger methods
	*/
	std::string retrieveLogString(){
		return decoratedLog->retrieveLogString() + gameObservable->getAttackLog();
	}
	void LoggerAttack::update(){
		retrieveLogString();
	}
};

#endif