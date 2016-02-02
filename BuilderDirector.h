#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <string>
#include <iostream>
#include "Map.h"
#include "MapBuilder.h"
#include "Game.h"
using namespace std;

class Director //Director
{
public:
	void setMapBuilder(MapBuilder* mapBuild)
	{
		mapBuilder = mapBuild;
	}
	Map* getMap()
	{
		return mapBuilder->getMap();
	}
	Game* getGame()
	{
		return mapBuilder->getGame();
	}
	bool constructMap(string location)
	{
		return mapBuilder->createNewMap(location);
	}
private:
	MapBuilder* mapBuilder;
};
#endif
