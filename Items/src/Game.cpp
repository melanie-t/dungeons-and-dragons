//! @file Game.cpp
//! @brief Implementation file for the Game class  
//!
#include "Game.h"
#include "Map.h"
#include "Chest.h"
#include <SFML\Graphics.hpp>

//! Constructor for Game class
//! @param tileWidth : width of the tile used
//! @param tileHeight : height of the tiled used
//! @param map : Map object that we are loading
Game::Game(unsigned int tileWidth, unsigned int tileHeight, Map* map){
	this->width = tileWidth;
	this->height = tileHeight;
	this->level = map->outputMap();
	this->m_map = map;
}

//! Deconstructor for Game class
//! @brief Deletes the window and map
Game::~Game(){
	//Destroys the window
	delete window;
	delete m_map;
}

//! validMap function
//! @brief tells us if the map created is valid or not (based on conditions))
//! @return true if the map is valid/fulfills conditions
bool Game::validMap(){
	int startPoint = -1;
	int endPoint = -1;
	//finds the starting point in the array
	for (int i = 0; i < level.size(); ++i){
		if (level[i] == 7){
			startPoint = i;
			break;
		}
	}
	if (startPoint == -1)
	{
		return false;
	}
	else{
		//Finds the ending point in the array
		for (int i = 0; i < level.size(); ++i){
			if (level[i] == 6){
				endPoint = i;
				break;
			}
		}
		if (endPoint == -1)
		{
			return false;
		}
		else{
			return validate(startPoint, endPoint);
		}
	}
}

//! validate function
//! @brief contains the map validity conditions
//! @param start : beginning of map
//!	@param end : end of map
//! @return true if the map is valid
bool Game::validate(int start, int end){
	if (start == end)
		return true;
	//checks if its out of bounds
	else if (start < 0 || start > (level.size() - 1))
	{
		return false;
	}
	//Checks if the position has already been checked
	else if (std::find(positionChecked.begin(), positionChecked.end(), start) != positionChecked.end())
	{
		return false;
	}
	//Checks if its walkable
	else if (level[start] == 1 || level[start] == 2 || level[start] == 4 || level[start] == 8 || level[start] == 9)
	{
		return false;
	}
	//Else checks right,left,top,bottom
	else{
		positionChecked.push_back(start);
		return validate(start + 1, end) || validate(start - 1, end) || validate(start - width, end) || validate(start + width, end);
	}
}

//! init function
//! @brief intializes the game window 
//! @return true if game window was initialized successfully
bool Game::init(){
	// col and row and reversed.
	window = new sf::RenderWindow(sf::VideoMode(m_map->getNumRows()*32, m_map->getNumCol()*32 + 250), "D&D 2.0"); //fix the w, h with size of map
	//Puts the window at the top left of the monitor screen
	window->setPosition(sf::Vector2i(0, 0));
	//Prevent multiple key presses
	window->setKeyRepeatEnabled(false);
	if (!window)
		return false;
	return true;
}

//! processInput function
//! @brief keeps track of event where X is pressed to close window
void Game::processInput(){
	//To close the window with x
	sf::Event evt;
	//In case there were several events happenning
	while (window->pollEvent(evt)){
		if (evt.type == sf::Event::Closed)
		{
			window->close();
		}
		update(evt);
	}
}

//! update function
//! @brief moves character based on key press (arrow keys)
//! Interacts with objects:
//! Will not walk through wall, water, tree
//! Opens chest once
//! @param evt : event from sfml class
void Game::update(sf::Event evt){
	//Register what was the last key released
	if (evt.type == sf::Event::KeyReleased){
		lastKey = evt.key.code;
	}
	switch (evt.type){
	case sf::Event::KeyPressed:
		if (evt.key.code == sf::Keyboard::Up){
			//sets the player looking upwards
			player.setTextureRect(sf::IntRect(20, 0, 20, 26));
			if (lastKey != evt.key.code)
			{

			}
			else{
				//Checks if space occupied or out of bounds
				if ((currentPos - width < 0))
					break;
				else if (level[currentPos - width] == 1) //1 is water
					break;
				else if (level[currentPos - width] == 2) //2 is tree
					break;
				else if (level[currentPos - width] == 9) //9 is item/chest
				{
					if (!openedChest) {
						Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
						openedChest = true;
					}
					else
						break;
				}
				else if (level[currentPos - width] == 6) // end
				{
					//YOU WIN!!!
					endGame();
				}
				player.move(0, -32);
				currentPos -= width;
			}
			break;
		}
		if (evt.key.code == sf::Keyboard::Down){
			//sets the player looking downwards
			player.setTextureRect(sf::IntRect(0, 0, 20, 26));
			if (lastKey != evt.key.code)
			{
				break;
			}
			else{
				//Checks if space occupied or out of bounds
				if ((currentPos + width >= level.size()))
					break;
				else if (level[currentPos + width] == 1) //1 is water
					break;
				else if (level[currentPos + width] == 2) //2 is tree
					break;
				else if (level[currentPos + width] == 9) //9 is item/chest
				{
					if (!openedChest) {
						Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
						openedChest = true;
					}
					else
						break;
				}
				else if (level[currentPos + width] == 6) // end
				{
					//m_map->getPlayer()->setLevel(m_map->getPlayer()->getLevel() + 1);
					endGame();
				}
				player.move(0, +32);
				currentPos += width;
			}
			break;
		}
		if (evt.key.code == sf::Keyboard::Left){
			//sets the player looking left
			player.setTextureRect(sf::IntRect(40, 0, 20, 26));
			if (lastKey != evt.key.code)
			{

			}
			else{
				//Checks if space occupied or out of bounds
				if ((currentPos) % width <= 0)
					break;
				else if (level[currentPos - 1] == 1) //1 is water
					break;
				else if (level[currentPos - 1] == 2) //2 is tree
					break;
				else if (level[currentPos - 1] == 9) //9 is item/chest
				{
					if (!openedChest) {
						Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
						openedChest = true;
					}
					else
						break;
				}
				else if (level[currentPos - 1] == 6) // end
				{
					//m_map->getPlayer()->setLevel(m_map->getPlayer()->getLevel() + 1);
					endGame(); // temp
				}
				player.move(-32, 0);
				currentPos--;
			}
			break;
		}
		if (evt.key.code == sf::Keyboard::Right){
			//sets the player looking upwards
			player.setTextureRect(sf::IntRect(60, 0, 20, 26));
			if (lastKey != evt.key.code)
			{
			}
			else{
				//Checks if space occupied or out of bounds
				if ((currentPos - 1) % width >= (width-2))
					break;
				else if (level[currentPos + 1] == 1) //1 is water
					break;
				else if (level[currentPos + 1] == 2) //2 is tree
					break;
				else if (level[currentPos +1] == 9) //9 is item/chest
				{
					if (!openedChest) {
						Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
						openedChest = true;
					}
					else
						break;
				}
				else if (level[currentPos + 1] == 6) // end
				{
					//m_map->getPlayer()->setLevel(m_map->getPlayer()->getLevel() + 1);
					endGame(); // temp.
				}
				player.move(+32, 0);
				currentPos++;
			}
			break;
		}
	default:
		break;
	}
}

//! endGame function
//! @brief Ends the game by showing the player they won.
//! Levels up the Character by 1 on each ability score and level and displays new stats
//! Closes the Game window after 6 seconds to be able to see the changes
void Game::endGame()
{
	m_map->getPlayer()->levelUp();

	text.setString(m_map->getPlayer()->statString());
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, (height * 32 + 8));

	sf::Texture winner;
	winner.loadFromFile("Win.png");
	sf::Sprite win(winner);
	win.setPosition(10, 10);
	window->clear(sf::Color(255,255,255,255));
	window->draw(text);
	window->draw(win);
	window->display();
	sf::sleep(sf::milliseconds(6000)); // for now. have to change later to exit only when escape/enter
	window->close();
}

//! loadTextures function
//! @brief loads up the sprites for the map 
//! Player sprite and map sprites
//! Exits if unable to load either
void Game::loadTextures(){
	//Loads the player's texture
	if (!playerTexture.loadFromFile("hero.png"))
		EXIT_FAILURE;
	//Creates the map according to the level
	else if (!map.load("bkrd.png", sf::Vector2u(32, 32), level, width, height))
		EXIT_FAILURE;
	//Sets the player's texture
	player.setTexture(playerTexture);
	player.setTextureRect(sf::IntRect(0, 0, 20, 26));
	//Sets the player to the starting position
	for (int i = 0; i < width * height; ++i){
		if (level[i] == 7){
			currentPos = i;
			break;
		}
	}
	player.setPosition((currentPos % width) * 32 + 5, (currentPos / width) * 32 + 3);
	createText();
}

//! createText function
//! @brief Initializes text that displays in Game GUI
//! Loads font and intializes text for character stats display
//! Creates textbox with white background for character stats display
void Game::createText(){
	//Loads the text's fonts
	if (!font.loadFromFile("font.ttf")){
		std::cout << "Loading fonts failed" << std::endl;
		EXIT_FAILURE;
	}
	//sets the text's font
	text.setFont(font);
	currentPosition.setFont(font);

	std::string heroName = m_map->getPlayer()->getName();

	//Initializes the text
	text.setString(m_map->getPlayer()->statString());
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, (height * 32 + 8));

	//Initializes the text of current position
	currentPosition.setCharacterSize(12);
	currentPosition.setFillColor(sf::Color::Black);
	currentPosition.setStyle(sf::Text::Bold);
	currentPosition.setPosition(20, (height * 32 + 56));

	//Initializes the box in which the text will be written in
	textBox.setSize(sf::Vector2f(150, 240));
	textBox.setPosition(5, height * 32 + 5);
	textBox.setOutlineColor(sf::Color::Green);
	textBox.setOutlineThickness(3);
}

//! render function
//! @brief Draws everything onto the window
void Game::render(){
	//currentPosition.setString("Current position: " + std::to_string((currentPos - 1) % width));
	window->draw(map);
	window->draw(player);
	window->draw(textBox);
	window->draw(text);
	window->draw(currentPosition);
}

//! mainLoop function
//! @brief Runs program while window is open
void Game::mainLoop(){
	while (window->isOpen()){
		window->clear();
		render();
		processInput();
		window->display();
	}
}

//! go function
//! @brief Checks if the map is valid and able to open window
void Game::go(){
	if (!init())
		throw "Could not initialize the window";
	if (validMap()){
		//Loads the textures to use them first
		loadTextures();
		mainLoop();
	}
	else{
		std::cout << "Invalid Map";
		EXIT_FAILURE;
	}
}
