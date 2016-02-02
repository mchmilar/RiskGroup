#pragma once
#include "Observer.h"
#include "Player.h"
#include "Map.h"

class Stats : public Observer
{
public:
	Stats();
	void update() = 0;
	virtual std::string getStatsString() = 0;
	std::string getLog()
	{
		return statsString;
	};
	Stats(Map*, Player*);
	~Stats();

	Map* getMap() { return mapObservable; };
	Player* getPlayer() { return playerObservable; };

protected:
	std::string statsString = "";
	Map *mapObservable;
	Player *playerObservable;
};

