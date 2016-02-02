#include "Logger.h"
#include "Map.h"
#include "Game.h"
#include <iostream>

Logger::Logger()
{
};

/*
Constructor that subscribes the created Logger object to Game objects
*/
Logger::Logger(Game* game)
{
	gameObservable = game;
	gameObservable->attach(this);
};

/*
Destructor that detaches the Logger from the Gam
*/
Logger::~Logger()
{
	gameObservable->detach(this);
};

