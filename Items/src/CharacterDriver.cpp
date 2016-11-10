#include "Character.h"
#include "Fighter.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
	Fighter player1;
	player1.retrieveName();
	player1.setExtraPoints();

	int damage;

	while (!player1.gameover) {
		cout << "Testing hit method. Enter damage: " << endl;
		cin >> damage;
		player1.hit(damage);
	}
}

/*int main()
{
	Fighter peanut;
	peanut.create();

	sf::RenderWindow window(sf::VideoMode(500, 500), "Character GUI");

	sf::Font font;
	if (!font.loadFromFile("gadugi.ttf"))
		return EXIT_FAILURE;
	sf::Text text(peanut.statString(), font, 20);
	text.setFillColor(sf::Color::Black);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(255, 255, 255));

		// Draw the string
		window.draw(text);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}*/