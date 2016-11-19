//! @file Enemy.h
//! @brief Header file for the Enemy class  
//! Creates an enemy (Character) by randomizing stats
#pragma once

#include "Character.h"

//This is BAD. find a way to change it later.
class Friend : public Character, public GameObject
{
public:
	Friend();
	Friend(int level, int str, int dex, int con, int intel, int wis, int cha);

	static Friend* randomize(Character* character);
};