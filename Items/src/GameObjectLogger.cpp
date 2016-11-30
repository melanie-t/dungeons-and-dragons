#include "GameObjectLogger.h"
#include "GameLogger.h"
#include <iostream>
using namespace std;

GameObjectLogger::GameObjectLogger() 
{
	this->showLog = true;
};

//toggles loggin of game data
void GameObjectLogger::toggle() {
	if (showLog) 
	{
		GameLogger::getInstance()->writeLine("Game Object Logger turned off.");
		showLog = false;
	}
	else 
	{
		GameLogger::getInstance()->writeLine("Game Object Logger turned on.");
		showLog = true;
	}
}

//reacts to Observable class notify
void GameObjectLogger::UpdateTurn(string character)
{
	//calls the method in the class which displys the state of the object
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("It is now " + character + "'s turn.");
	}
};

GameObjectLogger* GameObjectLogger::instance;

GameObjectLogger* GameObjectLogger::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameObjectLogger();
	}
	return instance;
}
