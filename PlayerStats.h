#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <string>
#include <iostream>
#include "StatsDecorator.h"
#include "Game.h"


class PlayerStats : public Stats {
public:

	PlayerStats(Map* map, Player* player)
	{
		mapObservable = map;
		mapObservable->attach(this);

		playerObservable = player;
		playerObservable->attach(this);

		statsString = player->getName();
	}
	~PlayerStats()
	{
		mapObservable->detach(this);
		mapObservable->detach(this);
	}

	std::string getStatsString()
	{
		return statsString;
	};

	void PlayerStats::update(){
		// Intenionally Blank
	}
};

#endif