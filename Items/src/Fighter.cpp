//! @file 
//! @brief Implementation file for the Fighter class  
//!
#include "Character.h"
#include "Fighter.h"
#include "Markup.h"
#include <iostream> /* cout */

using std::cout;
using std::endl;

//! Constructor: For loading Fighters
//! @param level level of Fighter
//! @param str strength of Fighter
//! @param dex dexterity of Fighter
//! @param con constitution of Fighter
//! @param intel intelligence of Fighter
//! @param wis wisdom of Fighter
//! @param cha charisma of Fighter
//! @param name name of Fighter
Fighter::Fighter(string name, int charClass, int level, int str, int dex, int con, int intel, int wis, int cha, int hp, 
	ItemContainer backpack, Item equips[7]) : Character(name, charClass, level, str, dex, con, intel, wis, cha, hp, backpack, equips)
{
	//1 represents character class Fighter
}

//! Default constructor: Assigns level as 1, 0 as all ability scores
Fighter::Fighter()
{
	setLevel(1);
	setName("Unknown");
	setCharClass(1);
}

//! Constructor for Fighter
//! @param name name of fighter
Fighter::Fighter(string name, int charClass)
{
	setName(name);
	setCharClass(charClass);
	setLevel(1);
	setCharClass(1);
	statGenerator();
	secondaryStatCalc();
}

//! validateNewFighter function
//! @brief validates the stats of the created Fighter.
bool Fighter::validateNewFighter()
{
	validateNewCharacter();
	if (getHitPoints() < 10)
		return false;
	if (getArmorClass() < 0)
		return false;
	if (getAttackBonus() < 0)
		return false;
	if (getDamageBonus() < 0)
		return false;
	return true;
}
