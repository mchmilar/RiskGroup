#pragma once

#include "Territory.h""
class AI{
private:
	int numberOfTerritories;
	int reinforcements;
	int aINumber;
	int aiIDNumber;
	std::vector<Territory*> territoriesOwned;
public:
	AI();
	int getAINumber();
	int getAiIDNumber();
	int getNumberOfTerritories();
	int getReinforcments();
	void addReinforcments(int);
	void removeReinforcments(int);
	std::vector<Territory*> getTerritories();
	void setTerritory(std::vector<Continent*> &countries);
	Territory* AIReinforcement(AI* ai, int armies, Territory* target);
	Territory* AIFortify(AI* ai);
	Territory* AIAttack(AI* ai);
};