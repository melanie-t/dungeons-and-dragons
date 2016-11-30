#include "DiceLogger.h"
#include "Dice.h"
#include "GameLogger.h"
using namespace std;

DiceLogger::DiceLogger() 
{
	this->showLog = true;
};

//toggles loggin of game data
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

//reacts to Observable class notify
void DiceLogger::Update(string roll, int result)
{
	//calls the method in the class which displys the state of the object
	if (showLog) 
	{
		GameLogger::getInstance()->writeLine("A " + roll + " roll resulted in " + std::to_string(result));
	}
};

DiceLogger* DiceLogger::instance;

DiceLogger* DiceLogger::getInstance()
{
	if (instance == nullptr)
		instance = new DiceLogger();
	return instance;
}

