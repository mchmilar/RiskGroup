#include "UI.h"
#include "Driver.h"
#include "Map.h"
#include "Continent.h"
#include "Territory.h"
#include "Game.h"
#include "Logger.h"
#include "LoggerNone.h"
#include "LoggerReinforcements.h"
#include "LoggerAttack.h"
#include "MapBuilder.h"	
#include "MapWithPlayers.h"
#include "MapWithoutPlayers.h"
#include "BuilderDirector.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <msclr\auto_gcroot.h>

using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::istringstream;
using std::endl;
using namespace Risk;
int command;
string inputText;
Map *mainMap = new Map();
Game *mainGame = new Game();
gcroot<Risk::UI^> form;


Driver::Driver()
{
	//connects basic map and game observers
	this->attachMap(mainMap);
	this->attachGame(mainGame);
	//creates an empty logger acting as an observer for the main game log observable
	this->fullLog();
}

void main(){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	form = gcnew Risk::UI;
	//form = Risk::UI form;
	Application::Run(form);
}

//Dynamic log functions that employ a decorator pattern
//Todo must call logger->getLog to access the latest log string. These may eventually 
//get too large so it might be useful to trim them from the driver
void Driver::emptyLog()
{
	logger = new LoggerNone(mainGame);
}
void Driver::reinforcementsLog()
{
	logger = new LoggerNone(mainGame);
	logger = new LoggerReinforcements(logger);
}
void Driver::attackLog()
{
	logger = new LoggerNone(mainGame);
	logger = new LoggerAttack(logger);
}
void Driver::fullLog()
{
	logger = new LoggerNone(mainGame);
	logger = new LoggerAttack(logger);
	logger = new LoggerReinforcements(logger);
}

//Increments the playerTurn by 1 and assigns reinforcements
void Driver::nextTurn(){
	playerTurn += 1;
	mainGame->endOfTurn(); //calls notify 
	this->updateLogInGui(logger->getLog());
	//this->updateLogInGui(mainGame->getReinforcementsLog() + "\n" + mainGame->getAttackLog());
	if (playerTurn > mainGame->getNumOfPlayers() - 1){
		playerTurn = 0;
	}
	while (mainGame->getNumberOfTerritoresOfPlayer(playerTurn) == 0){
		playerTurn += 1;
		if (playerTurn > mainGame->getNumOfPlayers() - 1){
			playerTurn = 0;
		}
	}
	mainGame->calculateReinforcementsOfPlayer(playerTurn);
	reinforceContinentNumberCalculate();
}
//Refreshes the GUI from the driver
void Driver::notifyView(){
	form->notify();
}

//Parser function to fet text after the "=" in the text file
string Driver::getAfterEqualSpacer(string line){
	bool notFinished = true;
	while (line != "" && notFinished){
		if (line[0] == '='){//found the equal spacer
			line = line.erase(0, 1);//delete the equal spacer
			notFinished = false;
		}
		else{
			line = line.erase(0, 1);//delete that first character of the text
		}
	}
	return line;
}
void Driver::updateLogInGui(string text){
	form->updateLogInUI(text);
}
string Driver::getStats(){
	statsString = "";

	for (int i = 0; i < mainGame->getNumOfPlayers(); i++){
		statsString += mainGame->getAllPlayersFromGame()->at(i)->getName();
		statsString += " has ";
		ostringstream convert;
		convert << mainGame->getAllPlayersFromGame()->at(i)->getNumberOfTerritories();
		statsString += convert.str();
		statsString += " territories.\n";
	}
	return statsString;
}
//Parser function to get text before the "=" in the text file
string Driver::getBeforeEqualSpacer(string line){
	bool notFinished = true;
	string buffer = "";
	while (line != "" && notFinished){
		if (line[0] == '='){//found the equal spacer
			notFinished = false;
		}
		else{
			buffer += line[0];
			line = line.erase(0, 1);//delete that first character of the text
		}
	}
	return buffer;
}
//Creates a map by calling the setMap function from the main map
bool Driver::createMap(string file, string name, string image2, bool wrap2, bool scroll2, bool warn2){
	mainMap->setMap(file, name, image2, wrap2, scroll2, warn2);
	return true;
}

bool loadOnlyMap(string location){
	Director director;
	MapBuilder* mapWithoutPlayersBuilder = new MapWithoutPlayers;
	director.setMapBuilder(mapWithoutPlayersBuilder);

	if (director.constructMap(location)){
		mainMap = director.getMap();
		return true;
	}
	else{
		return false;
	}

}
bool Driver::loadPlayersMap(string location){
	Director director;
	MapBuilder* mapWithPlayersBuilder = new MapWithPlayers;
	director.setMapBuilder(mapWithPlayersBuilder);
	if (director.constructMap(location)){
		mainMap = director.getMap();
		mainGame = director.getGame();
		playersSet = true;
		return true;
	}
	else{
		return false;
	}
}
//Loads the map, taking as an argument the name of the file located in the directory
bool Driver::loadMap(string location){
	string line;
	//Map map;
	bool mapWithPlayers = false;
	string fileLocation = location;
	ifstream file;

	file.close();
	file.open(fileLocation);
	if (file.is_open())
	{
		getline(file, line);//first phase when creating map with info and populating continents and territories
		if (line.compare("[Map]") == 0){
			file.close();
			return loadOnlyMap(fileLocation);
		}
		else if (line.compare("[Map With Players]") == 0){
			file.close();
			return loadPlayersMap(fileLocation);

		}
	}
	else{
		return false;
	}

	return true;
}


//Loads the map, taking as an argument the name of the file located in the directory
/*bool Driver::loadMap(string location){
	string line;
	//Map map;
	string fileLocation = location;
	ifstream file(fileLocation);
	if (file.is_open())
	{
		int counter = 0;//line counter
		int phase = 1;//2 is for continents, 3 is for territories
		string author;
		string image;
		bool wrap;
		bool scroll;
		bool warn;
		int continentCounter = 0;
		while (getline(file, line))//first phase when creating map with info and populating continents and territories
		{
			counter += 1;
			if (phase == 1){//map settings
				switch (counter){
				case 1:{//[Map]
					if (line.compare("[Map]") != 0){
						return false;
					}
					break;
				}
				case 2:{//author
					author = getAfterEqualSpacer(line);
					break;
				}
				case 3:{//image
					image = getAfterEqualSpacer(line);
					break;
				}
				case 4:{//wrap
					string wrapString = getAfterEqualSpacer(line);
					if (wrapString.compare("yes") == 0){
						wrap = true;
					}
					else{
						wrap = false;
					}
					break;
				}
				case 5:{//scroll
					string scrollString = getAfterEqualSpacer(line);
					if (scrollString.compare("horizontal") == 0){
						scroll = true;
					}
					else{
						scroll = false;
					}
					break;
				}
				case 6:{//warn
					string warnString = getAfterEqualSpacer(line);
					if (warnString.compare("yes") == 0){
						warn = true;
					}
					else{
						warn = false;
					}
					if (fileLocation.compare("") == 0 || author.compare("") == 0 || image.compare("") == 0){
						return false;
					}
					mainMap->setMap(fileLocation, author, image, wrap, scroll, warn);//creates map
					break;
				}
				case 7:{//blank spacer
					break;
				}
				case 8:{//[continents] first line
					phase = 2;
					break;
				}
				}
			}
			else if (phase == 2){//continents
				if (line.compare("[Territories]") == 0){//begining of territories
					phase = 3;
				}
				else if (line.compare("") != 0){//if line not empty
					int intergerValue;
					string intValue = getAfterEqualSpacer(line);
					istringstream(intValue) >> intergerValue;
					mainMap->addContinent(getBeforeEqualSpacer(line), intergerValue);
				}
			}
			else{//teritories
				if (line.compare("") != 0){
					string teritoryname;
					int xLoc;
					int yLoc;
					string buffer = "";
					int counter = 0;
					while (line != ""){
						buffer += line[0];
						line = line.erase(0, 1);//delete that first character of the text
						if (line[0] == ',' || line == ""){//found the equal spacer
							counter += 1;
							line = line.erase(0, 1);
							if (counter == 1){//teritory name
								teritoryname = buffer;
							}
							else if (counter == 2){//x loc
								istringstream(buffer) >> xLoc;
							}
							else if (counter == 3){//y loc
								istringstream(buffer) >> yLoc;
							}
							else if (counter == 4){//continent
								mainMap->addTeritory(teritoryname, xLoc, yLoc, mainMap->getContinent(continentCounter)->getName());
							}
							buffer = "";
						}
					}
				}
				else{
					continentCounter += 1;
				}
			}
		}
		file.close();
		ifstream file2(fileLocation);
		bool territoryPhase = false;
		int territoryCounter = 0;
		while (getline(file2, line)){//Second phase, after map was created and territories/continents added, this re-reads the file to add the territory links
			if (territoryPhase){
				if (line.compare("") != 0){//if not a spacer between contients

					string teritorybuffer = "";

					int wordCounter = 0;//line counter
					while (line != ""){
						teritorybuffer += line[0];
						line = line.erase(0, 1);//delete that first character of the text
						if (line[0] == ',' || line == ""){//found the equal spacer
							wordCounter += 1;
							line = line.erase(0, 1);
							if (wordCounter >= 5){//territory links
								int correctIndex = 0;
								for (int i = 0; i < mainMap->getNumberOfTerritories(); i++){
									if (mainMap->getTerritoriesNames(i).compare(teritorybuffer) == 0){//finds the index of the correct territory link
										correctIndex = i;
									}
								}
								mainMap->putTerritoryLink(territoryCounter, mainMap->getTerritory(correctIndex)->getName());//adds the territory link to the territory
							}
							teritorybuffer = "";
						}
					}
					territoryCounter += 1;
				}
				else{
					//next continent
				}
			}
			else if (line.compare("[Territories]") == 0){
				territoryPhase = true;
			}
		}
	}
	else{
		return false;
	}
	return true;
}*/
//Saves the map to the directory
void Driver::saveMap(){
	ofstream textFile(mainMap->getFilename());
	textFile << "[Map]" << endl;
	textFile << "author=" << mainMap->getAuthor() << endl;
	textFile << "image=" << mainMap->getImage() << endl;
	textFile << "wrap=";
	if (mainMap->getWrap()){
		textFile << "yes" << endl;
	}
	else{
		textFile << "no" << endl;
	}
	textFile << "scroll=";
	if (mainMap->getScroll()){
		textFile << "horizontal" << endl;
	}
	else{
		textFile << "vertical" << endl;
	}
	textFile << "warn=";
	if (mainMap->getWarn()){
		textFile << "yes" << endl;
	}
	else{
		textFile << "no" << endl;
	}
	textFile << "\n[Continents]" << endl;
	for (int i = 0; i < mainMap->getNumberOfContinents(); i++){
		textFile << mainMap->getContinentsNames(i) << "=" << mainMap->getContinentsIntegerValues(i) << endl;
	}
	textFile << "\n[Territories]" << endl;
	for (int i = 0; i < mainMap->getNumberOfContinents(); i++){
		for (int j = 0; j < mainMap->getNumberOfTerritories(); j++){
			if (mainMap->getContinentsNames(i).compare(mainMap->getContinentOfTerritory(j)) == 0){
				textFile << mainMap->getTerritoriesNames(j) << "," << mainMap->getTerritoryX(j) << "," << mainMap->getTerritoryY(j) << "," << mainMap->getContinentsNames(i);
				for (int k = 0; k < mainMap->getTerritoryNumberOfLinks(j); k++){
					textFile << "," << mainMap->getTerritoryLinkName(j, k);
				}
				textFile << endl;
			}
		}
		textFile << endl;
	}
}
//Adds a new continent to the driver assigning the string name as the continent name and a value to be associated with that continent
void Driver::addContinent(string name, int val){
	mainMap->addContinent(name, val);
}
//Adds a new territory to the driver assigning the string name as the territory name, the location values X and Y and the continent the territory is in 
void Driver::addTerritory(string name, int x, int y, string continent){
	mainMap->addTeritory(name, x, y, continent);
}
//Changes the basic characteristics of a continent - name and associated value
void Driver::editContinent(string oldName, string newName, int value){
	mainMap->editContinent(oldName, newName, value);
}
//Changes the basic characteristics of a territory - name and location
void Driver::editTerritory(string oldName, string newName, int xXalue, int yValue){
	mainMap->editTerritory(oldName, newName, xXalue, yValue);
}
//Accessor for the vector of neighboring territory names of the passed territory name argument
std::vector<std::string> Driver::getBordersOfTerritory(std::string territoryName){
	return mainMap->getBordersOfTerritory(territoryName);
}
//Accessor for the pointer of a territory object in the map class at the given continent index
Territory* Driver::getTerritory(int i){
	return mainMap->getTerritory(i);
}
//Returns the vector of territory objects in the mainMap->
std::vector<Territory> Driver::getAllTerritories(){
	return mainMap->getAllTerritories();
}
//Returns the vector of territory objects in the mainMap that are within the passed continent name
std::vector<Territory> Driver::getTerritoriesOfContinent(std::string continentName){
	return mainMap->getTerritoriesOfContinent(continentName);
}
//Returns the vector of Continent objects in the mainMap
vector<Continent> Driver::getAllContinents(){
	return mainMap->getAllContinents();
}
//Removes a continent from the main map when that continent name is passed as an argument
void Driver::deleteContinent(string continentName){
	mainMap->deleteContinent(continentName);
}
//Deletes a territory from the main map when that territory name is pased as an argument
void Driver::deleteTerritory(string territoryName){
	mainMap->deleteTerritory(territoryName);
}
//Checks for empty continents and if all territories are linked
std::string Driver::saveMapcheck(){
	string returnString = "";

	//phase 1, checking for empty continents

	std::vector<std::string> uniques;
	for (int i = 0; i < mainMap->getNumberOfTerritories(); i++){//for all territories
		bool found = false;
		for (int j = 0; j < uniques.size(); j++){//for all unique continent names
			if (uniques[j].compare(mainMap->getContinentOfTerritory(i)) == 0){//if current continent is already in the list
				found = true;
			}
		}
		if (!found){//if continent name wasn't in the list yet
			uniques.push_back(mainMap->getContinentOfTerritory(i));
		}
	}
	if (uniques.size() != mainMap->getNumberOfContinents()){
		returnString = "Error: There are empty continents";
	}

	//phase 2, checking for un-linked territories
	uniques.clear();
	if (returnString.compare("") == 0){
		uniques.push_back(mainMap->getTerritoriesNames(0));//adds the first element
		bool uniqueFound = false;//for checking if territory already in unique list
		bool newTerritoryFound = true;//for checking if no new territories have been added this loop
		int counter = 0;
		while (newTerritoryFound){
			newTerritoryFound = false;
			for (int z = counter; z < uniques.size(); z++){//for current number of unique territories added in list
				counter = uniques.size()-1;//doesn't scan previously scanned territories to reduce time
				int newTerritoryIndex = mainMap->getTerritoryIndex(uniques[z]);
				for (int i = 0; i < mainMap->getAllTerritories()[newTerritoryIndex].getNumberofLinks(); i++){//for the borders of that territory
					uniqueFound = false;
					for (int j = 0; j < uniques.size(); j++){//scans previously added territories
						if (uniques[j].compare(mainMap->getAllTerritories()[newTerritoryIndex].getTerritoryLink(i)) == 0){//if name of territory exists already
							uniqueFound = true;
						}
					}
					if (!uniqueFound){//if name is new
						newTerritoryFound = true;
						uniques.push_back(mainMap->getAllTerritories()[newTerritoryIndex].getTerritoryLink(i));
					}
					if (uniques.size() == mainMap->getNumberOfTerritories()){//if territories size already reached
						newTerritoryFound = false;//ends loop to save time
					}
				}
			}
		}
		if (uniques.size() != mainMap->getNumberOfTerritories() && returnString.compare("")==0){
			returnString = "Error: There are territories isolated from other territories";
		}
		
	}
	return returnString;
}
//Checks for unique continent names, unique territory names and no one way borders between territories
std::string Driver::loadMapCheck(){
	string returnString = "";
	std::vector<std::string> uniques;

	//phase 1, checking for unique continent names
	uniques.clear();
	for (int i = 0; i < mainMap->getNumberOfContinents(); i++){//for all continents
		for (int j = 0; j < uniques.size(); j++){//for all previously scanned continent names
			if (uniques[j].compare(mainMap->getContinentsNames(i)) == 0){//if current continent is already in the list
				returnString = "Duplicate continents name";
			}
		}
		uniques.push_back(mainMap->getContinentsNames(i));
	}
	//phase 2, checking for unique territories names
	uniques.clear();
	if (returnString.compare("") == 0){
		for (int i = 0; i < mainMap->getNumberOfTerritories(); i++){//for all territories
			for (int j = 0; j < uniques.size(); j++){//for all previously scanned territory names
				if (uniques[j].compare(mainMap->getTerritoriesNames(i)) == 0){//if current territory is already in the list
					returnString = "Duplicate territory name";
				}
			}
			uniques.push_back(mainMap->getTerritoriesNames(i));
		}
	}
	//phase 3, checking for one way borders between territories
	uniques.clear();
	if (returnString.compare("") == 0){
		bool found;
		for (int i = 0; i < mainMap->getAllTerritories().size(); i++){//for every territories
			vector<string> borders = mainMap->getTerritory(i)->getAllBorders();
			for (int j = 0; j < borders.size(); j++){//for all borders of every territory
				found = false;
				vector<string> secondDegreeBorders = mainMap->getBordersOfTerritory(borders[j]);
				for (int k = 0; k < secondDegreeBorders.size(); k++){
					if (secondDegreeBorders[k].compare(mainMap->getTerritoriesNames(i)) == 0){//if name of 
						found = true;
					}
				}
				if (!found){
					returnString = "A border is one way only";
				}
			}
		}
	}
	return returnString;
}
//Accessor for the territory name at a given index for the Territory vector
string Driver::getTerritoryName(int index){
	return mainMap->getTerritory(index)->getName();
}
//Adds a border between two territorries on the main map 
void Driver::addBorders(int i, string a){
	mainMap->addBordersBothWays(i,a);
}
//Removes a border between two territories on the main map
void Driver::deleteBorders(int i, string a){
	mainMap->deleteBordersBothWays(i, a);
}
//Accesor for the index in the Territory vector given a territory name
int Driver::getTerritoryIndex(string a){
	return mainMap->getTerritoryIndex(a);
}
//Accessor for the territory's X coordinate given the index for the Territory vector in the main map
int Driver::getTerritoryX(int i){
	return mainMap->getTerritoryX(i);
}
//Accessor for the territory's Y coordinate given the index for the Territory vector in the main map
int Driver::getTerritoryY(int i){
	return mainMap->getTerritoryY(i);
}
//Accessor for the territory's Continent given the index for the Territory vector in the main map
std::string Driver::getContinentOfTerritory(int index){

	return mainMap->getContinentOfTerritory(index);
}
string convertIntToString(int num){
	ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return convert.str();
}

vector<Player*>* Driver::getAllPlayers(){
	
	return mainGame->getAllPlayersFromGame();
}
Player* Driver::getPlayerByID(int id){
	
	return mainGame->getPlayerByIDFromGame(id);
}
void Driver::mapStartGameSetup(int playerNumber){

	mainMap->idStartSetUp();
	if (!playersSet){
		mainGame->setNumOfPlayers(playerNumber);
	}
	
	mainMap->mapStartGameSetup();
}

//function that gets how many territories player has and if complete Continent also adds the integer value of that continent as reinforcments to that player
void Driver::reinforceContinentNumberCalculate(){
	vector<Territory> territoriesInContinent;

	for (int i = 0; i < mainMap->getNumberOfContinents(); i++){
		for (int j = 0; j < mainMap->getNumberOfTerritories(); j++){

			if (mainMap->getAllTerritories()[j].getContinentName().compare(mainMap->getAllContinents()[i].getName()) == 0){
				territoriesInContinent.push_back(mainMap->getAllTerritories()[j]);
			}
		}
		if (territoriesInContinent.size() == mainMap->getAllContinents()[i].getNumberOfTerritories()){
			mainGame->addReinforcementToPlayer(playerTurn, mainMap->getContinentsIntegerValues(i));
		}
		territoriesInContinent.clear();
	}
}
//function that sends a number of armies to a certain territory
void Driver::reinforce(int armies, Territory* target){
	mainGame->removeReinforcementsFromPlayer(playerTurn,armies);
	target->addArmiesToTerritory(armies);
}

//function that does the rolling process between armies of 2 countries
bool Driver::attackCalculations(Territory* sourceAttacking, int armiesAttacking, Territory* target, bool alreadyWonOneBattleThisTurn){
	sourceAttacking->removeArmiesFromTerritory(armiesAttacking);//removes armies from territory
	return mainGame->attack(sourceAttacking, armiesAttacking, target, target->getArmiesInTerritory(), alreadyWonOneBattleThisTurn);//attacks
}
//function that removes armies from a territory and adds those armies to another territory
void Driver::fortify(Territory* source, int armiesToTransfer, Territory* target){
	source->removeArmiesFromTerritory(armiesToTransfer);
	target->addArmiesToTerritory(armiesToTransfer);
}
//function that checks if there is a path controlled by a single player between 2 territories. Used as check BEFORE fortification.
bool Driver::checkPathBetweenTerritoriesOfSamePlayer(Territory* source, Territory* target){
	//Breath first search graph algorythm in player's territories to find link between 2 nodes. Return true if found
	std::vector<Territory> allTerritories = mainMap->getAllTerritories();
	vector<Territory*> territoriesOfPlayer = getPlayerByID(getTurn())->getTerritories();
	std::vector<Territory*> uniques;
	uniques.push_back(source);//adds the source element
	bool targetFound = false;
	bool uniqueFound = false;//for checking if territory already in unique list
	bool newTerritoryFound = true;//for checking if no new territories have been added this loop
	//int counter = 0;
	while (newTerritoryFound && !targetFound){
		newTerritoryFound = false;
		int uniqueSize = uniques.size();
		for (int z = 0; z < uniqueSize; z++){//for current number of unique territories added in list
			//counter = uniques.size()-1;//doesn't scan previously scanned territories to reduce time
			for (int i = 0; i < uniques[z]->getNumberofBorders(); i++){//for the borders of that territory
				uniqueFound = false;
				if (allTerritories[uniques[z]->getBorders()[i]->getTerritoryId()].getIndexOfControllingPlayer() == getTurn()){//if territory is of that player
					if (uniques[z]->getBorders()[i]->getName().compare(target->getName()) == 0){//if target name equals to this new territory
						targetFound = true;
					}
					for (int j = 0; j < uniques.size(); j++){//scans previously added territories
						if (uniques[j]->getName().compare(uniques[z]->getBorders()[i]->getName()) == 0){//if name of territory exists already
							uniqueFound = true;
						}
					}
					if (!uniqueFound){//if name is new
						newTerritoryFound = true;
						uniques.push_back(&allTerritories[uniques[z]->getBorders()[i]->getTerritoryId()]);
					}
				}

			}
		}
	}
	return targetFound;
	//return true;
}
//Assigns the territory at territoryIndex to a player at the passed playerId and 
void Driver::assignTerritory(int playerId, int territoryIndex){
	mainMap->setControllingIndexOnTerritory(playerId, territoryIndex);
	mainGame->addTerritoryToPlayerID(playerId, mainMap->getTerritory(territoryIndex));
}
//Assigns the initial territories to each player at random 
void Driver::assignTerritoriesAtStart(int numberOfPlayers){
	if (!playersSet){
		int numberOfTerritoriesAssigned = 0;
		int playerIndex = 0;
		bool notAssigned = true;
		while (numberOfTerritoriesAssigned != mainMap->getNumberOfTerritories()){
			notAssigned = true;
			while (notAssigned){
				int t = rand() % mainMap->getAllTerritories().size() + 1;//between 1 and number of territories
				if (mainMap->getAllTerritories()[t - 1].getIndexOfControllingPlayer() == -1){// if not controlled by player
					notAssigned = false;
					assignTerritory(playerIndex, t - 1);//assigns random territory
					numberOfTerritoriesAssigned++;
				}
			}
			playerIndex++;
			if (playerIndex >= numberOfPlayers){
				playerIndex = 0;
			}
		}
	}
	/*
	for (int i = 0; i < playersNum; i++){
		bool notAssigned = true;
		while (notAssigned){
			int t = rand() % mainMap->getAllTerritories().size() + 1;//between 1 and number of territories
			if (mainMap->getAllTerritories()[t-1].getIndexOfControllingPlayer() == -1){// if not controlled by player
				notAssigned = false;
				assignTerritory(i,t-1);//assigns random territory
			}
		}
	}*/
}
//Accessor method for the player's turn
int Driver::getTurn(){
	return playerTurn;
}
//Mutator method for the player's turn 
void Driver::setTurn(int turn){
	playerTurn = turn;
}

//Mutator for the phase of the game
void Driver::setPhase(int phase){
	gamePhase = phase;
}
void Driver::setCurrentPlayerName(string name){
	mainGame->setPlayerName(playerTurn, name);
}
//Accessor for the number of reinforcments the player has
int Driver::getCurrentPlayerReinforcments(){
	return mainGame->getPlayerReinforcements(playerTurn);
}

//Card accessors and mutators
int Driver::getInfantryCards(){
	return mainGame->getInfantryCards(playerTurn);
}
int Driver::getCavalryCards(){
	return mainGame->getCavalryCards(playerTurn);
}
int Driver::getArtilleryCards(){
	return mainGame->getArtilleryCards(playerTurn);
}
int Driver::getCardsValue(){
	return mainGame->getCardsValue(playerTurn);
}
void Driver::setCardsPlayed(int v){
	mainGame->setCardsPlayed(v, playerTurn);
}
void Driver::setInfantryCards(int v){
	mainGame->setInfantryCards(v, playerTurn);
}
void Driver::setCavalryCards(int v){
	mainGame->setCavalryCards(v, playerTurn);
}
void Driver::setArtilleryCards(int v){
	mainGame->setArtilleryCards(v, playerTurn);
}
void Driver::addReinforcements(int v){
	mainGame->addReinforcementToPlayer(playerTurn,v);
}
int Driver::getLoadingTurn(){
	return mainMap->getTempTurnForLoadingMap();
}