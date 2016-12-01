#pragma once

#include <SFML\Graphics.hpp>
#include "Character.h"

class LevelUpWindow
{
public:
	LevelUpWindow(Character* character);
	bool spriteHovered(sf::Sprite &sprite);

private:
	sf::Event evt;
	Character* character;
	void init();
	void loop();
	int availablePoints;
	int STR, DEX, CON, INTEL, WIS, CHA;
	bool strUP = false, 
		dexUP = false,
		conUP = false,
		intUP = false,
		wisUP = false,
		chaUP = false;

	sf::Font font;
	sf::RenderWindow* window;
	sf::Texture background;
	sf::Texture rightButtonReg;
	sf::Texture rightButtonClick;

	sf::Texture OKButtonReg;
	sf::Texture OKButtonClick;
	sf::Texture resetButtonReg;
	sf::Texture resetButtonClick;

	sf::Sprite backgroundSprite;
	sf::Sprite OKButton;
	sf::Sprite resetButton;

	sf::Text availablePT;

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

	sf::Text WIS_label;
	sf::Text WIS_modifier;
	sf::Sprite leftButton_WIS;
	sf::Sprite rightButton_WIS;

	sf::Text CHA_label;
	sf::Text CHA_modifier;
	sf::Sprite leftButton_CHA;
	sf::Sprite rightButton_CHA;
};