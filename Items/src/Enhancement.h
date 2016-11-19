//! @file Enhancement.h
//! @brief Header file for the Enhancement class  
//!
#pragma once

#include <string>
#include<vector>

#include "EnhancementTypes.h"
using namespace std;

//! class for the implementation of an enhancement, i.e. a stat influenced by an item, as well as the bonus it gives
class Enhancement
{
public:
	// Default constructor
	Enhancement();
	// Constructor
	Enhancement(string type, int bonus);
	// method to get the type of the item
	string getType();
	// method to get the bonus of the type
	int getBonus();
	//setter for type
	void setType(string type);
	//setter for bonus
	void setBonus(int bonus);
private:
	string type;
	int bonus;
};

