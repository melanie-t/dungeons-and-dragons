//! @file 
//! @brief Header file for the Enhancement class  
//!
#ifndef Enhancement_h
#define Enhancement_h

#include <string>
#include<vector>
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
private:
	string type;
	int bonus;
};

#endif

