//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"
#include "GameObject.h"
#include <iostream>

//! default constructor
Item::Item() : Item("", vector<Enhancement>())
{
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences) : GameObject(ITEM)
{
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
				influence[i].getType() == EN_DAMAGE_BONUS)
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
				influence[i].getType() == EN_DAMAGE_BONUS ||
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
				influence[i].getType() == EN_DAMAGE_BONUS ||
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
				influence[i].getType() == EN_DAMAGE_BONUS ||
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
				influence[i].getType() == EN_DAMAGE_BONUS ||
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

//The next two functions are helpers
//used in the randomize function
//below.They randomize the possibility
//Of getting a certain type of enhancement
//and the bonus amount of the enhancement
//by the level of the player.
inline bool giveEnh(int lvl)
{
	return (rand() % lvl == 0);
}

inline int givePlusFiveBonus(int lvl)
{
	if ((rand() % (lvl*lvl)) == 0) return 5;
	else return 1;
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

	// For now, randomly generated items will not have enhancements.
	// Because this will take a while to do.

	vector<Enhancement> enh;

	//50/50 chance of getting enhancement
	bool addEnhance = (rand() % 2 == 1);

	if (addEnhance)
	{
		//Add random enhancements that make sure
		//That make the item is valid
		if (type == TYPE_HELMET)
		{
			//3 is the number of types enhancements
			//valid for helmet items
			//If there's a better way of doing this,
			//I can't think of it. May change in the future.
			for (int i = 0; i != 3; i++)
			{
				// Make the chance of giving this type of bonus
				// and the probability of getting a +5 bonus 
				// depend on the level requirement.
				// Higher level are less lightly to get good
				// enhancements.
				bool bonusFive = (rand() % (lvl*lvl) == 0);

				if (giveEnh(lvl))
				{
					switch (i)
					{
					case 0: //intel
					{
						Enhancement enhancement(EN_INTELLIGENCE, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 1: //wisdom
					{
						Enhancement enhancement(EN_WISDOM, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 2: //armor class
					{
						Enhancement enhancement(EN_ARMOR_CLASS, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					}
				}
			}
		}
		else if (type == TYPE_ARMOR || type == TYPE_SHIELD)
		{
			Enhancement enhancement(EN_ARMOR_CLASS, givePlusFiveBonus(lvl));
			enh.push_back(enhancement);
		}
		else if (type == TYPE_RING)
		{
			//3 is the number of types enhancements
			//valid for helmet items
			//If there's a better way of doing this,
			//I can't think of it. May change in the future.
			for (int i = 0; i != 5; i++)
			{
				// Make the chance of giving this type of bonus
				// and the probability of getting a +5 bonus 
				// depend on the level requirement.
				// Higher level are less lightly to get good
				// enhancements.
				bool bonusFive = (rand() % (lvl*lvl) == 0);

				if (giveEnh(lvl))
				{
					switch (i)
					{
					case 0: //strength
					{
						Enhancement enhancement(EN_STRENGTH, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 1: //wisdom
					{
						Enhancement enhancement(EN_WISDOM, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 2: //armor class
					{
						Enhancement enhancement(EN_ARMOR_CLASS, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 3: //cons
					{
						Enhancement enhancement(EN_CONSTITUTION, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 4: //charaisma
					{
						Enhancement enhancement(EN_CHARISMA, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					}
				}
			}
		}
		else if (type == TYPE_BELT)
		{
			//3 is the number of types enhancements
			//valid for helmet items
			//If there's a better way of doing this,
			//I can't think of it. May change in the future.
			for (int i = 0; i != 2; i++)
			{
				// Make the chance of giving this type of bonus
				// and the probability of getting a +5 bonus 
				// depend on the level requirement.
				// Higher level are less lightly to get good
				// enhancements.
				bool bonusFive = (rand() % (lvl*lvl) == 0);

				if (giveEnh(lvl))
				{
					switch (i)
					{
					case 0: //strength
					{
						Enhancement enhancement(EN_STRENGTH, givePlusFiveBonus(lvl));
						enh.push_back(enhancement); 
						break;
					}
					case 1: //cons
					{
						Enhancement enhancement(EN_CONSTITUTION, givePlusFiveBonus(lvl));
						enh.push_back(enhancement); 
						break;
					}
					}
				}
			}
		}
		else if (type == TYPE_BOOTS)
		{
			//3 is the number of types enhancements
			//valid for helmet items
			//If there's a better way of doing this,
			//I can't think of it. May change in the future.
			for (int i = 0; i != 2; i++)
			{
				// Make the chance of giving this type of bonus
				// and the probability of getting a +5 bonus 
				// depend on the level requirement.
				// Higher level are less lightly to get good
				// enhancements.
				bool bonusFive = (rand() % (lvl*lvl) == 0);

				if (giveEnh(lvl))
				{
					switch (i)
					{
					case 0: //armor class
					{
						Enhancement enhancement(EN_ARMOR_CLASS, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 1: //dexterity
					{
						Enhancement enhancement(EN_DEXTERITY, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					}
				}
			}
		}
		else if (type == TYPE_WEAPON)
		{
			//3 is the number of types enhancements
			//valid for helmet items
			//If there's a better way of doing this,
			//I can't think of it. May change in the future.
			for (int i = 0; i != 2; i++)
			{
				// Make the chance of giving this type of bonus
				// and the probability of getting a +5 bonus 
				// depend on the level requirement.
				// Higher level are less lightly to get good
				// enhancements.
				bool bonusFive = (rand() % (lvl*lvl) == 0);

				if (giveEnh(lvl))
				{
					switch (i)
					{
					case 0: //atk bon
					{
						Enhancement enhancement(EN_ATTACK_BONUS, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					case 1: //damage bonus
					{
						Enhancement enhancement(EN_DAMAGE_BONUS, givePlusFiveBonus(lvl));
						enh.push_back(enhancement);
						break;
					}
					}
				}
			}
		}
	}

	Item item(type, enh);

	return item;
}
