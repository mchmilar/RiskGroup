#include "Player.h"
#include <string>

class Strategy;
Player::Player()
{/*Left intentionally blank*/
}

void Player::setPlayer(std::string newName, int identifier) {
	name = newName;
	id = identifier;
	reinforcments=0;
	numOfTerritories=0;
	cardsPlayed = 1;//starts at 1 always
	infantryCard =0;
	cavalryCard = 0;
	artilleryCard = 0;
}
void Player::setPlayer(std::string playerName, int identifier, int reinforcements2, int numberOfTerritories2, int cardsPlayed2, int infantryCard2, int cavalryCard2, int artilleryCard2, bool AI2, int AIStrategy2){
	name = playerName;
	id = identifier;
	reinforcments = reinforcements2;
	numOfTerritories = numberOfTerritories2;
	cardsPlayed = cardsPlayed2;
	infantryCard = infantryCard2;
	cavalryCard = cavalryCard2;
	artilleryCard = artilleryCard2;
	AI = AI2 ;
	AIStrategy = AIStrategy2;
}

/*Player::Player(Player& otherPlayer) {
	name = otherPlayer.name;
}*/
std::string Player::getName() {
	return name;
}


Player::~Player()
{
}
/*void Player::setTerritory(std::vector<Continent*> &countries)
{
	this->continents = continents;
}*/

/*Continent *Player::chooseTerritory(Continent *continent)
{
	Continent *chosenContinent = nullptr;
	for (auto c : continents)
	{
		if (!(c == (continent)))
		{
			return nullptr;
		}
		else
		{
			chosenContinent = continent;
		}
	}
	return chosenContinent;
}*/
int Player::getReinforcments()
{
	return reinforcments;
}
void Player::calculateTerritoriesReinforcments(){
	numOfTerritories = territoriesOwned.size();
	if (numOfTerritories > 11){
		reinforcments += (numOfTerritories+1) / 3 - 1;
	}
	else{
		reinforcments += 3;
	}
}
void Player::addReinforcments(int r)
{
	reinforcments += r;
}
void Player::removeReinforcments(int r)
{
	reinforcments -= r;
}
//Removes the Territory pointer from the territoriesOwned vector of the player (Not tested)
void Player::removeTerritoryOwned(Territory* t){
	for (int i = 0; i < territoriesOwned.size(); i++){
		if (territoriesOwned[i]->getName().compare(t->getName())==0)
			territoriesOwned.erase(territoriesOwned.begin() + i);
	}
	numOfTerritories = territoriesOwned.size();
}
//Removes the Territory pointer from the territoriesOwned vector of the player
void Player::addTerritoryOwned(Territory* t){
	territoriesOwned.push_back(t);
	numOfTerritories = territoriesOwned.size();
}
std::vector<Territory*> Player::getTerritories(){
	return territoriesOwned;
}
void Player::setName(std::string newName){
	name = newName;
}
int Player::getNumberOfTerritories(){
	return numOfTerritories;
}