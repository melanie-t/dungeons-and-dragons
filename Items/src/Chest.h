/*@file Chest.h
*   @brief Implementation file for the Chest header
*	Chest takes in a parameter of item and checks for its type.
*	Displays the item type
*	Will implement randomization later
*	To call displayChest, use Chest::displayChest()
*/
#pragma once
#include "Item.h"

class Chest {
public:
	static void displayChest(Item* inputItem);
};