#ifndef MAPBUILDER_H
#define MAPBUILDER_H
#include<string>
#include "Map.h"
#include "Game.h"

using std::string;

class MapBuilder
{
public:

	Map* getMap(){
		return mapModel;
	}
	Game* getGame(){
		return gameModel;
	}
	virtual bool setMapModel(string location) = 0;
	bool createNewMap(string location){
		mapModel = new Map;
		return setMapModel(location);
	}

protected:
	Map* mapModel;
	Game* gameModel;
};
#endif