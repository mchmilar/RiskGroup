#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Observable.h" //Game is a concrete observable for the driver observer

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Game: public Observable
{
private:
	std::vector<Player*> *players;
	int numOfPlayers = 0;
	std::string reinforcementLogString = "";
	std::string attackLogString = "";
public:
	Game();
	void endOfTurn();
	std::string getAttackLog();
	std::string getReinforcementsLog();
	int getNumOfPlayers();
	void setNumOfPlayers(int numOfPlayers);
	std::vector<Player*>* getAllPlayersFromGame();
	Player* getPlayerByIDFromGame(int);
	void addTerritoryToPlayerID(int, Territory*);
	void calculateReinforcementsOfPlayer(int);
	int getPlayerReinforcements(int);
	void removeReinforcementsFromPlayer(int,int);
	void addReinforcementToPlayer(int, int);
	void setPlayerName(int, std::string);
	bool attack(Territory* sourceAttacking, int armiesAttacking, Territory* target, int defendingArmies, bool);
	int getNumberOfTerritoresOfPlayer(int);
	int rollDie();
	int getInfantryCards(int);
	int getCavalryCards(int);
	int getArtilleryCards(int);
	int getCardsValue(int);
	void setCardsPlayed(int, int);
	void setInfantryCards(int, int);
	void setCavalryCards(int, int);
	void setArtilleryCards(int, int);
	void addPlayer(std::string , int , int , int , int , int , int , bool , int );
};
#endif