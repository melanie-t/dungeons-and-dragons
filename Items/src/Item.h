//! @file 
//! @brief Header file for the Item class  
//!
#ifndef Item_h
#define Item_h

#include <string>
#include<vector>
#include "Enhancement.h"
using namespace std;

//! class for the implementation of items wearable by a character
class Item
{
public:
	// Default constructor
	Item();
	// Constructor
	Item(string type,vector<Enhancement> influences);
	// method to get the type of the item
	string getType();
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();
private:
	string type;
	vector<Enhancement> influence;
};
#endif

