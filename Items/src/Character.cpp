//! @file Character.cpp 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"
#include "Dice.h"
#include <iostream> /* cin, cout */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <sstream>
#include "Markup.h"

using namespace std;

//! Default constructor: initializes level to 1 and generates new character with 0 stats
Character::Character() : Character(1, 0, 0, 0, 0, 0, 0)
{
}

//! Constructor: passes values to each ability score and generates hp at level 1
//! @param lvl level of Character
//! @param str strength of Character
//! @param dex dexterity of Character
//! @param con constitution of Character
//! @param intel intelligence of Character
//! @param wis wisdom of Character
//! @param cha charisma of Character
Character::Character(int lvl, int str, int dex, int con, int intel, int wis, int cha) 
{
	level = lvl;
	abilityScores[Ability::STRENGTH] = str;
	abilityScores[Ability::DEXTERITY] = dex;
	abilityScores[Ability::CONSTITUTION] = con;
	abilityScores[Ability::INTELLIGENCE] = intel;
	abilityScores[Ability::WISDOM] = wis;
	abilityScores[Ability::CHARISMA] = cha;
	currentHitPoints = 10 + abilityModifier(Ability::CONSTITUTION);
	secondaryStatCalc();
}

//! Constructor: Used to load characters from saved XML files
//! @param lvl level of Character
//! @param str strength of Character
//! @param dex dexterity of Character
//! @param con constitution of Character
//! @param intel intelligence of Character
//! @param wis wisdom of Character
//! @param cha charisma of Character
//! @param name name of Character
//! @param hp health points of Character
//! @param backpack contains all items in backpack inventory
//! @param equips contains all items that are currently worn
Character::Character(string name, int charclass, int lvl, int str, int dex, int con, int intel,
	int wis, int cha, int hp, ItemContainer backpack, Item* equips[7])
{
	this->name = name;
	level = lvl;
	charClass = charclass;
	abilityScores[Ability::STRENGTH] = str;
	abilityScores[Ability::DEXTERITY] = dex;
	abilityScores[Ability::CONSTITUTION] = con;
	abilityScores[Ability::INTELLIGENCE] = intel;
	abilityScores[Ability::WISDOM] = wis;
	abilityScores[Ability::CHARISMA] = cha;
	currentHitPoints = 10 + abilityModifier(Ability::CONSTITUTION);
	secondaryStatCalc();
}

//! notify function
//! @brief implementation of notify from Observable class
//! notifies the observer of any changes
void Character::notify() {
	displayStats();
}

//! attach function
//! @brief implementation of attach from Observable class
//! attaches observers to Character
//! @param player pointer to a character object
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

//! detach function
//! @brief implementation of detach from Observable class
//! detach observers to Character
//! @param player pointer to a character object
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
//! @brief generates random stats for the character using 4d6
void Character::statGenerator() {
	srand(time(NULL));
	Dice dice;
	int choice;
	int totalScores[6];
	bool strSet = false,
		dexSet = false,
		conSet = false,
		intSet = false,
		wisSet = false,
		chaSet = false;

	//Initializes all 6 rolls (4d6)
	for (int i = 0; i < 6; i++) {
		totalScores[i] = dice.roll("4d6[0]");
	}

	for (int i = 0; i < 6; i++) {
		do {
			cout << "Scores leftover: ";
			for (int j = i; j < 6; j++) {
				cout << totalScores[j] << " ";
			}
			cout << "\nChoose ability to set as " << totalScores[i]
				<< "\n1. STR"
				<< "\n2. DEX"
				<< "\n3. CON"
				<< "\n4. INTEL"
				<< "\n5. WIS"
				<< "\n6. CHA" << endl;
			cin >> choice;

			switch (choice) {
			case 1: {
				if (!strSet)
				{
					setSTR(totalScores[i]);
					cout << "STR: " << totalScores[i] << endl;
					strSet = true;
					displayStats();
				}
				else {
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 2: {
				if (!dexSet)
				{
					setDEX(totalScores[i]);
					cout << "DEX: " << totalScores[i] << endl;
					dexSet = true;
					displayStats();
				}
				else {
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 3: {
				if (!conSet)
				{
					setCON(totalScores[i]);
					cout << "CON: " << totalScores[i] << endl;
					conSet = true;
					displayStats();
				}
				else {
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 4: {
				if (!intSet) {
					setINTEL(totalScores[i]);
					cout << "INTEL: " << totalScores[i] << endl;
					intSet = true;
					displayStats();
				}
				else {
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 5: {
				if (!wisSet) {
					setWIS(totalScores[i]);
					cout << "WIS: " << totalScores[i] << endl;
					wisSet = true;
					displayStats();
				}
				else {
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 6: {
				if (!chaSet) {
					setCHA(totalScores[i]);
					cout << "CHA: " << totalScores[i] << endl;
					chaSet = true;
					displayStats();
				}
				else {
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			default: {
				cout << "Invalid choice. Choose between 1-6" << endl;
				if (i != 0)
					i--;
				break;
			}
			}
		} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);
	}
	secondaryStatCalc();
}

//! Implementation of the ability modifier calculation
//! @param abilityScore: value of abilityScore
int Character::abilityModifier(int abilityScore)
{
	// Proper calculation of abilityMod;
	int abilityMod = (abilityScore - 10) / 2;

	if (abilityMod < 0)
	{
		abilityMod = 0;
	}

	return abilityMod;
}

//! secondaryStatCalc function
//! @brief generates secondary stats based on
//! primary stats.
void Character::secondaryStatCalc() {
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
	return (10 + getLevel()*abilityModifier(getCON()));
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
	return (abilityModifier(getDEX()));
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
	return (getLevel()*(abilityModifier(getSTR()) + abilityModifier(getDEX())) / 5);
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
	damageBonus = abilityModifier(getSTR());
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

//! Implementation of getter method for charClass
//! @return charClass: the class of character in terms of int (Ex: 1 = Fighter)
int Character::getCharClass()
{
	return charClass;
}

//! Implementation of setter method for charClass
//! @param classOfChar: class of character in terms of int (Ex: 1 = Fighter)
void Character::setCharClass(int classOfChar)
{
	charClass = classOfChar;
}

//! Implementation of level up method.
//! Occurs when we complete a map.
//  Using if-else shortcut: (condition) ? (if_true) : (if_false)
void Character::levelUp()
{
	level = level + 1;
	abilityScores[Ability::STRENGTH] < 18 ? setSTR(abilityScores[Ability::STRENGTH] + 1) : false;
	abilityScores[Ability::DEXTERITY] < 18 ? setSTR(abilityScores[Ability::DEXTERITY] + 1) : false;
	abilityScores[Ability::CONSTITUTION] < 18 ? setSTR(abilityScores[Ability::CONSTITUTION] + 1) : false;
	abilityScores[Ability::INTELLIGENCE] < 18 ? setSTR(abilityScores[Ability::INTELLIGENCE] + 1) : false;
	abilityScores[Ability::WISDOM] < 18 ? setSTR(abilityScores[Ability::WISDOM] + 1) : false;
	abilityScores[Ability::CHARISMA] < 18 ? setSTR(abilityScores[Ability::CHARISMA] + 1) : false;
}

//! Getter method to get the ItemContainer backpack
//! @return backpack: the backpack (itemcontainer vector) inventory
ItemContainer Character::getBackpack()
{
	return backpack;
}

//! Implementation of equip method
//! @param item: The item that you wish to equip
void Character::equipItem(Item* item) {
	string type = item->getType();

	if (type == TYPE_HELMET) {
		if (!helmetEquipped)
		{
			//Nothing equipped
			equips[Equip::HELMET] = item;
			helmetEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::HELMET]);
			equips[Equip::HELMET] = item;
		}
	}

	else if (type == TYPE_ARMOR)
	{
		if (!armorEquipped)
		{
			//Nothing equipped
			equips[Equip::ARMOR] = item;
			armorEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::ARMOR]);
			equips[Equip::ARMOR] = item;
		}
	}

	else if (type == TYPE_BELT)
	{
		if (!beltEquipped)
		{
			//Nothing equipped
			equips[Equip::BELT] = item;
			beltEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::BELT]);
			equips[Equip::BELT] = item;
		}
	}

	else if (type == TYPE_BOOTS)
	{
		if (!bootsEquipped)
		{
			//Nothing equipped
			equips[Equip::BOOTS] = item;
			bootsEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::BOOTS]);
			equips[Equip::BOOTS] = item;
		}
	}

	else if (type == TYPE_SHIELD)
	{
		if (!bootsEquipped)
		{
			//Nothing equipped
			equips[Equip::BOOTS] = item;
			bootsEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::BOOTS]);
			equips[Equip::BOOTS] = item;
		}
	}

	else if (type == TYPE_WEAPON)
	{
		if (!weaponEquipped)
		{
			//Nothing equipped
			equips[Equip::WEAPON] = item;
			weaponEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::WEAPON]);
			equips[Equip::WEAPON] = item;
		}
	}

	else if (type == TYPE_RING)
	{
		if (!ringEquipped)
		{
			//Nothing equipped
			equips[Equip::RING] = item;
			ringEquipped = true;
		}
		else
		{
			//Puts current item into backpack and equips new item
			backpack.addItem(*equips[Equip::RING]);
			equips[Equip::RING] = item;
		}
	}

	else
		cout << "Invalid item type" << endl;
}

//! Implementation to unequip helmet in equips
void Character::removeHelmet()
{
	if (helmetEquipped)
	{
		backpack.addItem(*equips[Equip::HELMET]);
		equips[Equip::HELMET] = NULL;
		helmetEquipped = false;
	}
}

//! Implementation to unequip armor in equips
void Character::removeArmor()
{
	if (armorEquipped)
	{
		backpack.addItem(*equips[Equip::ARMOR]);
		equips[Equip::ARMOR] = NULL;
		armorEquipped = false;
	}
}

//! Implementation to unequip belt in equips
void Character::removeBelt()
{
	if (beltEquipped)
	{
		backpack.addItem(*equips[Equip::BELT]);
		equips[Equip::BELT] = NULL;
		beltEquipped = false;
	}
}

//! Implementation to unequip boots in equips
void Character::removeBoots()
{
	if (bootsEquipped)
	{
		backpack.addItem(*equips[Equip::BOOTS]);
		equips[Equip::BOOTS] = NULL;
		bootsEquipped = false;
	}
}

//! Implementation to unequip shield in equips
void Character::removeShield()
{
	if (shieldEquipped)
	{
		backpack.addItem(*equips[Equip::SHIELD]);
		equips[Equip::SHIELD] = NULL;
		shieldEquipped = false;
	}
}

//! Implementation to unequip weapon in equips
void Character::removeWeapon()
{
	if (weaponEquipped)
	{
		backpack.addItem(*equips[Equip::WEAPON]);
		equips[Equip::WEAPON] = NULL;
		weaponEquipped = false;
	}
}

//! Implementation to unequip ring in equips
void Character::removeRing()
{
	if (ringEquipped)
	{
		backpack.addItem(*equips[Equip::RING]);
		equips[Equip::RING] = NULL;
		ringEquipped = false;
	}
}

//! displayStats function
//! @brief displays the stats of the Character.
void Character::displayStats()
{
	for (basic_string<char>::iterator p = name.begin(); p != name.end(); ++p)
	{
		if (p == name.begin())
			*p = toupper(*p);
		else
			*p = tolower(*p);
	}

	string items;
	for (Item* i : equips) 
	{
		if (i != NULL)
			items = items + i->toString() + "\n";
	}

	cout << "\n= PLAYER STATS ="
		<< "\nName: " << getName()
		<< "\nClass: " << classtoString()
		<< "\nLVL: " << getLevel()
		<< "\nHP : " << getHitPoints()
		<< "\nSTR: " << getSTR()
		<< "\nDEX: " << getDEX()
		<< "\nCON: " << getCON()
		<< "\nINT: " << getINTEL()
		<< "\nWIS: " << getWIS()
		<< "\nCHA: " << getCHA()
		<< "\nArmor Class: " << getArmorClass()
		<< "\nAttack Bonus: " << getAttackBonus()
		<< "\nDamage Bonus: " << getDamageBonus()
		<< "\nItems equipped: " << items
		<< "\nBackpack: " << backpack.toString()
		<< "\n" << endl;
}

//! statString function
//! @brief returns the stats of Character in string form
//! @return string of the Character stats
string Character::statString()
{
	//Converts name to first char capitalized
	for (basic_string<char>::iterator p = name.begin(); p != name.end(); ++p)
	{
		if (p == name.begin())
			*p = toupper(*p);
		else
			*p = tolower(*p);
	}

	string items;
	for (Item* i : equips) {
		items = items + i->toString() + "\n";
	}

	std::ostringstream out;
	out << "\nName: " << getName()
		<< "\nClass: " << classtoString()
		<< "\nLVL: " << getLevel()
		<< "\nHP : " << getHitPoints()
		<< "\nSTR: " << getSTR()
		<< "\nDEX: " << getDEX()
		<< "\nCON: " << getCON()
		<< "\nINT: " << getINTEL()
		<< "\nWIS: " << getWIS()
		<< "\nCHA: " << getCHA()
		<< "\nArmor Class: " << getArmorClass()
		<< "\nAttack Bonus: " << getAttackBonus()
		<< "\nDamage Bonus: " << getDamageBonus()
		<< "\nItems equipped: " << items
		<< "\nBackpack: " << backpack.toString()
		<< "\n" << endl;
	return out.str();
}

//! classToString function
//! @brief converts integer to Character class
//! @return : string containing the class of the Character
string Character::classtoString()
{
	switch (charClass) {
	case 1: {
		return "Fighter";
		break;
	}
	default: {
		return "N/A";
		break;
	}
	}
}

//! saveCharacter function
//! @brief saves the Character stats to an XML file (to be loaded later as a save)
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
	xml.AddElem("hp", getHitPoints());
	xml.AddElem("class", getCharClass());
	xml.AddElem("backpack");
	xml.IntoElem();
	//Iterate through the item IDs in backpack
	for (int i: backpack.getIDs()) 
	{
		xml.AddElem("item", i);
	}
	xml.OutOfElem();
	xml.AddElem("equips");
	xml.IntoElem();
	
	//Iterate through equips
	for (Item* i : equips) {
		if (i = NULL)
			xml.AddElem("equip", 0);
		else
			xml.AddElem("equip", i->getID());
	}

	//char di[20];
	//sprintf_s(di, 20, "characters/%s.xml", name.c_str());
	xml.Save("characters/" + name + ".xml");
}

//! loadCharacter function
//! @brief loads the Character stats from an XML file
//! @param name : name of Character
//! @return : pointer to Character object
// typo here, will fix later
Character* Character::loadCharacter(string name)
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
			int level, charclass, str, dex, con, intel, wis, cha, hp;
			ItemContainer backpack;
			Item* equips[7];

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
				else if (tag == "hp")
				{
					hp = atoi(xml.GetData().c_str());
				}
				else if (tag == "class")
				{
					charclass = atoi(xml.GetData().c_str());
				}
				else if (tag == "backpack")
				{
					xml.IntoElem();
					while (xml.FindElem("item"))
					{
						// Reads Item ID and loads XML file into backpack
						int id = atoi(xml.GetData().c_str());
						backpack.addItem(*Item::load(id));
					}
					xml.OutOfElem();
				}
				else if (tag == "equips") // Reads Item ID and loads XML file into equips
				{
					xml.IntoElem();
					int i = 0;
					while (xml.FindElem("item"))
					{
						int id = atoi(xml.GetData().c_str());
						if (id != 0)
							equips[i] = Item::load(id);
						i++;
					}
					xml.OutOfElem();
				}
			}
			return new Character(name, charclass, level, str, dex, con, intel, 
				wis, cha, hp, backpack, equips);
		}
	}
	return nullptr; //Empty
}

//USELESS FOR NOW. IMPLEMENT LATER
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

//WILL BE USED LATER TO LEVEL UP STATS
////! setExtraPoints function
////set the extraPoints stats
//void Character::setExtraPoints()
//{
//	int ExtraPoints = 2;
//	while (ExtraPoints != 0)
//	{
//		//Display message and retrieve the user's input
//		int choice;
//		cout << "\nYou have: " << ExtraPoints << " upgrade(s) available. What would you like to upgrade?\n";
//		cout << "1. STR (Strength)\n";
//		cout << "2. DEX (Dexterity)\n";
//		cout << "3. CON (Constitution)\n";
//		cout << "4. INT (Intelligence)\n";
//		cout << "5. WIS (Wisdom)\n";
//		cout << "6. CHA (Charisma)\n";
//		cin >> choice;
//
//		//if user whishes to improve strength
//		if (choice == 1)
//		{
//			setSTR(getSTR() + 1);
//			ExtraPoints--;
//			cout << "Strength: " << getSTR() << "\n";
//		}
//
//		//if user whishes to improve Dexterity
//		else if (choice == 2)
//		{
//			setDEX(getDEX() + 1);
//			ExtraPoints--;
//			cout << "Dexterity: " << getDEX() << "\n";
//
//		}
//
//		//if user whishes to improve Constitution
//		else if (choice == 3)
//		{
//			setCON(getCON() + 1);
//			ExtraPoints--;
//			cout << "Constitution: " << getCON() << "\n";
//		}
//
//		//if user whishes to improve Intelligence
//		else if (choice == 4)
//		{
//			setINTEL(getINTEL() + 1);
//			ExtraPoints--;
//			cout << "Intelligence: " << getINTEL() << "\n";
//		}
//
//		//if user whishes to improve Wisdom
//		else if (choice == 5)
//		{
//			setWIS(getWIS() + 1);
//			ExtraPoints--;
//			cout << "Wisdom: " << getWIS() << "\n";
//		}
//
//		//if user whishes to improve Luck
//		else if (choice == 6)
//		{
//			setCHA(getCHA() + 1);
//			ExtraPoints--;
//			cout << "Luck: " << getCHA() << "\n";
//		}
//
//		//if no specific bonus has been entered then display error and loop again
//		else
//		{
//			cout << "Error, invalid choice. Please try again.\n";
//		}
//
//		notify();
//	}
//
//}
