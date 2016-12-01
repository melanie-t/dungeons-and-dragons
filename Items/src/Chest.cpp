/*@file Chest.cpp
* @brief Implementation file for the Chest .cpp file
*/

#include "Chest.h"
#include "Item.h"
#include <SFML\Graphics.hpp>
#include <iostream> //for debugging
#include <windows.h> // for pause

//! default constructor
Chest::Chest() : GameObject(OBJ_CHEST)
{
}

//! default constructor to initialize chests on maps
//! randomizes # of items in container + generate random items
Chest::Chest(int level) : GameObject(OBJ_CHEST)
{
	int n = generateNumber();
	for (int i = 0; i < n; i++)
	{
		chestItems.addItem(*Item::randommize(level));
		Sleep(1000);
	}
}

//! constructor to accept enemy container
//! turns enemy's items into a chest
//! @param container : the backpack container
Chest::Chest(ItemContainer container) : GameObject(OBJ_CHEST)
{
	this->chestItems = container;
}

//! displayChest function
//! @brief Implementation of Chest GUI when Character encounters a chest on the Map
//! @param inputItem : Item pointer for finding out what type of item it is
void Chest::displayChest()
{
	sf::RenderWindow chestPopup(sf::VideoMode(285, 274), "Hover to reveal item!");
	sf::Texture goldChest;
	goldChest.loadFromFile("res/Chest.png");
	sf::Sprite chest(goldChest);
	sf::Texture item;

	while (chestPopup.isOpen())
	{
		sf::Event event;
		while (chestPopup.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				chestPopup.close();
			}

			sf::Sprite displayItem(item);
			displayItem.setPosition(80, 100);
			chestPopup.clear();
			chestPopup.draw(chest);
			chestPopup.draw(displayItem);
			chestPopup.display();
		}
	}
}

//! generateNumber function
//! randomly generates the amount of items in chest between 1-3
//! @return : integer between 1-3
int Chest::generateNumber()
{
	srand(time(NULL));
	return rand() % 3 + 1; // returns random number between 1 and 3
}

//! printChest function
//! displays chest items and their stats
void Chest::printChest()
{
	vector <Item> items = chestItems.getItems();
	cout << "Items in chest\n" << endl;
	for (Item i : items)
	{
		cout << i.toString();
	}
}

//! transferItems function
//! transfers chest items to the character
//! @param character : pointer to character
void Chest::transferItems(Character* character)
{
	//vector <Item> chest = chestItems.getItems();

	for (int i = 0; i < chestItems.getItems().size(); i++)
	{
		character->addBackpack(&chestItems.itemAtIndex(i));
	}
}