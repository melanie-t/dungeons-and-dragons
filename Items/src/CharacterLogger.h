//! @file CharacterLogger.h
//! @brief Header file for CharacterLogger Class
//!

#pragma once

#include "Observer.h"
#include <string>
using namespace std;

class CharacterLogger
{
public:
	CharacterLogger();
	void Update(string attacker, string target, bool succeed);
	void toggle();
private:
	bool showLog;
};
