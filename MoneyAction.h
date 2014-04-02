#ifndef MONEYACTION_H
#define MONEYACTION_H
#include "Action.h"
#include "Player.h"

class MoneyAction : public Action{

	protected:
		int money; //money for working with

	public:	

		//constructors
		MoneyAction(); //create MoneyAction with name "Default"
		MoneyAction(std::string newName); //create MoneyAction with specific name

		//functions
		void payMoney(Player& p, int amount); //pay p amount sum of money
		int takeMoney(Player& p, int amount); //take amount sum of money from player p

};

#endif