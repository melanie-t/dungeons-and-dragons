//! @file GameLogger.h
//! @brief Header file for GameLogger Class
//!
//! Libraries used:
//! SMFL: The library was used to so that we can have a GUI for displaying maps.
//! It was the easiest library to use out of the ones we researched.
//! Standard Input/Output Streams Library <iostream> is necessary to display the stats of the character created, by using cout
//! Statndard vector library was used so to facillitate dynamic arrays.

#pragma once

#include <SFML\Graphics.hpp>
#include <string>
using namespace std;

class GameLogger
{
private:
	void init();
	int lineNum;
	sf::Text logText;
	sf::Font font;
	sf::RectangleShape logBox;

	static GameLogger* singleton;
	const int MAX_LINE = 20;

public:
	GameLogger();
	void draw(sf::RenderWindow* window);
	void writeLine(string line);
	//instance
	static GameLogger* getInstance();
};