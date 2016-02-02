#pragma once
#include "Observer.h" //The logger is the concrete observer to the LogObserver
#include "Game.h" 
#include "Player.h"
#include "Map.h"

class Logger : public Observer
{
public:
	Logger();
	virtual void update() = 0;
	std::string getLog()
	{
		return log;
	};


	Logger(Game* game);
	~Logger();
	
	Game* getGame() { return gameObservable; };
	
protected:
	std::string log = "";
	Map *mapObservable;
	Game *gameObservable;
};

