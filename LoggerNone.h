
#ifndef LOGGERNONE_H
#define LOGGERNONE_H
#include <string>
#include <iostream>
#include "Logger.h"
#include "LoggerDecorator.h"
#include "Game.h"

/** Decorator that leave the Logger empty (Basic).
*  It is a subclass of LoggerDecorator, and thus a subclass of Logger.
*/
class LoggerNone : public Logger {
public:

	LoggerNone(Game* game) 
	{
		gameObservable = game;
		gameObservable->attach(this);
		log = "";
	}
	~LoggerNone()
	{
		gameObservable->detach(this);
	}
		
	void LoggerNone::update(){
		//left blank intentionally
	}
};

#endif