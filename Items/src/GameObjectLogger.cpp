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

void GameObjectLogger::UpdateSetup(int id)
{
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("Object on map #" + std::to_string(id) + "setup.");
	}
}

void GameObjectLogger::UpdateMap(int id)
{
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("Loaded map #" + std::to_string(id));
	} 
}

void GameObjectLogger::UpdateTurn(string character)
{
	if (showLog)
	{
		GameLogger::getInstance()->writeLine("It is now " + character + "'s turn.");
	}
}

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

GameObjectLogger* GameObjectLogger::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameObjectLogger();
	}
	return instance;
}
