//! @file Game.h
//! @brief Header file for Game Class
//!
//! Libraries used:
//! SMFL: The library was used to so that we can have a GUI for displaying maps.
//! It was the easiest library to use out of the ones we researched.
//! Standard Input/Output Streams Library <iostream> is necessary to display the stats of the character created, by using cout
//! Statndard vector library was used so to facillitate dynamic arrays.

#pragma once

#include <SFML\Graphics.hpp>
#include "TileMap.h"
#include "Map.h"
#include "CharacterLogger.h"
#include "MapLogger.h"
#include <iostream>
#include <vector>

class Game
{
private:
	//Initializes the window, the player, the font, the text, and creates the map.
	sf::RenderWindow* window;
	//sf::Texture playerTexture;
	//sf::Sprite player;
	sf::Sprite equipWindow;
	sf::Sprite equipSprite[7];
	sf::Texture equipTexture;

	sf::Sprite inventoryWindow;
	sf::Sprite inventorySprite[24];
	sf::Texture inventoryTexture;

	sf::Sprite chestWindow;
	sf::Sprite chestSprite[3];

	sf::Font font;
	sf::Text text;
	sf::Text enemyStats;
	sf::Text inventoryText;
	sf::Text equipText;
	sf::Text itemText;
	sf::Text turnText;
	sf::Text currentPosition;
	sf::RectangleShape textBox;
	sf::RectangleShape enemyStatsBox;
	sf::RectangleShape inventoryBox;
	sf::RectangleShape equipBox;
	sf::RectangleShape turnBox;
	sf::RectangleShape itemStatBox;

	TileMap map;
	std::vector<sf::Sprite> enemies;

	//Checks if the map is valid
	bool validMap();
	bool validate(int start, int end);
	std::vector<int> positionChecked;

	//Initializes the game
	bool init();

	//Creates a textbox
	void createText();

	//Main game loop
	void mainLoop();

	//Load the content
	void loadContent();
	
	//Updates player stats
	void updatePlayerStats();

	//Add items to GUI
	void drawItems();

	//Add equips to GUI
	void drawEquips();

	//Add Chest Items ot GUI
	void drawChest(Chest* chest);

	//Checks if items are clicked
	bool isSpriteClicked(sf::Sprite &sprite);

	//Draw onto the game
	void render();

	//Processes Inputs
	bool processInput();

	//Load textures
	void loadTextures(bool resetStart = true);

	//Updates the game
	bool update(sf::Event* evt);

	//Ends the game
	void endGame(bool won = true);
	void goToNewMap(Map* map); // for the future.

	//Variables for player to move in the map

	int lastKey;
	int width;
	int height;
	std::vector<int> level;

	Map* m_map;

	int attackNum;

	CharacterLogger characterlogger;
	MapLogger maplogger;

	bool openedChest = false;
	bool ended;
	bool inventoryOpen;
	bool equipOpen;
	bool itemStatOpen;
	bool showChest;

	Chest* selectedChest;
public:
	Game(unsigned int tileWidth, unsigned int tileHeight, Map* map);
	~Game();
	//Method to start the game
	void go();
};