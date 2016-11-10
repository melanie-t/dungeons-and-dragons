//! @file 
//! @brief Header file for the Enemy class  
//!
#include "Character.h"

//This is BAD. find a way to change it later.
class Enemy : public Character, public GameObject 
{
public:
	Enemy();
	Enemy(int level, int str, int dex, int con, int intel, int wis, int cha);
	
	static Enemy* randomize(Character* character);
};