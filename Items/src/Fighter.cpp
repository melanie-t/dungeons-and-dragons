
#include "Character.h"
#include "Fighter.h"
#include <iostream> /* cout */

using std::cout;
using std::endl;

//! Constructor: Passes values to each ability score
Fighter::Fighter(int level, int str, int dex, int con, int intel, int wis, int cha):
													Character(level, str, dex, con, intel, wis, cha)
{
}

//! Default constructor: Assigns values for level 1
Fighter::Fighter()
{
	setLevel(1);
	statGenerator();
}

Fighter::Fighter(int level)
{
	setLevel(level);
	statGenerator();
}

void Fighter::displayStats()
{
	cout << "Level: " << getLevel()
		<< "\nClass: Fighter"
		<< "\nHitpoints: " << getHitPoints()
		<< "\nStrength: " << getSTR()
		<< "\nDexterity: " << getDEX()
		<< "\nConstitution: " << getCON()
		<< "\nIntelligence: " << getINTEL()
		<< "\nWisdom: " << getWIS()
		<< "\nCharisma: " << getCHA()
		<< "\nArmor Class: " << getArmorClass()
		<< "\nAttack Bonus: " << getAttackBonus()
		<< "\nDamage Bonus: " << getDamageBonus()
		<< "\n" << endl;
}

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

