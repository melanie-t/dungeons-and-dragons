/** @file Fighter.h
* @brief Header file for the Fighter class
* @author Melanie Taing
* @date 10/21/2016
*
* Fighter's main abilities are Strength, Dexterity and Constitution.
* Fighter relies heavily on the methods found in Character.h: statGenerator and abilityModifier.
* Fighter creation is done by a) default as level 1, b) inputting a level, c) inputting specific stats and level
*
* The libraries used are:
*	1. Standard Input/Output Streams Library <iostream> is necessary to 
*	   display the stats of the character created, by using cout
*/

#pragma 

#include "Character.h"
#include "GameObject.h"
#include "ItemContainer.h"

class Fighter: public Character, public GameObject {
public:
	Fighter();
	Fighter(string name);
	Fighter(string name, int level, int str, int dex, int con, int intel, int wis, int cha, int hp, 
		vector <ItemContainer> backpack, vector <ItemContainer> equips);
	bool validateNewFighter();
};

