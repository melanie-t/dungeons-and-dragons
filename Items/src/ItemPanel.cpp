#include <SFML/Graphics.hpp>
using sf::IntRect;
using sf::Sprite;

//Need to split it up into a .h file

int main()
{
	sf::RenderWindow window(sf::VideoMode(280, 140), "Inventory");

	//Inventory creation

	sf::Texture texture;
	if (!texture.loadFromFile("Sprites/Items.png"))
	{
		return 1;
	}

	Sprite armor;
	armor.setTexture(texture);
	armor.setTextureRect(IntRect(0, 0, 70, 70));

	Sprite belt;
	belt.setTexture(texture);
	belt.setTextureRect(IntRect(70, 0, 70, 70));
	belt.setPosition(70, 0);

	Sprite helmet;
	helmet.setTexture(texture);
	helmet.setTextureRect(IntRect(140, 0, 70, 70));
	helmet.setPosition(140, 0);

	Sprite ring;
	ring.setTexture(texture);
	ring.setTextureRect(IntRect(210, 0, 70, 70));
	ring.setPosition(210, 0);

	Sprite shield;
	shield.setTexture(texture);
	shield.setTextureRect(IntRect(280, 0, 70, 70));
	shield.setPosition(0, 70);

	Sprite boots;
	boots.setTexture(texture);
	boots.setTextureRect(IntRect(350, 0, 70, 70));
	boots.setPosition(70, 70);

	Sprite sword;
	sword.setTexture(texture);
	sword.setTextureRect(IntRect(420, 0, 70, 70));
	sword.setPosition(140, 70);

	Sprite empty;
	empty.setTexture(texture);
	empty.setTextureRect(IntRect(490, 0, 70, 70));
	empty.setPosition(210, 70);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
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
		window.display();
	}

	return 0;
}