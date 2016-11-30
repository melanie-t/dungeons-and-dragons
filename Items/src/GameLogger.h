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