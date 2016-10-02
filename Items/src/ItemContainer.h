//! @file 
//! @brief Header file for the ItemContainer class  
//!

#ifndef ItemContainer_h
#define ItemContainer_h

#include <string>
#include<vector>
using namespace std;
#include "Item.h"

//! Class that implements an item container
class ItemContainer
{
public:
	// Default constructor
	ItemContainer();
	// Constructor
	ItemContainer(vector<Item> items);
	// method to get the items of the container
	vector<Item> getItems();
	// method to add an item to the item container
	void addItem(Item anitem);
	// method to get an item from the item container
	Item getItem(string itemType);
private:
	vector<Item> Items;
};
#endif

