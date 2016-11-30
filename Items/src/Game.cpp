//! @file Game.cpp
//! @brief Implementation file for the Game class  
//!
#include <SFML\Graphics.hpp>
#include <thread>

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
#include "CharacterType.h"
#include "FileMapBuilder.h"
#include "ItemDecorator.h"

//! Constructor for Game class
//! @param tileWidth : width of the tile used
//! @param tileHeight : height of the tiled used
//! @param map : Map object that we are loading
Game::Game(unsigned int tileWidth, unsigned int tileHeight, Map* map)
{
	this->width = tileWidth;
	this->height = tileHeight;
	this->level = map->outputMap();
	this->m_map = map;
	this->ended = false;
	this->inventoryOpen = false;
	this->equipOpen = false;
	this->attackNum = 0;
}

//! Deconstructor for Game class
//! @brief Deletes the window and map
Game::~Game()
{
	//Destroys the window & map
	delete window;
	//delete m_map;
}

//! validMap function
//! @brief tells us if the map created is valid or not (based on conditions))
//! @return true if the map is valid/fulfills conditions
bool Game::validMap()
{
	int startPoint = -1;
	int endPoint = -1;
	//finds the starting point in the array
	for (unsigned int i = 0; i < level.size(); ++i)
	{
		if (level[i] == TileTypes::START)
		{
			startPoint = i;
			break;
		}
	}
	if (startPoint == -1)
	{
		return false;
	}
	else
	{
		//Finds the ending point in the array
		for (unsigned int i = 0; i < level.size(); ++i)
		{
			if (level[i] == TileTypes::END)
			{
				endPoint = i;
				break;
			}
		}
		if (endPoint == -1)
		{
			return false;
		}
		else
		{
			return validate(startPoint, endPoint);
		}
	}
}

//! validate function
//! @brief contains the map validity conditions
//! @param start : beginning of map
//!	@param end : end of map
//! @return true if the map is valid
bool Game::validate(int start, int end)
{
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
	else
	{
		positionChecked.push_back(start);
		return validate(start + 1, end) || validate(start - 1, end) || validate(start - width, end) || validate(start + width, end);
	}
}

//! init function
//! @brief intializes the game window 
//! @return true if game window was initialized successfully
bool Game::init()
{
	window = new sf::RenderWindow(sf::VideoMode(m_map->getWidth() * 32 + 250, m_map->getLength() * 32 + 250), "D&D 2.0");
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
bool Game::processInput()
{
	//To close the window with x
	sf::Event evt;
	bool process = false;
	//In case there were several events happenning
	while (window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
		{
			window->close();
		}
		if (update(&evt))
		{
			process = true;
		}
	}
	return process;
}

//! update function
//! @brief moves character based on key press (arrow keys)
//! Interacts with objects:
//! Will not walk through wall, water, tree
//! Opens chest once
//! @param evt : event from sfml class
bool Game::update(sf::Event* evt)
{
	Character* character = m_map->getTurn();

	if (character == m_map->getPlayer() && evt == nullptr)
	{
		return false;
	}

	//Register what was the last key released
	if (evt != nullptr)
	{
		if (evt->type == sf::Event::KeyReleased)
		{
			lastKey = evt->key.code;
		}
	}

	if (character != m_map->getPlayer())
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	turnText.setString("Turn: " + character->getName());

	int action = character->getStrategy()->execute(character->getPosition(),
		m_map->getPlayer()->getPosition(), level, m_map->getWidth(), lastKey, evt);

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
			if (!openedChest) 
			{
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
			if (!openedChest) 
			{
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
			if (!openedChest) 
			{
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
		if (character->getPosition().x >= m_map->getWidth() - 1)
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
			if (!openedChest) 
			{
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
		Character* target;

		if (character->getCharacterType() == CT_PLAYER || character->getCharacterType() == CT_FRIEND)
		{
			target = m_map->getClosestEnemy(character);
		}
		else
		{
			target = m_map->getPlayer();
		}

		if (target != nullptr)
		{
			int distance = MathHelper::getDistance(character->getPosition(), target->getPosition());

			//Target character is in range. Must be 1 tile away.
			if (distance <= 1)
			{
				attackNum++;
				Dice dice;
				int d20 = dice.roll("1d20");
				int attackRoll = character->attackRoll(d20);

				if ((attackRoll > target->getArmorClass() && d20 != 1) || d20 == 20)
				{
					int weaponRoll = 0;

					// Every character is assumed to have a short sword
					// if holding a weapon.
					if (character->isHoldingWeapon())
					{
						weaponRoll = dice.roll("1d6");
					}
					else
					{
						//Else, use unarmed attack.
						weaponRoll = dice.roll("1d4");
					}
					int damage = 0;

					//Formula for basic melee attack is:
					// 1[W] + strength modifier for under level 21.
					// 2[W] + strength modifier for level 21 and above.

					if (character->getLevel() < 21) //Lower than 21
					{
						damage = weaponRoll + character->getDamageBonus();
					}
					else
					{
						damage = (2 * weaponRoll) + character->getDamageBonus();
					}

					target->hit(damage);

					if (target->getHitPoints() <= 0)
					{
						if (target->getCharacterType() == CT_ENEMY)
						{
							this->m_map->removeEnemy(dynamic_cast<Enemy*>(target));

							//Drop Items
							Chest* chest = new Chest(target->getBackpack());
							this->m_map->fillCell(target->getPosition().x, target->getPosition().y, chest);
							level = m_map->outputMap();
							loadTextures();
						}
						else if (target->getCharacterType() == CT_FRIEND)
						{
							this->m_map->removeFriend(dynamic_cast<Friend*>(target));
						}
						else
						{
							endGame(); // Game over.
						}
					}
				}
				if (attackNum == (1 + character->getLevel() % 5))
				{
					std::cout << "attack 1" << endl;
					m_map->nextTurn();
					attackNum = 0;
					break;
				}
			}
			std::cout << "attack 2" << endl;
			m_map->nextTurn();
			attackNum = 0;
			break;
		}
		//std::cout << "attack 3" << endl;
		break;
	}
	case PlayerAction::LOOTING:
	{
		//This is where looting items
		//For enemies or chests would go 
		// *******************************************
		// use character->blahblah .......... for accessing characters
		
		//! RANDOMLY GENERATED CHEST - TO BE IMPLEMENTED
		Item chest;
		m_map->getPlayer()->getBackpack().addItem(chest);

		// each character takes turns in this update method.
		// Be nice. Let everyone loot.
		
		break;
	}
	}
	if (evt != nullptr)
	{
		if (evt->type == sf::Event::MouseMoved)
		{
			int tileY = evt->mouseMove.y / 32;
			int tileX = evt->mouseMove.x / 32;

			if (tileX > 0 && tileY > 0)
			{
				Character* c = m_map->getCharacterAt(tileX, tileY);

				if (c != nullptr)
				{
					Enemy* enemy = dynamic_cast<Enemy*>(c);
					Friend* frien = dynamic_cast<Friend*>(c);

					if (enemy != nullptr)//this->m_map->getObject(tileX, tileY)->getObjectType() == OBJ_ENEMY)
					{
						enemyStats.setString("Enemy" + enemy->statString());
						return true; //So it doesn't do the friend check.
					}

					if (frien != nullptr)
					{
						enemyStats.setString("Friend" + frien->statString());
						return true;
					}
				}
				else
				{
					//Don't show enemy stats.
					enemyStats.setString("Enemy/Friend");
					return true;
				}
			}
		}
		else if (evt->type == sf::Event::KeyReleased)
		{
			if (evt->key.code == sf::Keyboard::I)
			{
				if (inventoryOpen)
				{
					//Close inventory
					inventoryOpen = false;
				}
				else
				{
					//Open Inventory
					inventoryOpen = true;
				}
			}
			else if (evt->key.code == sf::Keyboard::E)
			{
				if (equipOpen)
				{
					//Close Equip
					equipOpen = false;
				}
				else
				{
					//Open Equip
					equipOpen = true;
				}
			}
		}
		else if (evt->type == sf::Event::MouseButtonPressed && equipOpen)
		{
			// If mouse is right clicked, check if it's over items
			if (evt->mouseButton.button == sf::Mouse::Right)
			{
				//Equips
				for (int i = 0; i < 7; i++)
				{
					if (isSpriteClicked(equipSprite[i]))
					{
						//Decorator pattern used to unequips equips
						Item* equip = m_map->getPlayer()->getEquipAtIndex(i);
						m_map->getPlayer()->unequip(equip);
						m_map->getPlayer()->displayStats();
						//reload equips
						drawEquips();
						updatePlayerStats();
					}
				}
			}
		}
	}
	return true;
}


//Initializes the text
void Game::updatePlayerStats()
{
	text.setString("Player" + m_map->getPlayer()->statString());
	window->draw(text);
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

	while (window->isOpen())
	{
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
void Game::loadTextures(bool resetStart)
{
	//Sets the player to the starting position
	if (resetStart)
	{
		int currentPos = -1;
		for (int i = 0; i < width * height; ++i)
		{
			if (level[i] == TileTypes::START)
			{
				currentPos = i;
				break;
			}
		}
		this->m_map->getPlayer()->setPosition((currentPos % width), (currentPos / width));
		this->m_map->getPlayer()->initSprite(CharacterSpriteType::S_PLAYER);
	}
	//Loads the map's texture
	map.load("bkrd.png", sf::Vector2u(32, 32), level, width, height);

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
void Game::createText()
{
	//Loads the text's fonts
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Loading fonts failed" << std::endl;
		EXIT_FAILURE;
	}
	//sets the text's font
	text.setFont(font);
	enemyStats.setFont(font);
	currentPosition.setFont(font);
	equipText.setFont(font);
	turnText.setFont(font);
	inventoryText.setFont(font);

	std::string heroName = m_map->getPlayer()->getName();

	//Initializes the text
	text.setString("Player" + m_map->getPlayer()->statString());
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, (height * 32 + 8));

	//Enemy Stats text
	enemyStats.setString("Enemy/Friend");
	enemyStats.setCharacterSize(12);
	enemyStats.setFillColor(sf::Color::Black);
	enemyStats.setStyle(sf::Text::Bold);
	enemyStats.setPosition(185, (height * 32 + 8));

	//Initializes the text of current position
	currentPosition.setCharacterSize(12);
	currentPosition.setFillColor(sf::Color::Black);
	currentPosition.setStyle(sf::Text::Bold);
	currentPosition.setPosition(20, (height * 32 + 56));

	//Initializes the box in which the text will be written in
	textBox.setSize(sf::Vector2f(160, 242));
	textBox.setPosition(5, height * 32 + 5);
	textBox.setOutlineColor(sf::Color::Green);
	textBox.setOutlineThickness(3);

	enemyStatsBox.setSize(sf::Vector2f(160, 242));
	enemyStatsBox.setPosition(170, height * 32 + 5);
	enemyStatsBox.setOutlineColor(sf::Color::Green);
	enemyStatsBox.setOutlineThickness(3);

	//Equips
	equipText.setString("Equips");
	equipText.setCharacterSize(12);
	equipText.setFillColor(sf::Color::Black);
	equipText.setStyle(sf::Text::Bold);
	equipText.setPosition(340, (height * 32 + 8));

	equipTexture.loadFromFile("res/Equips.png");
	equipWindow.setPosition(341, height * 32 + 45);
	equipWindow.setTexture(equipTexture);

	equipBox.setSize(sf::Vector2f(140, 242));
	equipBox.setPosition(335, height * 32 + 5);
	equipBox.setOutlineColor(sf::Color::Green);
	equipBox.setOutlineThickness(3);

	turnBox.setSize(sf::Vector2f(250, 242));
	turnBox.setPosition(32 * m_map->getWidth() - 3, 0);
	turnBox.setOutlineColor(sf::Color::Green);
	turnBox.setOutlineThickness(3);

	//Inventory
	inventoryText.setString("Inventory");
	inventoryText.setCharacterSize(12);
	inventoryText.setFillColor(sf::Color::Black);
	inventoryText.setStyle(sf::Text::Bold);
	inventoryText.setPosition(485, (height * 32 + 8));

	inventoryTexture.loadFromFile("res/Inventory.png");
	inventoryWindow.setPosition(496, height * 32 + 45);
	inventoryWindow.setTexture(inventoryTexture);

	inventoryBox.setSize(sf::Vector2f(157, 242));
	inventoryBox.setPosition(480, height * 32 + 5);
	inventoryBox.setOutlineColor(sf::Color::Green);
	inventoryBox.setOutlineThickness(3);

	//Turn
	turnText.setString("Turn: " + m_map->getTurn()->getName());
	turnText.setCharacterSize(24);
	turnText.setFillColor(sf::Color::Black);
	turnText.setStyle(sf::Text::Bold);
	turnText.setPosition(32 * m_map->getWidth(), 0);

}

//! addItems function
//! loads the items currently in Character's inventory
void Game::drawItems() 
{
	int row = 0;
	vector<Item> items = m_map->getPlayer()->getBackpack().getItems();
	for (int i = 0; i < m_map->getPlayer()->getBackpack().getItems().size(); i++)
	{
		sf::Texture texture;
		texture.loadFromFile(items[i].getItemPath());
		
		inventorySprite[i].setTexture(texture);
		inventorySprite[i].setPosition(496 + ((i%4)*31),height * 32 + 45 + 31*row);
		window->draw(inventorySprite[i]);

		if ((i + 1) % 4 == 0)
			row = row + 1;
	}
}

//! addEquips function
//! loads the items currently equipped by Character
void Game::drawEquips()
{
	vector <Item> items;
	for (int i = 0; i < 7; i++)
	{
		items.push_back(*m_map->getPlayer()->getEquipAtIndex(i));
	}

	for (int i = 0; i < 7; i++)
	{
		Item* equipPointer;
		equipPointer = m_map->getPlayer()->getEquipAtIndex(i);

		// If an item is equipped, then load sprite to GUI
		if (items[i].getID() != 0)
		{
			sf::Texture texture;
			texture.loadFromFile(items[i].getItemPath());
			equipSprite[i].setTexture(texture);

			// Switch statement will set the sprite position depending on which item it is
			switch (i)
			{
			case 0: //helmet
			{
				equipSprite[i].setPosition(341 + 48, height * 32 + 45 + 4);
				window->draw(equipSprite[i]);
				break;
			}
			case 1: //armor
			{
				equipSprite[i].setPosition(341 + 85, height * 32 + 45 + 42);
				window->draw(equipSprite[i]);
				break;
			}
			case 2: //belt
			{
				equipSprite[i].setPosition(341 + 10, height * 32 + 45 + 108);
				window->draw(equipSprite[i]);
				break;
			}
			case 3: //boots
			{
				equipSprite[i].setPosition(341 + 47, height * 32 + 45 + 121);
				window->draw(equipSprite[i]);
				break;
			}
			case 4: //shield
			{
				equipSprite[i].setPosition(341 + 10, height * 32 + 45 + 68);
				window->draw(equipSprite[i]);
				break;
			}
			case 5: //weapon
			{
				equipSprite[i].setPosition(341 + 85, height * 32 + 45 + 84);
				window->draw(equipSprite[i]);
				break;
			}
			case 6: //ring
			{
				equipSprite[i].setPosition(341 + 10, height * 32 + 45 + 28);
				window->draw(equipSprite[i]);
				break;
			}
			default:
				break;
			} // end switch
		}
	} // end for loop
}

bool Game::isSpriteClicked(sf::Sprite &sprite) {

	sf::IntRect rect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	//If mouse position is in the rectangle do whatever
	if (rect.contains(sf::Mouse::getPosition(*window)))
	{
		return true;
	}

	//Otherwise, don't do anything
	return false;
}

void Game::eventOnClick()
{

}

//! render function
//! @brief Draws everything onto the window
void Game::render()
{
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
	window->draw(turnBox);
	window->draw(turnText);

	if (this->equipOpen)
	{
		window->draw(equipBox);
		window->draw(equipText);
		window->draw(equipWindow);
		drawEquips();
	}
	if (this->inventoryOpen)
	{
		window->draw(inventoryBox);
		window->draw(inventoryText);
		window->draw(inventoryWindow);
		drawItems();
	}

	//window->draw(currentPosition);
}

//! mainLoop function
//! @brief Runs program while window is open
void Game::mainLoop()
{
	while (window->isOpen())
	{
		window->clear();
		if (!processInput())
		{
			update(nullptr);
		}
		render();
		window->display();
	}
}

//! go function
//! @brief Checks if the map is valid and able to open window
void Game::go()
{
	if (!init())
		throw "Could not initialize the window";
	if (validMap())
	{
		//Loads the textures to use them first
		loadTextures();
		mainLoop();
	}
	else
	{
		std::cout << "Invalid Map";
		EXIT_FAILURE;
	}
}

void Game::goToNewMap(Map* map)
{
	map->getPlayer()->levelUp();
	
	if (map != nullptr)
	{
		FileMapBuilder build(map->getPlayer());
		build.loadMap(map->getID());

		m_map = nullptr;
		this->m_map = build.getMap();
		this->level = map->outputMap();

		loadTextures();
	}
}