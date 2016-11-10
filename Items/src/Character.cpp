//! @file 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"
#include <iostream> /* cin, cout */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include "Markup.h"

using namespace std;

//! Default constructor: initializes level to 1 and generates new character with 0 stats
Character::Character() : Character(1, 0, 0, 0, 0, 0, 0) //hi, this is just cleaner. So I changed it - Dylan.
{
}

//! Constructor: passes values to each ability score and set hit points to 10
Character::Character(int lvl, int str, int dex, int con, int intel, int wis, int cha, string name)
{
	this->name = name;
	level = lvl;
	abilityScores[AbilityModifiers::STRENGTH] = str;
	abilityScores[AbilityModifiers::DEXTERITY] = dex;
	abilityScores[AbilityModifiers::CONSTITUTION] = con;
	abilityScores[AbilityModifiers::INTELLIGENCE] = intel;
	abilityScores[AbilityModifiers::WISDOM] = wis;
	abilityScores[AbilityModifiers::CHARISMA] = cha;

	secondaryStatCalc();
}

//! Implementation of the verification of a newly created Character
//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter()
{
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i]<3 || abilityScores[i]>18)
			return false;
	return true;
}

//! statGenerator function
//! @brief generates random stats for the character
void Character::statGenerator() {
	srand(time(NULL));
	abilityScores[AbilityModifiers::STRENGTH] = rand() % 16 + 3;
	abilityScores[AbilityModifiers::DEXTERITY] = rand() % 16 + 3;
	abilityScores[AbilityModifiers::CONSTITUTION] = rand() % 16 + 3;
	abilityScores[AbilityModifiers::INTELLIGENCE] = rand() % 16 + 3;
	abilityScores[AbilityModifiers::WISDOM] = rand() % 16 + 3;
	abilityScores[AbilityModifiers::CHARISMA] = rand() % 16 + 3;
	secondaryStatCalc();
}

//! Implementation of the ability modifier calculation
//! @param abilityScore: value of abilityScore
int Character::abilityModifier(int abilityScore)
{
	// Proper calculation of abilityMod;
	int abilityMod = (abilityScore - 10) / 2;

	// In case of negative abilityMod
	if (abilityMod <= 0)
		abilityMod = 1;
	return abilityMod;
}

//! secondaryStatCalc function
//! @brief generates secondary stats based on
//! primary stats.
void Character::secondaryStatCalc() {
	setHitPoints(10 + getLevel()*abilityModifier(getCON()));
	setArmorClass(abilityModifier(getDEX()));
	setAttackBonus(getLevel()*(abilityModifier(getSTR()) + abilityModifier(getDEX())) / 5);
	setDamageBonus(abilityModifier(getSTR()));
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the character
void Character::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;
}

//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}

//! Implementation of a setter method for currentHitPoints
//! @param newHP: new HP of character
void Character::setHitPoints(int newHP)
{
	currentHitPoints = newHP;
}

//! Implementation of a getter method for level
//! @return int: value of level
int Character::getLevel()
{
	return level;
}

//! Implementation of a setter method for level
//! @param currentLevel: input value of level
void Character::setLevel(int currentLevel)
{
	if (currentLevel > 0)
		level = currentLevel;
	else
		level = 1;
}

//! Implementation of a getter method for armorClass
//! @return int: value of armorClass
int Character::getArmorClass()
{
	return armorClass;
}

//! Implementation of a setter method for armorClass
//! @param newArmorClass: value of armorClass
void Character::setArmorClass(int newArmorClass)
{
	armorClass = newArmorClass;
}

//! Implementation of a getter method for attackBonus
//! @return int: value of attackBonus
int Character::getAttackBonus()
{
	return attackBonus;
}

//! Implementation of a setter method for attackBonus
//! @param newAttackBonus: value of character's attack bonus
void Character::setAttackBonus(int newAttackBonus)
{
	attackBonus = newAttackBonus;
}

//! Implementation of a getter method for damageBonus
//! @return int: value of damageBonus
int Character::getDamageBonus()
{
	return damageBonus;
}

//! Implementation of a setter method for damageBonus
//! @param damageBonus: value of bonus damage dealt to monsters
void Character::setDamageBonus(int newDamageBonus)
{
	damageBonus = newDamageBonus;
}

//! Implementation of a getter method for STR
//! @return int: value of STR
int Character::getSTR()
{
	return abilityScores[AbilityModifiers::STRENGTH];
}

//! Implementation of a setter method for STR
//! @param newSTR: value of STR
void Character::setSTR(int newSTR)
{
	abilityScores[AbilityModifiers::STRENGTH] = newSTR;
}

//! Implementation of a getter method for DEX
//! @return int: value of DEX	
int Character::getDEX()
{
	return abilityScores[AbilityModifiers::DEXTERITY];
}

//! Implementation of a setter method for DEX
//! @param newDEX: value of DEX	
void Character::setDEX(int newDEX)
{
	abilityScores[AbilityModifiers::DEXTERITY] = newDEX;
}

//! Implementation of a getter method for CON
//! @return int: value of CON
int Character::getCON()
{
	return abilityScores[AbilityModifiers::CONSTITUTION];
}

//! Implementation of a setter method for CON
//! @param newCON: value of CON
void Character::setCON(int newCON)
{
	abilityScores[AbilityModifiers::CONSTITUTION] = newCON;
}

//! Implementation of a getter method for INTEL
//! @return int: value of INTEL
int Character::getINTEL()
{
	return abilityScores[AbilityModifiers::INTELLIGENCE];
}

//! Implementation of a setter method for INTEL
//! @param newINTEL: value of INTEL
void Character::setINTEL(int newINTEL)
{
	abilityScores[AbilityModifiers::INTELLIGENCE] = newINTEL;
}

//! Implementation of a getter method for WIS
//! @return int: value of WIS
int Character::getWIS()
{
	return abilityScores[AbilityModifiers::WISDOM];
}

//! Implementation of a setter method for WIS
//! @param newWIS: value of WIS
void Character::setWIS(int newWIS)
{
	abilityScores[AbilityModifiers::WISDOM] = newWIS;
}

//! Implementation of a getter method for CHA
//! @return int: value of CHA
int Character::getCHA()
{
	return abilityScores[AbilityModifiers::CHARISMA];
}

//! Implementation of a setter method for CHA
//! @return newCHA: value of CHA
void Character::setCHA(int newCHA)
{
	abilityScores[AbilityModifiers::CHARISMA] = newCHA;
}

//! armorEquipped function
//! @return true if equipArmor=true, else false.
bool Character::armorEquipped()
{
	return equipArmor;
}
//! shieldEquipped function
//! @return true if equipShield=true, else false.
bool Character::shieldEquipped()
{
	if (equipShield)
		return true;
	return false;
}
//! weaponEquipped function
//! @return true if equipWeapon=true, else false.
bool Character::weaponEquipped()
{
	if (equipWeapon)
		return true;
	return false;
}
//! bootsEquipped function
//! @return true if equipBoots=true, else false.
bool Character::bootsEquipped()
{
	if (equipBoots)
		return true;
	return false;
}

//! ringEquipped function
//! @return true if equipRing=true, else false.
bool Character::ringEquipped()
{
	if (equipRing)
		return true;
	return false;
}
//! helmetEquipped function
//! @return true if equipHelmet=true, else false.
bool Character::helmetEquipped()
{
	if (equipHelmet)
		return true;
	return false;
}
//! displayStats function
//! @brief displays the stats of the Character.
void Character::displayStats()
{
	cout << "Level: " << getLevel()
		<< "\nClass: N/A"
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

void Character::saveCharacter()
{
	CMarkup xml;
	xml.AddElem("character");
	xml.IntoElem();
	xml.AddElem("level", level);
	xml.AddElem("strength", getSTR());
	xml.AddElem("dexterity", getDEX());
	xml.AddElem("constitution", getCON());
	xml.AddElem("intelligence", getINTEL());
	xml.AddElem("wisdom", getWIS());
	xml.AddElem("charisma", getCHA());
	//char di[20];
	//sprintf_s(di, 20, "characters/%s.xml", name.c_str());
	xml.Save("characters/" + name + ".xml");
}

Character Character::loadCharacer(string name)
{
	CMarkup xml;
	if (xml.Load("characters/" + name + ".xml"))
	{
		xml.FindElem();
		if (xml.GetTagName() != "character")
		{
			cout << "This file is not a character." << endl;
			cout << xml.GetTagName() << endl;
		}
		else
		{
			xml.IntoElem();
			int level, str, dex, con, intel, wis, cha;
			while (xml.FindElem())
			{
				string tag = xml.GetTagName();
				if (tag == "level")
				{
					level = atoi(xml.GetData().c_str());
				}
				else if (tag == "strength")
				{
					str = atoi(xml.GetData().c_str());
				}
				else if (tag == "dexterity")
				{
					dex = atoi(xml.GetData().c_str());
				}
				else if (tag == "constitution")
				{
					con = atoi(xml.GetData().c_str());
				}
				else if (tag == "intelligence")
				{
					intel = atoi(xml.GetData().c_str());
				}
				else if (tag == "wisdom")
				{
					wis = atoi(xml.GetData().c_str());
				}
				else if (tag == "charisma")
				{
					cha = atoi(xml.GetData().c_str());
				}
			}
			return Character(level, str, dex, con, intel, wis, cha);
		}
	}
	return Character(); //Empty
}


