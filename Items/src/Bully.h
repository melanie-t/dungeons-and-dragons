//! file Bully.h
//! @brief Header file and Implementation of the Bully Character
//!
#pragma once
#include "CharacterBuilder.h"
#include <algorithm>
//! Class for the Bully, inherit from the CharacterBuilder
class Bully : public CharacterBuilder
{
public:
	//! Method to set the ability scores to the character
	virtual void buildAbilityScores()
	{
		Dice dice;
		int abilityScores[6];
		for (int i = 0; i < 6; i++)
		{
			abilityScores[i] = dice.roll("4d6[0]");
		}
		//Sorting the ability Scores
		sort(abilityScores, abilityScores + 6);

		//Assigns the ability score depending on importance
		m_character->setSTR(abilityScores[5]);
		m_character->setCON(abilityScores[4]);
		m_character->setDEX(abilityScores[3]);
		m_character->setINTEL(abilityScores[2]);
		m_character->setCHA(abilityScores[1]);
		m_character->setWIS(abilityScores[0]);

		//Assigns the charclass
		m_character->setCharClass(1);
		m_character->setHitPoints(10 + m_character->abilityModifier(m_character->getCON()));
		m_character->setMaxHP(10 + m_character->abilityModifier(m_character->getCON()));
		m_character->setAttackBonus(m_character->getLevel());
		m_character->setArmorClass(10);
		m_character->totalEnhancement();
	}
};
