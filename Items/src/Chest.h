/*@file Chest.h
*   @brief Header file for Chest
*	Chest takes in a parameter of item and checks for its type.
*	Displays a picture of the inputted item type
*	To call displayChest, use Chest::displayChest()
*/
#pragma once
#include "ItemContainer.h"

class Chest 
{
public:
	static void displayChest(Item* inputItem);

private:
	ItemContainer chestItems;
};