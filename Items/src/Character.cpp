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
	currentHitPoints = 10 + abilityModifier(getCON());
	attackBonus = lvl;
	totalEnhancement();
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
	int wis, int cha, int hp, ItemContainer bkpack, Item equips[7], int maxhp)
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
	maxHP = maxhp;
	currentHitPoints = hp;
	backpack = bkpack;
	setEquips(equips);
	attackBonus = lvl;
	totalEnhancement();
}

//! notify function
//! @brief implementation of notify from Observable class
//! notifies the observer of any changes
void Character::notify()
{
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
	int abilityMod = (abilityScore / 2) - 5;
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

//! Implementation of a getter method for maxHP
//! @param newHP : new HP value
int Character::getMaxHP()
{
	return maxHP;
}

//! Implementation of a getter method for maxHP
//! @param newHP : new HP value
void Character::setMaxHP(int newHP)
{
	maxHP = newHP;
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
	Dice dice;
	string constitutionString = this->abilityScores[Ability::CONSTITUTION] +"";
	level = level + 1;
	//should roll 1d10[constitution]
	int hpIncrease = dice.roll("1d10[" + constitutionString + "]");
	currentHitPoints = currentHitPoints + hpIncrease;
	maxHP = maxHP + hpIncrease;
	//Sets the enhancement attack bonus as the level
	this->enh_attackbonus = level;

	cout << "Congratulations on leveling up!" << endl;
	cout << "Your Maximum hitpoints has increased by " << dice.roll("1d10[" + constitutionString + "]") << endl;
	int availablePoints = 2;
	while (availablePoints > 0){
		int currentStr = this->getSTR();
		int currentDex = this->getDEX();
		int currentCon = this->getCON();
		int currentInt = this->getINTEL();
		int currentWis = this->getWIS();
		int currentCha = this->getCHA();
		if (currentStr + currentDex + currentCon + currentInt + currentWis + currentCha == 120)
			break;
		int choice;
		cout << "You have " << availablePoints << " available,"
			<< "\n1. STR"
			<< "\n2. DEX"
			<< "\n3. CON"
			<< "\n4. INTEL"
			<< "\n5. WIS"
			<< "\n6. CHA" << endl;
		cin >> choice;
		switch (choice){
		case 1:{
			int x = this->getSTR();
			if (x < 20){
				this->setSTR(x + 1);
				cout << "Strength set to " << x << endl;
				availablePoints--;
			}
			else{
				cout << "Strength is at max level, please choose something else" << endl;
			}
			break;
		}
		case 2:{
			int x = this->getDEX();
			if (x < 20){
				this->setSTR(x + 1);
				cout << "Dexterity set to " << x << endl;
				availablePoints--;
			}
			else{
				cout << "Dexterity is at max level, please choose something else" << endl;
			}
			break;
		}
		case 3:{
			int x = this->getCON();
			if (x < 20){
				this->setCON(x + 1);
				cout << "Constitution set to " << x << endl;
				availablePoints--;
			}
			else{
				cout << "Constitution is at max level, please choose something else" << endl;
			}
			break;
		}
		case 4:{
			int x = this->getINTEL();
			if (x < 20){
				this->setINTEL(x + 1);
				cout << "Intelligence set to " << x << endl;
				availablePoints--;
			}
			else{
				cout << "Intelligence is at max level, please choose something else" << endl;
			}
			break;
		}
		case 5:{
			int x = this->getWIS();
			if (x < 20){
				this->setWIS(x + 1);
				cout << "Wisdom set to " << x << endl;
				availablePoints--;
			}
			else{
				cout << "Wisdom is at max level, please choose something else" << endl;
			}
			break;
		}
		case 6:{
			int x = this->getCHA();
			if (x < 20){
				this->setCHA(x + 1);
				cout << "Charisma set to " << x << endl;
				availablePoints--;
			}
			else{
				cout << "Charisma is at max level, please choose something else" << endl;
			}
			break;
		}
		default:{
			cout << "Enter a valid option" << endl;
		}
		}
	}
		
	
	/*
	abilityScores[Ability::STRENGTH] < 18 ? setSTR(abilityScores[Ability::STRENGTH] + 1) : false;
	abilityScores[Ability::DEXTERITY] < 18 ? setSTR(abilityScores[Ability::DEXTERITY] + 1) : false;
	abilityScores[Ability::CONSTITUTION] < 18 ? setSTR(abilityScores[Ability::CONSTITUTION] + 1) : false;
	abilityScores[Ability::INTELLIGENCE] < 18 ? setSTR(abilityScores[Ability::INTELLIGENCE] + 1) : false;
	abilityScores[Ability::WISDOM] < 18 ? setSTR(abilityScores[Ability::WISDOM] + 1) : false;
	abilityScores[Ability::CHARISMA] < 18 ? setSTR(abilityScores[Ability::CHARISMA] + 1) : false;*/
}

//! Getter method to get the ItemContainer backpack
//! @return backpack: the backpack (itemcontainer vector) inventory
ItemContainer Character::getBackpack()
{
	return backpack;
}

//! addBackpack function to add items to backpack
//! @param item : pointer to item added to backpack
void Character::addBackpack(Item* item)
{
	backpack.addItem(*item);
}

//! removeBackpackIndex FUNCTION
//! @param i index of to deleted.
void Character::removeBackpackIndex(int i)
{
	backpack.removeItemAtIndex(i);
}

//! getBackpackSize function
//! @return # of items in backpack
int Character::getBackpackSize()
{
	return backpack.getItems().size();
}

//! getBackpackItems function to return vector of Item objects
//! @return : vector containing Item objects in backpack
vector <Item> Character::getBackpackItems()
{
	return backpack.getItems();
}


//! getItemAtIndex function
//! @brief get backpack item at index.
//! @param i index of item.
Item* Character::getItemAtIndex(int i)
{
	vector <Item> Items = getBackpackItems();
	cout << " Item Type: " << Items[i].getType() << endl;
	cout << "Influences: " << Items[i].getInfluences()[i].toString() << endl;
	cout << "Item Path: " << Items[i].getItemPath() << endl;
	Item item(Items[i].getID(), Items[i].getType(), Items[i].getInfluences(), Items[i].getItemPath());
	return &item;
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

	string STRplus = " ";
	string DEXplus = " ";
	string CONplus = " ";
	string INTELplus = " ";
	string WISplus = " ";
	string CHAplus = " ";

	if (enh_str >= 0)
		STRplus = " +";
	if (enh_dex >= 0)
		DEXplus = " +";
	if (enh_con >= 0)
		CONplus = " +";
	if (enh_int >= 0)
		INTELplus = " +";
	if (enh_wis >= 0)
		WISplus = " +";
	if (enh_cha >= 0)
		CHAplus = " +";

	cout << "\n= PLAYER STATS ="
		<< "\nName: " << getName()
		<< "\nClass: " << classtoString()
		<< "\nLVL: " << getLevel()
		<< "\nHP : " << getHitPoints() << "/" << maxHP
		<< "\nSTR: " << getSTR() << STRplus << enh_str
		<< "\nDEX: " << getDEX() << DEXplus << enh_dex
		<< "\nCON: " << getCON() << CONplus << enh_con
		<< "\nINT: " << getINTEL() << INTELplus << enh_int
		<< "\nWIS: " << getWIS() << WISplus << enh_wis
		<< "\nCHA: " << getCHA() << CHAplus << enh_cha
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

	string STRplus = "";
	string DEXplus = "";
	string CONplus = "";
	string INTELplus = "";
	string WISplus = "";
	string CHAplus = "";

	if (enh_str >= 0)
		STRplus = " +";
	if (enh_dex >= 0)
		DEXplus = " +";
	if (enh_con >= 0)
		CONplus = " +";
	if (enh_int >= 0)
		INTELplus = " +";
	if (enh_wis >= 0)
		WISplus = " +";
	if (enh_cha >= 0)
		CHAplus = " +";

	std::ostringstream out;
	out << "\n" << getName()
		<< "\n" << classtoString()
		<< "\nLVL: " << getLevel()
		<< "\nHP : " << getHitPoints() << "/" << maxHP
		<< "\nHP : " << getHitPoints() << "/" << maxHP
		<< "\nSTR: " << getSTR() << STRplus << enh_str
		<< "\nDEX: " << getDEX() << DEXplus << enh_dex
		<< "\nCON: " << getCON() << CONplus << enh_con
		<< "\nINT: " << getINTEL() << INTELplus << enh_int
		<< "\nWIS: " << getWIS() << WISplus << enh_wis
		<< "\nCHA: " << getCHA() << CHAplus << enh_cha
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
	xml.AddElem("maxhp", getMaxHP());
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
			int level, charclass, str, dex, con, intel, wis, cha, hp, maxhp;
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
				else if (tag == "maxhp")
				{
					maxhp = atoi(xml.GetData().c_str());
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
					while (xml.FindElem("equip"))
					{
						int id = atoi(xml.GetData().c_str());
						if (id != 0)
							equips[i] = *Item::load(id);
						else // id = 0, empty
							equips[i] = Item();
						i++;
					}
					xml.OutOfElem();
				}
			}
			return new Character(name, charclass, level, str, dex, con, intel,
				wis, cha, hp, backpack, equips, maxhp);
		}
	}
	return nullptr; //Empty
}

//! setEquips function
//! will take in an Item pointer array of length 7 and copy to Character's equips array
//! @param equips : the equips that's getting passed to Character's equips
void Character::setEquips(Item newEquips[7])
{
	// Make equipped items true if player has equips
	for (int i = 0; i < 7; i++)
	{
		equips[i] = newEquips[i];
		if (equips[i].getType() == "helmet")
		{
			helmetEquipped = true;
		}
		else if (equips[i].getType() == "armor")
		{
			armorEquipped = true;
		}
		else if (equips[i].getType() == "shield")
		{
			shieldEquipped = true;
		}
		else if (equips[i].getType() == "ring")
		{
			ringEquipped = true;
		}
		else if (equips[i].getType() == "belt")
		{
			beltEquipped = true;
		}
		else if (equips[i].getType() == "boots")
		{
			bootsEquipped = true;
		}
		else if (equips[i].getType() == "weapon")		
		{
			weaponEquipped = true;
		}
	}
}

//! getEquips function
//! @return : Pointer to Item array of size 7 with equips
Item* Character::getEquips()
{
	return equips;
}

//! getEquipAtIndex function
//! @brief gets equip item at index.
//! @param i index of equiped item.
Item* Character::getEquipAtIndex(int i)
{
	return &equips[i];
}

//! getEquipType function
//! @brief returns Equipped of of type.
//! @param equip type of item.
Item* Character::getEquipType(string equip)
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
	string type = item->getType();
	if (type.compare("armor") == 0)
	{
		// If item is already equipped, unequip first.
		if (armorEquipped)
			unequip(item);
		
		equips[Equip::ARMOR] = *item;
		armorEquipped = true;
		//remove item from backpack

	}

	else if (type.compare("helmet") == 0)
	{
		if (helmetEquipped)
			unequip(item);

		equips[Equip::HELMET] = *item;
		helmetEquipped = true;
	}

	else if (type.compare("shield") == 0)
	{
		if (shieldEquipped)
			unequip(item);
		
		equips[Equip::SHIELD] = *item;
		shieldEquipped = true;
	}
	else if (type.compare("ring") == 0)
	{
		if (ringEquipped)
			unequip(item);

		cout << "Ring clicked on" << endl;
		equips[Equip::RING] = *item;
		ringEquipped = true;
	}
	else if (type.compare("belt") == 0)
	{
		if (beltEquipped)
			unequip(item);

		equips[Equip::BELT] = *item;
		beltEquipped = true;
	}

	else if (type.compare("boots") == 0)
	{
		if (bootsEquipped)
			unequip(item);

		equips[Equip::BOOTS] = *item;
		bootsEquipped = true;
	}
	else if (type.compare("weapon") == 0)
	{
		if (weaponEquipped)
			unequip(item);

		equips[Equip::WEAPON] = *item;
		weaponEquipped = true;
	}

	else
	{
		cout << "Item type unknown" << endl;
	}

	totalEnhancement();
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
		armorEquipped = false;
	}

	else if (equip.compare("helmet") == 0)
	{
		backpack.addItem(equips[Equip::HELMET]);
		equips[Equip::HELMET] = Item();
		helmetEquipped = false;
	}

	else if (equip.compare("shield") == 0)
	{
		backpack.addItem(equips[Equip::SHIELD]);
		equips[Equip::SHIELD] = Item();
		shieldEquipped = false;
	}

	else if (equip.compare("ring") == 0)
	{
		backpack.addItem(equips[Equip::RING]);
		equips[Equip::RING] = Item();
		ringEquipped = false;
	}

	else if (equip.compare("belt") == 0)
	{
		backpack.addItem(equips[Equip::BELT]);
		equips[Equip::BELT] = Item();
		beltEquipped = false;
	}

	else if (equip.compare("boots") == 0)
	{
		backpack.addItem(equips[Equip::BOOTS]);
		equips[Equip::BOOTS] = Item();
		bootsEquipped = false;
	}

	else if (equip.compare("weapon") == 0)
	{
		backpack.addItem(equips[Equip::WEAPON]);
		equips[Equip::WEAPON] = Item();
		weaponEquipped = false;
	}

	else
	{
		cout << "Item type unknown" << endl;
	}

	totalEnhancement();
}

//! initEnh function
//! initializes the ability modifier bonus
void Character::totalEnhancement()
{
	enh_str = abilityModifier(abilityScores[Ability::STRENGTH]),
	enh_dex = abilityModifier(abilityScores[Ability::DEXTERITY]),
	enh_con = abilityModifier(abilityScores[Ability::CONSTITUTION]),
	enh_int = abilityModifier(abilityScores[Ability::INTELLIGENCE]),
	enh_wis = abilityModifier(abilityScores[Ability::WISDOM]),
	enh_cha = abilityModifier(abilityScores[Ability::CHARISMA]),
	enh_armorclass = abilityModifier(abilityScores[Ability::DEXTERITY]),
	enh_damagebonus = 0,
	enh_attackbonus = 0;

	for (Item i : equips)
	{
		enh_str = enh_str + i.getEnhancement("strength");
		enh_dex = enh_dex + i.getEnhancement("dexterity");
		enh_con = enh_con + i.getEnhancement("constitution");
		enh_int = enh_int + i.getEnhancement("intelligence");
		enh_wis = enh_wis + i.getEnhancement("wisdom");
		enh_cha = enh_cha + i.getEnhancement("charisma");
		enh_armorclass = enh_armorclass + i.getEnhancement("armorclass");
		enh_attackbonus = enh_attackbonus + i.getEnhancement("attackbonus");
		enh_damagebonus = enh_damagebonus + i.getEnhancement("damagebonus");
	}
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