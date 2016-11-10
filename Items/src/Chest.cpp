/*@file Chest.cpp
*   @brief Implementation file for the Chest .cpp file
*/

#include "Chest.h"
#include "Item.h"
#include <SFML\Graphics.hpp>
using sf::Sprite;

void Chest::displayChest(Item inputItem){

	sf::RenderWindow chestPopup(sf::VideoMode(285, 274), "Hover to reveal item!");
	sf::Texture goldChest;
	goldChest.loadFromFile("Sprites/Chest.png");
	Sprite chest(goldChest);
	sf::Texture item;

	while (chestPopup.isOpen())
	{
		sf::Event event;
		while (chestPopup.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				chestPopup.close();
			}
			switch (inputItem.getItemType()) {
				case 1: item.loadFromFile("Sprites/armor2.png"); break;
				case 2: item.loadFromFile("Sprites/belt2.png"); break;
				case 3: item.loadFromFile("Sprites/helmet2.png"); break;
				case 4: item.loadFromFile("Sprites/ring2.png"); break;
				case 5: item.loadFromFile("Sprites/shield2.png"); break;
				case 6: item.loadFromFile("Sprites/boots2.png"); break;
				case 7: item.loadFromFile("Sprites/sword2.png"); break;
			}

			Sprite displayItem(item);
			displayItem.setPosition(80, 100);
			chestPopup.clear();
			chestPopup.draw(chest);
			chestPopup.draw(displayItem);
			chestPopup.display();
		}
	}
}