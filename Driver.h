#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "UI.h"
#include "Map.h"
#include "Game.h"
#include "Continent.h"
#include "Territory.h"
#include "Player.h"
#include "Logger.h"
#include "Observer.h"

/**
This program employs a Model, View, Controller structure, with the Driver acting as the Controller.
Because of the requirement to implement Observer classes which cannot be done with this GUI implementation,
the driver extends the MasterObserver class to act as an observer, notifying the GUI.
*/
using std::string;
using std::vector;
using namespace System;
using namespace System::Windows::Forms;
using namespace Risk;
class Driver : public Observer
{
private:
	bool playersSet = false;
public:
	//Observer functions as the driver is being used to update the GUI
	void attachMap(Map* m){
		mapObservable = m;
		mapObservable->attach(this);
	}
	void attachGame(Game* g){
		gameObservable = g;
		gameObservable->attach(this);
	}
	void update(){
		notifyView();
	};
	void notifyView();
	void updateLogInGui(string);
	//Decorator and observer functions for the logger
	void emptyLog();
	void fullLog();
	void reinforcementsLog();
	void attackLog();
	string getStats();

	Driver();
	bool createMap(string, string, string, bool, bool, bool);
	string getAfterEqualSpacer(string line);
	string getBeforeEqualSpacer(string line);
	std::vector<std::string> getBordersOfTerritory(std::string a);
	std::vector<Territory> getAllTerritories();
	std::vector<Territory> getTerritoriesOfContinent(std::string a);
	vector<Continent> getAllContinents();
	void addContinent(string, int);
	void addTerritory(string, int, int, string);
	void editContinent(string, string, int);
	void editTerritory(string, string, int, int);
	bool loadMap(string);
	bool loadPlayersMap(string);
	void saveMap();
	void deleteContinent(string);
	void deleteTerritory(string);
	std::string saveMapcheck();
	std::string loadMapCheck();
	string getTerritoryName(int);
	void addBorders(int, string);
	void deleteBorders(int, string);
	Territory* getTerritory(int);
	int getTerritoryIndex(string);
	int getTerritoryX(int);
	int getTerritoryY(int);
	std::string getContinentOfTerritory(int);
	void mapStartGameSetup(int);
	void reinforceContinentNumberCalculate();
	void reinforce(int , Territory* );
	bool attackCalculations(Territory*, int, Territory*, bool);
	void fortify(Territory* , int , Territory* );
	bool checkPathBetweenTerritoriesOfSamePlayer(Territory*, Territory*);
	vector<Player*>* getAllPlayers();
	Player* getPlayerByID(int);
	int getTurn();
	void setTurn(int);
	void nextTurn();
	void setPhase(int);
	void assignTerritoriesAtStart(int);
	void assignTerritory(int, int);
	int getCurrentPlayerReinforcments();
	void addReinforcements(int);
	void setCurrentPlayerName(string);
	int getInfantryCards();
	int getCavalryCards();
	int getArtilleryCards();
	int getCardsValue();
	void setCardsPlayed(int);
	void setInfantryCards(int);
	void setCavalryCards(int);
	void setArtilleryCards(int);
	bool getPlayerSet(){
		return playersSet;
	};
	int getLoadingTurn();
private:
	Map *mapObservable;
	Game *gameObservable;
	Logger *logger;
	int gamePhase;//1= reinforce, 2= attack, 3= fortify
	int playerTurn;
	string statsString;
	
};

#endif
