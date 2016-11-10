//Dylan, I changed the ENUM AbilityModifiers -> Ability

//! @file Character.cpp 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"
#include <iostream> /* cin, cout */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <sstream>
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
	abilityScores[Ability::STRENGTH] = str;
	abilityScores[Ability::DEXTERITY] = dex;
	abilityScores[Ability::CONSTITUTION] = con;
	abilityScores[Ability::INTELLIGENCE] = intel;
	abilityScores[Ability::WISDOM] = wis;
	abilityScores[Ability::CHARISMA] = cha;

	secondaryStatCalc();
}

void Character::notify() {
	displayStats();
}

void Character::attach(Character* player)
{
	bool condition = false;
	int index = 0;
	while (!condition)
	{
		if ((List[index]) == 0)
		{
			List[index] = 0;
			condition = true;
		}
	}
	List[index] = player;
}

void Character::detach(Character* player)
{
	bool condition = false;
	int index2 = 0;
	while (!condition)
	{
		if (player == (List[index2]))
		{
			List[index2] = 0;
			condition = true;
		}
	}
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
	abilityScores[Ability::STRENGTH] = rand() % 16 + 3;
	abilityScores[Ability::DEXTERITY] = rand() % 16 + 3;
	abilityScores[Ability::CONSTITUTION] = rand() % 16 + 3;
	abilityScores[Ability::INTELLIGENCE] = rand() % 16 + 3;
	abilityScores[Ability::WISDOM] = rand() % 16 + 3;
	abilityScores[Ability::CHARISMA] = rand() % 16 + 3;
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
	if (currentHitPoints > damage)
	{
		currentHitPoints = currentHitPoints - damage;
		cout << "\nYou got hit! (-" << damage << " HP)\n" << endl;
		notify();
	}

	else
	{
		currentHitPoints = 0;
		cout << "GAME OVER. Thanks for playing!" << endl;
		gameover = true;
	}

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
	return abilityScores[Ability::STRENGTH];
}

//! Implementation of a setter method for STR
//! @param newSTR: value of STR
void Character::setSTR(int newSTR)
{
	abilityScores[Ability::STRENGTH] = newSTR;
}

//! Implementation of a getter method for DEX
//! @return int: value of DEX	
int Character::getDEX()
{
	return abilityScores[Ability::DEXTERITY];
}

//! Implementation of a setter method for DEX
//! @param newDEX: value of DEX	
void Character::setDEX(int newDEX)
{
	abilityScores[Ability::DEXTERITY] = newDEX;
}

//! Implementation of a getter method for CON
//! @return int: value of CON
int Character::getCON()
{
	return abilityScores[Ability::CONSTITUTION];
}

//! Implementation of a setter method for CON
//! @param newCON: value of CON
void Character::setCON(int newCON)
{
	abilityScores[Ability::CONSTITUTION] = newCON;
}

//! Implementation of a getter method for INTEL
//! @return int: value of INTEL
int Character::getINTEL()
{
	return abilityScores[Ability::INTELLIGENCE];
}

//! Implementation of a setter method for INTEL
//! @param newINTEL: value of INTEL
void Character::setINTEL(int newINTEL)
{
	abilityScores[Ability::INTELLIGENCE] = newINTEL;
}

//! Implementation of a getter method for WIS
//! @return int: value of WIS
int Character::getWIS()
{
	return abilityScores[Ability::WISDOM];
}

//! Implementation of a setter method for WIS
//! @param newWIS: value of WIS
void Character::setWIS(int newWIS)
{
	abilityScores[Ability::WISDOM] = newWIS;
}

//! Implementation of a getter method for CHA
//! @return int: value of CHA
int Character::getCHA()
{
	return abilityScores[Ability::CHARISMA];
}

//! Implementation of a setter method for CHA
//! @param newCHA: value of CHA
void Character::setCHA(int newCHA)
{
	abilityScores[Ability::CHARISMA] = newCHA;
}

//! Implementation of a getter method for name
//! @return name: name of character
string Character::getName()
{
	return name;
}

//! Implementation of a setter method for name
//! @param newName: name of character
void Character::setName(string newName) 
{
	name = newName;
}

int Character::getCharClass()
{
	return charClass;
}
void Character::setCharClass(int classOfChar)
{
	charClass = classOfChar;
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
	cout << "\n= Character STATS ="
		<< "\nName: " << getName()
		<< "\nLevel: " << getLevel()
		<< "\nClass: " << classtoString()
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
		<< endl;
}

string Character::statString()
{
	std::ostringstream out;
	out << "Name: " << getName()
		<< "\nLevel: " << getLevel()
		<< "\nClass: " << classtoString()
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
	return out.str();
}

string Character::classtoString()
{
	switch (charClass) {
	case 1: return "Fighter";
	default: return "N/A";
	}
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
	char di[40];
	sprintf_s(di, 40, "Character/%s.xml", name);
	xml.Save(string(di));
}

Character Character::loadCharacer(string name)
{
	char di[40];
	sprintf_s(di, 40, "Character/%d.xml", name);
	CMarkup xml;
	if (xml.Load(string(di)))
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

////retrieve the gender of the character and return it
//string Character::retrieveGender()
//{
//	//variables
//	bool a = false;
//
//	//loops until we have an actual gender for the character
//	while (a == false)
//	{
//
//		//Display message and retrieve the user's input
//		cout << "Please Enter your gender: \n";
//		cout << "For a male character, please enter: Male, male, M or m\n";
//		cout << "For a female character, please enter: Female, female, F or f\n";
//		cin >> gender;
//
//		//if user is male then set gender as male and return it
//		if (gender == "Male" || gender == "male" || gender == "M" || gender == "m")
//		{
//			gender = "male";
//			a = true;
//			return gender;
//		}
//
//		//if user is female then set gender as female and return it
//		else if (gender == "Female" || gender == "female" || gender == "F" || gender == "f")
//		{
//			gender = "female";
//			a = true;
//			return gender;
//		}
//
//		//if no specific gender has been entered then display error and loop again
//		else
//		{
//			cout << "Error\n";
//			a = 0;
//
//		}
//	}
//	return "";
//}

void Character::retrieveName() {
	string charName;

	//retrieve the name and set it to the character
	cout << "Please enter the name of your character: \n";
	cin >> charName;
	setName(charName);
}

//set the extraPoints stats
void Character::setExtraPoints()
{
	int ExtraPoints = 2;
	while (ExtraPoints != 0)
	{
		//Display message and retrieve the user's input
		int choice;
		cout << "\nYou have: " << ExtraPoints << " upgrade(s) available. What would you like to upgrade?\n";
		cout << "1. STR (Strength)\n";
		cout << "2. DEX (Dexterity)\n";
		cout << "3. CON (Constitution)\n";
		cout << "4. INT (Intelligence)\n";
		cout << "5. WIS (Wisdom)\n";
		cout << "6. CHA (Charisma)\n";
		cin >> choice;

		//if user whishes to improve strength
		if (choice == 1)
		{
			setSTR(getSTR() + 1);
			ExtraPoints--;
			cout << "Strength: " << getSTR() << "\n";
		}

		//if user whishes to improve Dexterity
		else if (choice == 2)
		{
			setDEX(getDEX() + 1);
			ExtraPoints--;
			cout << "Dexterity: " << getDEX() << "\n";

		}

		//if user whishes to improve Constitution
		else if (choice == 3)
		{
			setCON(getCON() + 1);
			ExtraPoints--;
			cout << "Constitution: " << getCON() << "\n";
		}

		//if user whishes to improve Intelligence
		else if (choice == 4)
		{
			setINTEL(getINTEL() + 1);
			ExtraPoints--;
			cout << "Intelligence: " << getINTEL() << "\n";
		}

		//if user whishes to improve Wisdom
		else if (choice == 5)
		{
			setWIS(getWIS() + 1);
			ExtraPoints--;
			cout << "Wisdom: " << getWIS() << "\n";
		}

		//if user whishes to improve Luck
		else if (choice == 6)
		{
			setCHA(getCHA() + 1);
			ExtraPoints--;
			cout << "Luck: " << getCHA() << "\n";
		}

		//if no specific bonus has been entered then display error and loop again
		else
		{
			cout << "Error, invalid choice. Please try again.\n";
		}

		notify();
	}

}
