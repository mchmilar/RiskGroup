#ifndef PLAYER_H
#define PLAYER_H

#include "Territory.h"
#include "Observable.h"

#include <string>

class Player : public Observable
{
public:
	Player();
	void setPlayer(std::string newName, int identifier);
	void setPlayer(std::string playerName, int identifier, int reinforcements, int numberOfTerritories, int cardsPlayed, int infantryCard, int cavalryCard, int artilleryCard, bool AI, int AIStrategy);
	//Player(Player&);
	~Player();
	std::string getName();
	//Continent *chooseTerritory(Continent *country);
	std::vector<Territory*> territoriesOwned; //does this need to be public?
	//std :: vector<Continent*> continents;
	void setTerritory(std::vector<Continent*> &countries);
	int getReinforcments();
	void addReinforcments(int);
	void removeReinforcments(int);
	void calculateTerritoriesReinforcments();
	void addTerritoryOwned(Territory*);
	void removeTerritoryOwned(Territory*);
	std::vector<Territory*> getTerritories();
	void setName(std::string);
	int getNumberOfTerritories();
	void attack();
	void defend();
	void random();
	int getInfantryCards(){
		return infantryCard;
	}
	int getCavalryCards(){
		return cavalryCard;
	}
	int getArtilleryCards(){
		return artilleryCard;
	}
	int getCardsValue(){
		return cardsPlayed * 5;
	}
	void setCardsPlayed(int v){
		cardsPlayed = v;
	}
	void setInfantryCards(int v){
		infantryCard = v;
	}
	void setCavalryCards(int v){
		cavalryCard = v;
	}
	void setArtilleryCards(int v){
		artilleryCard = v;
	}
private:
	std::string name;
	int id;
	int reinforcments;
	int numOfTerritories;
	int cardsPlayed;//starts at 1 always
	int infantryCard;
	int cavalryCard;
	int artilleryCard;
	bool AI;
	int AIStrategy;
};

#endif