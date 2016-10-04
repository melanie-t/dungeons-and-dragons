//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"
#include <iostream>

//! default constructor
Item::Item()
{
	type = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences)
{
	// ***todo***: this constructor should verify that an new item of a certain type only 
	// enhances a character statistic valid for this item type
	type = type_name;
	influence = influences;

	if (!this->validateItem())
	{
		//Probably have a popup window for this later on.
		//When GUI is implemented
		std::cout << "Invalid Item!!" << std::endl; 
	}
	//If the item is valid, we don't do anything.
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
	// ***todo*** done.

	//Not sure if needed: HEEEEELP
	for (int i = 0; i != influence.size(); ++i)
	{
		if (influence[i].getBonus != 1 || influence[i].getBonus != 5)
		{
			return false;
		}
	}
	//Actual checking
	if (type == "Helmet")
	{
		for (int i = 0; i != influence.size(); ++i)
		{
			/*
			If the item has has anything except intelligence, wisdom, or armor class,
			we return false.
			Hence, strength, constitution, charisma, dexterity, attack bonus 
			and defence bonus are all illgal.
			*/
			//Case sensitive FOR NOW.
			if (influence[i].getType() == "Strength"||
				influence[i].getType() == "Constitution" ||
				influence[i].getType() == "Charisma"||
				influence[i].getType() == "Dexterity"||
				influence[i].getType() == "Attack bonus"||
				influence[i].getType() == "Defence bonus")
			{
				return false;
			}
		}
	}
	else if (type == "Armor" || type == "Shield")
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
			if (influence[i].getType() == "Strength" ||
				influence[i].getType() == "Constitution" ||
				influence[i].getType() == "Wisdom" ||
				influence[i].getType() == "Charisma" ||
				influence[i].getType() == "Dexterity" ||
				influence[i].getType() == "Attack bonus" ||
				influence[i].getType() == "Defence bonus"||
				influence[i].getType() == "Intelligence")
			{
				return false;
			}
		}
	}
	else if (type == "Ring")
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
			if (influence[i].getType() == "Dexterity" ||
				influence[i].getType() == "Attack bonus" ||
				influence[i].getType() == "Defence bonus" ||
				influence[i].getType() == "Intelligence")
			{
				return false;
			}
		}
	}
	else if (type == "Belt")
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
			if (influence[i].getType() == "Wisdom" ||
				influence[i].getType() == "Charisma" ||
				influence[i].getType() == "Dexterity" ||
				influence[i].getType() == "Attack bonus" ||
				influence[i].getType() == "Defence bonus" ||
				influence[i].getType() == "Intelligence"||
				influence[i].getType() == "Armor class")
			{
				return false;
			}
		}
	}
	else if (type == "Boots")
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
			if (influence[i].getType() == "Strength" ||
				influence[i].getType() == "Constitution" ||
				influence[i].getType() == "Wisdom" ||
				influence[i].getType() == "Charisma" ||
				influence[i].getType() == "Attack bonus" ||
				influence[i].getType() == "Defence bonus" ||
				influence[i].getType() == "Intelligence")
			{
				return false;
			}
		}
	}
	else if (type == "Weapon")
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
			if (influence[i].getType() == "Strength" ||
				influence[i].getType() == "Constitution" ||
				influence[i].getType() == "Wisdom" ||
				influence[i].getType() == "Charisma" ||
				influence[i].getType() == "Armor class" ||
				influence[i].getType() == "Dexterity" ||
				influence[i].getType() == "Intelligence")
			{
				return false;
			}
		}
	}
	else //Unknown Item type.
	{
		return false;
	}
	return true;
}
