#ifndef TERRITORY_H
#define TERRITORY_H

#include "Continent.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/*
Territory objects are created in the Map class. Each territory is controlled by a player
with a number of army units. Information about the continent it is a part of and the bordering 
territories. 
*/
class Territory
{
private:
	std::string name;	//the territory name 
	int xLoc;	//location of the territory along the x axis
	int yLoc;	//location of the terriroty along the y axis
	std::vector<std::string> territoryLinksStrings;	//the names of the bordering countries in a vector
	std::string continentLinkString;	//the name of the continent the territory is in
	std::vector<Territory*> territoryLinks;	//a vector of pointers to the neighboring territories
	Continent* continentLink;	//a pointer to the continent the territory is in
	int armies;	//the number of armies on the territory
	int controlledByPlayer; //the number of the player controlling the country
	int TerritoryIntId;//unique identifier
public:
	Territory();
	Territory(std::string, int, int, std::string);
	Territory(std::string, int, int, std::string, int, int);
	//Territory(const Territory &p);//copy constructor
	void addTerritoryLink(std::string);
	void removeTerritoryLink(std::string);
	std::string getName();
	std::string getContinentName();
	Continent* getContinentLink();
	int getX();
	int getY();
	int getNumberofLinks();
	int getNumberofBorders();
	std::string getTerritoryLink(int);
	std::vector<std::string> getAllBorders(){
		return territoryLinksStrings;
	}
	bool isBorder(Territory);
	void setTerritory(std::string, int, int);
	void setPointers(std::vector<Territory>, std::vector<Continent>);
	~Territory();
	int getArmiesInTerritory();
	void setArmiesInTerritory(int);
	void addArmiesToTerritory(int);
	void removeArmiesFromTerritory(int);
	int getIndexOfControllingPlayer();
	void setIndexOfControllingPlayer(int);
	std::vector<Territory*> getBorders();
	void setTerritoryId(int);
	int getTerritoryId();
};

#endif