//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"
#include "GameObject.h"
#include "Markup.h"
#include <iostream>

//! default constructor
Item::Item() : Item(0, "", vector<Enhancement>())
{
}


//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! this constructor sets the item id to 0. eg. not caring.
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences) : Item(0, type_name, influences)
{
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param id : id of the item.
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(int id, string type_name, vector<Enhancement> influences) : GameObject(ITEM)
{
	this->id = id;
	this->type = type_name;
	this->influence = influences;
}

//! Destructor For the Item class
//! Empties the enhacement container
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

//! saveItem function
//! @brief saves the item class as a xml file using Cmarkup
bool Item::saveItem()
{
	//Hopefully this shit worksssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
	CMarkup xml;

	//xml.SetDoc("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n");
	xml.AddElem("item");
	xml.IntoElem();
	xml.AddElem("id", id);
	xml.AddElem("type", this->type);
	xml.AddElem("enhancements");
	xml.IntoElem();
	for (int i = 0; i != influence.size(); i++)
	{
		xml.AddElem("enhancement");
		xml.IntoElem();
		xml.AddElem("type", influence[i].getType());
		xml.AddElem("bonus", influence[i].getBonus());
		xml.OutOfElem();
	}
	xml.OutOfElem();

	char di[20];
	sprintf_s(di, 20, "items/%d.xml", id);
	xml.Save(string(di));
	return true;

}

//! function that randomly chooses
//! if we should give an enhancement
//! The chance of giving an enhancement
//! is 1/(the level of the character)
//! @param lvl level of player
inline bool giveEnh(int lvl)
{
	return (rand() % lvl == 0);
}

//! function that randomly chooses
//! the bonus amount for an enhancement (+1 or +5)
//! The chance of giving a +5 enhancement
//! is 1/(the level of the character)^2
//! @param lvl level of player
inline int givePlusFiveBonus(int lvl)
{
	if ((rand() % (lvl*lvl)) == 0) return 5;
	else return 1;
}

//! function that creates a randomly generated item.
//! The item is created according to the level of the character
//! @param lvl the level of the character
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
	//item.levelRequirement = lvl;

	return item;
}

static Item load(int id)
{
	char di[20];
	sprintf_s(di, 20, "Items/%d.xml", id);
	CMarkup xml;
	if (xml.Load(string(di)))
	{
		xml.FindElem();
		if (xml.GetTagName() != "item")
		{
			cout << "This file is not a item." << endl;
			cout << xml.GetTagName() << endl;
		}
		else
		{
			xml.IntoElem();
			vector<Enhancement> enhancements;
			int id;
			string type;

			while (xml.FindElem())
			{
				string s = xml.GetTagName();
				if (s == "id")
				{
					id = atoi(xml.GetData().c_str());
				}
				else if (s == "type")
				{
					type = xml.GetData();
				}
				else if (s == "enhancements")
				{
					xml.IntoElem();
					while (xml.FindElem())
					{
						xml.IntoElem();
						while (xml.FindElem())
						{
							string enh_type;
							int bonus;
							string tag = xml.GetTagName();
							if (tag == "type")
							{
								enh_type = xml.GetData();
							}
							else if (tag == "bonus")
							{
								bonus = atoi(xml.GetData().c_str());
							}
							Enhancement enh(enh_type, bonus);
							enhancements.push_back(enh);
						}
					}
				}
				xml.OutOfElem();
				return Item(id, type, enhancements);
			}

			xml.OutOfElem();
		}
		return Item(); //return empty item.
	}
	else
	{
		cout << xml.GetError() << endl;
		return Item(); //return empty item.
	}
}

int Item::getItemType() {
	string itemType = getType();
	if (itemType.compare("armor"))
		return 1;
	else if (itemType.compare("belt"))
		return 2;
	else if (itemType.compare("helmet"))
		return 3;
	else if (itemType.compare("ring"))
		return 4;
	else if (itemType.compare("shield"))
		return 5;
	else if (itemType.compare("boots"))
		return 6;
	else if (itemType.compare("weapon"))
		return 7;
}
