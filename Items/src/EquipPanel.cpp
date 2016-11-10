#include "EquipPanel.h"
#include <SFML/Graphics.hpp>
using sf::IntRect;
using sf::Sprite;

int main()
{
	sf::RenderWindow window(sf::VideoMode(257, 431), "Character Inventory");

	//Character Equipment Inventory Creation
	sf::Texture texture;
	if (!texture.loadFromFile("res/EmptySlots.png"))
	{
		return 1;
	}

	sf::Texture equipped;
	if (!texture.loadFromFile("res/Equipped.png"))
	{
		return 1;
	}

	sf::Texture dummy;
	dummy.create(257, 431);
	if (!dummy.loadFromFile("res/Dummy.jpg"))
	{
		return 1;
	}

	Sprite blankCharacter;
	blankCharacter.setTexture(dummy);
	blankCharacter.setPosition(0, 0);

	Sprite armor(texture);
	armor.setTextureRect(IntRect(0, 0, 70, 70));
	armor.setPosition(90, 118);

	Sprite belt(texture);
	belt.setTextureRect(IntRect(70, 0, 70, 70));
	belt.setPosition(90, 202);

	Sprite helmet(texture);
	helmet.setTextureRect(IntRect(140, 0, 70, 70));
	helmet.setPosition(90, 12);

	Sprite ring(texture);
	ring.setTextureRect(IntRect(210, 0, 70, 70));
	ring.setPosition(180, 40);

	Sprite shield(texture);
	shield.setTextureRect(IntRect(280, 0, 70, 70));
	shield.setPosition(180, 187);

	Sprite boots(texture);
	boots.setTextureRect(IntRect(350, 0, 70, 70));
	boots.setPosition(90, 355);

	Sprite sword(texture);
	sword.setTextureRect(IntRect(420, 0, 70, 70));
	sword.setPosition(3, 187);

	//Sprites for equipped


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(blankCharacter);
		window.draw(armor);
		window.draw(belt);
		window.draw(helmet);
		window.draw(ring);
		window.draw(shield);
		window.draw(boots);
		window.draw(sword);
		window.display();
	}

	return 0;
}