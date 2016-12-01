#include "LevelUpWindow.h"

LevelupWindow::LevelupWindow(Character* character)
{
	this->character = character;
	this->availblePoints = 2;
	init();
}

void LevelupWindow::init()
{
	window = new sf::RenderWindow(sf::VideoMode(550, 450), "D&D 2.0 - Level up", sf::Style::Close);
	
	//Font
	this->font.loadFromFile("font.ttf");

	//Textures
	this->background.loadFromFile("res/menu/scrollpaper.png");

	this->rightButtonReg.loadFromFile("res/menu/rightreg.png");
	this->rightButtonHover.loadFromFile("res/menu/rightover.png");
	this->rightButtonClick.loadFromFile("res/menu/rightdown.png");

	this->leftButtonReg.loadFromFile("res/menu/leftreg.png");
	this->leftButtonHover.loadFromFile("res/menu/leftover.png");
	this->leftButtonClick.loadFromFile("res/menu/leftdown.png");

	this->OKButtonReg.loadFromFile("res/menu/messageokayreg.png");
	this->OKButtonHover.loadFromFile("res/menu/messageokayover.png");
	this->OKButtonClick.loadFromFile("res/menu/messageokaydown.png");

	//Sprites
	this->backgroundSprite.setTexture(background);
	this->backgroundSprite.setPosition(sf::Vector2f(20, 0));
	window->draw(backgroundSprite);

	this->OKButton.setTexture(OKButtonReg);
	this->OKButton.setPosition(sf::Vector2f(245, 360));

	this->leftButton_STR.setTexture(this->leftButtonReg); //Strength
	this->leftButton_STR.setPosition(sf::Vector2f(250, 200));
	this->rightButton_STR.setTexture(this->rightButtonReg);
	this->rightButton_STR.setPosition(sf::Vector2f(300, 200));
	this->STR_label.setFont(font);
	this->STR_label.setString("Strength");
	this->STR_label.setCharacterSize(14);
	this->STR_label.setFillColor(sf::Color::Black);
	this->STR_label.setStyle(sf::Text::Bold);
	this->STR_label.setPosition(sf::Vector2f(180, 195));
	this->STR_modifier.setFont(font);
	this->STR_modifier.setString(std::to_string(character->getSTR()));
	this->STR_modifier.setCharacterSize(14);
	this->STR_modifier.setFillColor(sf::Color::Black);
	this->STR_modifier.setStyle(sf::Text::Bold);
	this->STR_modifier.setPosition(sf::Vector2f(272, 195));

	this->leftButton_DEX.setTexture(this->leftButtonReg); //Dexterity
	this->leftButton_DEX.setPosition(sf::Vector2f(250, 214));
	this->rightButton_DEX.setTexture(this->rightButtonReg);
	this->rightButton_DEX.setPosition(sf::Vector2f(300, 214));
	this->DEX_label.setFont(font);
	this->DEX_label.setString("Dexterity");
	this->DEX_label.setCharacterSize(14);
	this->DEX_label.setFillColor(sf::Color::Black);
	this->DEX_label.setStyle(sf::Text::Bold);
	this->DEX_label.setPosition(sf::Vector2f(180, 209));
	this->DEX_modifier.setFont(font);
	this->DEX_modifier.setString(std::to_string(character->getDEX()));
	this->DEX_modifier.setCharacterSize(14);
	this->DEX_modifier.setFillColor(sf::Color::Black);
	this->DEX_modifier.setStyle(sf::Text::Bold);
	this->DEX_modifier.setPosition(sf::Vector2f(272, 209));

	this->leftButton_CON.setTexture(this->leftButtonReg); //Constitution
	this->leftButton_CON.setPosition(sf::Vector2f(250, 228));
	this->rightButton_CON.setTexture(this->rightButtonReg);
	this->rightButton_CON.setPosition(sf::Vector2f(300, 228));
	this->CON_label.setFont(font);
	this->CON_label.setString("Constitution");
	this->CON_label.setCharacterSize(14);
	this->CON_label.setFillColor(sf::Color::Black);
	this->CON_label.setStyle(sf::Text::Bold);
	this->CON_label.setPosition(sf::Vector2f(158, 223));
	this->CON_modifier.setFont(font);
	this->CON_modifier.setString(std::to_string(character->getCON()));
	this->CON_modifier.setCharacterSize(14);
	this->CON_modifier.setFillColor(sf::Color::Black);
	this->CON_modifier.setStyle(sf::Text::Bold);
	this->CON_modifier.setPosition(sf::Vector2f(272, 223));

	this->leftButton_INTEL.setTexture(this->leftButtonReg); //Intelligence
	this->leftButton_INTEL.setPosition(sf::Vector2f(250, 228));
	this->rightButton_INTEL.setTexture(this->rightButtonReg);
	this->rightButton_INTEL.setPosition(sf::Vector2f(300, 242));
	this->INTEL_label.setFont(font);
	this->INTEL_label.setString("Intelligence");
	this->INTEL_label.setCharacterSize(14);
	this->INTEL_label.setFillColor(sf::Color::Black);
	this->INTEL_label.setStyle(sf::Text::Bold);
	this->INTEL_label.setPosition(sf::Vector2f(158, 237));
	this->INTEL_modifier.setFont(font);
	this->INTEL_modifier.setString(std::to_string(character->getCON()));
	this->INTEL_modifier.setCharacterSize(14);
	this->INTEL_modifier.setFillColor(sf::Color::Black);
	this->INTEL_modifier.setStyle(sf::Text::Bold);
	this->INTEL_modifier.setPosition(sf::Vector2f(272, 237));

	loop();
}

void LevelupWindow::loop()
{
	while (window->isOpen())
	{
		window->clear();
		window->draw(backgroundSprite);
		window->draw(OKButton);

		window->draw(leftButton_STR);
		window->draw(rightButton_STR);
		window->draw(STR_label);
		window->draw(STR_modifier);

		window->draw(leftButton_DEX);
		window->draw(rightButton_DEX);
		window->draw(DEX_label);
		window->draw(DEX_modifier);

		window->draw(leftButton_CON);
		window->draw(rightButton_CON);
		window->draw(CON_label);
		window->draw(CON_modifier);

		window->display();
	}
}