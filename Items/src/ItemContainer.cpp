//! @file 
//! @brief Implementation file for the ItemContainer class  
//!

#include "ItemContainer.h"
#include <sstream>

//! default constructor
ItemContainer::ItemContainer()
{
	Items = vector<Item>();
}

//! constructor that takes a vector of items as input to create an ItemContainer
//! @param containeritems: vector of items to put in the new container
ItemContainer::ItemContainer( vector<Item> containeritems)
{
	Items = containeritems;
}

//! method to get the items of the container
//! @return : return the vector of items contained in the ItemContainer
vector<Item> ItemContainer::getItems()
{
	int i = 0;
	vector <Item> inventory;
	for (int i = 0; i < Items.size(); i++)
	{
		if (Items[i].getID() != 0)
		{
			inventory.push_back(Items[i]);
		}
		i++;
	}
	return inventory;
	//Returning nothing
}

//! method to add an item to the item container
//! @param anitem : new item to put in the ItemContainer
void ItemContainer::addItem(Item anitem)
{
	Items.push_back(anitem);
}

//! method to return the item of a certain type contained in the ItemContainer
//! assumption: the container can only contain one element of each type
//! @param itemType : type of item to extract from the container
//! @return : item of the specified kind provided in input
Item ItemContainer::getItem(string itemType)
{
	for (int i = 0; i < Items.size(); i++)
		if (Items[i].getType() == itemType)
			return Items[i];
	return Item(); //return empty Item.
}

vector<int> ItemContainer::getIDs() {
	for (auto it = Items.begin(); it != Items.end(); ++it)
	{
		itemIDs.push_back(it->getID());
	}
	return itemIDs;
}

string ItemContainer::toString()
{
	std::ostringstream out;
	
	for (auto it = Items.begin(); it != Items.end(); ++it)
	{
		if (it->getID() != 0)
			out << it->toString();
	}

	return out.str();
}

Item ItemContainer::itemAtIndex(int i)
{
	Item item = Item(Items[i].getID(), Items[i].getType(), Items[i].getInfluences(), Items[i].getItemPath());
	return item;
}

void ItemContainer::removeItemAtIndex(int i)
{
	Items.erase(Items.begin() + i);
}

