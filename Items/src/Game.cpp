//! @file Game.cpp
//! @brief Implementation file for the Game class  
//!
#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Map.h"
#include "Chest.h"
#include "TileTypes.h"
#include "Enemy.h"
#include "Friend.h"
#include "Door.h"
#include "Dice.h"
#include "HumanPlayerStrategy.h"
#include "PlayerActionTypes.h"
#include "MathHelper.h"

//! Constructor for Game class
//! @param tileWidth : width of the tile used
//! @param tileHeight : height of the tiled used
//! @param map : Map object that we are loading
Game::Game(unsigned int tileWidth, unsigned int tileHeight, Map* map){
	this->width = tileWidth;
	this->height = tileHeight;
	this->level = map->outputMap();
	this->m_map = map;
	this->ended = false;
}

//! Deconstructor for Game class
//! @brief Deletes the window and map
Game::~Game(){
	//Destroys the window & map
	delete window;
	//delete m_map;
}

//! validMap function
//! @brief tells us if the map created is valid or not (based on conditions))
//! @return true if the map is valid/fulfills conditions
bool Game::validMap(){
	int startPoint = -1;
	int endPoint = -1;
	//finds the starting point in the array
	for (unsigned int i = 0; i < level.size(); ++i){
		if (level[i] == TileTypes::START){
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
		for (unsigned int i = 0; i < level.size(); ++i){
			if (level[i] == TileTypes::END){
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
	else if (start < 0 || start >(level.size() - 1))
	{
		return false;
	}
	//Checks if the position has already been checked
	else if (std::find(positionChecked.begin(), positionChecked.end(), start) != positionChecked.end())
	{
		return false;
	}
	//Checks if its walkable
	else if (level[start] == TileTypes::WATER || level[start] == TileTypes::TREE || level[start] == TileTypes::CHEST)
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
	window = new sf::RenderWindow(sf::VideoMode(m_map->getWidth() * 32, m_map->getLength() * 32 + 250), "D&D 2.0");
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
		Character* character = m_map->getTurn();//static_cast<Character*>(m_map->getEnemies()[0]);
		//Character* character = m_map->getTurn();

		int action = character->getStrategy()->execute(character->getPosition(),
			m_map->getPlayer()->getPosition(), level, m_map->getWidth(), lastKey, &evt);

		/*int action = m_map->getPlayer()->getStrategy()->execute(m_map->getPlayer()->getPosition(), 
			m_map->getPlayer()->getPosition(), level, lastKey, &evt);*/

		int currentPos = character->getPosition().y*width + character->getPosition().x;

		switch (action)
		{
		case PlayerAction::MOVE_UP:
		{
			character->changeSprite(PlayerMove::UP);

			//Checks if space occupied or out of bounds
			if (character->getPosition().y <= 0) //todo change to character.
				break;
			else if (level[currentPos - width] == TileTypes::WATER) //1 is water
				break;
			else if (level[currentPos - width] == TileTypes::TREE) //2 is tree
				break;
			else if (level[currentPos - width] == TileTypes::CHEST) //9 is item/chest
			{
				if (!openedChest) {
					Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
					openedChest = true;
				}
				else
					break;
			}
			else if (level[currentPos - width] == TileTypes::END) // end
			{
				int x = currentPos % width;
				int y = currentPos / width - 1;

				Door* door = static_cast<Door*>(this->m_map->getObject(x, y));

				if (door != nullptr && m_map->getEnemies().empty() && character == m_map->getPlayer())
				{
					if (door->getDestination() != nullptr)
					{
						this->goToNewMap(door->getDestination());
					}
					else
					{
						endGame();
					}
					break;
				}
			}
			character->move(PlayerMove::UP);
			m_map->nextTurn();
			currentPos -= width;
			break;
		}
		case PlayerAction::MOVE_DOWN:
		{
			character->changeSprite(PlayerMove::DOWN);
			//player.setTextureRect(sf::IntRect(0, 0, 20, 26)); //Change Sprite
			//Checks if space occupied or out of bounds
			if (character->getPosition().y >= m_map->getLength() - 1)
				break;
			else if (level[currentPos + width] == TileTypes::WATER) //1 is water
				break;
			else if (level[currentPos + width] == TileTypes::TREE) //2 is tree
				break;
			else if (level[currentPos + width] == TileTypes::CHEST) //9 is item/chest
			{
				if (!openedChest) {
					Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
					openedChest = true;
				}
				else
					break;
			}
			else if (level[currentPos + width] == TileTypes::END) // end
			{
				//m_map->getPlayer()->setLevel(m_map->getPlayer()->getLevel() + 1);
				int x = currentPos % width;
				int y = currentPos / width + 1;
				Door* door = static_cast<Door*>(this->m_map->getObject(x, y));

				if (door != nullptr && m_map->getEnemies().empty() && character == m_map->getPlayer())
				{
					if (door->getDestination() != nullptr)
					{
						this->goToNewMap(door->getDestination());
					}
					else
					{
						endGame();
					}
					break;
				}
			}
			character->move(PlayerMove::DOWN);
			m_map->nextTurn();
			currentPos += width;
			break;
		}
		case PlayerAction::MOVE_LEFT:
		{
			character->changeSprite(PlayerMove::LEFT);
			//player.setTextureRect(sf::IntRect(40, 0, 20, 26)); //Change Sprite.
			//Checks if space occupied or out of bounds
			if (character->getPosition().x <= 0)
				break;
			else if (level[currentPos - 1] == TileTypes::WATER) //1 is water
				break;
			else if (level[currentPos - 1] == TileTypes::TREE) //2 is tree
				break;
			else if (level[currentPos - 1] == TileTypes::CHEST) //9 is item/chest
			{
				if (!openedChest) {
					Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
					openedChest = true;
				}
				else
					break;
			}
			else if (level[currentPos - 1] == TileTypes::END) // end
			{
				//m_map->getPlayer()->setLevel(m_map->getPlayer()->getLevel() + 1);
				int x = currentPos % width - 1;
				int y = currentPos / width;
				Door* door = static_cast<Door*>(this->m_map->getObject(x, y));

				if (door != nullptr && m_map->getEnemies().empty() && character == m_map->getPlayer())
				{
					if (door->getDestination() != nullptr)
					{
						this->goToNewMap(door->getDestination());
					}
					else
					{
						endGame();
					}
					break;
				}
			}
			//player.move(-32, 0);
			character->move(PlayerMove::LEFT);
			m_map->nextTurn();
			currentPos--;
			break;
		}
		case PlayerAction::MOVE_RIGHT:
		{
			character->changeSprite(PlayerMove::RIGHT);
			//player.setTextureRect(sf::IntRect(60, 0, 20, 26));
			//Checks if space occupied or out of bounds
			if (character->getPosition().x >= m_map->getWidth()-1)
			{
				break;
			}
			else if (level[currentPos + 1] == TileTypes::WATER) //1 is water
			{
				break;
			}
			else if (level[currentPos + 1] == TileTypes::TREE) //2 is tree
			{
				break;
			}
			else if (level[currentPos + 1] == TileTypes::CHEST) //9 is item/chest
			{
				if (!openedChest) {
					Chest::displayChest(Item::randommize(m_map->getPlayer()->getLevel()));
					openedChest = true;
				}
				else
					break;
			}
			else if (level[currentPos + 1] == TileTypes::END) // end
			{
				//m_map->getPlayer()->setLevel(m_map->getPlayer()->getLevel() + 1);
				int x = currentPos % width + 1;
				int y = currentPos / width;
				Door* door = static_cast<Door*>(this->m_map->getObject(x, y));

				if (door != nullptr && m_map->getEnemies().empty() && character == m_map->getPlayer())
				{
					if (door->getDestination() != nullptr)
					{
						this->goToNewMap(door->getDestination());
					}
					else
					{
						endGame();
					}
					break;
				}
			}
			//player.move(+32, 0);
			character->move(PlayerMove::RIGHT);
			m_map->nextTurn();
			currentPos++;
			break;
		}
		case PlayerAction::ATTACK:
		{
			//TODO: edit this.
			Dice dice;
			//int d20 = dice.roll("d20");
			//int attackRoll = m_map->getPlayer()->attackRoll(d20);
			//int index = m_map->getClosestEnemy(m_map->getPlayer());

			///These don't work.
			Enemy* enemy = m_map->getClosestEnemy(m_map->getPlayer());

			if (enemy != nullptr)
			{
				int distance = MathHelper::getDistance(m_map->getPlayer()->getPosition(), enemy->getPosition());

				//Character is in range. Must be 1 tile away.
				if (distance <= 1)
				{
					Dice dice;
					int d20 = dice.roll("1d20"); //dunno.
					int attackRoll = m_map->getPlayer()->attackRoll(d20);

					if ((attackRoll > enemy->getArmorClass() && d20 != 1) || d20 == 20)
					{
						// Every character is assumed to have a short sword
						int swordRoll = dice.roll("1d6");
						int strengthModifier = m_map->getPlayer()->abilityModifier(m_map->getPlayer()->getSTR());
						int damage = 0;

						//Formula for basic melee attack is:
						// 1[W] + strength modifier for under level 21.
						// 2[W] + strength modifier for level 21 and above.

						if (m_map->getPlayer()->getLevel() < 21) //Lower than 21
						{
							damage = swordRoll + strengthModifier;
						}
						else
						{
							damage = (2 * swordRoll) + strengthModifier;
						}

						enemy->hit(damage);

						cout << enemy->getHitPoints() << endl; //remains the same before change.
						if (enemy->getHitPoints() <= 0)
						{
							this->m_map->removeEnemy(enemy);
						}
					}
				}
			}
			m_map->nextTurn();
			break;
		}
		}
	if (sf::Event::MouseMoved)
	{
		int tileY = evt.mouseMove.y / 32;
		int tileX = evt.mouseMove.x / 32;

		if (tileX > 0 && tileY > 0)
		{

			if (this->m_map->getObject(tileX, tileY)->getObjectType() == OBJ_ENEMY)
			{
				Enemy* enemy = static_cast<Enemy*>(this->m_map->getObject(tileX, tileY));
				enemyStats.setString("Enemy" + enemy->statString());
			}
			else if (this->m_map->getObject(tileX, tileY)->getObjectType() == OBJ_FRIEND)
			{
				Friend* frien = static_cast<Friend*>(this->m_map->getObject(tileX, tileY));
				enemyStats.setString("Friend" + frien->statString());
			}
			else
			{
				//Don't show enemy stats.
				enemyStats.setString("Enemy/Friend");
			}
		}
	}
}

//! endGame function
//! @brief Ends the game by showing the player they won.
//! Levels up the Character by 1 on each ability score and level and displays new stats
//! Closes the Game window after 6 seconds to be able to see the changes
void Game::endGame()
{
	m_map->getPlayer()->levelUp();

	//window->display();
	ended = true;

	while (window->isOpen()){
		window->clear();

		text.setString(m_map->getPlayer()->statString());
		text.setCharacterSize(12);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
		text.setPosition(20, (height * 32 + 8));

		window->clear(sf::Color(255, 255, 255, 255));
		window->draw(text);

		processInput();
		window->display();
	}

	//sf::sleep(sf::milliseconds(6000)); // for now. have to change later to exit only when escape/enter
	//window->close();
}

//! loadTextures function
//! @brief loads up the sprites for the map 
//! Player sprite and map sprites
//! Exits if unable to load either
void Game::loadTextures(){
	//Loads the player's texture
	/*if (!playerTexture.loadFromFile("hero.png"))
		EXIT_FAILURE;
	//Creates the map according to the level
	else if (!map.load("bkrd.png", sf::Vector2u(32, 32), level, width, height))
		EXIT_FAILURE;
	//Sets the player's texture
	player.setTexture(playerTexture);
	player.setTextureRect(sf::IntRect(0, 0, 20, 26));*/
	//Sets the player to the starting position
	int currentPos = -1;
	for (int i = 0; i < width * height; ++i){
		if (level[i] == TileTypes::START){
			currentPos = i;
			break;
		}
	}
	map.load("bkrd.png", sf::Vector2u(32, 32), level, width, height);
	this->m_map->getPlayer()->setPosition((currentPos % width), (currentPos / width));
	this->m_map->getPlayer()->initSprite(CharacterSpriteType::S_PLAYER);

	for (Enemy* enemy : m_map->getEnemies())
	{
		enemy->initSprite(CharacterSpriteType::S_ENEMY);
	}
	for (Friend* frien : m_map->getFriends())
	{
		frien->initSprite(CharacterSpriteType::S_FRIEND);
	}
	//player.setPosition((currentPos % width) * 32 + 5, (currentPos / width) * 32 + 3);
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
	enemyStats.setFont(font);
	currentPosition.setFont(font);

	std::string heroName = m_map->getPlayer()->getName();


	//Initializes the text
	text.setString(m_map->getPlayer()->statString());
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, (height * 32 + 8));

	//Enemy Stats text
	enemyStats.setString("Enemy/Friend");
	enemyStats.setCharacterSize(12);
	enemyStats.setFillColor(sf::Color::Black);
	enemyStats.setStyle(sf::Text::Bold);
	enemyStats.setPosition(165, (height * 32 + 8));

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

	enemyStatsBox.setSize(sf::Vector2f(150, 240));
	enemyStatsBox.setPosition(150, height * 32 + 5);
	enemyStatsBox.setOutlineColor(sf::Color::Green);
	enemyStatsBox.setOutlineThickness(3);
}

//! render function
//! @brief Draws everything onto the window
void Game::render(){
	//currentPosition.setString("Current position: " + std::to_string((currentPos - 1) % width));
	window->draw(map);
	window->draw(*this->m_map->getPlayer()->getSprite());

	for (Enemy* enemy : m_map->getEnemies())
	{
		window->draw(*enemy->getSprite());
	}
	for (Friend* frien : m_map->getFriends())
	{
		window->draw(*frien->getSprite());
	}

	window->draw(textBox);
	window->draw(enemyStatsBox);
	window->draw(text);
	window->draw(enemyStats);
	//window->draw(currentPosition);
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

void Game::goToNewMap(Map* map)
{
	if (map != nullptr)
	{
		m_map = nullptr;
		this->m_map = map;
		this->level = map->outputMap();
		loadTextures();
	}
}