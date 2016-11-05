//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"
#include "GameObject.h"
#include <iostream>

//! default constructor
Item::Item()
{
	GameObject(ITEM);
	type = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences)
{
	GameObject(ITEM);
	// ***todo***: this constructor should verify that an new item of a certain type only 
	// enhances a character statistic valid for this item type
	type = type_name;
	influence = influences;

	if (!this->validateItem())
	{
		//Probably have a popup window for this later on.
		//When GUI is implemented
		std::cout << "[WARNING] Invalid Item." << std::endl; 
	}
	//If the item is valid, we don't do anything.
}

Item::~Item()
{
	while (!influence.empty()) {
		//delete influence.back();
		influence.pop_back();
	}
}

//! method to get the type of the item
//! @return : type of the item
string Item::getType()
{
	return type;
}

//! method to get the influences of the item
//! @return : vector containg the list of stats that the item enhances
vector<Enhancement> Item::getInfluences()
{
	return influence;
}

//! method to validate an item, e.g. verify that an new item of a certain type only enhances a character statistic valid for this item type
//! @return : true if the enhancement list is valid according to the rules, false if not
bool Item::validateItem()
{
	for (int i = 0; i != influence.size(); ++i)
	{
		if (influence[i].getBonus() != 1 && influence[i].getBonus() != 5)
		{
			return false;
		}
	}
	//Actual checking
	if (type == TYPE_HELMET)
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except intelligence, wisdom, or armor class,
			we return false.
			Hence, strength, constitution, charisma, dexterity, attack bonus 
			and defence bonus are all illgal.
			*/
			if (influence[i].getType() == EN_STRENGTH ||
				influence[i].getType() == EN_CONSTITUTION ||
				influence[i].getType() == EN_CHARISMA ||
				influence[i].getType() == EN_DEXTERITY ||
				influence[i].getType() == EN_ATTACK_BONUS ||
				influence[i].getType() == EN_DEF_BONUS)
			{
				return false;
			}
		}
	}
	else if (type == TYPE_ARMOR || type == TYPE_SHIELD)
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except armor class,
			we return false.
			Hence, strength, constitution, intelligence, wisdom, charisma, dexterity, attack bonus
			and defence bonus are all illgal.
			*/
			//Case sensitive FOR NOW.
			if (influence[i].getType() == EN_STRENGTH ||
				influence[i].getType() == EN_CONSTITUTION ||
				influence[i].getType() == EN_WISDOM ||
				influence[i].getType() == EN_CHARISMA ||
				influence[i].getType() == EN_DEXTERITY ||
				influence[i].getType() == EN_ATTACK_BONUS ||
				influence[i].getType() == EN_DEF_BONUS ||
				influence[i].getType() == EN_INTELLIGENCE)
			{
				return false;
			}
		}
	}
	else if (type == TYPE_RING)
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except armor class, strength, Constituion,
			Wisdom, Charisma
			we return false.
			Hence, intelligence, dexterity, attack bonus
			and defence bonus are all illgal.
			*/
			//Case sensitive FOR NOW.
			if (influence[i].getType() == EN_DEXTERITY ||
				influence[i].getType() == EN_ATTACK_BONUS ||
				influence[i].getType() == EN_DEF_BONUS ||
				influence[i].getType() == EN_INTELLIGENCE)
			{
				return false;
			}
		}
	}
	else if (type == TYPE_BELT)
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except strength and Constituion,
			we return false.
			Hence, Intelligence, wisdom, charisma, dexterity, attack bonus, defence bonus 
			and armor class
			*/

			//Case sensitive FOR NOW.
			if (influence[i].getType() == EN_WISDOM ||
				influence[i].getType() == EN_CHARISMA ||
				influence[i].getType() == EN_DEXTERITY ||
				influence[i].getType() == EN_ATTACK_BONUS ||
				influence[i].getType() == EN_DEF_BONUS ||
				influence[i].getType() == EN_INTELLIGENCE ||
				influence[i].getType() == EN_ARMOR_CLASS)
			{
				return false;
			}
		}
	}
	else if (type == TYPE_BOOTS)
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except Armor Class and dexterity
			we return false.
			Hence, Intelligence, wisdom, charisma, consitution, attack bonus, defence bonus
			and strength
			*/

			//Case sensitive FOR NOW.
			if (influence[i].getType() == EN_STRENGTH ||
				influence[i].getType() == EN_CONSTITUTION ||
				influence[i].getType() == EN_WISDOM ||
				influence[i].getType() == EN_CHARISMA ||
				influence[i].getType() == EN_ATTACK_BONUS ||
				influence[i].getType() == EN_DEF_BONUS ||
				influence[i].getType() == EN_INTELLIGENCE)
			{
				return false;
			}
		}
	}
	else if (type == TYPE_WEAPON)
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except Atack Bonus and Defence Bonus||Armor Class and dexterity
			we return false.
			Hence, Intelligence, wisdom, charisma, consitution, Armor Class, dexterity
			and strength
			*/

			//Case sensitive FOR NOW.
			if (influence[i].getType() == EN_STRENGTH ||
				influence[i].getType() == EN_CONSTITUTION ||
				influence[i].getType() == EN_WISDOM ||
				influence[i].getType() == EN_CHARISMA ||
				influence[i].getType() == EN_ARMOR_CLASS ||
				influence[i].getType() == EN_DEXTERITY ||
				influence[i].getType() == EN_INTELLIGENCE)
			{
				return false;
			}
		}
	}
	else //Unknown Item type.
	{
		std::cout << "Unknown Item Type." << std::endl;
		return false;
	}
	return true;
}

Item Item::randommize(int lvl)
{
	int r = rand() % 7 + 1; //Random number between 1 and 7 for choosing item type.
	string type;
	switch (r)
	{
	case 1:
		type = TYPE_HELMET; break;
	case 2:
		type = TYPE_ARMOR; break;
	case 3:
		type = TYPE_SHIELD; break;
	case 4:
		type = TYPE_RING; break;
	case 5:
		type = TYPE_BELT; break;
	case 6:
		type = TYPE_BOOTS; break;
	case 7:
		type = TYPE_WEAPON; break;
	}

createBonus: //For goto statement, later, we check if the item is valid
	//if it's not, we start this process over again.
	//Horrible way to do it, but only one I can think of right now.
	//do while loop might work. Have to think about it.
	
	// For added enhancements, we interate through
	// 9 numbers, 1 for each enhancement type.
	// generate a random number t
	// there's a 50/50 chance of getting an enhancement
	// for that type
	vector<Enhancement> enh;
	for (int i = 0; i != 9; i++)
	{
		int t = rand();
		if (t % 2 == 1)
		{
			Enhancement enhancement;
			switch (i)
			{
			case 0: //strength
				enhancement.setType(EN_STRENGTH); break;
			case 1: //constitution
				enhancement.setType(EN_CONSTITUTION); break;
			case 2: //wisdom
				enhancement.setType(EN_WISDOM); break;
			case 3: //charisma
				enhancement.setType(EN_CHARISMA); break;
			case 4: //dexterity
				enhancement.setType(EN_DEXTERITY); break;
			case 5: //atk bonus
				enhancement.setType(EN_ATTACK_BONUS); break;
			case 6: //defence bonus
				enhancement.setType(EN_DEF_BONUS); break;
			case 7: //armor class
				enhancement.setType(EN_ARMOR_CLASS); break;
			case 8: //intelligence
				enhancement.setType(EN_INTELLIGENCE); break;
			}

			int bon = rand(); //generate random number for determining bonus
			
			if (bon % 100 == 0) //if divisible by 100, therefore, 1/100 times roughly.
			{
				enhancement.setBonus(5);
			}
			else
			{
				//We get a bonus of 1 most times.
				enhancement.setBonus(1);
			}
			enh.push_back(enhancement);
		}
		//Else do nothing, don't add enhancement.
	}
	Item item(type, enh);

	if (!item.validateItem())
	{
		goto createBonus;
	}
	else
	{
		return item;
	}
}
