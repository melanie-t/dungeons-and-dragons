//! @file 
//! @brief Header file for the Item class  
//!
//! Libraries used: 
//! CMarkup, chosen due to ease of use to parse xml files
//! And it's extremely light, does not require, it's simply
//! .cpp/.h file that you add to the project(Markup.cpp + Markup.h), no .lib or .dll files.
#ifndef Item_h
#define Item_h

#include <string>
#include<vector>
#include "Enhancement.h"
#include "GameObject.h"
using namespace std;

//! class for the implementation of items wearable by a character
class Item : public GameObject
{
public:
	// Default constructor
	Item();
	// Constructor
	Item(int id, string type,vector<Enhancement> influences);
	Item(string type, vector<Enhancement> influences);
	//Destructor
	~Item();
	// method to get the type of the item
	string getType();
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();
	//levelRequirement
	//int getLevelRequirements(){ return levelRequirement; }
	//save item to file
	bool saveItem();
	//Creates Random Item based on level
	static Item randommize(int lvl);
	//Creates Item Class from File Load
	static Item load(int id);
private:
	int id;
	string type;
	//int levelRequirement;
	vector<Enhancement> influence;
};

//Item types
#define TYPE_HELMET "helmet"
#define TYPE_ARMOR "armor"
#define TYPE_SHIELD "shield"
#define TYPE_RING "ring"
#define TYPE_BELT "belt"
#define TYPE_BOOTS "boots"
#define TYPE_WEAPON "weapon"
#endif

