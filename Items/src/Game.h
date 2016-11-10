#include <SFML\Graphics.hpp>
#include "TileMap.h"
#include <iostream>

class Game{
private:
	//Initializes the window, the player, the font, the text, and creates the map.
	sf::RenderWindow* window;
	sf::Texture playerTexture;
	sf::Sprite player;
	sf::Font font;
	sf::Text text;
	sf::Text currentPosition;
	sf::RectangleShape textBox;
	TileMap map;

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

	//Draw onto the game
	void render();

	//Processes Inputs
	void processInput();

	//Load textures
	void loadTextures();

	//Updates the game
	void update(sf::Event evt);

	//Variables for player to move in the map
	int currentPos;
	int lastKey;
	int width;
	int height;
	std::vector<int> level;

public:
	Game(unsigned int tileWidth, unsigned int tileHeight, std::vector<int> level);
	~Game();
	//Method to start the game
	void go();
};