#include "AI.h"
#include <vector>
#include <string>

AI::AI(){

}
int AI::getAiIDNumber(){
	return aiIDNumber;
}
int AI:: getAINumber(){
	return aINumber;
}
int AI:: getNumberOfTerritories(){
	return numberOfTerritories;
}
int AI:: getReinforcments(){
	return reinforcements;
}
void AI::addReinforcments(int r){
	reinforcements += r;
}
void AI::removeReinforcments(int r){
	reinforcements -= r;
}
std::vector<Territory*> AI::getTerritories(){
	return territoriesOwned;
}
Territory* AI::AIReinforcement(AI* ai, int armies, Territory* source){
	std::vector<Territory*> territories;
	int sumOfEnemies = 0;
	Territory* mostEnemies;
	for (int i = 0; i < ai->getNumberOfTerritories(); i++){
		territories[i] = ai->getTerritories()[i];
		for (i = 0; i < territories.size(); i++){
			std::vector<Territory*> borders;
			borders = territories[i]->getBorders();
			borders = territories[i]->getBorders();
			int borderEnemies = 0;
			for (int i = 0; i < borders.size(); i++)
				while (i < borders.size()){
					if (borders[i]->getIndexOfControllingPlayer() != ai->aiIDNumber){
						borderEnemies += 1;
					}
				}
			if (borderEnemies > sumOfEnemies){
				sumOfEnemies = borderEnemies;
				mostEnemies = territories[i];
			}
		}
		return mostEnemies;
	}
}
//Returns the Territory with the most bordering enemies, this will be the target Territory for fortify
Territory* AI::AIFortify(AI* ai){
	std::vector<Territory*> territories;
	int sumOfEnemies = 0;
	Territory* mostEnemies;
	for (int i = 0; i < ai->getNumberOfTerritories(); i++){
		territories[i] = ai->getTerritories()[i];
		for (i = 0; i < territories.size(); i++){
			std::vector<Territory*> borders;
			borders = territories[i]->getBorders();
			int borderEnemies = 0;
			for (int i = 0; i < borders.size(); i++)
				while (i < borders.size()){
					if (borders[i]->getIndexOfControllingPlayer() != ai->aiIDNumber){
					borderEnemies += 1;
					}
				}
				if (borderEnemies > sumOfEnemies){
					sumOfEnemies = borderEnemies;
					mostEnemies = territories[i];
			}
		}
		return mostEnemies;
	}
}
//returns the bordering territory with the least amount of enemies.
Territory* AI::AIAttack(AI* ai){
	std::vector<Territory*> territories;
	int sumOfEnemies = 100;		//put 100 just for now
	Territory* leastEnemies;
	for (int i = 0; i < ai->getNumberOfTerritories(); i++){
		territories[i] = ai->getTerritories()[i];
		for (i = 0; i < territories.size(); i++){
			std::vector<Territory*> borders;
			borders = territories[i]->getBorders();
			int borderEnemies = 0;
			for (int i = 0; i < borders.size(); i++)
				while (i < borders.size()){
					if (borders[i]->getIndexOfControllingPlayer() != ai->getAiIDNumber()){
						borderEnemies += 1;
					}
				}
			if (borderEnemies < sumOfEnemies){
				sumOfEnemies = borderEnemies;
				leastEnemies = borders[i];
			}
		}
		return leastEnemies;
	}
}
