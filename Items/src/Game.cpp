#include "Game.h"
#include <SFML\Graphics.hpp>

Game::Game(unsigned int tileWidth, unsigned int tileHeight, std::vector<int> level){
	this->width = tileWidth;
	this->height = tileHeight;
	this->level = level;
}

Game::~Game(){
	//Destroys the window
	delete window;
}

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

bool Game::init(){
	window = new sf::RenderWindow(sf::VideoMode(600, 512), "D&D 2.0");
	//Puts the window at the top left of the monitor screen
	window->setPosition(sf::Vector2i(0, 0));
	//Prevent multiple key presses
	window->setKeyRepeatEnabled(false);
	if (!window)
		return false;
	return true;
}

void Game::processInput(){
	//To close the window with x
	sf::Event evt;
	//In case there were several events happenning
	while (window->pollEvent(evt)){
		if (evt.type == sf::Event::Closed)
		{
			//window->close();
		}
		update(evt);
	}
}

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
				else if (level[currentPos - width] == 6) // end
				{
					window->close();
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
			}
			else{
				//Checks if space occupied or out of bounds
				if ((currentPos + width >= level.size()))
					break;
				else if (level[currentPos + width] == 1) //1 is water
					break;
				else if (level[currentPos + width] == 2) //2 is tree
					break;
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
				if ((currentPos - 1 < 0))
					break;
				else if (level[currentPos - 1] == 1) //1 is water
					break;
				else if (level[currentPos - 1] == 2) //2 is tree
					break;
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
				if ((currentPos + 1 < 0))
					break;
				else if (level[currentPos + 1] == 1) //1 is water
					break;
				else if (level[currentPos + 1] == 2) //2 is tree
					break;
				player.move(+32, 0);
				currentPos++;
			}
			break;
		}
	default:
		break;
	}
}

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

void Game::createText(){
	//Loads the text's fonts
	if (!font.loadFromFile("font.ttf")){
		std::cout << "Loading fonts failed" << std::endl;
		EXIT_FAILURE;
	}
	//sets the text's font
	text.setFont(font);
	currentPosition.setFont(font);

	std::string heroName = "Donald J. Trump";
	int health = 100;
	int mana = 25;

	//Initializes the text
	text.setString(heroName + "\nHealth: " + std::to_string(health) + "\nMana: " + std::to_string(mana) + "\n");
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
	textBox.setSize(sf::Vector2f(width * 32 - 20, 200));
	textBox.setPosition(12, height * 32 + 5);
	textBox.setOutlineColor(sf::Color::Green);
	textBox.setOutlineThickness(3);
}

void Game::render(){
	//Draws everything onto the window
	currentPosition.setString("Current position: " + std::to_string(currentPos));
	window->draw(map);
	window->draw(player);
	window->draw(textBox);
	window->draw(text);
	window->draw(currentPosition);
}

void Game::mainLoop(){
	//Runs program while window is open
	while (window->isOpen()){
		window->clear();
		render();
		processInput();
		window->display();
	}
}

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
