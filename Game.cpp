#include "Game.h"
#include "Continent.h"
#include "Player.h"
#include "Observer.h"

#include <time.h>
#include <string>
#include <algorithm>
#include <Windows.h> // debugging

//Default constructor
Game::Game()
{
	players = new std::vector<Player*>;
}

//Accessor for the total number of players
int Game::getNumOfPlayers()
{
	return numOfPlayers;
}
std::string convertIntToString2(int num){
	std::ostringstream convert;   // stream used for the conversion
	convert << num;      // insert the textual representation of 'Number' in the characters in the stream
	return convert.str();
}
//Assigns the total number of players in the game
void Game::setNumOfPlayers(int numOfPlayers2){

	for (int i = 0; i < numOfPlayers2; i++){
		//Player *temp = new Player();
		players->push_back(new Player());
		//OutputDebugString(L"here");
		players->at(i)->setPlayer("Player" + convertIntToString2(i + 1), i);
	}

	numOfPlayers = numOfPlayers2;
}
//Returns the player vector containing all Player objects ing the game
std::vector<Player*>* Game::getAllPlayersFromGame(){
	return players;
}
//Returns the Player object given an Id argument representing that player
Player* Game::getPlayerByIDFromGame(int playerId){
	return players->at(playerId);
}
//Adds a new Territory to a given Player object based on the player's ID number
void Game::addTerritoryToPlayerID(int playerId, Territory* t){
	players->at(playerId)->addTerritoryOwned(t);
}
//Calculates the reinforcements awarded to a player based on their territories by calling the calculateTerritoriesReinforcments() function
void Game::calculateReinforcementsOfPlayer(int playerId){
	players->at(playerId)->calculateTerritoriesReinforcments();
}
//Accessor for a player's reinforcements given a playerId
int Game::getPlayerReinforcements(int playerId){
	return players->at(playerId)->getReinforcments();
}

//Accessor for the reinforcement log 
std::string Game::getReinforcementsLog()
{
	return reinforcementLogString;
}

//todo call this from the driver at the end of a turn to update the log
void Game::endOfTurn()
{
	notify();
}

//Removes the an integer amount of army reinforcements from a player with the passed playerID
void Game::removeReinforcementsFromPlayer(int playerId, int armies){
	players->at(playerId)->removeReinforcments(armies);
	reinforcementLogString += "Reinforcements deployed: Player " + std::to_string(playerId+1) + " deployed " + std::to_string(armies) +" armies \n";
	//the location will be determined by next notify in the gamelogger
}
//Adds an integer amount of army reinforcements to a player with the passed playerID
void Game::addReinforcementToPlayer(int playerId, int armies){
	reinforcementLogString = "Reinforcements received: Player " + std::to_string(playerId+1) + " gained " + std::to_string(armies) + " armies \n";
	players->at(playerId)->addReinforcments(armies);
}
int getGreatest(std::vector<int> rolls){
	int greatest=0;
	for (int i = 0; i < rolls.size(); i++){
		if (greatest < rolls[i]){
			greatest = rolls[i];
		}
	}
	return greatest;
}
int getSecondGreatest(std::vector<int> rolls){
	int greatest = 0;
	int secondGreatest = 0;
	for (int i = 0; i < rolls.size(); i++){
		if (secondGreatest < rolls[i]){
			if (greatest < rolls[i]){
				greatest = rolls[i];
			}
			else{
				secondGreatest = rolls[i];
			}
		}
	}
	return secondGreatest;
}
//Method to actually rold the dice
int Game::rollDie()
{	
	return rand() % 6 + 1;
}

//Accesor for the attackLogString
std::string Game::getAttackLog()
{
	return attackLogString;
}

//Determines the result of an attack between countries based on the forces used
bool Game::attack(Territory* sourceAttacking, int armiesAttacking, Territory* target, int defendingArmies, bool alreadyWonOneBattleThisTurn){
	int attacking = armiesAttacking;
	int defending = defendingArmies;
	attackLogString += "Attack: Player " + std::to_string(sourceAttacking->getIndexOfControllingPlayer()+1) + " attacked ";
	attackLogString += "Player " + std::to_string(target->getIndexOfControllingPlayer()+1) + " from " + sourceAttacking->getName();
	attackLogString += " with " + std::to_string(armiesAttacking) + " armies to " + target->getName() + " with " + std::to_string(defendingArmies) + ".\n";

	std::vector<int> attRolls;
	std::vector<int> defRolls;
	srand(time(NULL));
	while (attacking != 0 && defending != 0){//while there are attacking or defending armies remaining
		for (int i = 0; i < attacking; i++){
			if (i < 3){
				attRolls.push_back(rollDie());
			}
		}
		for (int i = 0; i < defending; i++){
			if (i < 2){
				defRolls.push_back(rollDie());
			}
		}	
		if (defRolls.size() > 1 && attRolls.size() > 1){//for atleast 2 dice in attacker and defender
			if (getGreatest(defRolls) >= getGreatest(attRolls)){//if def is greater or equal to attacking
				attacking = attacking-1;
			}
			else{//if attacking is greater
				defending = defending - 1;
			}
			if (getSecondGreatest(defRolls) >= getSecondGreatest(attRolls)){//if def is greater or equal to attacking
				attacking = attacking - 1;
			}
			else{//if attacking is greater
				defending = defending-1;
			}
		}
		else{//for less than 2 dices in either attacking or defending
			if (getGreatest(defRolls) >= getGreatest(attRolls)){//if def is greater or equal to attacking
				attacking = attacking - 1;
			}
			else{//if attacking is greater
				defending = defending-1;
			}
		}
		attRolls.clear();
		defRolls.clear();
	}
	if (attacking == 0){
		attackLogString += "The defending army was victorious!\n";
		target->setArmiesInTerritory(defending);
		return false;
	}
	else if (defending == 0){
		attackLogString += "The attacking army was victorious!\n";
		int tempIndexOfDef = target->getIndexOfControllingPlayer();
		target->setArmiesInTerritory(attacking);
		players->at(target->getIndexOfControllingPlayer())->removeTerritoryOwned(target);//removing from defender the territory
		target->setIndexOfControllingPlayer(sourceAttacking->getIndexOfControllingPlayer());
		players->at(sourceAttacking->getIndexOfControllingPlayer())->addTerritoryOwned(target);//adding to attacker the territory
		if (alreadyWonOneBattleThisTurn == false){//wont allow to win more than 1 cards per turn
			int card = rand() % 3 + 1;
			if (card == 1){
				players->at(sourceAttacking->getIndexOfControllingPlayer())->setArtilleryCards(players->at(sourceAttacking->getIndexOfControllingPlayer())->getArtilleryCards() + 1);
			}
			else if (card == 2){
				players->at(sourceAttacking->getIndexOfControllingPlayer())->setCavalryCards(players->at(sourceAttacking->getIndexOfControllingPlayer())->getCavalryCards() + 1);
			}
			else if (card == 3){
				players->at(sourceAttacking->getIndexOfControllingPlayer())->setInfantryCards(players->at(sourceAttacking->getIndexOfControllingPlayer())->getInfantryCards() + 1);
			}
		}
		if (players->at(tempIndexOfDef)->getNumberOfTerritories() == 0){//if player lost, transfers cards
			players->at(sourceAttacking->getIndexOfControllingPlayer())->setArtilleryCards(players->at(sourceAttacking->getIndexOfControllingPlayer())->getArtilleryCards() + players->at(tempIndexOfDef)->getArtilleryCards());
			players->at(sourceAttacking->getIndexOfControllingPlayer())->setCavalryCards(players->at(sourceAttacking->getIndexOfControllingPlayer())->getCavalryCards() + players->at(tempIndexOfDef)->getCavalryCards());
			players->at(sourceAttacking->getIndexOfControllingPlayer())->setInfantryCards(players->at(sourceAttacking->getIndexOfControllingPlayer())->getInfantryCards() + players->at(tempIndexOfDef)->getInfantryCards());
			players->at(tempIndexOfDef)->setArtilleryCards(0);
			players->at(tempIndexOfDef)->setCavalryCards(0);
			players->at(tempIndexOfDef)->setInfantryCards(0);
		}
		return true;
	}
}
int Game::getNumberOfTerritoresOfPlayer(int i){
	return players->at(i)->getNumberOfTerritories();
}
//changes the player's name
void Game::setPlayerName(int index, std::string name){
	players->at(index)->setName(name);
}
int Game::getInfantryCards(int p){
	return players->at(p)->getInfantryCards();
}
int Game::getCavalryCards(int p){
	return players->at(p)->getCavalryCards();
}
int Game::getArtilleryCards(int p){
	return players->at(p)->getArtilleryCards();
}
int Game::getCardsValue(int p){
	return players->at(p)->getCardsValue();
}
void Game::setCardsPlayed(int v, int p){
	players->at(p)->setCardsPlayed(v);
}
void Game::setInfantryCards(int v, int p){
	players->at(p)->setInfantryCards(v);
}
void Game::setCavalryCards(int v, int p){
	players->at(p)->setCavalryCards(v);
}
void Game::setArtilleryCards(int v, int p){
	players->at(p)->setArtilleryCards(v);
}
void Game::addPlayer(std::string playerName, int reinforcements, int numberOfTerritories, int cardsPlayed, int infantryCard, int cavalryCard, int artilleryCard, bool AI, int AIStrategy){
	players->push_back(new Player());
	players->at(players->size() - 1)->setPlayer(playerName, players->size() - 1,  reinforcements,  numberOfTerritories,  cardsPlayed,  infantryCard,  cavalryCard,  artilleryCard,  AI,  AIStrategy);
}
