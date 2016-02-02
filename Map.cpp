#include "Map.h"
#include "Continent.h"
#include "Territory.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <vector>

Map::Map(){//default constructor

}

//map initialization that assigns the filename, author, image name, wrap, scroll and warn properties
void Map::setMap(std::string file, std::string name, std::string image2, bool wrap2, bool scroll2, bool warn2)
{
	filename = file;
	author = name;
	image = image2;
	wrap = wrap2;
	scroll = scroll2;
	warn = warn2;
}
void Map::setMap(std::string file, std::string name, std::string image2, bool wrap2, bool scroll2, bool warn2, int tempTurnForLoadingMap2)
{
	filename = file;
	author = name;
	image = image2;
	wrap = wrap2;
	scroll = scroll2;
	warn = warn2;
	tempTurnForLoadingMap = tempTurnForLoadingMap2;
}


//adds a new continent to the continents vector by name, while assigning it an integer value
void Map::addContinent(std::string name, int value){
	continents.push_back(Continent(name, value));
}
//adds a new Territory object to the territories vector, passing the name, x and y coordinates and the associated continent name
void Map::addTeritory(std::string name, int xLoc, int yLoc, std::string continent){
	territories.push_back(Territory(name, xLoc, yLoc, continent));
}
void Map::addTeritory(std::string name, int xLoc, int yLoc, std::string continent, int player, int armies){
	territories.push_back(Territory(name, xLoc, yLoc, continent, player, armies));
}
//returns the filename of the map
std::string Map::getFilename(){
	return filename;
}
//returns the author of the map
std::string Map::getAuthor(){
	return author;
}
//returns the image filename of the map
std::string Map::getImage(){
	return image;
}
//provides a boolean value for whether wrap is set
bool Map::getWrap(){
	return wrap;
}
//provides a boolean value for whether scroll is set
bool Map::getScroll(){
	return scroll;
}
//provides a boolean value for whether warn is set
bool Map::getWarn(){
	return warn;
}
//returns the name for the Continent in the continents vector at the passed index
std::string Map::getContinentsNames(int i){
	return continents[i].getName();
}
//returns the integer value associated to a Continent object in the continents vector at the passed index
int Map::getContinentsIntegerValues(int i){
	return continents[i].getIntegerValue();
}
//returns the number of Continent objects in the continents vector
int Map::getNumberOfContinents(){
	return continents.size();
}
//returns the name for the Territory object in the territories vector at the passed index
std::string Map::getTerritoriesNames(int i){
	return territories[i].getName();
}
//returns the number of Territory objects in the territories vector
int Map::getNumberOfTerritories(){
	return territories.size();
}
//returns the X coordinate location for the Territory object in the territories vector at the passed index 
int Map::getTerritoryX(int i){
	return territories[i].getX();
}
//returns the Y coordinate location for the Territory object in the territories vector at the passed index 
int Map::getTerritoryY(int i){
	return territories[i].getY();
}
//returns the number of neighboring territories for a Territory object in the territories array at the passed index
int Map::getTerritoryNumberOfLinks(int i){
	return territories[i].getNumberofLinks();
}
//returns the name of the continent associated with the Territory object in the territories vector at the passed index
std::string Map::getContinentOfTerritory(int territoryIndex){
	return territories[territoryIndex].getContinentName();
}
//returns the name of a territory border having passed the Territory object index and the index of that particular border (link)
std::string Map::getTerritoryLinkName(int territoryIndex, int territoryLinkIndex){
	return territories[territoryIndex].getTerritoryLink(territoryLinkIndex);
}
//assigns a new link between a the Territory at the passed index by calling addTerritoryLink(..) and assigning the link name as an argument
void Map::putTerritoryLink(int territoryIndex, std::string pointer){
	territories[territoryIndex].addTerritoryLink(pointer);
}
//removes the link name from the Territory at the passed index by calling removeTerritory(..) and assigning the link name as an argument  
void Map::removeTerritoryLink(int territoryIndex, std::string pointer){
	territories[territoryIndex].removeTerritoryLink(pointer);
}

//Accessor for the pointer of a continent object in the map class at the given continent index
Continent* Map::getContinent(int index){
	Continent *pntContinent = &continents[index];
	return pntContinent;
}
//Accessor for the pointer of a territory object in the map class at the given continent index
Territory* Map::getTerritory(int index){
	Territory *pntTerritory = &territories[index];
	return pntTerritory;
}
//Accessor for the vector of neighboring territory names of the passed territory name argument
std::vector<std::string> Map::getBordersOfTerritory(std::string territoryName){
	
	int index = 0;
	for (int i = 0; i < territories.size(); i++){
		if (territories[i].getName().compare(territoryName) == 0){
			index = i;
		}
	}
	std::vector<std::string> T;
	for (int i = 0; i < territories[index].getAllBorders().size(); i++){
		T.push_back(territories[index].getAllBorders()[i]);
	}
	return T;
}
//Accessor for the vector of neighboring territories in a passed continent name argument
std::vector<Territory> Map::getTerritoriesOfContinent(std::string continentName){
	std::vector<Territory> T;
	for (int i = 0; i < territories.size(); i++){
		if (continentName.compare(territories[i].getContinentName()) == 0){
			T.push_back(territories[i]);
		}
	}
	return T;
}
//Changes the basic characteristics of a continent - name and associated value
void Map::editContinent(std::string oldName, std::string newName, int val){
	for (int i = 0; i < continents.size(); i++){
		if (continents[i].getName().compare(oldName) == 0){
			continents[i].setContinent(newName, val);
		}
	}
}

//Changes the basic characteristics of a territory - name and location
void Map::editTerritory(std::string oldName, std::string newName, int xValue, int yValue){
	for (int i = 0; i < territories.size(); i++){
		if (territories[i].getName().compare(oldName) == 0){
			territories[i].setTerritory(newName, xValue, yValue);
		}
	}
}
//Removes a continent name from the vector of continent names
void Map::deleteContinent(std::string name){
	for (int i = 0; i < continents.size(); i++){
		if (continents[i].getName().compare(name) == 0){
			continents.erase(continents.begin()+i);
		}
	}
}
//Removes a territory name from the vector of territory names 
void Map::deleteTerritory(std::string name){
	for (int i = 0; i < territories.size(); i++){
		if (territories[i].getName().compare(name) == 0){
			territories.erase(territories.begin() + i);
		}
	}
}
//Accesor for the territory index having the passed territory name
int Map::getTerritoryIndex(std::string tName){
	int returnIndex = -1;
	for (int i = 0; i < territories.size(); i++){
		if (territories[i].getName().compare(tName) == 0){
			returnIndex = i;
			i = territories.size();//ending loop
		}
	}
	return returnIndex;
}
//Accesor for the territory index having the passed territory
int Map::getTerritoryIndex(Territory* t){
	return t->getTerritoryId();
}
//Adds borders between two territories by taking as arguments the index i of the first territory object and
//the string name of the second territory object
void Map::addBordersBothWays(int i, std::string borderingTerritory){
	int j = getTerritoryIndex(borderingTerritory);
	putTerritoryLink(i, borderingTerritory);
	putTerritoryLink(j, getTerritoriesNames(i));
}
//Removes the border between two territories by taking as arguments index i of the first territory object and 
//the string name of the bordering territory object
void Map::deleteBordersBothWays(int i, std::string borderingTerritory){
	int j = getTerritoryIndex(borderingTerritory);
	removeTerritoryLink(i, borderingTerritory);
	removeTerritoryLink(j, getTerritoriesNames(i));
}
//Assigns the index of the controlling player to the Territory object (accessed through its index)
void Map::setControllingIndexOnTerritory(int playerIndex, int territoryIndex){
	territories[territoryIndex].setIndexOfControllingPlayer(playerIndex);
}
void Map::idStartSetUp(){
	for (int i = 0; i < continents.size(); i++){
		continents[i].setContinentIntId(i);//sets an unique identifier
	}
	for (int j = 0; j < territories.size(); j++){
		territories[j].setTerritoryId(j);//sets an unique identifier
	}
}
//set correct pointers in territory and player class
void Map::mapStartGameSetup(){
	std::vector<int> continentsTracker(continents.size(),0);//vector of size contient size with value 0
	for (int i = 0; i < continents.size(); i++){
		continents[i].setNumberOfTerritories(continentsTracker[i]);//sets number of territories of each contient
	}
	for (int i = 0; i < territories.size(); i++){
		territories[i].setPointers(territories, continents);
		for (int j = 0; j < continents.size(); j++){
			if (territories[i].getContinentName().compare(continents[j].getName())){
				continentsTracker[j] = continentsTracker[j] + 1;
				j = continents.size();//exits loop
			}
		}
	}
	
}
int Map::getIndexOfControllingPlayerOfTerritory(int territory){
	return territories[territory].getIndexOfControllingPlayer();
}
Map::~Map()
{
}
