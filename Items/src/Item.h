//! @file Item.h
//! @brief Header file for the Item class  
//!
//! Libraries used: 
//! CMarkup, chosen due to ease of use to parse xml files
//! And it's extremely light, does not require, it's simply
//! .cpp/.h file that you add to the project(Markup.cpp + Markup.h), no .lib or .dll files.
#pragma once

#include <string>
#include<vector>
#include "Enhancement.h"
#include "GameObject.h"
#include "ItemTypes.h"
#include "StatisticsHelper.h"
using namespace std;

//! class for the implementation of items wearable by a character
class Item
{
public:
	// Default constructor
	Item();
	// Constructor
	Item(string type_name, vector<Enhancement> influences);
	//Constructor to load items
	Item(int id, string type, vector<Enhancement> influences, string path);
	//Destructor
	~Item();
	// method to get the type of the item
	string getType();
	void setType(string type);
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();
	//levelRequirement
	//int getLevelRequirements(){ return levelRequirement; }
	//save item to file
	bool saveItem();
	//Creates Random Item based on level
	static Item* randommize(int lvl);
	//Creates Item Class from File Load
	static Item* load(int id);
	//Returns an integer for the type. Used by Chest.h to check which type it is
	//int getItemType();
	//add enhancment to influences
	void addEnhancement(Enhancement enh);
	//remove enhancement
	void removeEnhancement(string type);
	void setItemPath(string path);
	int getID();
	string toString();
	string enhancementString();

private:
	int id;
	string type;
	string itemPath = "Default item path";
	//int levelRequirement;
	vector<Enhancement> influence;
};

