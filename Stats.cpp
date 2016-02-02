#include "Stats.h"
#include "Map.h"
#include "Player.h"
#include <iostream>

Stats::Stats()
{
};

/*
Constructor that subscribes created Stats object to Map  and Player objects
*/
Stats::Stats(Map* map, Player* player)
{
	mapObservable = map;
	mapObservable->attach(this);
	
	playerObservable = player;
	playerObservable->attach(this);
};

/*
Destructor that detaches the Stats object from Player and Map objects
*/
Stats::~Stats()
{
	playerObservable->detach(this);
	mapObservable->detach(this);
};
