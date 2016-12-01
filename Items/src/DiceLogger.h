//! @file DiceLogger.h
//! @brief Header file for DiceLogger Class
//!
#pragma once

#include <string>
using namespace std;

class DiceLogger 
{
public:
	DiceLogger();
	void Update(string roll , int result);
	void toggle();

	static DiceLogger* getInstance();

private:
	bool showLog;

	static DiceLogger* instance;
};
