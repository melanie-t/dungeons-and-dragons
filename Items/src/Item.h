//! @file 
//! @brief Header file for the Item class  
//!
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
	Item(string type,vector<Enhancement> influences);
	//Destructor
	~Item();
	// method to get the type of the item
	string getType();
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();
	//levelRequirement
	int getLevelRequirements(){ return levelRequirement; }
	//Creates Random Item based on level
	static Item randommize(int lvl);
private:
	string type;
	int levelRequirement;
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

