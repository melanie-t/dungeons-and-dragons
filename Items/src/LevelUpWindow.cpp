#include "LevelUpWindow.h"
#include "Dice.h"
#include <iostream>
using namespace std;

LevelUpWindow::LevelUpWindow(Character* character)
{
	Dice dice;
	string constitutionString = character->getCON() + "";
	character->setLevel(character->getLevel() + 1);

	//should roll 1d10[constitution]
	int hpIncrease = dice.roll("1d10[" + constitutionString + "]");
	character->setHitPoints(character->getHitPoints() + hpIncrease);
	character->setMaxHP(character->getMaxHP() + hpIncrease);
	//Sets the enhancement attack bonus as the level
	character->setAttackBonus(character->getLevel());

	this->character = character;
	this->availablePoints = 2;
	this->STR = character->getSTR();
	this->DEX = character->getDEX();
	this->CON = character->getCON();
	this->INTEL = character->getINTEL();
	this->WIS = character->getWIS();
	this->CHA = character->getCHA();
	init();
}

void LevelUpWindow::init()
{
	// 15 px between every button height

	window = new sf::RenderWindow(sf::VideoMode(550, 450), "D&D 2.0 - Level up", sf::Style::Close);
	
	//Font
	this->font.loadFromFile("font.ttf");
	//Textures
	this->background.loadFromFile("res/menu/scrollpaper.png");

	this->rightButtonReg.loadFromFile("res/menu/rightreg.png");
	this->rightButtonClick.loadFromFile("res/menu/rightdown.png");

	this->OKButtonReg.loadFromFile("res/menu/confirm.png");
	this->OKButtonClick.loadFromFile("res/menu/confirmclick.png");

	this->resetButtonReg.loadFromFile("res/menu/reset.png");
	this->resetButtonClick.loadFromFile("res/menu/resetclick.png");

	//Sprites
	this->backgroundSprite.setTexture(background);
	this->backgroundSprite.setPosition(sf::Vector2f(20, 0));
	window->draw(backgroundSprite);

	this->availablePT.setFont(font);
	this->availablePT.setString("Available Points: " + std::to_string(availablePoints));
	this->availablePT.setCharacterSize(14);
	this->availablePT.setFillColor(sf::Color::Black);
	this->availablePT.setStyle(sf::Text::Bold);
	this->availablePT.setPosition(sf::Vector2f(180, 150));

	this->OKButton.setTexture(OKButtonReg);
	this->OKButton.setPosition(sf::Vector2f(275, 360));

	this->resetButton.setTexture(resetButtonReg);
	this->resetButton.setPosition(sf::Vector2f(200, 360));

	this->leftButton_STR.setPosition(sf::Vector2f(250, 198));
	this->rightButton_STR.setTexture(this->rightButtonReg);
	this->rightButton_STR.setPosition(sf::Vector2f(300, 198));
	this->STR_label.setFont(font);
	this->STR_label.setString("Strength");
	this->STR_label.setCharacterSize(14);
	this->STR_label.setFillColor(sf::Color::Black);
	this->STR_label.setStyle(sf::Text::Bold);
	this->STR_label.setPosition(sf::Vector2f(181, 195));
	this->STR_modifier.setFont(font);
	this->STR_modifier.setString(std::to_string(character->getSTR()));
	this->STR_modifier.setCharacterSize(14);
	this->STR_modifier.setFillColor(sf::Color::Black);
	this->STR_modifier.setStyle(sf::Text::Bold);
	this->STR_modifier.setPosition(sf::Vector2f(272, 195));

	this->leftButton_DEX.setPosition(sf::Vector2f(250, 216));
	this->rightButton_DEX.setTexture(this->rightButtonReg);
	this->rightButton_DEX.setPosition(sf::Vector2f(300, 216));
	this->DEX_label.setFont(font);
	this->DEX_label.setString("Dexterity");
	this->DEX_label.setCharacterSize(14);
	this->DEX_label.setFillColor(sf::Color::Black);
	this->DEX_label.setStyle(sf::Text::Bold);
	this->DEX_label.setPosition(sf::Vector2f(176, 213));
	this->DEX_modifier.setFont(font);
	this->DEX_modifier.setString(std::to_string(character->getDEX()));
	this->DEX_modifier.setCharacterSize(14);
	this->DEX_modifier.setFillColor(sf::Color::Black);
	this->DEX_modifier.setStyle(sf::Text::Bold);
	this->DEX_modifier.setPosition(sf::Vector2f(272, 213));

	this->leftButton_CON.setPosition(sf::Vector2f(250, 234));
	this->rightButton_CON.setTexture(this->rightButtonReg);
	this->rightButton_CON.setPosition(sf::Vector2f(300, 234));
	this->CON_label.setFont(font);
	this->CON_label.setString("Constitution");
	this->CON_label.setCharacterSize(14);
	this->CON_label.setFillColor(sf::Color::Black);
	this->CON_label.setStyle(sf::Text::Bold);
	this->CON_label.setPosition(sf::Vector2f(153, 231));
	this->CON_modifier.setFont(font);
	this->CON_modifier.setString(std::to_string(character->getCON()));
	this->CON_modifier.setCharacterSize(14);
	this->CON_modifier.setFillColor(sf::Color::Black);
	this->CON_modifier.setStyle(sf::Text::Bold);
	this->CON_modifier.setPosition(sf::Vector2f(272, 231));

	this->leftButton_INTEL.setPosition(sf::Vector2f(250, 252));
	this->rightButton_INTEL.setTexture(this->rightButtonReg);
	this->rightButton_INTEL.setPosition(sf::Vector2f(300, 252));
	this->INTEL_label.setFont(font);
	this->INTEL_label.setString("Intelligence");
	this->INTEL_label.setCharacterSize(14);
	this->INTEL_label.setFillColor(sf::Color::Black);
	this->INTEL_label.setStyle(sf::Text::Bold);
	this->INTEL_label.setPosition(sf::Vector2f(159, 249));
	this->INTEL_modifier.setFont(font);
	this->INTEL_modifier.setString(std::to_string(character->getINTEL()));
	this->INTEL_modifier.setCharacterSize(14);
	this->INTEL_modifier.setFillColor(sf::Color::Black);
	this->INTEL_modifier.setStyle(sf::Text::Bold);
	this->INTEL_modifier.setPosition(sf::Vector2f(272, 249));

	this->leftButton_WIS.setPosition(sf::Vector2f(250, 270));
	this->rightButton_WIS.setTexture(this->rightButtonReg);
	this->rightButton_WIS.setPosition(sf::Vector2f(300, 270));
	this->WIS_label.setFont(font);
	this->WIS_label.setString("Wisdom");
	this->WIS_label.setCharacterSize(14);
	this->WIS_label.setFillColor(sf::Color::Black);
	this->WIS_label.setStyle(sf::Text::Bold);
	this->WIS_label.setPosition(sf::Vector2f(185, 267));
	this->WIS_modifier.setFont(font);
	this->WIS_modifier.setString(std::to_string(character->getWIS()));
	this->WIS_modifier.setCharacterSize(14);
	this->WIS_modifier.setFillColor(sf::Color::Black);
	this->WIS_modifier.setStyle(sf::Text::Bold);
	this->WIS_modifier.setPosition(sf::Vector2f(272, 267));

	this->leftButton_CHA.setPosition(sf::Vector2f(250, 288));
	this->rightButton_CHA.setTexture(this->rightButtonReg);
	this->rightButton_CHA.setPosition(sf::Vector2f(300, 288));
	this->CHA_label.setFont(font);
	this->CHA_label.setString("Charisma");
	this->CHA_label.setCharacterSize(14);
	this->CHA_label.setFillColor(sf::Color::Black);
	this->CHA_label.setStyle(sf::Text::Bold);
	this->CHA_label.setPosition(sf::Vector2f(175, 285));
	this->CHA_modifier.setFont(font);
	this->CHA_modifier.setString(std::to_string(character->getCHA()));
	this->CHA_modifier.setCharacterSize(14);
	this->CHA_modifier.setFillColor(sf::Color::Black);
	this->CHA_modifier.setStyle(sf::Text::Bold);
	this->CHA_modifier.setPosition(sf::Vector2f(272, 285));
	loop();
}

void LevelUpWindow::loop()
{
	while (window->isOpen())
	{
		//Draw everything
		window->clear();
		window->draw(backgroundSprite);
		window->draw(availablePT);
		window->draw(OKButton);
		window->draw(resetButton);

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

		window->draw(leftButton_INTEL);
		window->draw(rightButton_INTEL);
		window->draw(INTEL_label);
		window->draw(INTEL_modifier);

		window->draw(leftButton_WIS);
		window->draw(rightButton_WIS);
		window->draw(WIS_label);
		window->draw(WIS_modifier);

		window->draw(leftButton_CHA);
		window->draw(rightButton_CHA);
		window->draw(CHA_label);
		window->draw(CHA_modifier);

		window->display();
		while (window->pollEvent(evt))
		{
			if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left)
			{
				if (spriteHovered(rightButton_STR) && availablePoints > 0)
				{
					//Update arrow
					rightButton_STR.setTexture(rightButtonClick);
					window->draw(rightButton_STR);

					//Update stats
					character->setSTR(character->getSTR()+1);
					STR_modifier.setString(std::to_string(character->getSTR()));
					window->draw(STR_modifier);

					//Update available points
					availablePoints = availablePoints - 1;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					strUP = true;
				}

				else if (spriteHovered(rightButton_DEX) && availablePoints > 0)
				{
					//Update arrow
					rightButton_DEX.setTexture(rightButtonClick);
					window->draw(rightButton_DEX);

					//Update stats
					character->setDEX(character->getDEX() + 1);
					DEX_modifier.setString(std::to_string(character->getDEX()));
					window->draw(DEX_modifier);

					//Update available points
					availablePoints = availablePoints - 1;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					dexUP = true;
				}

				else if (spriteHovered(rightButton_CON) && availablePoints > 0)
				{
					//Update arrow
					rightButton_CON.setTexture(rightButtonClick);
					window->draw(rightButton_CON);

					//Update stats
					character->setCON(character->getCON() + 1);
					CON_modifier.setString(std::to_string(character->getCON()));
					window->draw(CON_modifier);

					//Update available points
					availablePoints = availablePoints - 1;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					conUP = true;
				}

				else if (spriteHovered(rightButton_INTEL) && availablePoints > 0)
				{
					//Update arrow
					rightButton_INTEL.setTexture(rightButtonClick);
					window->draw(rightButton_INTEL);

					//Update stats
					character->setINTEL(character->getINTEL() + 1);
					INTEL_modifier.setString(std::to_string(character->getINTEL()));
					window->draw(INTEL_modifier);

					//Update available points
					availablePoints = availablePoints - 1;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					intUP = true;
				}

				else if (spriteHovered(rightButton_WIS) && availablePoints > 0)
				{
					//Update arrow
					rightButton_WIS.setTexture(rightButtonClick);
					window->draw(rightButton_WIS);

					//Update stats
					character->setWIS(character->getWIS() + 1);
					WIS_modifier.setString(std::to_string(character->getWIS()));
					window->draw(WIS_modifier);

					//Update available points
					availablePoints = availablePoints - 1;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					wisUP = true;
				}

				else if (spriteHovered(rightButton_CHA) && availablePoints > 0)
				{
					//Update arrow
					rightButton_CHA.setTexture(rightButtonClick);
					window->draw(rightButton_CHA);

					//Update stats
					character->setCHA(character->getCHA() + 1);
					CHA_modifier.setString(std::to_string(character->getCHA()));
					window->draw(CHA_modifier);

					//Update available points
					availablePoints = availablePoints - 1;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					chaUP = true;
				}

				//Reset button
				if (spriteHovered(resetButton))
				{
					window->draw(resetButton);
					availablePoints = 2;
					availablePT.setString("Available Points: " + std::to_string(availablePoints));
					window->draw(availablePT);

					//Reset all stats back to original
					if (strUP)
					{
						rightButton_STR.setTexture(rightButtonReg);
						window->draw(rightButton_STR);
						character->setSTR(this->STR);
						STR_modifier.setString(std::to_string(character->getSTR()));
						window->draw(STR_modifier);
					}

					if (dexUP)
					{
						rightButton_DEX.setTexture(rightButtonReg);
						window->draw(rightButton_DEX);
						character->setDEX(this->DEX);
						DEX_modifier.setString(std::to_string(character->getDEX()));
						window->draw(DEX_modifier);
					}

					if (conUP)
					{
						rightButton_CON.setTexture(rightButtonReg);
						window->draw(rightButton_CON);
						character->setCON(this->CON);
						CON_modifier.setString(std::to_string(character->getCON()));
						window->draw(CON_modifier);
					}

					if (intUP)
					{
						rightButton_INTEL.setTexture(rightButtonReg);
						window->draw(rightButton_INTEL);
						character->setINTEL(this->INTEL);
						INTEL_modifier.setString(std::to_string(character->getINTEL()));
						window->draw(INTEL_modifier);
					}

					if (wisUP)
					{
						rightButton_WIS.setTexture(rightButtonReg);
						window->draw(rightButton_WIS);
						character->setWIS(this->WIS);
						WIS_modifier.setString(std::to_string(character->getWIS()));
						window->draw(WIS_modifier);
					}

					if (chaUP)
					{
						rightButton_CHA.setTexture(rightButtonReg);
						window->draw(rightButton_DEX);
						character->setCHA(this->CHA);
						CHA_modifier.setString(std::to_string(character->getCHA()));
						window->draw(CHA_modifier);
					}
				}

				if (spriteHovered(OKButton) && availablePoints == 0)
				{
					//Exits
					window->close();
				}
			} // end if clicked
		} // end while event

	}
}

//! isSpriteClicked function
//! Checks if mouse hovers over sprite
//! @param : sprite that's checked for hover
//! @return : true if mouse is over sprite
bool LevelUpWindow::spriteHovered(sf::Sprite &sprite) {

	sf::IntRect rect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	//If mouse position is in the rectangle do whatever
	if (rect.contains(sf::Mouse::getPosition(*window)))
	{
		return true;
	}
	//Otherwise, don't do anything
	return false;
}