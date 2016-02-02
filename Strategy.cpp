#include <iostream>;
#include "Player.h";
#include "Strategy.h";
#include <vector>
#include <algorithm> 

/*void AttackStrategy::attackBehaviour(Player *attacker, Player *defender) {
	bool test = true;
	Territory attackCountry = attackCountry.getName;
	std::vector<Territory*> defendCountries = defender->getTerritories;
		for (int i = 0; defendCountries.size(); i++){
		while (test){
			if (attackCountry.getArmiesInTerritory() > defendCountries[i]->getArmiesInTerritory() && defendCountries[i]->isBorder(attackCountry))
			{
				std::cout << attacker->getName() << " will attack " << defender->getName() << std::endl;
				attacker->attack();
				test = false;
			}
		test = false;
	}
	}
	}

void DefensiveStrategy::attackBehaviour(Player *attacker, Player *defender) {
	bool test = true;
	Territory attackCountry = attackCountry.getName;
	std::vector<Territory*> defendCountries = defender->getTerritories;
		for (int i = 0; defendCountries.size(); i++){
			while (test){
				if (attackCountry.getArmiesInTerritory() < defendCountries[i]->getArmiesInTerritory() && defendCountries[i]->isBorder(attackCountry))
				{
					std::cout << attacker->getName() << " will defend against " << defender->getName() << std::endl;
					attacker->attack();
					test = false;
				}
		}
		test = false;
	}
}

void RandomStrategy::attackBehaviour(Player *attacker, Player *defender) {
	bool test = true;
	Territory attackCountry = attackCountry.getName;
	std::vector<Territory*> defendCountries = defender->getTerritories;
		for (int i = 0; defendCountries.size(); i++){
			while (test){
			if (attackCountry.getArmiesInTerritory() == defendCountries[i]->getArmiesInTerritory() && defendCountries[i]->isBorder(attackCountry))
			{
				std::cout << attacker->getName() << " will randomly attack or defend against " << defender->getName() << std::endl;
				attacker->attack();
				test = false;
			}
			}
		}
		test = false;
	}*/

//void DefensiveStrategy::attackBehaviour(Player *attacker, Player *defender) {
//	Territory attackCountry = attacker->getCountry;
//	Territory defendCountry = defender->getCountry;
//	if (attackCountry.getArmiesInTerritory() < defendCountry.getArmiesInTerritory())
//	{
//		std::cout << attacker->getName() << " will defend against " << defender->getName() << std::endl;
//		attacker->defend();
//	}
//}
//
//void RandomStrategy::attackBehaviour(Player *attacker, Player *defender) {
//	Territory attackCountry = attacker->getCountry;
//	Territory defendCountry = defender->getCountry;
//	if (attackCountry.getArmiesInTerritory() > defendCountry.getArmiesInTerritory())
//	{
//		std::cout << attacker->getName() << " will randomly attack or defend against " << defender->getName() << std::endl;
//		attacker->random();
//	}
//}


