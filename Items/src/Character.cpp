//! @file Character.cpp 
//! @brief Implementation file for the Character class  
//!

#include <iostream> /* cin, cout */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <sstream>
#include "Character.h"
#include "Dice.h"
#include "Markup.h"
#include "HumanPlayerStrategy.h"
#include "AgressorStrategy.h"
#include "FriendlyStrategy.h"
#include "CharacterType.h"

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
	currentHitPoints = 10;
	secondaryStatCalc();
	initEnh();

	this->gameover = false;
	this->helmetEquipped = false;
	this->armorEquipped = false;
	this->beltEquipped = false;
	this->bootsEquipped = false;
	this->shieldEquipped = false;
	this->weaponEquipped = false;
	this->ringEquipped = false;
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
Character::Character(string playerName, int charclass, int lvl, int str, int dex, int con, int intel,
	int wis, int cha, int hp, ItemContainer bkpack, Item equips[7])
{
	name = playerName;
	level = lvl;
	charClass = charclass;
	abilityScores[Ability::STRENGTH] = str;
	abilityScores[Ability::DEXTERITY] = dex;
	abilityScores[Ability::CONSTITUTION] = con;
	abilityScores[Ability::INTELLIGENCE] = intel;
	abilityScores[Ability::WISDOM] = wis;
	abilityScores[Ability::CHARISMA] = cha;
	currentHitPoints = hp;
	backpack = bkpack;
	setEquips(equips);
	secondaryStatCalc();
	initEnh();
}

//! notify function
//! @brief implementation of notify from Observable class
//! notifies the observer of any changes
void Character::notify()
{
	initEnh();
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

//! initSprite function
//! @brief loads appropirate Sprite for character.
//! @param type The type of character this is: player, enemy or friend

void Character::initSprite(CharacterSpriteType type)
{
	characterTexture = new sf::Texture();
	switch (type)
	{
	case CharacterSpriteType::S_PLAYER:
	{
		characterTexture->loadFromFile("res/character/hero.png");
		setStrategy(new HumanPlayerStrategy());
		characterType = CT_PLAYER;
		break;
	}
	case CharacterSpriteType::S_ENEMY:
	{
		characterTexture->loadFromFile("res/character/enemy.png");
		setStrategy(new AgressorStrategy());
		characterType = CT_ENEMY;
		break;
	}
	case CharacterSpriteType::S_FRIEND:
	{
		characterTexture->loadFromFile("res/character/friend.png");
		setStrategy(new FriendlyStrategy());
		characterType = CT_FRIEND;
		break;
	}
	}

	characterSprite = new sf::Sprite();
	characterSprite->setTexture(*characterTexture);
	characterSprite->setTextureRect(sf::IntRect(0, 0, 20, 26));
	characterSprite->setPosition(position.x * 32 + 5, position.y * 32 + 3);
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
void Character::statGenerator()
{
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
	for (int i = 0; i < 6; i++)
	{
		totalScores[i] = dice.roll("4d6[0]");
	}

	for (int i = 0; i < 6; i++)
	{
		do
		{
			cout << "Scores leftover: ";
			for (int j = i; j < 6; j++)
			{
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

			switch (choice)
			{
			case 1:
			{
				if (!strSet)
				{
					setSTR(totalScores[i]);
					cout << "STR: " << totalScores[i] << endl;
					strSet = true;
					displayStats();
				}
				else
				{
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 2:
			{
				if (!dexSet)
				{
					setDEX(totalScores[i]);
					cout << "DEX: " << totalScores[i] << endl;
					dexSet = true;
					displayStats();
				}
				else
				{
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 3:
			{
				if (!conSet)
				{
					setCON(totalScores[i]);
					cout << "CON: " << totalScores[i] << endl;
					conSet = true;
					displayStats();
				}
				else
				{
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 4:
			{
				if (!intSet)
				{
					setINTEL(totalScores[i]);
					cout << "INTEL: " << totalScores[i] << endl;
					intSet = true;
					displayStats();
				}
				else
				{
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 5:
			{
				if (!wisSet) {
					setWIS(totalScores[i]);
					cout << "WIS: " << totalScores[i] << endl;
					wisSet = true;
					displayStats();
				}
				else
				{
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			case 6:
			{
				if (!chaSet) {
					setCHA(totalScores[i]);
					cout << "CHA: " << totalScores[i] << endl;
					chaSet = true;
					displayStats();
				}
				else
				{
					cout << "Already set. Please choose another ability." << endl;
					if (i != 0)
						i--;
				}
				break;
			}
			default:
			{
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
	return abilityMod;
}

//! secondaryStatCalc function
//! @brief generates secondary stats based on
//! primary stats.
void Character::secondaryStatCalc()
{
	setArmorClass(10);
	setAttackBonus(getLevel()*(abilityModifier(getSTR()) + abilityModifier(getDEX())) / 5);
	setDamageBonus(abilityModifier(getSTR()));
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the character
void Character::hit(int damage)
{
	if (currentHitPoints > damage)
	{
		this->currentHitPoints -= damage;
	}

	else
	{
		this->currentHitPoints = 0;
		gameover = true;
	}

}

//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return this->currentHitPoints;//(10 + getLevel()*abilityModifier(getCON()));
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
	for (int i = 0; i < 7; i++)
	{
		if (equips[i].getID() != 0)
			items = items + equips[i].toString();
	}

	cout << "\n= PLAYER STATS ="
		<< "\nName: " << getName()
		<< "\nClass: " << classtoString()
		<< "\nLVL: " << getLevel()
		<< "\nHP : " << getHitPoints()
		<< "\nSTR: " << getSTR() << " +" << enh_str
		<< "\nDEX: " << getDEX() << " +" << enh_dex 
		<< "\nCON: " << getCON() << " +" << enh_con
		<< "\nINT: " << getINTEL() << " +" << enh_int
		<< "\nWIS: " << getWIS() << " +" << enh_wis
		<< "\nCHA: " << getCHA() << " +" << enh_cha
		<< "\nArmor Class : " << getArmorClass() << " +" << enh_armorclass
		<< "\nAttack Bonus: " << getAttackBonus() << " +" << enh_attackbonus
		<< "\nDamage Bonus: " << getDamageBonus() << " +" << enh_damagebonus
		<< "\n= Equips =" << items
		<< "\n= Backpack =" << backpack.toString() << endl;
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
	for (Item i : equips)
	{
		if (i.getID() != 0)
			items = items + i.toString() + "\n";
	}

	std::ostringstream out;
	out << "\n" << classtoString()
		<< "\nName: " << getName()
		<< "\nLVL: " << getLevel()
		<< "\nHP : " << getHitPoints()
		<< "\nSTR: " << getSTR() << " +" << enh_str
		<< "\nDEX: " << getDEX() << " +" << enh_dex
		<< "\nCON: " << getCON() << " +" << enh_con
		<< "\nINT: " << getINTEL() << " +" << enh_int
		<< "\nWIS: " << getWIS() << " +" << enh_wis
		<< "\nCHA: " << getCHA() << " +" << enh_cha
		<< "\nArmor Class : " << getArmorClass() << " +" << enh_armorclass
		<< "\nAttack Bonus: " << getAttackBonus() << " +" << enh_attackbonus
		<< "\nDamage Bonus: " << getDamageBonus() << " +" << enh_damagebonus << endl;
	return out.str();
}

//! classToString function
//! @brief converts integer to Character class
//! @return : string containing the class of the Character
string Character::classtoString()
{
	switch (charClass) {
	case 1:
	{
		return "Bully Fighter";
		break;
	}
	case 2:
	{
		return "Nimble Fighter";
		break;
	}
	case 3:
		return "Tank Fighter";
	default:
	{
		return "";
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
	for (Item i : equips)
	{
		if (i.getID() == 0)
			xml.AddElem("equip", 0); // nothing equipped
		else
			xml.AddElem("equip", i.getID());
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
			Item equips[7];

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
							equips[i] = *Item::load(id);
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

//! setEquips function
//! will take in an Item pointer array of length 7 and copy to Character's equips array
//! @param equips : the equips that's getting passed to Character's equips
void Character::setEquips(Item newEquips[7])
{
	for (int i = 0; i < 7; i++)
	{
		equips[i] = newEquips[i];
	}
}


Item* Character::getEquip(string equip)
{
	if (equip.compare("armor") == 0)
		return &equips[Equip::ARMOR];

	else if (equip.compare("helmet") == 0)
		return &equips[Equip::HELMET];

	else if (equip.compare("shield") == 0)
		return &equips[Equip::SHIELD];

	else if (equip.compare("ring") == 0)
		return &equips[Equip::RING];

	else if (equip.compare("belt") == 0)
		return &equips[Equip::BELT];

	else if (equip.compare("boots") == 0)
		return &equips[Equip::BOOTS];

	else if (equip.compare("weapon") == 0)
		return &equips[Equip::WEAPON];

	else
		return nullptr;
}

//! equip function used by ItemDecorator
//! @brief equips the item passed as a parameter
//! @param item : item that will be equipped
void Character::equip(Item *item)
{
	string itemtype = item->getType();
	if (itemtype.compare("armor") == 0)
		equips[Equip::ARMOR] = *item;

	else if (itemtype.compare("helmet") == 0)
		equips[Equip::HELMET] = *item;

	else if (itemtype.compare("shield") == 0)
		equips[Equip::SHIELD] = *item;

	else if (itemtype.compare("ring") == 0)
		equips[Equip::RING] = *item;

	else if (itemtype.compare("belt") == 0)
		equips[Equip::BELT] = *item;

	else if (itemtype.compare("boots") == 0)
		equips[Equip::BOOTS] = *item;

	else if (itemtype.compare("weapon") == 0)
		equips[Equip::WEAPON] = *item;
}

//! unequip function used by ItemDecorator
//! @brief unequips the item passed as a parameter
void Character::unequip(Item* item)
{
	string equip = item->getType();

	if (equip.compare("armor") == 0)
	{
		backpack.addItem(equips[Equip::ARMOR]);
		equips[Equip::ARMOR] = Item();
	}

	else if (equip.compare("helmet") == 0)
	{
		backpack.addItem(equips[Equip::HELMET]);
		equips[Equip::HELMET] = Item();
	}

	else if (equip.compare("shield") == 0)
	{
		backpack.addItem(equips[Equip::SHIELD]);
		equips[Equip::SHIELD] = Item();
	}

	else if (equip.compare("ring") == 0)
	{
		backpack.addItem(equips[Equip::RING]);
		equips[Equip::RING] = Item();
	}

	else if (equip.compare("belt") == 0)
	{
		backpack.addItem(equips[Equip::BELT]);
		equips[Equip::BELT] = Item();
	}

	else if (equip.compare("boots") == 0)
	{
		backpack.addItem(equips[Equip::BOOTS]);
		equips[Equip::BOOTS] = Item();
	}

	else if (equip.compare("weapon") == 0)
	{
		backpack.addItem(equips[Equip::WEAPON]);
		equips[Equip::WEAPON] = Item();
	}
}

//! setEnh function
//! sets the enhancement and ability modifier bonus
//! @param type : string of the enhancement type
//! @param bonus : value of enhancement
void Character::setEnh(string type, int bonus)
{
	if (type.compare("strength") == 0)
		enh_str = enh_str + bonus;

	else if (type.compare("dexterity") == 0)
		enh_dex = enh_dex + bonus;

	else if (type.compare("constitution") == 0)
		enh_con = enh_con + bonus;

	else if (type.compare("intelligence") == 0)
		enh_int = enh_int + bonus;

	else if (type.compare("wisdom") == 0)
		enh_wis = enh_wis + bonus;

	else if (type.compare("charisma") == 0)
		enh_cha = enh_cha + bonus;

	else if (type.compare("armorclass") == 0)
		enh_armorclass = enh_armorclass + bonus;

	else if (type.compare("attackbonus") == 0)
		enh_attackbonus = enh_attackbonus + bonus;

	else if (type.compare("damagebonus") == 0)
		enh_damagebonus = enh_damagebonus + bonus;
}

//! initEnh function
//! initializes the ability modifier bonus
void Character::initEnh()
{
	enh_str = abilityModifier(getSTR());
	enh_dex = abilityModifier(getDEX());
	enh_con = abilityModifier(getCON());
	enh_int = abilityModifier(getINTEL());
	enh_wis = abilityModifier(getWIS());
	enh_cha = abilityModifier(getCHA());
	enh_armorclass = abilityModifier(getDEX());
	enh_attackbonus = 0;
	enh_damagebonus = 0;
}

//! setEquipTF function
//! sets the item's itemEquipped value as true or false, depending on parameter
//! @param item : item that is being modified
//! @param boolean : true represents the item as equipped and false represents the item as unequipped
void Character::setEquipTF(Item* item, bool T_F)
{
	string type = item->getType();
	if (type == TYPE_HELMET)
		helmetEquipped = T_F;

	else if (type == TYPE_SHIELD)
		shieldEquipped = T_F;

	else if (type == TYPE_RING)
		ringEquipped = T_F;

	else if (type == TYPE_ARMOR)
		armorEquipped = T_F;

	else if (type == TYPE_BELT)
		beltEquipped = T_F;

	else if (type == TYPE_BOOTS)
		bootsEquipped = T_F;

	else if (type == TYPE_WEAPON)
		weaponEquipped = T_F;
}

//! isEquipped function
//! checks if the item type passed as a parameter is already equipped
//! @param item : item that is being checked if it's already worn
//! @return true if it is already equipped, false otherwise
bool Character::isEquipped(Item* item)
{
	string type = item->getType();
	if (type == TYPE_HELMET)
		return helmetEquipped;

	else if (type == TYPE_SHIELD)
		return shieldEquipped;

	else if (type == TYPE_RING)
		return ringEquipped;

	else if (type == TYPE_ARMOR)
		return armorEquipped;

	else if (type == TYPE_BELT)
		return beltEquipped;

	else if (type == TYPE_BOOTS)
		return bootsEquipped;

	else if (type == TYPE_WEAPON)
		return weaponEquipped;
}

//! getStrategy function
//! @brief returns character strategy.
Strategy* Character::getStrategy()
{
	return this->strategy;
}

//! setStrategy function
//! setter for the strategy field.
//! @param strat stategy to set
void Character::setStrategy(Strategy* strat)
{
	this->strategy = strat; 
}

//! getPosition function
//! @brief getter for position field.
//! @return position of character
pos Character::getPosition()
{
	return this->position;
}

//! setPosition function
//! @brief setter for position field
//! @param x x position of player.
//! @param y y position of player
void Character::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

//! changeSprite function
//! change sprite according to action.
void Character::changeSprite(PlayerMove move)
{
	switch (move)
	{
	case PlayerMove::UP:
	{
		characterSprite->setTextureRect(sf::IntRect(20, 0, 20, 26));
		break;
	}
	case PlayerMove::DOWN:
	{
		characterSprite->setTextureRect(sf::IntRect(0, 0, 20, 26));
		break;
	}
	case PlayerMove::RIGHT:
	{
		characterSprite->setTextureRect(sf::IntRect(60, 0, 20, 26));
		break;
	}
	case PlayerMove::LEFT:
	{
		characterSprite->setTextureRect(sf::IntRect(40, 0, 20, 26)); //Change Sprite.
		break;
	}
	}
}

//! changeSprite function
//! change sprite according to action.
void Character::move(PlayerMove move)
{
	switch (move)
	{
	case PlayerMove::UP:
	{
		position.y -= 1;
		characterSprite->move(0, -32);
		break;
	}
	case PlayerMove::DOWN:
	{
		position.y += 1;
		characterSprite->move(0, +32);
		break;
	}
	case PlayerMove::RIGHT:
	{
		position.x += 1;
		characterSprite->move(+32, 0);
		break;
	}
	case PlayerMove::LEFT:
	{
		position.x -= 1;
		characterSprite->move(-32, 0);
		break;
	}
	}
}
//! attackRoll function
//! d20 roll + attack bonus
//! @param d20 : integer that represents the dice rolled
//! @return result of attack bonus
int Character::attackRoll(int d20)
{
	return d20 + this->attackBonus;
}

//! attack function
//! attackRoll + strength modifier.
//! @return total attack.
int Character::attack(int attackRoll)
{
	return attackRoll + getSTR(); //+ size
}

//! getCharacterrType function
//! returns the type of character created (player, friendly, enemy)
//! @return : string of type of character
string Character::getCharacterType()
{
	return this->characterType;
}