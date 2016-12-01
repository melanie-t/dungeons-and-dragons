//! @file Enemy.h
//! @brief Header file for the Enemy class  
//! Creates an enemy (Character) by randomizing stats
#pragma once

#include "Character.h"

class Enemy : public Character, public GameObject 
{
public:
	Enemy();
	Enemy(int level, int str, int dex, int con, int intel, int wis, int cha);
	
	static Enemy* randomize(Character* character);
};