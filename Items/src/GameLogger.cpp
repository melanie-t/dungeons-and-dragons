#include <iostream>
#include "GameLogger.h"

GameLogger::GameLogger()
{
	this->lineNum = 0;
	init();
}

void GameLogger::draw(sf::RenderWindow* window)
{
	window->draw(logBox);
	window->draw(logText);
}

void GameLogger::writeLine(string line)
{
	if (lineNum%MAX_LINE == 0)
	{
		logText.setString("-" + line);
	}
	else
	{
		string curString = logText.getString();
		logText.setString(curString + "\n-" + line);
	}
	lineNum++;
}

void GameLogger::init()
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Loading fonts failed" << std::endl;
		return; 
	}

	logText.setFont(font);

	logBox.setSize(sf::Vector2f(250, 10 * 32 + 8));
	logBox.setPosition(32 * 20 - 3, 242);
	logBox.setOutlineColor(sf::Color::Green);
	logBox.setOutlineThickness(3);

	logText.setString("No Log to show");
	logText.setCharacterSize(12);
	logText.setFillColor(sf::Color::Black);
	logText.setStyle(sf::Text::Bold);
	logText.setPosition(32 * 20, 242);
}
GameLogger* GameLogger::singleton;

GameLogger* GameLogger::getInstance()
{
	if (singleton == nullptr)
		singleton = new GameLogger();
	return singleton;
}