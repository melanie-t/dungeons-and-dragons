//! @file 
//! @brief Header file for the Human Player Strategy class  
//!
//! The AgressiveStrategy, is a concrete strategy 
//! that determines the moves that an Enemy will take.
//!
//! Each player take a turn, where they choose to move or attack.
//! When you attack, the player rolls an d20 dice. Adding this value to the attack bonus
//! gives you the attack roll. If the atatck roll is higher than the target's armor class
//! Or the d20 roll is 20, then the attack hits if not, it misses. If the d20 roll is 1,
//! the attack is also a miss.
//! If the attack is a hit then the damage is equal to the [W] + damag bonus for those under
//! level 21, and 2[W] + damaga bonus for those above level 21. [W] depends on the weapon of choice.
//! For unarmed attack, [W] is a a 1d4 roll. For a short sword [W] is a 1d6 roll.
//!
//!
//! Libraries used: 
//! CMarkup, chosen due to ease of use to parse xml files
//! And it's extremely light, does not require, it's simply
//! .cpp/.h file that you add to the project(Markup.cpp + Markup.h), no .lib or .dll files.
//! SFML: Graphics library
//! For displaying character sprites and receives keyboard/mouse input.
#pragma once

#include "Strategy.h"

class HumanPlayerStrategy : public Strategy
{
public:
	int execute(pos characterPos, pos targetPos, std::vector<int> level, int width, int length, int lastkey = -1, sf::Event* evt = nullptr);
};