//! @file 
//! @brief Implementation file for the Fighter class  
//!
#include "Character.h"
#include "Fighter.h"
#include <iostream> /* cout */

using std::cout;
using std::endl;

//! Constructor: Passes values to each ability score
Fighter::Fighter(int level, int str, int dex, int con, int intel, int wis, int cha):
													Character(level, str, dex, con, intel, wis, cha)
{
	setCharClass(1);
}

//! Default constructor: Assigns values for level 1
Fighter::Fighter()
{
	setLevel(1);
	setName("Unknown");
	setCharClass(1);
	statGenerator();
}

//! Constructor for Fighter
//! @param level level of fighter
Fighter::Fighter(string name)
{
	setName(name);
	setLevel(1);
	setCharClass(1);
	statGenerator();
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


