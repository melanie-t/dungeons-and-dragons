//! @file 
//! @brief Header file for the Enhancement class  
//!
#pragma once

#include <string>
#include<vector>
using namespace std;

//! class for the implementation of an enhancement, i.e. a stat influenced by an item, as well as the bonus it gives
class Enhancement
{
public:
	// Default constructor
	Enhancement();
	// Constructor
	Enhancement(string type, int bonus);
	// method to get the type of the item
	string getType();
	// method to get the bonus of the type
	int getBonus();
	//setter for type
	void setType(string type);
	//setter for bonus
	void setBonus(int bonus);
private:
	string type;
	int bonus;
};

//Enhancement types
#define EN_STRENGTH "strength"
#define EN_CONSTITUTION "constitution"
#define EN_WISDOM "wisdom"
#define EN_CHARISMA "charisma"
#define EN_DEXTERITY "dexterity"
#define EN_ATTACK_BONUS "attackbonus"
#define EN_DAMAGE_BONUS "damagebonus"
#define EN_ARMOR_CLASS "armorclass"
#define EN_INTELLIGENCE "intelligence"

