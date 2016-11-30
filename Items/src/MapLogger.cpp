#include "MapLogger.h"
#include "Map.h"
#include "GameLogger.h"
using namespace std;

//! default constructor
MapLogger::MapLogger() 
{
	this->showLog = true;
};

//! toggle function
//! @brief toggle MapLogger on/off
void MapLogger::toggle() 
{
	if (showLog) 
	{
		GameLogger::getInstance()->writeLine("Map Logger was turned off.");
		showLog = false;
	}
	else
	{
	
		GameLogger::getInstance()->writeLine("Map Logger was turned on.");
		showLog = true;
	}
}

//! Update function
//! @param character name of character
//! @param move type of move.
void MapLogger::Update(string character, PlayerMove move) {
	//calls the method in the class which displys the state of the object
	if (showLog) 
	{
		switch (move)
		{
		case PlayerMove::DOWN:
			{
				GameLogger::getInstance()->writeLine(character + " moved down.");
				break;
			}
		case PlayerMove::LEFT:
		{
			GameLogger::getInstance()->writeLine(character + " moved left.");
			break;
		}
		case PlayerMove::RIGHT:
		{
			GameLogger::getInstance()->writeLine(character + " moved right.");
			break;
		}
		case PlayerMove::UP:
		{
			GameLogger::getInstance()->writeLine(character + " moved up.");
			break;
		}
		}
	}
};
