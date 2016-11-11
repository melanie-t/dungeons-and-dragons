/** @file ItemPanel.cpp
*   @brief Implementation file for the ItemPanel class
*/

#include "ItemPanel.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using sf::IntRect;
using sf::Sprite;
using std::cout;

//Need to split it up into a .h file

void ItemPanel::createInventories()
{
	sf::RenderWindow equipWindow(sf::VideoMode(257, 431), "Character Inventory");

	//Character Equipment Inventory Creation
	sf::Texture emptySlots;
	emptySlots.loadFromFile("res/EmptySlots.png");

	sf::Texture equipped;
	equipped.loadFromFile("res/Equipped.png");
	
	sf::Texture dummy;
	dummy.loadFromFile("res/Dummy.jpg");

	sf::Texture numbers;
	numbers.loadFromFile("res/Numbers.png");
	
	Sprite one(numbers);
	one.setTextureRect(IntRect(0, 0, 19, 25));
	one.setPosition(50, 2);

	Sprite two(numbers);
	two.setTextureRect(IntRect(20, 0, 19, 25));
	two.setPosition(120, 2);

	Sprite three(numbers);
	three.setTextureRect(IntRect(40, 0, 19, 25));
	three.setPosition(190, 2);

	Sprite four(numbers);
	four.setTextureRect(IntRect(60, 0, 19, 25));
	four.setPosition(260, 2);

	Sprite five(numbers);
	five.setTextureRect(IntRect(80, 0, 19, 25));
	five.setPosition(50, 71);

	Sprite six(numbers);
	six.setTextureRect(IntRect(100, 0, 19, 25));
	six.setPosition(120, 71);

	Sprite seven(numbers);
	seven.setTextureRect(IntRect(120, 0, 19, 25));
	seven.setPosition(190, 71);

	Sprite eight(numbers);
	eight.setTextureRect(IntRect(140, 0, 19, 25));
	eight.setPosition(260, 71);

	Sprite blankCharacter (dummy);
	blankCharacter.setPosition(0, 0);

	Sprite armorEquip(emptySlots);
	armorEquip.setTextureRect(IntRect(0, 0, 70, 70));
	armorEquip.setPosition(90, 118);

	Sprite beltEquip(emptySlots);
	beltEquip.setTextureRect(IntRect(70, 0, 70, 70));
	beltEquip.setPosition(90, 202);

	Sprite helmetEquip(emptySlots);
	helmetEquip.setTextureRect(IntRect(140, 0, 70, 70));
	helmetEquip.setPosition(90, 12);

	Sprite ringEquip(emptySlots);
	ringEquip.setTextureRect(IntRect(210, 0, 70, 70));
	ringEquip.setPosition(180, 40);

	Sprite shieldEquip(emptySlots);
	shieldEquip.setTextureRect(IntRect(280, 0, 70, 70));
	shieldEquip.setPosition(180, 187);

	Sprite bootsEquip(emptySlots);
	bootsEquip.setTextureRect(IntRect(350, 0, 70, 70));
	bootsEquip.setPosition(90, 355);

	Sprite swordEquip(emptySlots);
	swordEquip.setTextureRect(IntRect(420, 0, 70, 70));
	swordEquip.setPosition(3, 187);

	sf::RenderWindow window(sf::VideoMode(280, 140), "Inventory");

	//Inventory Creation
	sf::Texture items;
	items.loadFromFile("res/Items.png");

	Sprite armor(items);
	armor.setTextureRect(IntRect(0, 0, 70, 70));

	Sprite belt(items);
	belt.setTextureRect(IntRect(70, 0, 70, 70));
	belt.setPosition(70, 0);

	Sprite helmet(items);
	helmet.setTextureRect(IntRect(140, 0, 70, 70));
	helmet.setPosition(140, 0);

	Sprite ring(items);
	ring.setTextureRect(IntRect(210, 0, 70, 70));
	ring.setPosition(210, 0);

	Sprite shield(items);
	shield.setTextureRect(IntRect(280, 0, 70, 70));
	shield.setPosition(0, 70);

	Sprite boots(items);
	boots.setTextureRect(IntRect(350, 0, 70, 70));
	boots.setPosition(70, 70);

	Sprite sword(items);
	sword.setTextureRect(IntRect(420, 0, 70, 70));
	sword.setPosition(140, 70);

	Sprite empty(items);
	empty.setTextureRect(IntRect(490, 0, 70, 70));
	empty.setPosition(210, 70);

	window.setKeyRepeatEnabled(false);
	while (window.isOpen() && equipWindow.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event) || equipWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				equipWindow.close();
			}

			else if (event.type == sf::Event::KeyPressed)
			{
				//Armor
				if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
				{
					//When it's empty, set it to item
					if (armor.getTextureRect() == empty.getTextureRect()) {
						armor.setTextureRect(IntRect(0, 0, 70, 70));
						armorEquip.setTexture(emptySlots);
					}
					
					//When it has an item
					else
					{
						armor.setTextureRect(IntRect(490, 0, 70, 70));
						armorEquip.setTexture(equipped);
					}
				}

				//Belt
				else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
				{
					if (belt.getTextureRect() == empty.getTextureRect()) 
					{
						belt.setTextureRect(IntRect(70, 0, 70, 70));
						beltEquip.setTexture(emptySlots);
					}
					else
					{
						belt.setTextureRect(IntRect(490, 0, 70, 70));
						beltEquip.setTexture(equipped);
					}
				}

				//Helmet
				else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
				{
					if (helmet.getTextureRect() == empty.getTextureRect())
					{
						helmet.setTextureRect(IntRect(140, 0, 70, 70));
						helmetEquip.setTexture(emptySlots);
					}
					else
					{
						helmet.setTextureRect(IntRect(490, 0, 70, 70));
						helmetEquip.setTexture(equipped);
					}
				}

				//Ring
				else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4)
				{
					if (ring.getTextureRect() == empty.getTextureRect())
					{
						ring.setTextureRect(IntRect(210, 0, 70, 70));
						ringEquip.setTexture(emptySlots);
					}
					else
					{
						ring.setTextureRect(IntRect(490, 0, 70, 70));
						ringEquip.setTexture(equipped);
					}
				}

				//Shield
				else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5)
				{
					if (shield.getTextureRect() == empty.getTextureRect())
					{
						shield.setTextureRect(IntRect(280, 0, 70, 70));
						shieldEquip.setTexture(emptySlots);
					}
					else
					{
						shield.setTextureRect(IntRect(490, 0, 70, 70));
						shieldEquip.setTexture(equipped);
					}
				}

				//Boots
				else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6)
				{
					if (boots.getTextureRect() == empty.getTextureRect())
					{
						boots.setTextureRect(IntRect(350, 0, 70, 70));
						bootsEquip.setTexture(emptySlots);
					}
					else
					{
						boots.setTextureRect(IntRect(490, 0, 70, 70));
						bootsEquip.setTexture(equipped);
					}
				}

				//Sword
				else if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7)
				{
					if (sword.getTextureRect() == empty.getTextureRect())
					{
						sword.setTextureRect(IntRect(420, 0, 70, 70));
						swordEquip.setTexture(emptySlots);
					}
					else
					{
						sword.setTextureRect(IntRect(490, 0, 70, 70));
						swordEquip.setTexture(equipped);
					}
				}
			}
		}
			window.clear();
			window.draw(armor);
			window.draw(belt);
			window.draw(helmet);
			window.draw(ring);
			window.draw(shield);
			window.draw(boots);
			window.draw(sword);
			window.draw(empty);
			window.draw(one);
			window.draw(two);
			window.draw(three);
			window.draw(four);
			window.draw(five);
			window.draw(six);
			window.draw(seven);
			window.draw(eight);
			window.display();
			
			//equipWindow.setPosition(sf::Vector2i(440, 300));
			equipWindow.clear();
			equipWindow.draw(blankCharacter);
			equipWindow.draw(armorEquip);
			equipWindow.draw(beltEquip);
			equipWindow.draw(helmetEquip);
			equipWindow.draw(ringEquip);
			equipWindow.draw(shieldEquip);
			equipWindow.draw(bootsEquip);
			equipWindow.draw(swordEquip);
			equipWindow.display();
		}
}