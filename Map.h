#ifndef MAP_H
#define MAP_H

#include "Territory.h"
#include "Continent.h"
#include "Observable.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
/*
The implementation of the Risk Map is as a vector of territories with string names which points to
Continent objects contained within a vector of Continents. The map object contains other characteristics
such as filename, author, and imagefile, as well as properties wrap, scroll and warn. The map object is used
to build a risk map by creating territories and continents, while assigning their respective characteristics
*/
class Map : public Observable
{
private:
	std::string filename;	//filename for the map
	std::string author;	//author of the map
	std::string image;	//image file associated with the map
	bool wrap;
	bool scroll;	//true = horizontal, false = vertical
	bool warn;
	std::vector<Continent> continents;	//continents vector containing the continent objects in the map
	std::vector<Territory> territories;	//territories vector containing the territory objects in the map
	int tempTurnForLoadingMap;
public:
	Map();//default constructor
	void setMap(std::string, std::string, std::string, bool, bool, bool);
	void setMap(std::string, std::string, std::string, bool, bool, bool, int);
	void Map::addContinent(std::string, int);
	void Map::addTeritory(std::string, int, int, std::string);
	void Map::addTeritory(std::string name, int xLoc, int yLoc, std::string continent, int player, int armies);
	std::string getFilename();
	std::string getAuthor();
	std::string getImage();
	bool getWrap();
	bool getScroll();
	bool getWarn();
	std::string getContinentsNames(int);
	int getContinentsIntegerValues(int);
	int getNumberOfContinents();
	std::string getTerritoriesNames(int);
	int getNumberOfTerritories();
	std::string getContinentOfTerritory(int);
	int getTerritoryX(int);
	int getTerritoryY(int);
	int getTerritoryNumberOfLinks(int);
	std::string getTerritoryLinkName(int, int);
	void putTerritoryLink(int, std::string);
	void removeTerritoryLink(int, std::string);
	Territory* getTerritory(int);
	Continent* getContinent(int);
	//Returns the vector of Continent objects in the Map
	std::vector<Continent> getAllContinents(){
		return continents;
	}
	//returns a vector of Territory objects in the Map
	std::vector<Territory> getAllTerritories(){
		return territories;
	}
	void editContinent(std::string, std::string, int);
	void editTerritory(std::string, std::string, int, int);
	void deleteContinent(std::string);
	void deleteTerritory(std::string);
	std::vector<std::string>getBordersOfTerritory(std::string a);
	std::vector<Territory> getTerritoriesOfContinent(std::string a);
	int getTerritoryIndex(std::string);
	int getTerritoryIndex(Territory* t);
	void addBordersBothWays(int, std::string);
	void deleteBordersBothWays(int, std::string);
	void mapStartGameSetup();
	void idStartSetUp();
	void setControllingIndexOnTerritory(int,int);
	int Map::getIndexOfControllingPlayerOfTerritory(int territory);
	int getTempTurnForLoadingMap(){
		return tempTurnForLoadingMap;
	}
	~Map();
};

#endif
