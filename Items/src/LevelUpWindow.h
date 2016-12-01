#pragma once

#include <SFML\Graphics.hpp>
#include "Character.h"

class LevelupWindow
{
public:
	LevelupWindow(Character* character);
private:
	Character* character;
	void init();
	void loop();
	int availblePoints;
	sf::Font font;
	sf::RenderWindow* window;
	sf::Texture background;
	sf::Texture rightButtonReg;
	sf::Texture rightButtonHover;
	sf::Texture rightButtonClick;

	sf::Texture leftButtonReg;
	sf::Texture leftButtonHover;
	sf::Texture leftButtonClick;

	sf::Texture OKButtonReg;
	sf::Texture OKButtonHover;
	sf::Texture OKButtonClick;

	sf::Sprite backgroundSprite;
	sf::Sprite OKButton;

	sf::Text STR_label;
	sf::Text STR_modifier;
	sf::Sprite leftButton_STR;
	sf::Sprite rightButton_STR;

	sf::Text DEX_label;
	sf::Text DEX_modifier;
	sf::Sprite leftButton_DEX;
	sf::Sprite rightButton_DEX;

	sf::Text CON_label;
	sf::Text CON_modifier;
	sf::Sprite leftButton_CON;
	sf::Sprite rightButton_CON;

	sf::Text INTEL_label;
	sf::Text INTEL_modifier;
	sf::Sprite leftButton_INTEL;
	sf::Sprite rightButton_INTEL;

};