#pragma once
#include "Player.h"

/*
Strategy pattern to be implemented for AI players to determine whether they will attack or 
defend or act randomly from their territory. Could possibly use the stats observer
*/

class Player; //forward declare; because circular logic

class Strategy {
public:
	virtual void attackBehaviour(Player* attacker, Player* defender) = 0;
};

class AttackStrategy : public Strategy {
	virtual void attackBehaviour(Player* attacker, Player* defender);
};

class DefensiveStrategy : public Strategy {
	virtual void attackBehaviour(Player* attacwker, Player* defender);
};

class RandomStrategy : public Strategy {
	virtual void attackBehaviour(Player* attacker, Player* defender);
};