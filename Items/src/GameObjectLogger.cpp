#include "GameObjectLogger.h"
#include "GameLogger.h"
#include <iostream>
using namespace std;

//! default constructor
GameObjectLogger::GameObjectLogger() 
{
	this->showLog = true;
};

//! toggle function
//! @brief turns GameObjectLogger on and off.
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

//! UpdateSetup function
//! @param id id of the map that was setup.
void GameObjectLogger::UpdateSetup(int id)
{
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("Object on map #" + std::to_string(id) + "setup.");
	}
}

//! UpdateMap function
//! @param id id of map that was loaded
void GameObjectLogger::UpdateMap(int id)
{
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("Loaded map #" + std::to_string(id));
	} 
}

//! UpdateTurn function
//! @character name of character who's turn it is.
void GameObjectLogger::UpdateTurn(string character)
{
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("It is now " + character + "'s turn.");
	}
}

//! UpdateEnd function
//! @param won Did the player win when they won?
void GameObjectLogger::UpdateEnd(bool won)
{
	if (showLog)
	{
		if (won)
		{
			GameLogger::getInstance()->writeLine("You won the game, congradulations! Thanks For Playing.");
		}
		else
		{
			GameLogger::getInstance()->writeLine("Better luck next time! Thanks For Playing.");
		}
	}
}

GameObjectLogger* GameObjectLogger::instance;

//! getInstance function
//! @brief gets singleton instance.
GameObjectLogger* GameObjectLogger::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameObjectLogger();
	}
	return instance;
}
