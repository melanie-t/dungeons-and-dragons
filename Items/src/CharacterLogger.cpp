//! @file CharacterLogger.cpp 
//! @brief Implementation file for the Character class  
//!

#include "CharacterLogger.h"
#include "GameLogger.h"
#include "Character.h"
#include <iostream>
using namespace std;

//! DEFAULT CONSTRUCTOR
CharacterLogger::CharacterLogger()
{
	this->showLog = true;
};

//! toggle function
//! toggles logger on/off.
void CharacterLogger::toggle() 
{
	if (showLog) 
	{
		GameLogger::getInstance()->writeLine("Character Logger turned off.");
		showLog = false;
	}
	else 
	{
	
		GameLogger::getInstance()->writeLine("Character Logger turned on.");
		showLog = true;
	}
}

//reacts to Observable class notify
void CharacterLogger::Update(string attacker, string target, bool succeed)
{
	//calls the method in the class which displys the state of the object
	if (showLog) 
	{
		if (succeed)
		{
			GameLogger::getInstance()->writeLine(attacker + " attacked " + target + " and succeded!");
		}
		else
		{
			GameLogger::getInstance()->writeLine(attacker + " attacked " + target + " and failed. =(");
		}
		//subject->displayCurrentState();
	}
}