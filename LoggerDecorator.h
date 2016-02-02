#ifndef LOGGERDECORATOR_H
#define LOGGERDECORATOR_H
#include <string>
#include <iostream>
#include "Logger.h"

/**
*  Concrete decorator. Note that it extends the Logger abstract class
*/
class LoggerDecorator : public Logger {
protected:
	Logger *decoratedLog;
public:
	/**
	* Wraps a Logger object inside an object of one of
	* LoggerDecorator's subclasses
	*/
	LoggerDecorator(){};
	LoggerDecorator(Logger *decoratedLog){
		this->decoratedLog = decoratedLog;
	}
	
};
#endif