#ifndef STATSDECORATOR_H
#define STATSDECORATOR_H
#include <string>
#include <iostream>
#include "Stats.h"

/**
*  Concrete decorator. Note that it extends the Stats abstract class
*/
class StatsDecorator : public Stats {
protected:
	Stats *decoratedStats;
public:
	/**
	* Wraps a Stats object inside an object of one of
	* StatsDecorator's subclasses
	*/
	StatsDecorator(){};
	StatsDecorator(Stats *decoratedStats){
		this->decoratedStats = decoratedStats;
	}
	
};
#endif