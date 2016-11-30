//! @file DiceLogger.cpp 
//! @brief Implementation file for the Character class  
//!
#include "DiceLogger.h"
#include "Dice.h"
#include "GameLogger.h"
using namespace std;

//! defualt constructor.
DiceLogger::DiceLogger() 
{
	this->showLog = true;
};

//! toggle function
//! toggles DiceLogger on/off
void DiceLogger::toggle()
{
	if (showLog) 
	{
		GameLogger::getInstance()->writeLine("Dice Logger turned off.");
		showLog = false;
	}
	else 
	{
		GameLogger::getInstance()->writeLine("Dice Logger turned on.");
		showLog = true;
	}
}

//! Update function
//! @brief roll roll notation
//! @param result result of roll
void DiceLogger::Update(string roll, int result)
{
	//calls the method in the class which displys the state of the object
	if (showLog) 
	{
		GameLogger::getInstance()->writeLine("A " + roll + " roll resulted in " + std::to_string(result));
	}
};

DiceLogger* DiceLogger::instance;

//! getInstance function
//! @brief gets singleton instance.
DiceLogger* DiceLogger::getInstance()
{
	if (instance == nullptr)
		instance = new DiceLogger();
	return instance;
}

