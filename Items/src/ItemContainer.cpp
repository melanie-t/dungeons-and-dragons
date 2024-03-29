//! @file 
//! @brief Implementation file for the ItemContainer class  
//!

#include "ItemContainer.h"
#include <sstream>
#include <iostream>

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

//! getIDs function
//! @return array of Items IDs.
vector<int> ItemContainer::getIDs() {
	for (auto it = Items.begin(); it != Items.end(); ++it)
	{
		itemIDs.push_back(it->getID());
	}
	return itemIDs;
}

//! toString function
//! @brief Item Container to string.
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

//! itemAtIndex function
//! @brief gets items at index.
//! @brief i index of item.
Item ItemContainer::itemAtIndex(int i)
{
	Item item = Item(Items[i].getID(), Items[i].getType(), Items[i].getInfluences(), Items[i].getItemPath());
	return item;
}

//void ItemContainer::removeItemByID(int id)
//{
//	for (auto it = Items.begin(); it != Items.end(); ++it)
//	{
//		if (it->getID() == id)
//			*it = Item();
//	}
//}

//! removeItemAtIndex function
//! @brief removes item
//! @param i idnex of item.
void ItemContainer::removeItemAtIndex(int i)
{
	if (i == 0)
		Items.erase(Items.begin());
	else
		Items.erase(Items.begin() + i);
}

