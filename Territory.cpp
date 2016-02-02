#include "Territory.h"
#include "Continent.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

//Default constructor
Territory::Territory(){

}

//Constructor taking the name of the territory, the integer locations along the X and Y axis, and the name of the continent where it is found
Territory::Territory(std::string name2, int xLoc2, int yLoc2, std::string continents2)
{
	name = name2;
	xLoc = xLoc2;
	yLoc = yLoc2;
	continentLinkString = continents2;
	armies = 1;
	controlledByPlayer = -1;
	TerritoryIntId = 0;
}
Territory::Territory(std::string name2, int xLoc2, int yLoc2, std::string continents2, int player, int armies2)
{
	name = name2;
	xLoc = xLoc2;
	yLoc = yLoc2;
	continentLinkString = continents2;
	armies = armies2;
	controlledByPlayer = player;
	TerritoryIntId = 0;
}
/*Territory::Territory(const Territory &p){//copy constructor
name = p.name;
xLoc = p.xLoc;
yLoc = p.yLoc;
continents = p.continents;
territoryLinks = p.territoryLinks;
}*/
void Territory::addTerritoryLink(std::string pointer){
	territoryLinksStrings.push_back(pointer);
}

//Removes a border by name from the territoryLinksStrings vector of string border names 
void Territory::removeTerritoryLink(std::string name){
	for (int i = 0; i < territoryLinksStrings.size(); i++){
		if (territoryLinksStrings[i].compare(name) == 0){
			territoryLinksStrings.erase(territoryLinksStrings.begin() + i);
		}
	}
}
//Returns the name of the territory
std::string Territory::getName(){
	return name;
}
//Returns the name of the Continent the territory is found in
std::string Territory::getContinentName(){
	return continentLinkString;
}
//Returns the Continent pointer associated with the given territory
Continent* Territory::getContinentLink(){
	return continentLink;
}
//Returns the integer value of the territory's position on the X axis
int Territory::getX(){
	return xLoc;
}
//Returns the integer value of the territory's position on the Y axis
int Territory::getY(){
	return yLoc;
}
//Returns an integer count for the number of borders 
int Territory::getNumberofBorders(){
	return territoryLinks.size();
}
//Returns an integer count for the number of borders 
int Territory::getNumberofLinks(){
	return territoryLinksStrings.size();
}
//Returns the bordering territory names for a given territory
std::string Territory::getTerritoryLink(int territoryLinkIndex){
	return territoryLinksStrings[territoryLinkIndex];
}
//Assigns a terriotry Object with a new name and integer coordinates for X and Y locations
void Territory::setTerritory(std::string newName, int xLocation, int yLocation){
	name = newName;
	xLoc = xLocation;
	yLoc = yLocation;
}

/*
Assigns pointer values to the territories and continents. This function is only called after the map is no longer editable as
only strings are used during map creation, which prevents the pointers from getting messed up. This function adds actual pointers by 
scanning the unique strings. 
*/
void Territory::setPointers(std::vector<Territory> allTerritories, std::vector<Continent> allContinents){
	for (int i = 0; i < territoryLinksStrings.size();i++){
		for (int j = 0; j < allTerritories.size();j++){
			if (territoryLinksStrings[i].compare(allTerritories[j].getName())==0){
				territoryLinks.push_back(new Territory(allTerritories[j]));
				//j = allTerritories.size();//ends loop
			}
		}
	}
	for (int i = 0; i < allContinents.size(); i++){
		if (continentLinkString.compare(allContinents[i].getName())==0){
			continentLink = new Continent(allContinents[i]);
		}
	}
}
//Returns an integer representing the number of the armies in the given territory
int Territory::getArmiesInTerritory(){
	return armies;
}
void Territory::setArmiesInTerritory(int newArmies){
	armies = newArmies;
}
//Returns the integer value representing the player controlling that territory
int Territory::getIndexOfControllingPlayer(){
	return controlledByPlayer;
}
//Determines whether the Territory object has a border reference to the passed Object pointer
bool Territory::isBorder(Territory t){
	for (int i = 0; i < territoryLinks.size(); ++i)
	{
		if (territoryLinks[i]->getName().compare(t.getName()))
			return true;
	}
	return false;
}
//Sets the index of the controlling player of a country to the passed integer value
void Territory::setIndexOfControllingPlayer(int i){
	controlledByPlayer = i;
}
//Adds the passed integer value of armies to the territory
void Territory::addArmiesToTerritory(int a){
	armies += a;
}
//Removes the passed integer value of armies from the territory
void Territory::removeArmiesFromTerritory(int a)
{
	armies -= a;
}
std::vector<Territory*> Territory::getBorders(){
	return territoryLinks;
}
void Territory::setTerritoryId(int id){
	TerritoryIntId = id;
}
int Territory::getTerritoryId(){
	return TerritoryIntId;
}
//Destructor
Territory::~Territory()
{
}
