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

#pragma once
#ifndef FIGHTER_H
#define FIGHTER_H
#include "Character.h"

class Fighter: public Character {
public:
	Fighter();
	Fighter(int level);
	Fighter(int level, int str, int dex, int con, int intel, int wis, int cha);

	void displayStats();
	bool validateNewFighter();
};

#endif

